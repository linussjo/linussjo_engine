//
//  linussjo_engine.hpp
//  linussjo_engine
//
//  Created by Linus Sjöström on 2019-09-30.
//  Copyright © 2019 Linus Sjöström. All rights reserved.
//

#ifndef linussjo_engine_hpp
#define linussjo_engine_hpp

#include <stdio.h>
#include <vector>
#include <memory>
#include "world.hpp"

namespace engine
{
    class linussjo_engine {
    typedef linussjo_engine le;
    public:
        static le& getInstance();

        linussjo_engine(le const&) = delete; // Don't Implement
        void operator=(le const&) = delete; // Don't implement

        void start(const std::function<std::shared_ptr<world>(const std::shared_ptr<engine::graphic::graphic_engine> &,
                                             const unsigned int, const unsigned int)> &);
        bool show_fps = false;
        unsigned int width{800}, height{600};
        std::string title{""};
        
    private:
        linussjo_engine() {};
        static void window_focus_callback(GLFWwindow* window, int focused);
        std::shared_ptr<world> active_world;
        std::shared_ptr<graphic::graphic_engine> ge;
        GLFWwindow* window;
    };
}
#endif /* linussjo_engine_hpp */
