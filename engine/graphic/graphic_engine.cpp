//
//  graphic_engine.cpp
//  linussjo_engine
//
//  Created by Linus Sjöström on 2019-09-23.
//  Copyright © 2019 Linus Sjöström. All rights reserved.
//

#include "graphic_engine.hpp"
namespace engine::graphic
{
    graphic_engine::graphic_engine(GLFWwindow *window, unsigned int width, unsigned int height) :
        continue_render(true), width(width), height(height), window(window)
    {
        this->tp = std::chrono::high_resolution_clock::now();
        
        this->ff = std::make_shared<const font::font_factory>();
        
        this->fps_text = std::make_shared<shape::text>(math::vector2d{(int)this->width-70,(int)this->height-10}, "FPS: 0", this->ff->ARIAL);
        this->fps_text->size = 20;
        this->fps_text->color = color{255, 0, 0};

    }
    
    std::shared_ptr<const font::font_factory> graphic_engine::fonts()
    {
        return this->ff;
    }

    GLFWwindow* graphic_engine::get_window()
    {
        return this->window;
    }

    bool graphic_engine::should_render()
    {
        return this->continue_render;
    }

    void graphic_engine::render()
    {
        // Event loop
        if(!glfwWindowShouldClose(this->window))
        {
            if(this->show_fps)
            {
                auto end = std::chrono::high_resolution_clock::now();
                auto time = (double)std::chrono::duration_cast<std::chrono::microseconds>(end-this->tp).count()/1000000;
                this->tp = std::chrono::high_resolution_clock::now();
                this->fps_text->content = "FPS: " + std::to_string((int)(1/time));
                this->fps_text->draw(this->width, this->height);
            }
            // wipe the drawing surface clear
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            for (const auto &object : this->objects)
            {
                if(object->is_visible)
                    object->draw(this->width, this->height);
            }
            // put the stuff we've been drawing onto the display
            glfwSwapBuffers(this->window);
            // Maintain a certain FPS, To high makes it not smooth, should investigate?
            std::this_thread::sleep_for(std::chrono::microseconds(10000));
        }
        else
        {
            glfwTerminate();
            this->continue_render = false;
        }
    }
    
    void graphic_engine::prepare_draw_for_focus(const unsigned int moved_width, const unsigned int moved_height)
    {
        focus_pos.x += moved_width;
        focus_pos.y += moved_height;
        for(auto &s : this->objects)
        {
            if(!s->is_static)
            {
                s->pos.x += moved_width;
                s->pos.y += moved_height;
            }
        }
    }
    
    math::vector2d graphic_engine::get_focus_pos()
    {
        return this->focus_pos;
    }
}
