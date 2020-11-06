#ifndef WIDGET_HPP_INCLUDED
#define WIDGET_HPP_INCLUDED

#include "visualEntity.hpp"
#include "vector.hpp"
#include "collision.hpp"
#include "inputManager.hpp"

/***************************************
*                                      *
*                                      *
* ~ Widget ABSTRACT class~             *
*                                      *
* Base class of any Widget             *
*      -> (Button, TextBox...)         *
*                                      *
*                                      *
***************************************/

class Widget : public sf::Drawable, public sf::Transformable, public VisualEntity{

public:

    Widget();
    Widget(const Vector2f& size, const Vector2f& position);
    Widget(const Widget&) = default;
    Widget(Widget&&) noexcept = default;
    Widget& operator=(Widget&&) noexcept = default;
    virtual ~Widget() = default;
    Widget& operator=(const Widget&) = default;
    virtual void setSize(const Vector2f& newSize) = 0;
    virtual void setPosition(const Vector2f& newPosition) = 0;
    virtual Vector2f getSize() const = 0;
    virtual Vector2f getPosition() const = 0;
    virtual Vector4f getBox() const = 0;
    virtual inline bool& isClicked(InputManager& input, Window& window) noexcept;
    virtual inline bool clicked() const noexcept;
    bool& isMoved() noexcept;

protected:

    Vector2f size_;
    Vector2f position_;
    bool moved_ { false };
    bool clicked_ { false };

    virtual void update() = 0;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif // WIDGET_HPP_INCLUDED
