//
//  graphic_engine.hpp
//  linussjo_engine
//
//  Created by Linus Sjöström on 2019-09-23.
//  Copyright © 2019 Linus Sjöström. All rights reserved.
//

#ifndef graphic_engine_hpp
#define graphic_engine_hpp

#define GLFW_INCLUDE_NONE

#include <stdio.h>
#include <unordered_set>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <memory>
#include <thread>
#include <ft2build.h>
#include <chrono>
#include FT_FREETYPE_H

#include "shape.hpp"
#include "font_factory.hpp"
#include "text.hpp"


namespace engine::graphic
{
    class graphic_engine{
    public:
        graphic_engine(unsigned int, unsigned int);
        graphic_engine(GLFWwindow *, unsigned int, unsigned int);
        std::unordered_set<std::shared_ptr<shape::shape>> objects;
        void prepare_draw_for_focus(const unsigned int, const unsigned int);
        void prepare();
        void render();
        bool should_render();
        GLFWwindow* get_window();
        math::vector2d get_focus_pos();
        bool show_fps{false};
        std::shared_ptr<const font::font_factory> fonts();
    private:
        const unsigned int width, height;
        math::vector2d focus_pos {0,0};
        GLFWwindow* window;
        bool continue_render;
        std::chrono::high_resolution_clock::time_point tp;
        std::shared_ptr<shape::text> fps_text;
        std::shared_ptr<const font::font_factory> ff;
    };
}

#endif /* graphic_engine_hpp */
