//
//  world_state.h
//  linussjo_engine
//
//  Created by Linus Sjöström on 2019-10-04.
//  Copyright © 2019 Linus Sjöström. All rights reserved.
//

#ifndef world_state_h
#define world_state_h

class world_shared_state{
public:
    world_state(std::string id) : id(id) {}
    const std::string id;
}

#endif /* world_state_h */
