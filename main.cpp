#include <iostream>
#include <sstream>
#include <random>
#include <vector>
#include <string>
#include <iomanip>

#include "GL/glew.h"
#include "GL/freeglut.h"
#include "glm/glm.hpp"

#include "./libs/utils/utils.h"
#include "./libs/transform/transform.h"
#include "./libs/camera/camera.h"
#include "./libs/shaders/shaderclass.h"
#include "./libs/shaders/world_shader.h"
#include "./libs/shaders/water_shader.h"
#include "./libs/shaders/gui_shader.h"
#include "./libs/world/world.h"
#include "./libs/texture/texture.h"
#include "./libs/gui/gui.h"

int get_random_seed()
{
  std::random_device random;
  std::mt19937 range(random());
  std::uniform_int_distribution<int> distribution(1, 100);

  return distribution(range);
}

/**
  Structure which stores all the global informations
*/
struct global_struct
{
  float WINDOW_WIDTH = 1024.0f;
  float WINDOW_HEIGHT = 768.0f;

  int world_width = 15, world_height = 15;

  Camera camera;

  NoiseGenerator noise_generator;
  World world;
  Water water;
  Gui gui;

  const float SPEED = 10;
  float gradX, gradY;

  global_struct() : gradX(0.0f),
                    gradY(0.0f),
                    world(world_width, world_height),
                    water(glm::vec3(-world_width / 2, 0, -world_height / 2), world_width * 2, world_height * 2),
                    noise_generator(0.1, 2.0, get_random_seed())
  {
  }

  float time = 0;

  std::vector<Texture2D> texture_managers;
} global;

// Function invoked from the main loop that computes the transformation matrix
void MyRenderScene(void);
// Function invoked everytime the keyboard is pressed
void MyKeyboard(unsigned char key, int x, int y);
// Function invoked when the window is closed
void MyClose(void);
// Function invoked everytime a special key is pressed on the keyboard
void MySpecialKeyboard(int Key, int x, int y);
// Function invoked everytime a mouse click event is generated
void MyMouseClick(int button, int state, int x, int y);
// Function invoked everytime the window is resized
void MyReshape(int w, int h);
// Function invoked at each timer tick
void Timer(int);

// Initializes the OpenGL environment (GLUT + GLEW)
void init(int argc, char *argv[])
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

  glutInitWindowSize(global.WINDOW_WIDTH, global.WINDOW_HEIGHT);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("Procedural Terrain Generation");

  glutSetCursor(GLUT_CURSOR_LEFT_ARROW);

  global.camera.set_mouse_init_position(global.WINDOW_WIDTH / 2, global.WINDOW_HEIGHT / 2);
  global.camera.lock_mouse_position(true);
  glutWarpPointer(global.WINDOW_WIDTH / 2, global.WINDOW_HEIGHT / 2);

  GLenum res = glewInit();
  if (res != GLEW_OK)
  {
    std::cerr << "Error : " << glewGetErrorString(res) << std::endl;
    exit(1);
  }

  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

  glutDisplayFunc(MyRenderScene);
  glutTimerFunc(16, Timer, 0);
  glutKeyboardFunc(MyKeyboard);
  glutCloseFunc(MyClose);
  glutSpecialFunc(MySpecialKeyboard);
  glutMouseFunc(MyMouseClick);
  glutReshapeFunc(MyReshape);

  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
  glFrontFace(GL_CCW);
  glEnable(GL_DEPTH_TEST);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

/**
 * Function that creates the scene by defining objects, setting camera data
 * and loading shaders
 */
void create_scene()
{
  global.noise_generator.set_seed(get_random_seed());

  global.camera.set_camera(
      glm::vec3(0, 3, -global.world.height * 1.5),
      glm::vec3(0, 0, 0),
      glm::vec3(0, 1, 0));

  global.camera.set_perspective(
      45.0f,
      global.WINDOW_WIDTH,
      global.WINDOW_HEIGHT,
      0.1,
      100);

  if (!global.world.init())
  {
    std::cerr << "Error initializing world shaders..." << std::endl;
    exit(0);
  }

  if (!global.water.init())
  {
    std::cerr << "Error initializing water shaders..." << std::endl;
    exit(0);
  }

  if (!global.gui.init())
  {
    std::cerr << "Error initializing GUI shaders..." << std::endl;
    exit(0);
  }

  std::vector<std::string> textures = {
      "water.jpg", "grass.jpg", "sand.jpg", "mountain.jpg", "rock.jpg", "font.png"};

  for (int i = 0; i < textures.size(); i++)
  {
    Texture2D texture_manager = Texture2D();
    texture_manager.load("./textures/" + textures[i]);
    global.texture_managers.push_back(texture_manager);
  }

  global.world.regenerate_mesh(&global.noise_generator);
  global.water.regenerate_mesh();
}

