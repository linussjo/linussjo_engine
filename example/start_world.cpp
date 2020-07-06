//
//  start_world.cpp
//  linussjo_engine
//
//  Created by Linus Sjöström on 2019-10-03.
//  Copyright © 2019 Linus Sjöström. All rights reserved.
//

#include "start_world.hpp"


start_world::start_world(const std::shared_ptr<engine::graphic::graphic_engine> &ge, unsigned int w, unsigned int h) : world(ge, w, h){}

void start_world::first_prepare()
{
    auto t = std::make_shared<engine::graphic::shape::text>(engine::math::point2d{410,200}, "Flappy Copy", this->get_graphic_engine()->fonts()->ARIAL);
    t->color = engine::graphic::color{30,190,30};
    this->append_s_object(t);


    auto componet = std::make_shared<engine::input::component::button>("Start Game", engine::math::point2d{410,300});
    componet->set_size(300,80);
    componet->set_text_color(engine::graphic::color{255,255,255});

    componet->on_key_press = [this](){
        this->continue_run = false;
    };
    this->append_component(componet);
    
}

