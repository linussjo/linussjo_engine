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
    flappy_bird(const std::shared_ptr<engine::graphic::graphic_engine> &, unsigned int, unsigned int);
    virtual void on_key_input(GLFWwindow* window, int key, int scancode, int action, int mods);
protected:
    void first_prepare();
    void prepare();
    void on_iteration();
private:
    std::shared_ptr<engine::physic::physical_object> character;
    std::shared_ptr<engine::physic::physical_object> upper_obstacle;
    std::shared_ptr<engine::physic::physical_object> lower_obstacle;
    void create_obstacles();
};

#endif /* flappy_bird_hpp */
