#include <linussjo_engine.hpp>
#include "flappy_world.hpp"
#include "flappy_bird.hpp"
#include "start_world.hpp"



const unsigned int width{1000}, height{750};

int main()
{
    engine::linussjo_engine *le = &engine::linussjo_engine::getInstance();
    le->show_fps = true;
    auto s = std::make_shared<start_world>(width,height);
    auto f = std::make_shared<flappy_world>(width*5,height);
    auto fb = std::make_shared<flappy_bird>(width,height);
    s->next = f;
    f->next = fb;
    fb->next = s;
    
    le->start("Flappy Test", s, width, height);
}
