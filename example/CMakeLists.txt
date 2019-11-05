cmake_minimum_required (VERSION 3.9.1)
SET (CMAKE_CXX_STANDARD 17)
SET(CMAKE_EXE_LINKER_FLAGS "-v")

if(EXISTS "../engine/libengine.a")
    configure_file("../engine/libengine.a" "./libengine.a" COPYONLY)
else()
    message(FATAL_ERROR "library file not found")
    return()
endif()

if(EXISTS "./libengine.a")
    project(test_game C CXX)

    add_definitions( -DSHADERS_RESOURCE=std::string\("${PROJECT_BINARY_DIR}/resources/shaders"\))
    add_definitions( -DFONTS_RESOURCE=std::string\("${PROJECT_BINARY_DIR}/resources/fonts"\))

    include_directories("${CMAKE_SOURCE_DIR}/../engine")
    include_directories("${CMAKE_SOURCE_DIR}/../engine/graphic/font")
    include_directories("${CMAKE_SOURCE_DIR}/../engine/graphic/shape")
    include_directories("${CMAKE_SOURCE_DIR}/../engine/graphic")
    include_directories("${CMAKE_SOURCE_DIR}/../engine/physic/")
    include_directories("${CMAKE_SOURCE_DIR}/../engine/math/")

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
    
    file(GLOB SOURCES "*.cpp")

    add_executable(test_game ${SOURCES})

    target_link_libraries(test_game 
        ${CMAKE_CURRENT_SOURCE_DIR}/libengine.a
        glfw ${OPENGL_LIBRARIES} 
        ${GLUT_LIBRARY} 
        ${FREETYPE_LIBRARIES}
    )

else()
    message(FATAL_ERROR "library file not found")
    return()
endif()