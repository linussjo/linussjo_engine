//
//  font_factory.cpp
//  linussjo_engine
//
//  Created by Linus Sjöström on 2019-10-17.
//  Copyright © 2019 Linus Sjöström. All rights reserved.
//

#include "font_factory.hpp"

namespace engine::graphic::font
{
    font_factory::font_factory() : ARIAL(this->get(ARIAL_PATH)){}
    
    std::shared_ptr<font_description> font_factory::get(const std::string &font_path)
    {
        
        // FreeType
        FT_Library ft;
        // All functions return a value different than 0 whenever an error occurred
        if (FT_Init_FreeType(&ft))
        {
            std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
            exit(-1); // error, should not continue if library could not be initiliazed
        }

        // Load font as face
        FT_Face face;
        if (FT_New_Face(ft, font_path.c_str(), 0, &face))
        {
            std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
            std::cout << "FONT: " << font_path << std::endl;
            return NULL;
        }

        // Set size to load glyphs as
        FT_Set_Pixel_Sizes(face, 0, 600);

        // Disable byte-alignment restriction
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        
        std::map<GLchar, std::shared_ptr<character_font>> characters;
        // Load first 128 characters of ASCII set
        for (GLubyte c = 0; c < 128; c++)
        {
            // Load character glyph
            if (FT_Load_Char(face, c, FT_LOAD_RENDER))
            {
                std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
                continue; // return null or continue???
            }
            // Generate texture
            GLuint texture;
            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RED,
                face->glyph->bitmap.width,
                face->glyph->bitmap.rows,
                0,
                GL_RED,
                GL_UNSIGNED_BYTE,
                face->glyph->bitmap.buffer
            );
            // Set texture options
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            // Now store character for later use
            auto ch = std::make_shared<character_font>(
                texture,
                glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                static_cast<GLuint>(face->glyph->advance.x)
            );
            characters.insert(std::pair<GLchar, std::shared_ptr<character_font>>(c, ch));
        }
        glBindTexture(GL_TEXTURE_2D, 0);
        // Destroy FreeType once finished
        FT_Done_Face(face);
        FT_Done_FreeType(ft);
        
        return std::make_shared<font_description>(font_path, characters);
    }
}
