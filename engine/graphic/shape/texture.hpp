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
#include "shape.hpp"

namespace engine::graphic::shape
{
    class texture : public shape
    {
    public:
        texture(const math::vector2d, const std::string &);
        virtual ~texture();
        GLenum get_type();
        bool filled = true;
        int draw(const unsigned int& width, const unsigned int& height);
        bool has_focus(const math::vector2d &, length, length);
    private:
        
    };
}

#endif /* texture_hpp */
