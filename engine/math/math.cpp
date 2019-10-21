//
//  math.cpp
//  linussjo_engine
//
//  Created by Linus Sjöström on 2019-10-16.
//  Copyright © 2019 Linus Sjöström. All rights reserved.
//

#include "math.hpp"

namespace engine::math
{
    vector2d normal(const vector2d &v1, const vector2d &v2)
    {
        return vector2d {v2.x-v1.x, v2.y-v1.y};
    }
    
    int dot_product(const vector2d &v1, const vector2d &v2)
    {
        return v1.x*v2.x + v1.y*v2.y;
    }
    
    int vector_abs(const vector2d &v)
    {
        return std::sqrt(v.x*v.x + v.y*v.y);
    }
}
