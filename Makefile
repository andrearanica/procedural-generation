CC = g++
CCFLAGS = -O3 -s -DNDEBUG

ifeq ($(OS),Windows_NT)
	BASEDIR = ./base
	INCLUDEDIRS += -I$(BASEDIR)/freeglut/include
	INCLUDEDIRS += -I$(BASEDIR)/glew/include
	INCLUDEDIRS += -I$(BASEDIR)/glm

	LIBDIRS += -L$(BASEDIR)/freeglut/lib
	LIBDIRS += -L$(BASEDIR)/glew/lib/Release/Win32

	LIBS += -lfreeglut 
	LIBS += -lopengl32
	LIBS += -lglew32

	ifneq ($(findstring sh,$(SHELL)),)
        COPY_DLLS = cp base/freeglut/bin/freeglut.dll . 2>/dev/null || true; cp base/glew/bin/Release/Win32/glew32.dll . 2>/dev/null || true
    else
        # Se stiamo usando cmd.exe standard su Windows
        COPY_DLLS = -copy /Y base\freeglut\bin\freeglut.dll .\ >nul & -copy /Y base\glew\bin\Release\Win32\glew32.dll .\ >nul
    endif
else
	LIBS += -lglut
	LIBS += -lGLEW
	LIBS += -lGL
	COPY_DLLS = 
endif

OBJS = main.o utils.o transform.o camera.o shaderclass.o world_shader.o water_shader.o world.o noise.o water.o texture.o gui.o gui_shader.o font.o label.o widget.o falloff_generator.o

main.exe : $(OBJS)
	$(CC) $(CCFLAGS) $^ $(LIBDIRS) $(LIBS) -o $@
	$(COPY_DLLS)

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

font.o: ./libs/gui/font.cpp
	$(CC) -c $(CCFLAGS) $(INCLUDEDIRS) $? -o $@

label.o: ./libs/gui/widgets/label.cpp
	$(CC) -c $(CCFLAGS) $(INCLUDEDIRS) $? -o $@

widget.o: ./libs/gui/widgets/widget.cpp
	$(CC) -c $(CCFLAGS) $(INCLUDEDIRS) $? -o $@

falloff_generator.o: ./libs/noise/falloff_generator.cpp
	$(CC) -c $(CCFLAGS) $(INCLUDEDIRS) $? -o $@

.PHONY clean:
clean:
ifeq ($(OS),Windows_NT) 
		del *.o *.exe
else
		rm -f *.o *.exe
endif

run:
	./main.exe
