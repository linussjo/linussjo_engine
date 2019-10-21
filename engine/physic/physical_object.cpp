//
//  physical_object.cpp
//  linussjo_engine
//
//  Created by Linus Sjöström on 2019-09-25.
//  Copyright © 2019 Linus Sjöström. All rights reserved.
//

#include "physical_object.hpp"

namespace engine::physic
{
    physical_object::physical_object(std::shared_ptr<graphic::shape::shape> shape) {
        this->object_shapes.insert(shape);
        this->apply_new_position(0);
    }

    physical_object::~physical_object()
    {
    }

    std::vector<math::vector2d> physical_object::get_points()
    {
        std::vector<math::vector2d> points{
            this->pos,
            math::vector2d{this->pos.x+(int)this->width, this->pos.y},
            math::vector2d{this->pos.x+(int)this->width, this->pos.y+(int)this->height},
            math::vector2d{this->pos.x, this->pos.y+(int)this->height}
        };
        return points;
    }

    void physical_object::handle_intersect(const std::shared_ptr<physical_object> &po)
    {
        this->on_intersect(shared_from_this(), po);
        //printf("intersect\n");
    }

    math::vector2d physical_object::get_mid_pos()
    {
        return math::vector2d{this->pos.x+(int)this->width/2, this->pos.y+(int)this->height/2};
    }

    void physical_object::apply_new_position(const double &time)
    {
        this->pos.x += this->velocity.x*time;
        this->pos.y += this->velocity.y*time;
        
        for(const auto &s : this->object_shapes)
        {
            s->pos.x = this->pos.x + s->relative_pos.x;
            s->pos.y = this->pos.y + s->relative_pos.y;
        }
    }

    void physical_object::handle_out_of_bounds()
    {
        this->on_out_of_bounds(shared_from_this());
    }
}
