//
//  collision_engine.hpp
//  linussjo_engine
//
//  Created by Linus Sjöström on 2019-10-07.
//  Copyright © 2019 Linus Sjöström. All rights reserved.
//

#ifndef collision_engine_hpp
#define collision_engine_hpp

#include <stdio.h>
#include <memory>

#include "math.hpp"
#include "physical_object.hpp"

namespace engine::physic
{
    class collision_engine{
    public:
        virtual bool handle_collision(const std::shared_ptr<physical_object> &, const std::shared_ptr<physical_object> &);
    };
}

#endif /* collision_engine_hpp */
