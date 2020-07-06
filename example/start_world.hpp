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
#include <button.hpp>


class start_world: public engine::world{
public:
    start_world(const std::shared_ptr<engine::graphic::graphic_engine> &, unsigned int, unsigned int);
protected:
    void first_prepare();
};

#endif /* start_world_hpp */
