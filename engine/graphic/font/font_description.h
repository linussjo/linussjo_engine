//
//  font_description.h
//  linussjo_engine
//
//  Created by Linus Sjöström on 2019-10-17.
//  Copyright © 2019 Linus Sjöström. All rights reserved.
//

#ifndef font_description_h
#define font_description_h

#include <string>
#include <map>
#include <GL/glew.h>

namespace engine::graphic::font
{
    struct font_description
    {
        font_description(const std::string n, const std::map<GLchar, std::shared_ptr<character_font>> chars) : name(n), characters(chars) {}
        const std::string name;
        const std::map<GLchar, std::shared_ptr<character_font>> characters;
    };
}

#endif /* font_description_h */
