//
//  linussjo_engine.cpp
//  linussjo_engine
//
//  Created by Linus Sjöström on 2019-09-30.
//  Copyright © 2019 Linus Sjöström. All rights reserved.
//

#include "linussjo_engine.hpp"

namespace engine
{

    void linussjo_engine::start(const std::string &title, const std::shared_ptr<world> &world, const unsigned int w, const unsigned int h)
    {
        this->active_world = world;
        this->start(title,w,h);
    }

    void linussjo_engine::start(const std::string &title, const unsigned int w, const unsigned int h)
    {   
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        #ifdef __APPLE__
            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        #endif
        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
        

        //FULLSCREEN: this->window = glfwCreateWindow(width, height, "OpenGL", glfwGetPrimaryMonitor(), NULL);
        this->window = glfwCreateWindow(w, h, title.c_str(), NULL, NULL);
        glfwMakeContextCurrent(this->window);

        // Check for window creation failure
        if (!this->window)
        {
            // Terminate GLFW
            printf("ERROR: could not create window\n");
            glfwTerminate();
            return;
        }
        
        // Initialize GLEW
        glewExperimental = GL_TRUE;
        glewInit();

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glfwSetKeyCallback(this->window, linussjo_engine::key_callback);
        glfwSetWindowFocusCallback(this->window, window_focus_callback);
        this->ge = std::make_shared<graphic::graphic_engine>(this->window, w, h);
        this->ge->show_fps = this->show_fps;

        while(this->active_world != nullptr)
        {
            this->active_world->run(*this->ge);
            this->active_world = this->active_world->next;
        }
    }

    void linussjo_engine::window_focus_callback(GLFWwindow* window, int focused)
    {
        auto world = linussjo_engine::getInstance().active_world;
        world->is_paused = !focused;
        world->window_focus_callback(window, focused);
    }

    void linussjo_engine::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        linussjo_engine::getInstance().active_world->key_callback_wrapper(window, key, scancode, action, mods, *linussjo_engine::getInstance().ge);
    }
}
