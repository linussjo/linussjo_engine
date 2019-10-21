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
#include "rectangle.hpp"

namespace engine
{
    class linussjo_engine {
    typedef linussjo_engine le;
    public:
        static le& getInstance()
        {
            static le instance; // Guaranteed to be destroyed.
                                  // Instantiated on first use.
            return instance;
        };
        linussjo_engine(le const&) = delete;              // Don't Implement
        void operator=(le const&) = delete; // Don't implement
        std::shared_ptr<world> active_world;
        void start(const std::shared_ptr<world> &, const unsigned int, const unsigned int);
        void start(const unsigned int, const unsigned int);
        bool show_fps = false;
        
    private:
        linussjo_engine() {};
        static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
        static void window_focus_callback(GLFWwindow* window, int focused);
        // C++ 03
        // ========
        // Don't forget to declare these two. You want to make sure they
        // are unacceptable otherwise you may accidentally get copies of
        // your singleton appearing.
        
    };
}
#endif /* linussjo_engine_hpp */
