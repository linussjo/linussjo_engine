//
//  rectangle.hpp
//  linussjo_engine
//
//  Created by Linus Sjöström on 2019-09-22.
//  Copyright © 2019 Linus Sjöström. All rights reserved.
//

#ifndef rectangle_hpp
#define rectangle_hpp

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "shape.hpp"
#include "vector2d.hpp"

namespace engine::graphic::shape
{
    const auto rec_vert = SHADERS_RESOURCE+"/rectangle.vert";
    const auto rec_frag = SHADERS_RESOURCE+"/rectangle.frag";

    class rectangle: public shape{
    public:
        rectangle(const math::vector2d, length, length);
        virtual ~rectangle();
        GLenum get_type();
        bool filled = true;
        int draw(const unsigned int& width, const unsigned int& height);
        bool has_focus(const math::vector2d &, length, length);
    private:
        length width, heigth;
        static class shader helper();
        GLuint VBO,EBO;
    };
}

#endif /* rectangle_hpp */
