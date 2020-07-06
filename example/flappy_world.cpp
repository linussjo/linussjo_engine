//
//  flappy_world.cpp
//  linussjo_engine
//
//  Created by Linus Sjöström on 2019-09-30.
//  Copyright © 2019 Linus Sjöström. All rights reserved.
//

#include "flappy_world.hpp"

flappy_world::flappy_world(const std::shared_ptr<engine::graphic::graphic_engine> &ge, unsigned int w, unsigned int h) : world(ge, w, h){}

void flappy_world::first_prepare()
{
    this->right = std::make_shared<engine::graphic::shape::texture>(engine::math::point2d{0,0}, std::string(IMG_RESOURCE+"/8-bit_Andreas.png"), 3);
    this->left = std::make_shared<engine::graphic::shape::texture>(engine::math::point2d{0,0}, std::string(IMG_RESOURCE+"/8-bit_AndreasLeft.png"), 3);
    auto po = std::make_shared<engine::physic::physical_object>(this->right);
    this->left->is_visible = false;
    
    po->pos = engine::math::vector2d{200,350};
    po->velocity.y = 1500;
    po->velocity.x = 0;
    po->is_affected_by_gravity = true;
    po->width = 50;
    po->height = 50;

    this->character = po;
    this->character->insert_shape(this->left);
    this->append_po_object(po);
}

void flappy_world::create_obstacles()
{
    auto re3 = std::make_shared<engine::graphic::shape::rectangle>(engine::math::point2d{0,0}, 50,2500);
    auto po3 = std::make_shared<engine::physic::physical_object>(re3);
    po3->height = 50;
    po3->width = 2500;
    po3->pos = engine::math::vector2d{100,600};
    po3->is_affected_by_gravity = false;
    po3->is_static = true;
    
    this->append_po_object(po3);
    
    auto re4 = std::make_shared<engine::graphic::shape::rectangle>(engine::math::point2d{0,0}, 75,200);
    auto po4 = std::make_shared<engine::physic::physical_object>(re4);
    po4->height = 75;
    po4->width = 200;
    po4->pos = engine::math::vector2d{400,450};
    po4->is_affected_by_gravity = false;
    po4->is_static = true;
    
    this->append_po_object(po4);
    
    auto re5 = std::make_shared<engine::graphic::shape::rectangle>(engine::math::point2d{0,0}, 200, 50);
    auto po5 = std::make_shared<engine::physic::physical_object>(re5);
    po5->height = 200;
    po5->width = 50;
    po5->pos = engine::math::vector2d{949,300};
    po5->is_affected_by_gravity = false;
    po5->is_static = true;
    
    this->append_po_object(po5);
}

void flappy_world::prepare()
{
    this->character->pos = engine::math::vector2d{500,350};
    this->get_graphic_engine()->prepare_draw_for_focus(this->last_pos.x - this->character->pos.x, this->last_pos.y - this->character->pos.y);
    this->character->velocity = engine::math::vector2f{0,0};

    this->create_obstacles();
    this->last_pos = this->character->pos;
}

void flappy_world::on_iteration()
{
    this->get_graphic_engine()->prepare_draw_for_focus(this->last_pos.x - this->character->pos.x, this->last_pos.y - this->character->pos.y);
}

void flappy_world::on_key_input(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS && this->character->is_grounded)
    {
        this->character->velocity.y = -400;
        this->character->is_grounded = false;
    }
    if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
    {
        this->character->velocity.x = -300;
        this->left->is_visible = true;
        this->right->is_visible = false;
    }
    if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
    {
        this->character->velocity.x = 300;
        this->left->is_visible = false;
        this->right->is_visible = true;
    }
    if (key == GLFW_KEY_UP && action == GLFW_PRESS)
    {
        this->character->velocity.y = -400;
    }
    if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
    {
        this->character->velocity.y = 300;
    }
    if ((key == GLFW_KEY_ESCAPE || key == GLFW_KEY_Q) && action == GLFW_PRESS)
    {
        this->continue_run = false;
    }
    if((key == GLFW_KEY_LEFT || key == GLFW_KEY_RIGHT) && action == GLFW_RELEASE)
    {
        this->character->velocity.x = 0;
    }
    if((key == GLFW_KEY_UP || key == GLFW_KEY_DOWN) && action == GLFW_RELEASE)
    {
        this->character->velocity.y = 0;
    }
}
