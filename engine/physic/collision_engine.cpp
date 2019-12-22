//
//  collision_engine.cpp
//  linussjo_engine
//
//  Created by Linus Sjöström on 2019-10-07.
//  Copyright © 2019 Linus Sjöström. All rights reserved.
//

#include "collision_engine.hpp"

namespace engine::physic
{
    bool collision_engine::handle_collision(const std::shared_ptr<physical_object> &p1, const std::shared_ptr<physical_object> &p2)
    {
        const auto mid1 = p1->pos;
        const auto mid2 = p2->pos;
        const auto d = math::normal(mid1, mid2);
        float overlap = std::numeric_limits<float>::infinity();
        const auto p1_points = p1->get_points();
        const auto p2_points = p2->get_points();
        for(int a = 0;  a < p1_points.size(); a++)
        {
            const auto b = (a+1) % p1_points.size();
            math::vector2d axisProj = math::normal(p1_points[a], p1_points[b]);
            axisProj.x *= -1;
            
            const auto d = vector_abs(axisProj);
            axisProj = { (int)(axisProj.x / d), (int)(axisProj.y / d) };
            
            float min_r1 = std::numeric_limits<float>::infinity();
            float max_r1 = -std::numeric_limits<float>::infinity();
            
            for(int p = 0; p < p1_points.size(); p++)
            {
                const auto q = math::dot_product(p1_points[p], axisProj);
                min_r1 = std::min<float>(min_r1, q);
                max_r1 = std::max<float>(max_r1, q);
            }
            
            float min_r2 = std::numeric_limits<float>::infinity();
            float max_r2 = -std::numeric_limits<float>::infinity();
            
            for(int p = 0; p < p2_points.size(); p++)
            {
                const auto q = math::dot_product(p2_points[p], axisProj);
                min_r2 = std::min<float>(min_r2, q);
                max_r2 = std::max<float>(max_r2, q);
            }
            
            overlap = std::min(std::min(max_r1, max_r2) - std::max(min_r1, min_r2), overlap);
            
            if ((max_r1 < min_r2 || min_r1 > max_r2)){
                return false;
            }
        }
        
        auto s = std::sqrtf(math::dot_product(d,d));
        const auto displacement_y = overlap * d.y/s;
        const auto displacement_x = overlap * d.x/s;
        const auto old_v = p1->velocity;
        if(p1->velocity.y != 0)
        {
            p1->pos.y -= displacement_y;
            if(this->set_objects_static)
            {
                if(d.y >= 0.0f)
                {
                    p1->velocity.y = 0;
                    p1->is_grounded = true;
                    p1->on_lands(p1);
                }
                else if (d.y < 0.0f)
                {
                    p1->velocity.y = 0;
                    p1->pos.y += 2;
                }
            }
        }
        if(p1->velocity.x != 0)
        {
            p1->pos.x -= displacement_x;
            if(this->set_objects_static)
            {
                if(overlap > 0)
                {
                    if(d.x < 0.0f)
                    {
                        p1->pos.x += 2;
                    }
                    else if(d.x > 0.0f)
                    {
                        p1->pos.x += -2;
                    }
                    if(!p1->is_grounded)
                        p1->velocity.x *= 0;
                }
            }
        }
        return true;
    }
}
