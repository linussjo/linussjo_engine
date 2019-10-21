# linussjo_engine
A game engine for 2D game development

# How to make a world
Create a class that inherits from engine::world.  

example:
```
class example_world: public engine::world{
public:
    start_world(unsigned int, unsigned int);
    void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
protected:
    void first_prepare(engine::graphic::graphic_engine &ge, engine::physic::physics_engine &pe);
    void prepare(engine::graphic::graphic_engine &ge, engine::physic::physics_engine &pe);
    void on_iteration(engine::graphic::graphic_engine &ge, engine::physic::physics_engine &pe);
};
```
  
Then in main() get the singleton linussjo_engine and add it as the next world.  

example:
```
#include "linussjo_engine.hpp"
#include "example_world.hpp"

const unsigned int window_width{1000}, window_height{750};

int main()
{
    engine::linussjo_engine *le = &engine::linussjo_engine::getInstance();
    le->show_fps = true;
    auto s = std::make_shared<example_world>(window_width,window_height);
    auto f = std::make_shared<flappy_world>(window_width,window_height);
    s->next = f;
    f->next = s;
    
    le->start(s, window_width, window_height);
}
```
## To build it
cmake .  
make
### To run it
./test_game

## Dependicies 
FreeType2
OpenGL
GLFW
GLEW
GLUT

## License

MIT
