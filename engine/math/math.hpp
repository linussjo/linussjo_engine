//
//  math.hpp
//  linussjo_engine
//
//  Created by Linus Sjöström on 2019-10-16.
//  Copyright © 2019 Linus Sjöström. All rights reserved.
//

#ifndef math_hpp
#define math_hpp

#include <stdio.h>
#include <cmath>
#include "vector2d.hpp"

namespace engine::math
{
    vector2d normal(const vector2d &, const vector2d &);
    int dot_product(const vector2d &, const vector2d &);
    int vector_abs(const vector2d &);
}


#endif /* math_hpp */


