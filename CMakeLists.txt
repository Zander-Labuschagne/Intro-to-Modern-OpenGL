cmake_minimum_required(VERSION 3.7)   # CMake version check
project(GraphicsTutorial)               # Create project "simple_example"
set(CMAKE_CXX_STANDARD 17)            # Enable c++11 standard

#include(FindPkgConfig)
#pkg_check_modules(SDL2 REQUIRED sdl2)

find_package(SDL2 REQUIRED)
find_package(OpenGL)
find_package(GLEW REQUIRED)
if (GLEW_FOUND)
        include_directories($(GLEW_INCLUDE_DIRS))
        link_libraries(${GLEW_LIBRARIES})
endif ()

include_directories(GraphicsTutorial ${SDL2_INCLUDE_DIRS})
include_directories(GL)

#set(SOURCE_FILES src/main.cpp)            # Add main.cpp file of project root directory as source file
#add_executable(GraphicsTutorial ${SOURCE_FILES})       # Add executable target with source files listed in SOURCE_FILES variable

add_executable(GraphicsTutorial src/main.cpp src/Display.cpp include/Display.h src/Shader.cpp include/Shader.h src/Mesh.cpp include/Mesh.h src/Texture.cpp include/Texture.h include/stb_image.h src/stb_image.c include/Transform.h include/Camera.h src/obj_loader.cpp include/obj_loader.h)
target_link_libraries(GraphicsTutorial ${SDL2_LIBRARIES} ${OPENGL_gl_LIBRARY})


#Bring the headers, such as Student.h into the project
#include_directories(include)

#Can manually add the sources using the set command as follows:
#set(SOURCES src/mainapp.cpp src/Student.cpp)