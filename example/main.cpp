#include <linussjo_engine.hpp>
#include "flappy_world.hpp"
#include "flappy_bird.hpp"
#include "start_world.hpp"
#include <input_factory.hpp>



const unsigned int width{1000}, height{750};

int main()
{
    engine::linussjo_engine *le = &engine::linussjo_engine::getInstance();
    le->show_fps = true;
<<<<<<< HEAD
    le->title = "Flappy test";
    le->width = width;
    le->height = height;
    le->start((
        [](const std::shared_ptr<engine::graphic::graphic_engine> &ge, const unsigned int w, const unsigned int h)
        {
            auto s = std::make_shared<start_world>(ge, width,height);
            auto f = std::make_shared<flappy_world>(ge, width*5,height);
            auto fb = std::make_shared<flappy_bird>(ge, width,height);
            s->next = f;
            f->next = fb;
            fb->next = s;

            return s;
        }
    ));
=======
    auto s = std::make_shared<start_world>(width,height);
    auto f = std::make_shared<flappy_world>(width,height);
    auto fb = std::make_shared<flappy_bird>(width,height);
    s->next = f;
    f->next = fb;
    fb->next = s;
    
    le->start(s, width, height);
>>>>>>> parent of 7802ecd... fixed new tests and changed responsiblility of creating the window and settings to linussjo_engine from graphic_engine
}
