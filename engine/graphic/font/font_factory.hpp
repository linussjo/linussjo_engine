//
//  font_factory.hpp
//  linussjo_engine
//
//  Created by Linus Sjöström on 2019-10-17.
//  Copyright © 2019 Linus Sjöström. All rights reserved.
//

#ifndef font_factory_hpp
#define font_factory_hpp

#include <stdio.h>
#include <iostream>
#include <memory>

// FreeType
#include <ft2build.h>
#include FT_FREETYPE_H

#include "character_font.h"
#include "font_description.h"

namespace engine::graphic::font
{
    
    const std::string ARIAL_PATH = FONTS_RESOURCE+"/Arial.ttf";
    
    class font_factory
    {
    public:
        font_factory();
        std::shared_ptr<font_description> get(const std::string &);
        const std::shared_ptr<font_description> ARIAL;
    };
}

#endif /* font_factory_hpp */
