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
<<<<<<< HEAD

        void start(const std::function<std::shared_ptr<world>(const std::shared_ptr<engine::graphic::graphic_engine> &,
                                             const unsigned int, const unsigned int)> &);
=======
        std::shared_ptr<world> active_world;
        void start(const std::shared_ptr<world> &, const unsigned int, const unsigned int);
        void start(const unsigned int, const unsigned int);
>>>>>>> parent of 7802ecd... fixed new tests and changed responsiblility of creating the window and settings to linussjo_engine from graphic_engine
        bool show_fps = false;
        unsigned int width{800}, height{600};
        std::string title{""};
        
    private:
        linussjo_engine() {};
        static void window_focus_callback(GLFWwindow* window, int focused);
        std::shared_ptr<world> active_world;
        std::shared_ptr<graphic::graphic_engine> ge;
<<<<<<< HEAD
        GLFWwindow* window;
=======
        // C++ 03
        // ========
        // Don't forget to declare these two. You want to make sure they
        // are unacceptable otherwise you may accidentally get copies of
        // your singleton appearing.
        
>>>>>>> parent of 7802ecd... fixed new tests and changed responsiblility of creating the window and settings to linussjo_engine from graphic_engine
    };
}
#endif /* linussjo_engine_hpp */
