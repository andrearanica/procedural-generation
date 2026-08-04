CC = g++
CCFLAGS = -O3 -s -DNDEBUG

ifeq ($(OS),Windows_NT)
	BASEDIR = ../base
	INCLUDEDIRS += -I$(BASEDIR)/freeglut/include
	INCLUDEDIRS += -I$(BASEDIR)/glew/include
	INCLUDEDIRS += -I$(BASEDIR)/glm

	LIBDIRS += -L$(BASEDIR)/freeglut/lib
	LIBDIRS += -L$(BASEDIR)/glew/lib/Release/Win32

	LIBS += -lfreeglut 
	LIBS += -lopengl32
	LIBS += -lglew32

else
	LIBS += -lglut
	LIBS += -lGLEW
	LIBS += -lGL
endif

OBJS = main.o utils.o transform.o camera.o shaderclass.o world_shader.o water_shader.o world.o noise.o water.o texture.o gui.o gui_shader.o

main.exe : $(OBJS)
	$(CC) $(CCFLAGS) $^ $(LIBDIRS) $(LIBS) -o $@

main.o : main.cpp
	$(CC) -c $(CCFLAGS) $(INCLUDEDIRS) $? -o $@

utils.o : ./libs/utils/utils.cpp
	$(CC) -c $(CCFLAGS) $(INCLUDEDIRS) $? -o $@

transform.o : ./libs/transform/transform.cpp
	$(CC) -c $(CCFLAGS) $(INCLUDEDIRS) $? -o $@

camera.o : ./libs/camera/camera.cpp
	$(CC) -c $(CCFLAGS) $(INCLUDEDIRS) $? -o $@

shaderclass.o : ./libs/shaders/shaderclass.cpp
	$(CC) -c $(CCFLAGS) $(INCLUDEDIRS) $? -o $@

world_shader.o : ./libs/shaders/world_shader.cpp
	$(CC) -c $(CCFLAGS) $(INCLUDEDIRS) $? -o $@

water_shader.o : ./libs/shaders/water_shader.cpp
	$(CC) -c $(CCFLAGS) $(INCLUDEDIRS) $? -o $@

gui_shader.o: ./libs/shaders/gui_shader.cpp
	$(CC) -c $(CCFLAGS) $(INCLUDEDIRS) $? -o $@

world.o: ./libs/world/world.cpp
	$(CC) -c $(CCFLAGS) $(INCLUDEDIRS) $? -o $@

noise.o: ./libs/noise/noise_generator.cpp
	$(CC) -c $(CCFLAGS) $(INCLUDEDIRS) $? -o $@

water.o: ./libs/world/water.cpp
	$(CC) -c $(CCFLAGS) $(INCLUDEDIRS) $? -o $@

texture.o: ./libs/texture/texture.cpp
	$(CC) -c $(CCFLAGS) $(INCLUDEDIRS) $? -o $@

gui.o: ./libs/gui/gui.cpp
	$(CC) -c $(CCFLAGS) $(INCLUDEDIRS) $? -o $@

.PHONY clean:
clean:
	rm -f *.o *.exe

run:
	./main.exe

