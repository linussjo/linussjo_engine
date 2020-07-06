//
//  input_handler.hpp
//  linussjo_engine
//
//  Created by Linus Sjöström on 2020-02-19.
//  Copyright © 2019 Linus Sjöström. All rights reserved.
//

#ifndef input_handler_hpp
#define input_handler_hpp

#include <stdio.h>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <unordered_set>
#include "component.hpp"
#include "point.hpp"

namespace engine::input
{
    class input_handler
    {
    public:
        input_handler(GLFWwindow*, GLFWkeyfun, GLFWmousebuttonfun, GLFWcursorposfun);

        void add_component(const std::shared_ptr<component::component> &);
        std::unordered_set<std::shared_ptr<component::component>> get_components();

        void set_on_mouse_input(const std::function<void(GLFWwindow*, int, int, int)> &);
        std::function<void(GLFWwindow*, int, int, int)> get_on_mouse_input();

        void set_on_key_input(const std::function<void(GLFWwindow*, int, int, int, int)> &);
        std::function<void(GLFWwindow*, int, int, int, int)> get_on_key_input();

        void set_on_cursor_moved(const std::function<void(GLFWwindow*, const engine::math::point2d &)> &);
        std::function<void(GLFWwindow*, const engine::math::point2d &)> get_on_cursor_moved();
        
        void set_cursor_position(const engine::math::point2d &);
        engine::math::point2d get_cursor_position();
    
    private:
        std::unordered_set<std::shared_ptr<component::component>> components;
        engine::math::point2d cursor_position;
        std::function<void(GLFWwindow*, int, int, int, int)> on_key_input = 
            [](GLFWwindow* w, int a, int b, int c, int d){};
        std::function<void(GLFWwindow*, int, int, int)> on_mouse_input = 
            [](GLFWwindow* w, int a, int b, int c){};
        std::function<void(GLFWwindow*, const engine::math::point2d &)> on_cursor_moved = 
            [](GLFWwindow* w, const engine::math::point2d &p){};

    };
}
#endif /* input_handler_hpp */