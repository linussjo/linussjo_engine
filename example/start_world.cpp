//
//  start_world.cpp
//  linussjo_engine
//
//  Created by Linus Sjöström on 2019-10-03.
//  Copyright © 2019 Linus Sjöström. All rights reserved.
//

#include "start_world.hpp"


start_world::start_world(unsigned int w, unsigned int h) : world(w, h){}

void start_world::first_prepare(engine::graphic::graphic_engine &ge, engine::physic::physics_engine &pe)
{
    auto t = std::make_shared<engine::graphic::shape::text>(engine::math::vector2d{400,150}, "Flappy Copy", ge.fonts()->ARIAL);
    t->color = engine::graphic::color{30,190,30};
    this->append_s_object(ge, t);
    
    auto t1 = std::make_shared<engine::graphic::shape::text>(engine::math::vector2d{410,300}, "Start Game", ge.fonts()->ARIAL);
    t1->color = engine::graphic::color{30,190,30};
    this->append_s_object(ge, t1);
    
}

void start_world::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods,
    engine::graphic::graphic_engine &ge, engine::physic::physics_engine &pe)
{
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
    {
        this->continue_run = false;
    }
}

