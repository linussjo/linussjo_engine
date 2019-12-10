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
#include <unordered_set>
#include <memory>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "text.hpp"
#include "physical_object.hpp"
#include "graphic_engine.hpp"
#include "physics_engine.hpp"

namespace engine
{
    class world {
    public:
        world(unsigned int, unsigned int);
        virtual void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods,
            graphic::graphic_engine &ge, physic::physics_engine &pe) {};
        void key_callback_wrapper(GLFWwindow* window, int key, int scancode, int action, int mods,
            graphic::graphic_engine &ge);
        virtual void window_focus_callback(GLFWwindow* window, int focused) {};
        void append_po_object(graphic::graphic_engine &ge, physic::physics_engine &pe, std::shared_ptr<physic::physical_object> po);
        void remove_po_object(graphic::graphic_engine &ge, physic::physics_engine &pe, std::shared_ptr<physic::physical_object> po);
        void append_s_object(graphic::graphic_engine &ge, std::shared_ptr<graphic::shape::shape> po);
        void remove_s_object(graphic::graphic_engine &ge, std::shared_ptr<graphic::shape::shape> po);
        virtual void run(graphic::graphic_engine &ge);
        bool continue_run = true;
        const unsigned int width, height;
        std::shared_ptr<world> next;
        bool has_next();
        bool is_paused = false;
    protected:
        virtual void first_prepare(graphic::graphic_engine &ge, physic::physics_engine &pe) {};
        virtual void prepare(graphic::graphic_engine &ge, physic::physics_engine &pe) {};
        virtual void on_iteration(graphic::graphic_engine &ge, physic::physics_engine &pe) {};
        virtual void on_leave(graphic::graphic_engine &ge, physic::physics_engine &pe) {};
        physic::physics_engine pe;
        std::shared_ptr<graphic::graphic_engine> ge;
        std::unordered_set<std::shared_ptr<physic::physical_object>> po_objects;
        std::unordered_set<std::shared_ptr<graphic::shape::shape>> s_objects;
        bool initiated = false;
    };
}

#endif /* world_hpp */
