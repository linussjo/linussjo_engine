cmake_minimum_required (VERSION 3.9.1)
project(engine)

SET (CMAKE_CXX_STANDARD 17)
SET(CMAKE_EXE_LINKER_FLAGS "-v")

add_definitions( -DSHADERS_RESOURCE=std::string\("${PROJECT_BINARY_DIR}/../resources/shaders"\))
add_definitions( -DFONTS_RESOURCE=std::string\("${PROJECT_BINARY_DIR}/../resources/fonts"\))

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

add_subdirectory(math)
add_subdirectory(graphic)
add_subdirectory(graphic/font)
add_subdirectory(graphic/shape)
add_subdirectory(physic)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/graphic/font")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/graphic/shape")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/graphic")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/physic/")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/math/")

set(engine_source_files
    ${CMAKE_CURRENT_SOURCE_DIR}/linussjo_engine.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/linussjo_engine.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/thread_dispatcher.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/thread_dispatcher.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/world_state.h
    ${CMAKE_CURRENT_SOURCE_DIR}/world.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/world.hpp
)

add_library(engine STATIC ${engine_source_files} 
    ${engine_physic_source_files}
    ${engine_math_source_files}
    ${engine_graphic_font_source_files}
    ${engine_graphic_shape_source_files}
    ${engine_graphic_source_files}
)
