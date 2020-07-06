//
//  text.hpp
//  linussjo_engine
//
//  Created by Linus Sjöström on 2019-10-02.
//  Copyright © 2019 Linus Sjöström. All rights reserved.
//

#ifndef text_hpp
#define text_hpp

#include <stdio.h>
#include <string>
#include <map>
#include <memory>
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "shape.hpp"
#include "character_font.h"
#include "font_description.h"

namespace engine::graphic::shape
{
    const auto text_vert = SHADERS_RESOURCE+"/text.vert";
    const auto text_frag = SHADERS_RESOURCE+"/text.frag";

    class text: public shape{
    public:
        text(const math::point2d &, const std::string &, const std::shared_ptr<font::font_description> &);
        virtual ~text();
        std::string content;
        int draw(const unsigned int& width, const unsigned int& height);
        bool has_focus(const math::point2d &, length, length);
        unsigned int size {50};
    private:
        GLuint VBO;
        const std::shared_ptr<font::font_description> font_description;
        static class shader helper();
    };
}
#endif /* text_hpp */


