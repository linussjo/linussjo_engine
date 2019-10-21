//
//  position.hpp
//  linussjo_engine
//
//  Created by Linus Sjöström on 2019-09-22.
//  Copyright © 2019 Linus Sjöström. All rights reserved.
//

#ifndef position_hpp
#define position_hpp

#include <stdio.h>

namespace engine::math
{
    struct vector2d{
        int x{}, y{};
    };

    struct vector2f{
        float x{}, y{};
    };
}
#endif /* position_hpp */
