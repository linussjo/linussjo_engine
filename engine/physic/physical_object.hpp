//
//  physical_object.hpp
//  linussjo_engine
//
//  Created by Linus Sjöström on 2019-09-25.
//  Copyright © 2019 Linus Sjöström. All rights reserved.
//

#ifndef physical_object_hpp
#define physical_object_hpp

#include <stdio.h>
#include <memory>
#include <unordered_set>
#include <vector>

#include "shape.hpp"
#include "thread_dispatcher.hpp"

namespace engine::physic
{
    class physical_object : public std::enable_shared_from_this<physical_object> {
    public:
        physical_object(std::shared_ptr<graphic::shape::shape> shape);
        ~physical_object();
        
        // functions
        void handle_intersect(const std::shared_ptr<physical_object> &po);
        void handle_out_of_bounds();
        void apply_new_position(const double &time);
        std::vector<math::vector2d> get_points();
        math::vector2d get_mid_pos();
        void clear_shapes();
        bool insert_shape(const std::shared_ptr<graphic::shape::shape> &);
        const std::unordered_set<std::shared_ptr<graphic::shape::shape>> get_shapes();
        
        // variables
        math::vector2d pos{0,0};
        math::vector2f velocity{0,0};
        unsigned int width{0}, height{0};
        bool is_intersectable{false};
        bool is_affected_by_gravity{true};
        bool is_static{false};
        bool is_grounded{false};
        
        // function pointers
        std::function<void(const std::weak_ptr<physical_object> &, const std::shared_ptr<physical_object> &)> on_intersect =
            [](const std::weak_ptr<physical_object> &a, const std::shared_ptr<physical_object> &b){}; // do nothing by default
        std::function<void(const std::weak_ptr<physical_object> &)> on_out_of_bounds =
            [](const std::weak_ptr<physical_object> &a){}; // do nothing by default
        std::function<void(const std::weak_ptr<physical_object> &)> on_fall =
            [](const std::weak_ptr<physical_object> &a){}; // do nothing by default
        std::function<void(const std::weak_ptr<physical_object> &)> on_lands =
            [](const std::weak_ptr<physical_object> &a){}; // do nothing by default

    private:
        std::unordered_set<std::shared_ptr<graphic::shape::shape>> object_shapes;
    };
}

#endif /* physical_object_hpp */
