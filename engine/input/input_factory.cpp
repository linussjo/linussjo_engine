#include "input_factory.hpp"

namespace engine::input
{
    input_factory::input_factory() {}
    input_factory::~input_factory() {}

    std::shared_ptr<input_handler> input_factory::get(GLFWwindow* window) 
    {
        if(this->input_handlers.find(window) == this->input_handlers.end())
        {
            this->input_handlers.insert({window, std::make_shared<input_handler>(window, input_factory::key_callback,
             input_factory::mouse_callback, input_factory::cursor_moved_callback)});
        }
        return this->input_handlers[window];
    }

    input_factory& input_factory::get_factory() 
    {
        static input_factory instance;

        return instance;
    }

    void input_factory::key_callback(GLFWwindow* window, int button, int scancode, int action, int mods)
    {
        const auto input_handler = input_factory::get_factory().input_handlers[window];

        input_handler->get_on_key_input()(window, button, scancode, action, mods);
    }

    void input_factory::mouse_callback(GLFWwindow* window, int button, int action, int mods)
    {
        const auto input_handler = input_factory::get_factory().input_handlers[window];
        const auto cursor_pos = input_handler->get_cursor_position();

        if(button == GLFW_MOUSE_BUTTON_1 && action == GLFW_RELEASE)
        {
            for(auto &component : input_handler->get_components())
            {
                if(component->did_get_pressed(cursor_pos))
                {
                    component->on_key_press();
                }
            }
        }

        input_handler->get_on_mouse_input()(window, button, action, mods);
    }

    void input_factory::cursor_moved_callback(GLFWwindow* window, double x, double y)
    {
        const auto input_handler = input_factory::get_factory().input_handlers[window];
        input_handler->set_cursor_position({x,y});
        input_handler->get_on_cursor_moved()(window, input_handler->get_cursor_position());
    }
}