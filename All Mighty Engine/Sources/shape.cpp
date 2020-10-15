#include "shape.hpp"

/* Circle */

Circle::Circle() : Circle(5)
{}

Circle::Circle(std::size_t radius) : Circle(radius, Color::White)
{}

Circle::Circle(std::size_t radius, const Color& color) : sf::CircleShape(radius), radius_(radius){
    setFillColor(color);
    setRadius(radius_);
}

void Circle::setRadius(std::size_t radius){
    sf::CircleShape::setRadius(radius);
}

void Circle::setColor(const sf::Color& color){
    setFillColor(color);
}

void Circle::setPosition(const Vector2f& position){

    sf::CircleShape::setPosition(sf::Vector2f(position.x, position.y));
}

void Circle::move(const Vector2f& moveVector){

    sf::CircleShape::move(sf::Vector2f(moveVector.x,moveVector.y));
}

Vector2f const Circle::getSize() const{
    return Vector2f(getRadius(),getRadius());
}

Vector4u const Circle::getBox() const{

    return Vector4u(getPosition().x,getPosition().y,radius_,radius_);
}

/* Square */

Rectangle::Rectangle() : Rectangle(Vector2f(0,0), sf::Color::White){}

Rectangle::Rectangle(const Vector2f& size, const Color& color) : size_(size){
    setFillColor(color);
    sf::RectangleShape::setSize(sf::Vector2f(size_.x,size_.y));
}

void Rectangle::setSize(const Vector2f& size){
    size_ = size;
    sf::RectangleShape::setSize(sf::Vector2f(size_.x,size_.y));
}

void Rectangle::setColor(const Color& color){
    setFillColor(color);
}

void Rectangle::setPosition(const Vector2f& position){

    sf::RectangleShape::setPosition(sf::Vector2f(position.x, position.y));
}

void Rectangle::move(const Vector2f& moveVector){

    sf::RectangleShape::move(sf::Vector2f(moveVector.x,moveVector.y));
}

Vector4u const Rectangle::getBox() const{
    return Vector4u(getPosition().x,getPosition().y,getSize().x,getSize().y);
}
