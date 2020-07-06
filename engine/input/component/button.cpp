
#include "button.hpp"

namespace engine::input::component
{
    button::~button(){}

    button::button(const std::string &text, const math::point2d &position)
    {
        this->position = position;
        this->set_shape(std::make_shared<engine::graphic::shape::rectangle>(position, this->height, this->width));
        engine::graphic::font::font_factory ff;
        auto text_pos = position;
        text_pos.y += this->height/6;
        text_pos.x += this->width/8;
        this->text_shape = std::make_shared<engine::graphic::shape::text>(text_pos, text, ff.ARIAL);
        this->text_shape->z_index = this->get_shape()->z_index+1;
    }

    bool button::did_get_pressed(const engine::math::point2d &pos)
    {
        return pos.x > this->position.x && pos.x < this->position.x + this->width
            && pos.y > this->position.y && pos.y < this->position.y + this->height;
    }

    void button::set_text(const std::string &text)
    {
        this->text_shape->content = text;
    }

    void button::set_size(const unsigned int width, const unsigned int heigth)
    {
        // we know that the shape in this case is rectangle
        auto rec = std::dynamic_pointer_cast<engine::graphic::shape::rectangle>(this->get_shape());
        rec->width = width;
        rec->heigth = heigth;
    }

    std::vector<std::shared_ptr<engine::graphic::shape::shape>> button::get_shapes()
    {
        std::vector v = {this->get_shape()};
        v.push_back(this->text_shape);
        
        return v;
    }

    void button::set_shape(const std::shared_ptr<engine::graphic::shape::rectangle> &rec)
    {
        component::set_shape(rec);
    }

    void button::set_text_color(const engine::graphic::color &color)
    {
        this->text_shape->color = color;
    }

    void button::set_background_color(const engine::graphic::color &color)
    {
        this->get_shape()->color = color;
    }

    void button::set_z_index(const long long &z_index)
    {
        this->get_shape()->z_index = z_index;
        this->text_shape->z_index = z_index+1;
    }
}
