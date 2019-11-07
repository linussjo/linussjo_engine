//
//  texture.cpp
//  linussjo_engine
//
//  Created by Linus Sjöström on 2019-10-18.
//  Copyright © 2019 Linus Sjöström. All rights reserved.
//

#include "texture.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace engine::graphic::shape
{
    shader texture::helper()
    {
        static class shader s (tex_vert.c_str(), tex_frag.c_str());
        return s;
    }

    texture::texture(const math::vector2d &pos, const std::string &path) : rectangle(pos, helper())
    {
        this->setup(pos, path);
    }

    texture::texture(const math::vector2d &pos, const std::string &path, const unsigned int scale) : rectangle(pos, helper()), scale(scale)
    {
        this->setup(pos, path);
    }

    void texture::setup(const math::vector2d &pos, const std::string &path)
    {
        glGenTextures(1, &this->tex);
        glBindTexture(GL_TEXTURE_2D, this->tex);
        // set the texture wrapping parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->render_type);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->render_type);

        stbi_set_flip_vertically_on_load(true); //otherwise 180 degrees wrong
        int i_width, i_height, nrChannels;
        unsigned char *data = stbi_load(path.c_str(), &i_width, &i_height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, i_width, i_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cout << "Failed to load texture" << std::endl;
        }
        this->width = (length)i_width*this->scale;
        this->heigth = (length)i_height*this->scale;

        stbi_image_free(data); // release the image data as it is loaded into opengl
        
        this->shader.use();
        this->shader.setInt("texture1", 0);
    }

    int texture::draw(const unsigned int& width, const unsigned int& height)
    {
        float tl_x = ((float)this->pos.x) / (width/2) - 1.0f;
        float tl_y = ((float)height-this->pos.y) / (height/2) - 1.0f;
        
        float tr_x = ((float)this->pos.x+this->width) / (width/2) - 1.0f ;
        float tr_y = ((float)height-this->pos.y) / (height/2) - 1.0f;
        
        float bl_x = ((float)this->pos.x) / (width/2) - 1.0f;
        float bl_y = ((float)height-this->pos.y-this->heigth) / (float)(height/2) - 1.0f;
        
        float br_x = ((float)this->pos.x+this->width) / (width/2) - 1.0f;
        float br_y = ((float)height-this->pos.y-this->heigth) / (float)(height/2) - 1.0f;
        float vertices[] = {
            // positions          // colors           // texture coords
            tr_x, tr_y, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
            br_x, br_y, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
            bl_x, bl_y, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
            tl_x, tl_y, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
        };

        unsigned int indices[] = {
            0, 1, 3, // first triangle
            1, 2, 3  // second triangle
        };

        glBindVertexArray(this->get_graphic_id());

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_DYNAMIC_DRAW);

        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        // color attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        // texture coord attribute
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);
        
        this->shader.use();

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, this->tex);

        glBindVertexArray(this->get_graphic_id());
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        return this->get_graphic_id();
    }

    texture::~texture()
    {
        glDeleteTextures(1, &this->tex);
    }
}