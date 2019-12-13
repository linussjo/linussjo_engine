//
//  flappy_bird.hpp
//  linussjo_engine
//
//  Created by Linus Sjöström on 2019-12-12.
//  Copyright © 2019 Linus Sjöström. All rights reserved.
//

#ifndef flappy_bird_hpp
#define flappy_bird_hpp

#include <functional>
#include <world.hpp>
#include <texture.hpp>
#include <random>

class flappy_bird: public engine::world{
public:
    flappy_bird(unsigned int, unsigned int);
    void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods,
        engine::graphic::graphic_engine &ge, engine::physic::physics_engine &pe);
protected:
    void first_prepare(engine::graphic::graphic_engine &ge, engine::physic::physics_engine &pe);
    void prepare(engine::graphic::graphic_engine &ge, engine::physic::physics_engine &pe);
    void on_iteration(engine::graphic::graphic_engine &ge, engine::physic::physics_engine &pe);
private:
    std::shared_ptr<engine::physic::physical_object> character;
    std::shared_ptr<engine::physic::physical_object> upper_obstacle;
    std::shared_ptr<engine::physic::physical_object> lower_obstacle;
    void create_obstacles(engine::graphic::graphic_engine &ge, engine::physic::physics_engine &pe);
};

#endif /* flappy_bird_hpp */
