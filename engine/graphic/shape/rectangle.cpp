//
//  rectangle.cpp
//  linussjo_engine
//
//  Created by Linus Sjöström on 2019-09-22.
//  Copyright © 2019 Linus Sjöström. All rights reserved.
//

#include "rectangle.hpp"

namespace engine::graphic::shape
{
    shader rectangle::helper()
    {
        static class shader s (rec_vert.c_str(), rec_frag.c_str());
        return s;
    }

    rectangle::rectangle(const math::vector2d pos, length h, length w) : shape(pos, helper()), heigth(h), width(w)
    {
        GLuint VAO;
        glGenBuffers(1, &this->VBO);
        glGenBuffers(1, &this->EBO);
        glGenVertexArrays(1, &VAO);
        this->set_graphic_id(VAO);
    }
    GLenum rectangle::get_type(){
        return GL_TRIANGLES;
    }
    
    bool rectangle::has_focus(const math::vector2d &focus_pos, length width, length height)
    {
        // to be implemented
        return false;
    }

    int rectangle::draw(const unsigned int& width, const unsigned int& height){
        this->shader.use();
        // set up vertex data (and buffer(s)) and configure vertex attributes
        // ------------------------------------------------------------------
        const GLuint shader_programme = this->shader.ID;
        float tl_x = ((float)this->pos.x) / (width/2) - 1.0f;
        float tl_y = ((float)height-this->pos.y) / (height/2) - 1.0f;
        
        float tr_x = ((float)this->pos.x+this->width) / (width/2) - 1.0f ;
        float tr_y = ((float)height-this->pos.y) / (height/2) - 1.0f;
        
        float bl_x = ((float)this->pos.x) / (width/2) - 1.0f;
        float bl_y = ((float)height-this->pos.y-this->heigth) / (float)(height/2) - 1.0f;
        
        float br_x = ((float)this->pos.x+this->width) / (width/2) - 1.0f;
        float br_y = ((float)height-this->pos.y-this->heigth) / (float)(height/2) - 1.0f;
        
        float vertices[] = {
             tr_x, tr_y, 0.0f,  // top right
             br_x, br_y, 0.0f,  // bottom right
             bl_x, bl_y, 0.0f,  // bottom left
             tl_x, tl_y, 0.0f   // top left
        };
        
        unsigned int indices[] = {  // note that we start from 0!
            0, 1, 3,  // first Triangle
            1, 2, 3   // second Triangle
        };
        GLuint VAO = this->get_graphic_id();
        // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
        glBindVertexArray(VAO);
        glUseProgram(shader_programme);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_DYNAMIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        
        if(this->filled)
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        else
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        
        this->prepared = true;
        this->set_graphic_id(VAO);
        GLint color_location = glGetUniformLocation(shader_programme, "uColor");
        float color[4] = {(float)this->color.r/255, (float)this->color.g/255, (float)this->color.b/255, 1.0f};
        glUniform4fv(color_location, 1, color);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        // set back to some default values
        glBindVertexArray(0);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        return VAO;
    }
    
    rectangle::~rectangle()
    {
        glDeleteBuffers(1, &this->VBO);
        glDeleteBuffers(1, &this->EBO);
    }
}
