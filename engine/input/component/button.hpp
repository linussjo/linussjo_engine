//
//  button.hpp
//  linussjo_engine
//
//  Created by Linus Sjöström on 2019-09-22.
//  Copyright © 2019 Linus Sjöström. All rights reserved.
//

#ifndef button_hpp
#define button_hpp

#include <stdio.h>
#include <memory>
#include <vector>

#include "vector2d.hpp"
#include "color.hpp"
#include "text.hpp"
#include "rectangle.hpp"
#include "font_factory.hpp"
#include "component.hpp"

namespace engine::input::component
{
    class button : public component{
    public:
        button(const std::string &, const math::point2d &);
        virtual ~button();

        bool did_get_pressed(const engine::math::point2d &);
        void set_text(const std::string &);
        void set_size(const unsigned int, const unsigned int);

        virtual std::vector<std::shared_ptr<engine::graphic::shape::shape>> get_shapes();
        void set_shape(const std::shared_ptr<engine::graphic::shape::rectangle> &);

        void set_text_color(const engine::graphic::color &);
        void set_background_color(const engine::graphic::color &);
        void set_z_index(unsigned long);

    
    private:
        unsigned int width{300}, height{300};
        std::shared_ptr<engine::graphic::shape::text> text_shape;

    };
}
#endif /* Shape_hpp */
