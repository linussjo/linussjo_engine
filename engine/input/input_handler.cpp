
#include "input_handler.hpp"

namespace engine::input
{
    input_handler::input_handler(GLFWwindow* window, GLFWkeyfun key_callback, GLFWmousebuttonfun mouse_callback, 
        GLFWcursorposfun cursor_callback)
    {
        glfwSetKeyCallback(window, key_callback);
        glfwSetMouseButtonCallback(window, mouse_callback);
        glfwSetCursorPosCallback(window, cursor_callback);
    }

    void input_handler::add_component(const std::shared_ptr<component::component> &component)
    {
        this->components.insert(component);
    }

    std::unordered_set<std::shared_ptr<component::component>> input_handler::get_components()
    {
        return this->components;
    }

    void input_handler::set_on_key_input(const std::function<void(GLFWwindow*, int, int, int, int)> &on_key_input) 
    {
        this->on_key_input = on_key_input;
    }

    std::function<void(GLFWwindow*, int, int, int, int)> input_handler::get_on_key_input()
    {
        return this->on_key_input;
    }

    void input_handler::set_on_mouse_input(const std::function<void(GLFWwindow*, int, int, int)> &on_mouse_input) 
    {
        this->on_mouse_input = on_mouse_input;
    }

    std::function<void(GLFWwindow*, int, int, int)> input_handler::get_on_mouse_input()
    {
        return this->on_mouse_input;
    }

    void input_handler::set_on_cursor_moved(const std::function<void(GLFWwindow*, const engine::math::point2d &)> &on_cursor_moved) 
    {
        this->on_cursor_moved = on_cursor_moved;
    }

    std::function<void(GLFWwindow*, const engine::math::point2d &)> input_handler::get_on_cursor_moved()
    {
        return this->on_cursor_moved;
    }

    void input_handler::set_cursor_position(const engine::math::point2d &position)
    {
        this->cursor_position = position;
    }

    engine::math::point2d input_handler::get_cursor_position()
    {
        return this->cursor_position;
    }
}