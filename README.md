# linussjo_engine
A game engine for 2D game development

# How to make a world
Inherit from engine::world

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
