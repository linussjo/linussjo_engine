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
    flappy_world(unsigned int, unsigned int);
    void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods,
        engine::graphic::graphic_engine &ge, engine::physic::physics_engine &pe);
protected:
    void first_prepare(engine::graphic::graphic_engine &ge, engine::physic::physics_engine &pe);
    void prepare(engine::graphic::graphic_engine &ge, engine::physic::physics_engine &pe);
    void on_iteration(engine::graphic::graphic_engine &ge, engine::physic::physics_engine &pe);
private:
    std::shared_ptr<engine::physic::physical_object> character;
    std::shared_ptr<engine::graphic::shape::texture> right;
    std::shared_ptr<engine::graphic::shape::texture> left;
    std::shared_ptr<engine::physic::physical_object> upper_obstacle;
    std::shared_ptr<engine::physic::physical_object> lower_obstacle;
    void create_obstacles(engine::graphic::graphic_engine &ge, engine::physic::physics_engine &pe);
    engine::math::vector2d last_pos;
    
};

#endif /* flappy_world_hpp */
