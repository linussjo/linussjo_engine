//
//  thread_dispatcher.cpp
//  linussjo_engine
//
//  Created by Linus Sjöström on 2019-10-01.
//  Copyright © 2019 Linus Sjöström. All rights reserved.
//

#include "thread_dispatcher.hpp"

template <class Fn, class... Args>
thread_dispatcher::thread_dispatcher(Fn&& base, Args&&... args) :
    t(base, args...){}

//template <class Fn, class... Args>
void thread_dispatcher::run()
{
    this->t.detach();
}

void thread_dispatcher::runOnMainThread()
{
    this->t.join();
}
