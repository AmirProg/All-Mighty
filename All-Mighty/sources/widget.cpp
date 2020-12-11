#include "widget.hpp"

am::Widget::Widget() : Widget(Vector2f(0,0),Vector2f(0,0))
{}

am::Widget::Widget(const Vector2f& size, const Vector2f& position) : size_(size), position_(position)
{}

inline bool& am::Widget::isClicked(InputManager& input, Window& window) noexcept{

    if(Collision::intersectMouse(*this, window) && input.click())
        clicked_ = true;

    if(!(Collision::intersectMouse(*this, window)) && input.click())
        clicked_ = false;

    return clicked_;
}
inline bool am::Widget::clicked() const noexcept{

    return clicked_;
}


bool& am::Widget::isMoved() noexcept{

    return moved_;
}

void am::Widget::draw(sf::RenderTarget& target, sf::RenderStates states) const{

    target.draw(*this, states);
}
