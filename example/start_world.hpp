//
//  start_world.hpp
//  linussjo_engine
//
//  Created by Linus Sjöström on 2019-10-03.
//  Copyright © 2019 Linus Sjöström. All rights reserved.
//

#ifndef start_world_hpp
#define start_world_hpp

#include <stdio.h>
#include <functional>
#include <thread>
#include <world.hpp>


class start_world: public engine::world{
public:
    start_world(unsigned int, unsigned int);
    void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
protected:
    void first_prepare(engine::graphic::graphic_engine &ge, engine::physic::physics_engine &pe);
};

#endif /* start_world_hpp */
