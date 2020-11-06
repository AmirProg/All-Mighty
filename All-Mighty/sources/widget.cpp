#include "widget.hpp"

Widget::Widget() : Widget(Vector2f(0,0),Vector2f(0,0))
{}

Widget::Widget(const Vector2f& size, const Vector2f& position) : size_(size), position_(position)
{}

inline bool& Widget::isClicked(InputManager& input, Window& window) noexcept{

    if(Collision::intersectMouse(*this, window) && input.click())
        clicked_ = true;

    if(!(Collision::intersectMouse(*this, window)) && input.click())
        clicked_ = false;

    return clicked_;
}
inline bool Widget::clicked() const noexcept{

    return clicked_;
}


bool& Widget::isMoved() noexcept{

    return moved_;
}

void Widget::draw(sf::RenderTarget& target, sf::RenderStates states) const{

    target.draw(*this, states);
}
