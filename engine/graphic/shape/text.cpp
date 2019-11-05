//
//  text.cpp
//  linussjo_engine
//
//  Created by Linus Sjöström on 2019-10-02.
//  Copyright © 2019 Linus Sjöström. All rights reserved.
//

#include "text.hpp"

namespace engine::graphic::shape
{
    shader text::helper()
    {
        static class shader s (text_vert.c_str(), text_frag.c_str());
        return s;
    }
    
    bool text::has_focus(const math::vector2d &focus_pos, length width, length height)
    {
        // to be implemented
        return false;
    }

    text::text(const math::vector2d &pos, const std::string &text, const std::shared_ptr<font::font_description> &fd) : shape(pos, helper()), content(text), font_description(fd)
    {
        this->is_static = true;
            
        // Configure VAO/VBO for texture quads
        GLuint VAO;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &this->VBO);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
        this->set_graphic_id(VAO);
    }

    int text::draw(const unsigned int& width, const unsigned int& height){

        glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(width), 0.0f, static_cast<GLfloat>(height));
        this->shader.use();
        glUniformMatrix4fv(glGetUniformLocation(this->shader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        // Activate corresponding render state
        GLfloat scale = (float)this->size/800;
        GLfloat x = this->pos.x;
        GLfloat y = height-this->pos.y;

        glUniform3f(glGetUniformLocation(shader.ID, "textColor"), color.r, color.g, color.b);
        glActiveTexture(GL_TEXTURE0);
        glBindVertexArray(this->get_graphic_id());

        // Iterate through all characters
        std::string::const_iterator c;
        auto t = content;
        for (c = t.begin(); c != t.end(); c++)
        {
            auto ch = this->font_description->characters.find(*c)->second;

            GLfloat xpos = x + ch->Bearing.x * scale;
            GLfloat ypos = y - (ch->Size.y - ch->Bearing.y) * scale;

            GLfloat w = ch->Size.x * scale;
            GLfloat h = ch->Size.y * scale;
            // Update VBO for each character
            GLfloat vertices[6][4] = {
                { xpos,     ypos + h,   0.0, 0.0 },
                { xpos,     ypos,       0.0, 1.0 },
                { xpos + w, ypos,       1.0, 1.0 },

                { xpos,     ypos + h,   0.0, 0.0 },
                { xpos + w, ypos,       1.0, 1.0 },
                { xpos + w, ypos + h,   1.0, 0.0 }
            };
            // Render glyph texture over quad
            glBindTexture(GL_TEXTURE_2D, ch->TextureID);
            // Update content of VBO memory
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // Be sure to use glBufferSubData and not glBufferData

            glBindBuffer(GL_ARRAY_BUFFER, 0);
            // Render quad
            glDrawArrays(GL_TRIANGLES, 0, 6);
            // Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
            x += (ch->Advance >> 6) * scale; // Bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
        }
        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);
        return this->get_graphic_id();
    }

    GLenum text::get_type()
    {
        return 0;
    }
    
    text::~text()
    {
        glDeleteBuffers(1, &this->VBO);
    }
}
