//
//  flappy_world.hpp
//  linussjo_engine
//
//  Created by Linus Sjöström on 2019-09-30.
//  Copyright © 2019 Linus Sjöström. All rights reserved.
//

#ifndef flappy_world_hpp
#define flappy_world_hpp

#include <functional>
#include <thread>
#include <world.hpp>
#include <texture.hpp>

class flappy_world: public engine::world{
public:
    flappy_world(const std::shared_ptr<engine::graphic::graphic_engine> &, unsigned int, unsigned int);
    virtual void on_key_input(GLFWwindow* window, int key, int scancode, int action, int mods);
protected:
    void first_prepare();
    void prepare();
    void on_iteration();
private:
    std::shared_ptr<engine::physic::physical_object> character;
    std::shared_ptr<engine::graphic::shape::texture> right;
    std::shared_ptr<engine::graphic::shape::texture> left;
    std::shared_ptr<engine::physic::physical_object> upper_obstacle;
    std::shared_ptr<engine::physic::physical_object> lower_obstacle;
    void create_obstacles();
    engine::math::vector2d last_pos;
    
};

#endif /* flappy_world_hpp */
