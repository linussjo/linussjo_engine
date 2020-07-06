//
//  Shape.hpp
//  linussjo_engine
//
//  Created by Linus Sjöström on 2019-09-22.
//  Copyright © 2019 Linus Sjöström. All rights reserved.
//

#ifndef shape_hpp
#define shape_hpp

#include <stdio.h>
#include <vector>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "point.hpp"
#include "color.hpp"
#include "shader.h"

namespace engine::graphic::shape
{
    typedef unsigned int length;

    class shape{
    public:
        shape(math::point2d, class shader);
        shape(class shader);
        color color{0,0,0};
        virtual int draw(const unsigned int&, const unsigned int&) = 0;
        virtual bool has_focus(const math::point2d &, length, length) = 0;
        GLuint get_graphic_id();
        bool is_prepared();
        virtual ~shape();
        math::point2d pos;
        math::point2d relative_pos;
        bool is_static = false;
        bool is_in_focus = false;
        bool is_visible = true;
        unsigned long z_index = 1000;
    protected:
        void set_graphic_id(const GLuint gid);
        bool prepared;
        shader shader;
    private:
        GLuint graphic_id;
    };
}
#endif /* Shape_hpp */
