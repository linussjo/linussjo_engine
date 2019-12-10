//
//  world.cpp
//  linussjo_engine
//
//  Created by Linus Sjöström on 2019-09-30.
//  Copyright © 2019 Linus Sjöström. All rights reserved.
//

#include "world.hpp"

namespace engine
{

    world::world(unsigned int w, unsigned int h) :pe(w,h), width(w), height(h){}


    bool world::has_next()
    {
        if(this->next == nullptr)
            return false;
        else
            return true;
    }

    void world::append_po_object(graphic::graphic_engine &ge, physic::physics_engine &pe, std::shared_ptr<physic::physical_object> po)
    {
        for(const auto &s : po->get_shapes())
        {
            this->s_objects.insert(s);
            ge.objects.insert(s);
        }
        this->po_objects.insert(po);
        pe.objects.insert(po);
    }

    void world::append_s_object(graphic::graphic_engine &ge, std::shared_ptr<graphic::shape::shape> s)
    {
        this->s_objects.insert(s);
        ge.objects.insert(s);
    }

    void world::remove_po_object(graphic::graphic_engine &ge, physic::physics_engine &pe, std::shared_ptr<physic::physical_object> po)
    {
        for(const auto &s : po->get_shapes())
        {
            this->s_objects.erase(s);
            ge.objects.erase(s);
        }
        this->po_objects.erase(po);
        pe.objects.erase(po);
    }

    void world::remove_s_object(graphic::graphic_engine &ge, std::shared_ptr<graphic::shape::shape> s)
    {
        this->s_objects.erase(s);
        ge.objects.erase(s);
    }

    void world::run(graphic::graphic_engine &ge)
    {
        this->continue_run = true;
        if(!this->initiated){
            this->first_prepare(ge, this->pe);
            this->initiated = true;
        }
        // reinsert stored objects of the world to the physics engine and graphic engine.
        ge.objects = this->s_objects;
        pe.objects = this->po_objects;
        
        this->prepare(ge, this->pe);
        this->pe.update_time();
        
        while(this->continue_run)
        {
            // while game is paused, update physic engines time to avoid objects moving very far distances and check for updates in window
            while(this->is_paused){
                this->pe.update_time();
                glfwPollEvents();
            }
            glfwPollEvents();
            this->on_iteration(ge, this->pe);
            ge.render();
            this->pe.apply();
            this->pe.update_time();
        }
        this->on_leave(ge, this->pe);
        ge.objects.clear();
        pe.objects.clear();
    }

    void world::key_callback_wrapper(GLFWwindow* window, int key, int scancode, int action, int mods,
            graphic::graphic_engine &ge)
    {
        this->key_callback(window, key, scancode, action, mods, ge, this->pe);
    }
}
