//
//  world.hpp
//  linussjo_engine
//
//  Created by Linus Sjöström on 2019-09-30.
//  Copyright © 2019 Linus Sjöström. All rights reserved.
//

#ifndef world_hpp
#define world_hpp

#include <stdio.h>
#include <set>
#include <unordered_set>
#include <memory>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "text.hpp"
#include "physical_object.hpp"
#include "graphic_engine.hpp"
#include "physics_engine.hpp"
#include "input_factory.hpp"

namespace engine
{
    class world {
    public:
        world(const std::shared_ptr<graphic::graphic_engine> &, unsigned int, unsigned int);
        virtual void window_focus_callback(GLFWwindow* window, int focused) {};
        void append_po_object(const std::shared_ptr<physic::physical_object> &po);
        void remove_po_object(const std::shared_ptr<physic::physical_object> &po);
        void append_s_object(const std::shared_ptr<graphic::shape::shape> &po);
        void remove_s_object(const std::shared_ptr<graphic::shape::shape> &po);
        void append_component(const std::shared_ptr<input::component::component>&);
        virtual void run();

        std::shared_ptr<physic::physics_engine> get_physic_engine();
        std::shared_ptr<graphic::graphic_engine> get_graphic_engine();
        std::shared_ptr<input::input_handler> get_input_handler();

        bool continue_run = true;
        const unsigned int width, height;
        std::shared_ptr<world> next;
        bool has_next();
        bool is_paused = false;

        /**
         * Window
         * Key
         * Scancode
         * Action
         * Mods 
        **/
        virtual void on_key_input(GLFWwindow*, int, int, int, int) {};
        /**
         * Window
         * Key
         * Scancode
         * Action
        **/
        virtual void on_mouse_input(GLFWwindow*, int, int, int) {};
        /**
         * Window
         * Point
        **/
        virtual void on_cursor_moved(GLFWwindow*, const engine::math::point2d &) {};
    protected:
        virtual void first_prepare() {};
        virtual void prepare() {};
        virtual void on_iteration() {};
        virtual void on_leave() {};
        // override if you want to have your own physic engine
        virtual std::shared_ptr<physic::physics_engine> create_physic_engine(unsigned int w, unsigned int h);
        std::unordered_set<std::shared_ptr<physic::physical_object>> po_objects;
        std::set<std::shared_ptr<graphic::shape::shape>, graphic::z_index_compare> s_objects;
        bool initiated = false;

    private:
        std::shared_ptr<physic::physics_engine> physic_engine;
        std::shared_ptr<graphic::graphic_engine> graphic_engine;
        std::shared_ptr<input::input_handler> input_handler;
    };
}

#endif /* world_hpp */
