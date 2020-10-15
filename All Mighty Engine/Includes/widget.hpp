#ifndef WIDGET_HPP_INCLUDED
#define WIDGET_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include "vector.hpp"

/************************************
*
*
*
* ~ Widget ABSTRACT class~
*
* Base class of any Widgets type
*      -> (Button, ProgressBar...)
*
*
*
*************************************/

class Widget : public sf::Drawable, public sf::Transformable{

public:
    Widget();
    Widget(const Vector2u& size, const Vector2f& position);
    Widget(const Widget&) = default;
    Widget(const Widget&&);
    Widget& operator=(const Widget&&);
    ~Widget() = default;
    Widget& operator=(const Widget&) = default;
    virtual void setSize(const Vector2u& newSize) = 0;
    virtual void setPosition(const Vector2f& newPosition) = 0;
    virtual Vector2u getSize() const = 0;
    virtual Vector2f getPosition() const = 0;
    virtual Vector4f getBox() const = 0;

protected:
    Vector2u size_;
    Vector2f position_;
    virtual void update() = 0;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif // WIDGET_HPP_INCLUDED
