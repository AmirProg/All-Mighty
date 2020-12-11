#include "shape.hpp"

/* Circle */

am::Circle::Circle() : Circle(5)
{}

am::Circle::Circle(std::size_t radius) : Circle(radius, Color::White)
{}

am::Circle::Circle(std::size_t radius, const Color& color) : sf::CircleShape(radius), radius_(radius){
    setFillColor(color);
    setRadius(radius_);
}

void am::Circle::setRadius(std::size_t radius){
    sf::CircleShape::setRadius(radius);
}

void am::Circle::setColor(const sf::Color& color){
    setFillColor(color);
}

void am::Circle::setPosition(const Vector2f& position){

    sf::CircleShape::setPosition(sf::Vector2f(position.x, position.y));
}

void am::Circle::move(const Vector2f& moveVector){

    sf::CircleShape::move(sf::Vector2f(moveVector.x,moveVector.y));
}

am::Vector2f const am::Circle::getSize() const{
    return Vector2f(getRadius(),getRadius());
}

am::Vector4f const am::Circle::getBox() const{

    return Vector4f(getPosition().x,getPosition().y,radius_,radius_);
}

void am::Circle::update()
{}

/* Square */

am::Rectangle::Rectangle() : Rectangle(Vector2f(0,0), sf::Color::White){}

am::Rectangle::Rectangle(const Vector2f& size) : Rectangle(size, Color::White)
{}

am::Rectangle::Rectangle(const Vector2f& size, const Color& color) : size_(size){
    setFillColor(color);
    sf::RectangleShape::setSize(sf::Vector2f(size_.x,size_.y));
}

void am::Rectangle::setSize(const Vector2f& size){
    size_ = size;
    sf::RectangleShape::setSize(sf::Vector2f(size_.x,size_.y));
}

void am::Rectangle::setColor(const Color& color){
    setFillColor(color);
}

void am::Rectangle::setPosition(const Vector2f& position){

    sf::RectangleShape::setPosition(sf::Vector2f(position.x, position.y));
}

void am::Rectangle::move(const Vector2f& moveVector){

    sf::RectangleShape::move(sf::Vector2f(moveVector.x,moveVector.y));
}

am::Vector2f const am::Rectangle::getSize() const{

    return Vector2f(getBox().w, getBox().h);
}

am::Vector4f const am::Rectangle::getBox() const{
    return Vector4f(getPosition().x,getPosition().y,sf::RectangleShape::getSize().x, sf::RectangleShape::getSize().y);
}

void am::Rectangle::update()
{}
