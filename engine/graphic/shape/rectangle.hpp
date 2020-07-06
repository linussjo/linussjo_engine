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
        rectangle(const math::point2d &, length, length);
        virtual ~rectangle();
        length width, heigth;
        bool filled = true;
        virtual int draw(const unsigned int& width, const unsigned int& height);
        bool has_focus(const math::point2d &, length, length);
    protected:
        rectangle(const math::point2d &, const class shader &); // should not be exposed public as it only would confuse?
        GLuint VBO,EBO;
    private:
        static class shader helper();
    };
}

#endif /* rectangle_hpp */
