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

    linussjo_engine& linussjo_engine::getInstance()
    {
        static linussjo_engine instance;

        return instance;
    };

    void linussjo_engine::start(const std::function<std::shared_ptr<world>(const std::shared_ptr<engine::graphic::graphic_engine> &,
                                             const unsigned int, const unsigned int)> &on_create_worlds)
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
        this->window = glfwCreateWindow(this->width, this->height, this->title.c_str(), NULL, NULL);
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

        glfwSetWindowFocusCallback(this->window, window_focus_callback);
        this->ge = std::make_shared<graphic::graphic_engine>(this->window, this->width, this->height);
        this->ge->show_fps = this->show_fps;
        this->active_world = on_create_worlds(this->ge, this->width, this->height);

        auto input_handler = input::input_factory::get_factory().get(this->window);

        auto key_input = [this](GLFWwindow *w, int a, int b, int c, int d){
            this->active_world->on_key_input(w, a, b, c, d);
        };
        auto mouse_input = [this](GLFWwindow *w, int a, int b, int c){
            this->active_world->on_mouse_input(w, a, b, c);
        };
        auto cursor_moved = [this](GLFWwindow *w, const engine::math::point2d &p){
            this->active_world->on_cursor_moved(w, p);
        };

        input_handler->set_on_key_input(key_input);
        input_handler->set_on_mouse_input(mouse_input);
        input_handler->set_on_cursor_moved(cursor_moved);

        if(this->active_world == nullptr)
        {
            std::cout << "ERROR: not a defined world to start" << std::endl;
        }

        while(this->active_world != nullptr)
        {
            this->active_world->run();
            // update the input in case they have been modified by a world
            // the modification should affect the next world
            input_handler->set_on_key_input(key_input);
            input_handler->set_on_mouse_input(mouse_input);
            input_handler->set_on_cursor_moved(cursor_moved);
            this->active_world = this->active_world->next;
        }
    }

    void linussjo_engine::window_focus_callback(GLFWwindow* window, int focused)
    {
        auto world = linussjo_engine::getInstance().active_world;
        world->is_paused = !focused;
        world->window_focus_callback(window, focused);
    }
}
