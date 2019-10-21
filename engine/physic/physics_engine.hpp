//
//  physics_engine.hpp
//  linussjo_engine
//
//  Created by Linus Sjöström on 2019-09-24.
//  Copyright © 2019 Linus Sjöström. All rights reserved.
//

#ifndef physics_engine_hpp
#define physics_engine_hpp

#include <stdio.h>
#include <stdlib.h>
#include <memory>
#include <unordered_set>
#include <chrono>
#include <math.h>


#include "physical_object.hpp"
#include "collision_engine.hpp"

namespace engine::physic
{
    class physics_engine {
    public:
        physics_engine(unsigned int, unsigned int);
        void apply();
        std::unordered_set<std::shared_ptr<physical_object>> objects;
        void update_time();
        math::vector2d gravity_factor {0,900};
        unsigned int height, width;
        bool apply_collision_logic = true;
        collision_engine ce;
        double get_time();
    private:
        std::chrono::high_resolution_clock::time_point tp;
        double time;
        void apply_gravity(const std::shared_ptr<physical_object> &, const double &);
    };
}
#endif /* physics_engine_hpp */
