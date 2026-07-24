#include <iostream>
#include <sstream>
#include <random>
#include <vector>
#include <string>

#include "GL/glew.h"
#include "GL/freeglut.h"
#include "glm/glm.hpp"

#include "./libs/utils/utils.h"
#include "./libs/transform/transform.h"
#include "./libs/camera/camera.h"
#include "./libs/shaders/shaderclass.h"
#include "./libs/shaders/myshaderclass.h"
#include "./libs/world/world.h"
#include "./libs/texture/texture.h"

#define WATER_SPEED 0.005


/**
  Structure which stores all the global informations
*/
struct global_struct {
  int WINDOW_WIDTH  = 1024; 
  int WINDOW_HEIGHT = 768;

  Camera camera;

  World world;

  MyShaderClass shaders;

  const float SPEED = 10;
  float gradX;
  float gradY; 

  global_struct() : gradX(0.0f), gradY(0.0f), world(15, 15, 0, 0.1, 2) {}

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
// Function invoked everytime a mouse event is generated
void MyMouse(int x, int y);
// Function invoked at each timer tick
void Timer(int);

// Initializes the OpenGL environment (GLUT + GLEW)
void init(int argc, char*argv[]) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH);

  glutInitWindowSize(global.WINDOW_WIDTH, global.WINDOW_HEIGHT);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("Informatica Grafica");

  glutSetCursor(GLUT_CURSOR_NONE);

  global.camera.set_mouse_init_position(global.WINDOW_WIDTH/2, global.WINDOW_HEIGHT/2);
  global.camera.lock_mouse_position(true);
  glutWarpPointer(global.WINDOW_WIDTH/2, global.WINDOW_HEIGHT/2);

  GLenum res = glewInit();
  if (res != GLEW_OK) {
      std::cerr<<"Error : "<<glewGetErrorString(res)<<std::endl;
    exit(1);
  }

  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

  glutDisplayFunc(MyRenderScene);
  glutTimerFunc(16, Timer, 0);

  glutKeyboardFunc(MyKeyboard);

  glutCloseFunc(MyClose);

  glutSpecialFunc(MySpecialKeyboard);

  glutPassiveMotionFunc(MyMouse);

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
void create_scene() {
  std::random_device random;
  std::mt19937 range(random());
  std::uniform_int_distribution<int> distribution(1, 100);

  global.world.noise_generator.seed = distribution(range);

  global.camera.set_camera(
      glm::vec3(0, 3, -global.world.height * 1.5),
      glm::vec3(0,0,0),
      glm::vec3(0,1,0)
  );

  global.camera.set_perspective(
      45.0f,
      global.WINDOW_WIDTH,
      global.WINDOW_HEIGHT,
      0.1,
      100);

  if (!global.shaders.init()) {
      std::cerr << "Error initializing shaders..." << std::endl;
      exit(0);
  }

  global.shaders.enable();

  std::vector<std::string> textures = {
    "water.jpg", "grass.jpg", "sand.jpg", "mountain.jpg", "rock.jpg"
  };

  for (int i = 0; i < textures.size(); i++) {
    Texture2D texture_manager = Texture2D();
    texture_manager.load("./textures/" + textures[i]);
    global.texture_managers.push_back(texture_manager);
  }

  global.shaders.set_texture_sampler("WaterSampler", 0);
  global.shaders.set_texture_sampler("GrassSampler", 1);
  global.shaders.set_texture_sampler("SandSampler", 2);
  global.shaders.set_texture_sampler("MountainSampler", 3);
  global.shaders.set_texture_sampler("RockSampler", 4);
}

void MyRenderScene() {
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

  LocalTransform modelT;
  modelT.rotate(global.gradX, global.gradY, 0.0f);
  modelT.translate(-global.world.width / 2, 0, -global.world.height / 2);

  global.shaders.set_model_transform(modelT.T());
  global.shaders.set_camera_transform(global.camera.CP());
  global.shaders.set_time(global.time);

  for (int i = 0; i < global.texture_managers.size(); i++) {
    global.texture_managers[i].bind(i);
  }

  global.world.render();

  glutSwapBuffers();

  global.time += WATER_SPEED;
}

void MyKeyboard(unsigned char key, int x, int y) {
  switch ( key )
  {
      case 27: // Escape key
          glutDestroyWindow(glutGetWindow());
          return;
      break;

      case 'a':
          global.gradY -= global.SPEED;
      break;
      case 'd':
          global.gradY += global.SPEED;
      break;
      case 'w':
          global.gradX -= global.SPEED;
      break;
      case 's':
          global.gradX += global.SPEED;
      break;

  }

  glutPostRedisplay();
}

void MySpecialKeyboard(int Key, int x, int y) {
  global.camera.onSpecialKeyboard(Key);
  glutPostRedisplay();
}

void MyMouse(int x, int y) {
  if (global.camera.onMouse(x,y)) {
    // Risposto il mouse al centro della finestra
    glutWarpPointer(global.WINDOW_WIDTH/2, global.WINDOW_HEIGHT/2);
  }
  glutPostRedisplay();
}

void MyClose(void) {
  std::cout << "Tearing down the system..." << std::endl;

  exit(0);
}

void Timer(int) {
  glutPostRedisplay();
  glutTimerFunc(16, Timer, 0);
}

int main(int argc, char* argv[])
{
  srand(time(NULL));
  init(argc,argv);

  create_scene();

  glutMainLoop();

  return 0;
}