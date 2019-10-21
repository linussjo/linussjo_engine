//
//  thread_dispatcher.hpp
//  linussjo_engine
//
//  Created by Linus Sjöström on 2019-10-01.
//  Copyright © 2019 Linus Sjöström. All rights reserved.
//

#ifndef thread_dispatcher_hpp
#define thread_dispatcher_hpp

#include <stdio.h>
#include <thread>

class thread_dispatcher{
public:
    template <class Fn, class... Args>
    thread_dispatcher(Fn&&, Args&&... args);
    void run();
    void runOnMainThread();
private:
    std::thread t;
    
};

#endif /* thread_dispatcher_hpp */
