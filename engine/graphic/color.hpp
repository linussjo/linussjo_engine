//
//  color.hpp
//  linussjo_engine
//
//  Created by Linus Sjöström on 2019-09-23.
//  Copyright © 2019 Linus Sjöström. All rights reserved.
//

#ifndef color_hpp
#define color_hpp

#include <stdio.h>
#include "stdint.h"
namespace engine::graphic
{
    struct color {
        uint8_t r,g,b;
    };
    #define COLOR_RED color{255,0,0};
    #define COLOR_GREEN color{0,255,0};
    #define COLOR_BLUE color{0,0,255};
}

#endif /* color_hpp */
