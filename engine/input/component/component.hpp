//
//  component.hpp
//  linussjo_engine
//
//  Created by Linus Sjöström on 2019-02-19.
//  Copyright © 2019 Linus Sjöström. All rights reserved.
//

#ifndef component_hpp
#define component_hpp

#include <stdio.h>
#include <memory>

#include "shape.hpp"
#include "point.hpp"

namespace engine::input::component
{
    class component{
    public:
        component(){};
        virtual ~component(){};

        virtual bool did_get_pressed(const engine::math::point2d &) = 0;

        std::function<void()> on_key_press = [](){}; // do nothing by default

        math::point2d position;

        virtual std::vector<std::shared_ptr<engine::graphic::shape::shape>> get_shapes();
    
    protected:
        std::shared_ptr<engine::graphic::shape::shape> get_shape();
        void set_shape(const std::shared_ptr<engine::graphic::shape::shape> &);

    private:
        std::shared_ptr<engine::graphic::shape::shape> shape;

    };
}
#endif /* compenents_hpp */
