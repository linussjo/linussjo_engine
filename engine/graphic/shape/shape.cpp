//
//  Shape.cpp
//  linussjo_engine
//
//  Created by Linus Sjöström on 2019-09-22.
//  Copyright © 2019 Linus Sjöström. All rights reserved.
//

#include "shape.hpp"

namespace engine::graphic::shape
{
    shape::shape(const math::point2d pos, class shader s) : pos(pos), relative_pos(pos), prepared(false), shader(s){};

    shape::shape(class shader s) : pos(math::point2d{0,0}), relative_pos(math::point2d{0,0}), prepared(false), shader(s){};

    void shape::set_graphic_id(const GLuint gid)
    {
        this->graphic_id = gid;
    }

    GLuint shape::get_graphic_id()
    {
        return this->graphic_id;
    }

    bool shape::is_prepared()
    {
        return this->prepared;
    }

    long long shape::get_z_index_increment()
    {
        static long long z_index_incr = std::numeric_limits<long long>::min();

        return ++z_index_incr;
    }

    shape::~shape()
    {
        glDeleteVertexArrays(1, &this->graphic_id);
    }
}
