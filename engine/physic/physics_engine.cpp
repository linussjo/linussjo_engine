//
//  physics_engine.cpp
//  linussjo_engine
//
//  Created by Linus Sjöström on 2019-09-24.
//  Copyright © 2019 Linus Sjöström. All rights reserved.
//

#include "physics_engine.hpp"

namespace engine::physic
{

    physics_engine::physics_engine(unsigned int w, unsigned int h) : width(w), height(h) {}

    void physics_engine::update_time()
    {
        this->tp = std::chrono::high_resolution_clock::now();
    }

    void physics_engine::apply_gravity(const std::shared_ptr<physical_object> &po, const double &time)
    {
        po->velocity.y += this->gravity_factor.y*time;
        po->velocity.x += this->gravity_factor.x*time;
    }
    
    double physics_engine::get_time()
    {
        return this->time;
    }

    void physics_engine::apply()
    {
        auto end = std::chrono::high_resolution_clock::now();
        this->time = (double)std::chrono::duration_cast<std::chrono::microseconds>(end-this->tp).count()/1000000;
        const auto l1 = this->objects; // create a local copy, objects may be removed during iteration causing undefined behaviour
        for(const auto &o1 : l1)
        {
            if(o1->is_affected_by_gravity && !o1->is_grounded && !o1->is_static)
            {
                this->apply_gravity(o1, this->time);
            }
            o1->apply_new_position(this->time);
            auto mid_pos = o1->get_mid_pos();
            // check if the physical object is outside of the world
            if(mid_pos.x < -(int)o1->width/2 || mid_pos.x > (int)(this->width+o1->width/2)
               || mid_pos.y < -(int)o1->height/2 || mid_pos.y > (int) (this->height+o1->height/2))
                o1->handle_out_of_bounds();
            
            o1->is_grounded = false;
            if(!o1->is_static)
            {
                for(const auto &o2 : l1)
                {
                    if(o1 == o2){
                        continue;
                    }
                    if(this->apply_collision_logic && this->ce.handle_collision(o1, o2))
                    {
                        o1->handle_intersect(o2);
                        o2->handle_intersect(o1);
                    }
                        
                }
            }
        }
    }
}
