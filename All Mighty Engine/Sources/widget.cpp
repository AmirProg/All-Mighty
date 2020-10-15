#include "widget.hpp"

Widget::Widget() : Widget(Vector2u(0,0),Vector2f(0,0))
{}

Widget::Widget(const Vector2u& size, const Vector2f& position) : size_(size), position_(position)
{}

Widget::Widget(const Widget&& widget) : Widget(std::move(widget.size_), std::move(widget.position_))
{}

Widget& Widget::operator=(const Widget&& widget){

    *this = widget;
    return *this;
}

void Widget::draw(sf::RenderTarget& target, sf::RenderStates states) const{

    target.draw(*this, states);
}