void handle_seed_click(int button_type)
{
  global.noise_generator.set_seed(get_random_seed());
  global.world.regenerate_mesh(&global.noise_generator);
}

void handle_frequency_click(int button_type)
{
  if (button_type == 0 && global.noise_generator.get_frequency() < 1)
  {
    global.noise_generator.adjust_frequency(0.1);
  }
  else if (button_type == 2 && global.noise_generator.get_frequency() > 0)
  {
    global.noise_generator.adjust_frequency(-0.1);
  }
  else
  {
    return;
  }
  global.world.regenerate_mesh(&global.noise_generator);
}

void handle_amplitude_click(int button_type)
{
  if (button_type == 0)
  {
    global.noise_generator.adjust_amplitude(0.1);
  }
  else if (button_type == 2 && global.noise_generator.get_amplitude() > 0)
  {
    global.noise_generator.adjust_amplitude(-0.1);
  }
  else
  {
    return;
  }
  global.world.regenerate_mesh(&global.noise_generator);
}

void render_gui()
{
  global.gui.clear();
  const int text_size = 20;

  // Draw widgets
  std::string seed_label = "Seed: " +
                           std::to_string((int)global.noise_generator.get_seed());
  global.gui.add_label(glm::vec2(0, 0), seed_label, text_size, handle_seed_click);

  std::string width_label = "Width: " +
                            std::to_string((int)global.world.width);
  global.gui.add_label(glm::vec2(0, 20), width_label, text_size);

  std::string height_label = "Height: " +
                             std::to_string((int)global.world.height);
  global.gui.add_label(glm::vec2(0, 40), height_label, text_size);

  std::stringstream frequency_ss;
  frequency_ss << std::fixed << std::setprecision(1) << (float)global.noise_generator.get_frequency();
  std::string frequency_str = frequency_ss.str();
  std::string frequency = "Frequency: " + frequency_str;
  global.gui.add_label(glm::vec2(0, 60), frequency, text_size, handle_frequency_click);

  std::stringstream amplidute_ss;
  amplidute_ss << std::fixed << std::setprecision(1) << (float)global.noise_generator.get_amplitude();
  std::string amplitude_str = amplidute_ss.str();
  std::string amplitude = "Amplitude: " + amplitude_str;
  global.gui.add_label(glm::vec2(0, 80), amplitude, text_size, handle_amplitude_click);

  global.gui.render(global.WINDOW_WIDTH, global.WINDOW_HEIGHT);
}

void MyRenderScene()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  for (int i = 0; i < global.texture_managers.size(); i++)
  {
    global.texture_managers[i].bind(i);
  }

  LocalTransform modelT;
  modelT.rotate(global.gradX, global.gradY, 0.0f);
  modelT.translate(-global.world.width / 2, 0, -global.world.height / 2);

  global.water.render(&modelT, &global.camera, global.time);
  global.world.render(&modelT, &global.camera);
  render_gui();

  glutSwapBuffers();

  global.time += 1;
}

void MyKeyboard(unsigned char key, int x, int y)
{
  switch (key)
  {
  case 27: // Escape key
    glutDestroyWindow(glutGetWindow());
    return;
    break;

  case 'w':
    if (global.gradX > -90)
    {
      global.gradX -= global.SPEED;
    }
    break;
  case 's':
    if (global.gradX < 0)
    {
      global.gradX += global.SPEED;
    }
    break;
  case 'a':
    global.gradY -= global.SPEED;
    break;
  case 'd':
    global.gradY += global.SPEED;
    break;
  case ' ':
    global.gradX = 0.0f;
    global.gradY = 0.0f;
    break;
  }

  glutPostRedisplay();
}

void MySpecialKeyboard(int Key, int x, int y)
{
  global.camera.onSpecialKeyboard(Key);
  glutPostRedisplay();
}

void MyMouseClick(int button, int state, int x, int y)
{
  if (state == 0)
  {
    global.gui.handle_mouse_click(x, y, button);
  }
  glutPostRedisplay();
}

void MyReshape(int w, int h)
{
  glViewport(0, 0, w, h);

  global.WINDOW_WIDTH = w;
  global.WINDOW_HEIGHT = h;

  global.camera.set_perspective(
      45.0f,
      global.WINDOW_WIDTH,
      global.WINDOW_HEIGHT,
      0.1,
      100);
}

void MyClose(void)
{
  std::cout << "Tearing down the system..." << std::endl;

  exit(0);
}

void Timer(int)
{
  glutPostRedisplay();
  glutTimerFunc(16, Timer, 0);
}

int main(int argc, char *argv[])
{
  srand(time(NULL));
  init(argc, argv);

  create_scene();

  glutMainLoop();

  return 0;
}