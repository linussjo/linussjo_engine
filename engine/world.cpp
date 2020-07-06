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

    world::world(const std::shared_ptr<graphic::graphic_engine> &ge, unsigned int w, unsigned int h) : graphic_engine(ge),
     width(w), height(h)
    {
        this->physic_engine = this->create_physic_engine(w, h);
        this->input_handler = input::input_factory::get_factory().get(this->graphic_engine->get_window());
    }


    bool world::has_next()
    {
        if(this->next == nullptr)
            return false;
        else
            return true;
    }

    void world::append_component(const std::shared_ptr<input::component::component> &componet) 
    {
        for(const auto &s : componet->get_shapes())
        {
            this->append_s_object(s);
        }
        this->input_handler->add_component(componet);
    }

    void world::append_po_object(std::shared_ptr<physic::physical_object> po)
    {
        for(const auto &s : po->get_shapes())
        {
            this->s_objects.insert(s);
            this->graphic_engine->objects.insert(s);
        }
        this->po_objects.insert(po);
        this->physic_engine->objects.insert(po);
    }

    void world::append_s_object(std::shared_ptr<graphic::shape::shape> s)
    {
        this->s_objects.insert(s);
        this->graphic_engine->objects.insert(s);
    }

    void world::remove_po_object(std::shared_ptr<physic::physical_object> po)
    {
        for(const auto &s : po->get_shapes())
        {
            this->s_objects.erase(s);
            this->graphic_engine->objects.erase(s);
        }
        this->po_objects.erase(po);
        this->physic_engine->objects.erase(po);
    }

    void world::remove_s_object(std::shared_ptr<graphic::shape::shape> s)
    {
        this->s_objects.erase(s);
        this->graphic_engine->objects.erase(s);
    }

    void world::run()
    {
        this->continue_run = true;
        if(!this->initiated){
            this->first_prepare();
            this->initiated = true;
        }
        // reinsert stored objects of the world to the physics engine and graphic engine.
        this->graphic_engine->objects = this->s_objects;
        this->physic_engine->objects = this->po_objects;
        
        this->prepare();
        this->physic_engine->update_time();
        
        while(this->continue_run)
        {
            // while game is paused, update physic engines time to avoid objects moving very far distances and check for updates in window
            while(this->is_paused){
                this->physic_engine->update_time();
                glfwPollEvents();
            }
            glfwPollEvents();
            this->on_iteration();
            this->graphic_engine->render();
            this->physic_engine->apply();
            this->physic_engine->update_time();
        }
        this->on_leave();
        this->graphic_engine->objects.clear();
        this->physic_engine->objects.clear();
    }

    std::shared_ptr<physic::physics_engine> world::create_physic_engine(unsigned int w, unsigned int h)
    {
        return std::make_shared<physic::physics_engine>(w, h);
    }

    std::shared_ptr<physic::physics_engine> world::get_physic_engine()
    {
        return this->physic_engine;
    }

    std::shared_ptr<graphic::graphic_engine> world::get_graphic_engine()
    {
        return this->graphic_engine;
    }

    std::shared_ptr<input::input_handler> world::get_input_handler()
    {
        return this->input_handler;
    }
}
