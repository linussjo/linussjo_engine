
#ifndef input_factory_hpp
#define input_factory_hpp

#include <stdio.h>
#include <memory>
#include <map>
#include "input_handler.hpp"

namespace engine::input
{
    /**
     * input_factory uses the singleton design pattern
    **/
    class input_factory
    {
    public:
        virtual ~input_factory();

        std::shared_ptr<input_handler> get(GLFWwindow*);


        static input_factory& get_factory();

        input_factory(input_factory const&) = delete;
        void operator=(input_factory const&) = delete;
    
    private:
        input_factory();
        
        static void key_callback(GLFWwindow*, int, int, int, int);
        static void mouse_callback(GLFWwindow*, int, int, int);
        static void cursor_moved_callback(GLFWwindow*, double, double);

        std::map<GLFWwindow*, std::shared_ptr<input_handler>> input_handlers;

    };
}
#endif /* input_factory_hpp */