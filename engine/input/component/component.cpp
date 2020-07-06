
#include "component.hpp"

namespace engine::input::component
{

    std::shared_ptr<engine::graphic::shape::shape> component::get_shape() 
    {
        return this->shape;
    }

    void component::set_shape(const std::shared_ptr<engine::graphic::shape::shape> &shape) 
    {
        this->shape = shape;
    }

    std::vector<std::shared_ptr<engine::graphic::shape::shape>> component::get_shapes()
    {
        std::vector v = {this->shape};
        return v;
    }
}
