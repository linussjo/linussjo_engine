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
  
Then in main() get the singleton linussjo_engine and create the example world and then start it with given window size. The window size and the world size does not need to be the same.    

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
    
    le->start(s, window_width, window_height);
}
```
## To build it
### Engine
In the directory engine, run:  
cmake .  
make  

### example
To create the examples and link the engine:
(First build the static engine library)
In the diectory example, run:  
cmake .  
make  

#### To run the example
./test_game

## Dependencies 
FreeType2  
OpenGL  
GLFW  
GLEW  
GLUT  
C++17  

## License

MIT
