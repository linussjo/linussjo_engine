cmake_minimum_required (VERSION 2.6)
project (Linussjo_Engine)

# The version number.
set (Linussjo_Engine_VERSION_MAJOR 1)
set (Linussjo_Engine_VERSION_MINOR 0)
# use c++ 17 (project is using nested namespaces)
set (CMAKE_CXX_STANDARD 17)
SET(CMAKE_EXE_LINKER_FLAGS "-v")

add_definitions( -DSHADERS_RESOURCE=std::string\("${PROJECT_BINARY_DIR}/resources/shaders"\))
add_definitions( -DFONTS_RESOURCE=std::string\("${PROJECT_BINARY_DIR}/resources/fonts"\))

# internal
include_directories("${PROJECT_BINARY_DIR}")
include_directories("engine")
include_directories("engine/graphic")
include_directories("engine/graphic/shape")
include_directories("engine/graphic/font")
include_directories("engine/physic/")
include_directories("engine/math/")
# external
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLEW REQUIRED)
find_package(Freetype REQUIRED)
find_package(glfw3 3.3 REQUIRED)
if (GLEW_FOUND)
    include_directories(${GLEW_INCLUDE_DIRS})
    link_libraries(${GLEW_LIBRARIES})
endif()
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} ${FREETYPE_INCLUDE_DIRS})

file(GLOB SOURCES 
"*.cpp"
"engine/graphic/*.cpp"
"engine/graphic/shape/*.cpp"
"engine/graphic/font/*.cpp"
"engine/physic/*.cpp"
"engine/math/*.cpp"
"engine/*.cpp")

add_executable(test_game ${SOURCES})

target_link_libraries(test_game glfw ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} ${FREETYPE_LIBRARIES})
