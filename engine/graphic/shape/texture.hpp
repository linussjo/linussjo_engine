//
//  texture.hpp
//  linussjo_engine
//
//  Created by Linus Sjöström on 2019-10-18.
//  Copyright © 2019 Linus Sjöström. All rights reserved.
//

#ifndef texture_hpp
#define texture_hpp

#include <stdio.h>
#include "rectangle.hpp"

namespace engine::graphic::shape
{
    const auto tex_vert = SHADERS_RESOURCE+"/texture.vert";
    const auto tex_frag = SHADERS_RESOURCE+"/texture.frag";
    class texture : public rectangle
    {
    public:
        texture(const math::point2d &, const std::string &);
        texture(const math::point2d &pos, const std::string &path, const unsigned int scale);
        virtual ~texture();
        virtual int draw(const unsigned int& width, const unsigned int& height);
        GLuint render_type {GL_NEAREST};
    private:
        GLuint tex;
        unsigned int scale {1};
        static class shader helper();
        void setup(const math::point2d &, const std::string &p);
    };
}

#endif /* texture_hpp */
