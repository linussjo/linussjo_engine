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

    void linussjo_engine::start(const std::shared_ptr<world> &world, const unsigned int w, const unsigned int h)
    {
        this->active_world = world;
        this->start(w,h);
    }

    void linussjo_engine::start(const unsigned int w, const unsigned int h)
    {
        this->ge = std::make_shared<graphic::graphic_engine>(w,h);
        this->ge->show_fps = this->show_fps;
        
        glfwSetKeyCallback(this->ge->get_window(), linussjo_engine::key_callback);
        glfwSetWindowFocusCallback(this->ge->get_window(), window_focus_callback);
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
