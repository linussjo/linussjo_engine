//
//  character_font.h
//  linussjo_engine
//
//  Created by Linus Sjöström on 2019-10-17.
//  Copyright © 2019 Linus Sjöström. All rights reserved.
//

#ifndef character_font_h
#define character_font_h
#include "glm/glm.hpp"
#include <GL/glew.h>

namespace engine::graphic::font
{
    struct character_font {
        const GLuint TextureID;   // ID handle of the glyph texture
        const glm::ivec2 Size;    // Size of glyph
        const glm::ivec2 Bearing;  // Offset from baseline to left/top of glyph
        const GLuint Advance;    // Horizontal offset to advance to next glyph
        
        character_font(const GLuint tid, const glm::ivec2 s, const glm::ivec2 b, const GLuint a) : TextureID(tid), Size(s), Bearing(b), Advance(a) {}
        
        ~character_font() // would rather only have this as a storage unit, but someone has to destroy the allocated memory :<
        {
            glDeleteTextures(1, &this->TextureID);
        }
    };
}

#endif /* character_font_h */
