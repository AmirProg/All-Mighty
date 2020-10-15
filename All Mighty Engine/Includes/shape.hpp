#ifndef SHAPE_HPP_INCLUDED
#define SHAPE_HPP_INCLUDED

#include "vector.hpp"
#include <SFML/Graphics.hpp>

/*
* ~ Basic Geometric shapes ~
*
* Useful to add some new functions and an adapted bounding box for collisions management
*/

/* Circle */

typedef sf::Color Color;

class Circle : public sf::CircleShape{

public:
    Circle();
    Circle(const Circle&) = default;
    Circle& operator=(const Circle&) = default;
    Circle(std::size_t radius);
    Circle(std::size_t radius, const Color& color);
    virtual ~Circle() = default;
    void setRadius(std::size_t radius);
    void setColor(const Color& color);
    virtual void setPosition(const Vector2f& position);
    virtual void move(const Vector2f& moveVector);
    Vector2f const getSize() const;
    Vector4u const getBox() const;

private:
    size_t radius_ {};
};

/* Square */

class Rectangle : public sf::RectangleShape{

public:
    Rectangle();
    Rectangle(const Rectangle&) = default;
    Rectangle& operator=(const Rectangle&) = default;
    Rectangle(const Vector2f& size, const Color& color);
    virtual ~Rectangle() = default;
    virtual void setSize(const Vector2f& size);
    void setColor(const Color& color);
    virtual void setPosition(const Vector2f& position);
    virtual void move(const Vector2f& moveVector);
    Vector4u const getBox() const;

private:
    Vector2f size_;
};

#endif // SHAPE_HPP_INCLUDED
