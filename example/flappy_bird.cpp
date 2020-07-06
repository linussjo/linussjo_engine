//
//  flappy_bird.cpp
//  linussjo_engine
//
//  Created by Linus Sjöström on 2019-12-12.
//  Copyright © 2019 Linus Sjöström. All rights reserved.
//

#include "flappy_bird.hpp"

flappy_bird::flappy_bird(const std::shared_ptr<engine::graphic::graphic_engine> &ge, unsigned int w, unsigned int h) : world(ge, w, h){}

void flappy_bird::first_prepare()
{
    auto r_shape = std::make_shared<engine::graphic::shape::texture>(engine::math::point2d{0,0}, std::string(IMG_RESOURCE+"/8-bit_JumpAndreasRight.png"), 3);
    auto po = std::make_shared<engine::physic::physical_object>(r_shape);
    
    po->pos = engine::math::vector2d{200,350};
    po->velocity.y = 1500;
    po->velocity.x = 0;
    po->is_affected_by_gravity = true;
    po->width = 50;
    po->height = 50;
    po->on_intersect = [this](const std::weak_ptr<engine::physic::physical_object> &a, const std::shared_ptr<engine::physic::physical_object> &b){
        this->continue_run = false;
    };
    po->on_out_of_bounds = [this](const std::weak_ptr<engine::physic::physical_object> &obs){
        this->continue_run = false;
    };

    this->character = po;
    this->append_po_object(po);
}

void flappy_bird::create_obstacles()
{
    int gap_size = 175;
    int min_size = 100;
    int r1 = min_size + rand() % (this->height-gap_size-min_size*3);
    int r2 = this->height-gap_size-r1;

    auto re3 = std::make_shared<engine::graphic::shape::rectangle>(engine::math::point2d{0,0}, r1,75);
    auto po3 = std::make_shared<engine::physic::physical_object>(re3);
    po3->height = r1;
    po3->width = 75;
    po3->pos = engine::math::vector2d{999,0};
    po3->is_affected_by_gravity = false;
    po3->is_static = true;
    po3->velocity = engine::math::vector2f{-200, 0};
    po3->on_out_of_bounds = [this](const std::weak_ptr<engine::physic::physical_object> &obs){
        
    };
    
    this->append_po_object(po3);
    this->upper_obstacle = po3;
    
    auto re4 = std::make_shared<engine::graphic::shape::rectangle>(engine::math::point2d{0,0}, r2,75);
    auto po4 = std::make_shared<engine::physic::physical_object>(re4);
    po4->height = r2;
    po4->width = 75;
    po4->pos = engine::math::vector2d{999,r1+gap_size};
    po4->is_affected_by_gravity = false;
    po4->is_static = true;
    po4->velocity = engine::math::vector2f{-200, 0};
    po4->on_out_of_bounds = [this, po3](const std::weak_ptr<engine::physic::physical_object> &obs){
        this->remove_po_object(obs.lock());
        this->remove_po_object(po3);
        this->create_obstacles();
    };
    
    this->append_po_object(po4);
    this->lower_obstacle = po4;
}

void flappy_bird::on_iteration()
{
}

void flappy_bird::prepare()
{
    this->character->pos = engine::math::vector2d{500,350};
    this->character->velocity = engine::math::vector2f{0,0};
    this->create_obstacles();
}

void flappy_bird::on_leave()
{
    this->remove_po_object(this->upper_obstacle);
    this->remove_po_object(this->lower_obstacle);
}

void flappy_bird::on_key_input(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS && this->character->is_grounded)
    {
        this->character->velocity.y = -450;
    }
    if (key == GLFW_KEY_UP && action == GLFW_PRESS)
    {
        this->character->velocity.y = -450;
    }
    if ((key == GLFW_KEY_ESCAPE || key == GLFW_KEY_Q) && action == GLFW_PRESS)
    {
        this->continue_run = false;
    }
}
