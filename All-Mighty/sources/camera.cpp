#include "camera.hpp"

am::Camera::~Camera() noexcept{

    views_.clear();
}

void am::Camera::setCenter(const am::Vector2f& center){

    commonCenterPosition_ = center;

    for(auto& i : views_)
        i.second.setCenter(commonCenterPosition_.x, commonCenterPosition_.y);
}

void am::Camera::setCenter(const sf::Transformable& object){

    commonCenterPosition_ = Vector2f(object.getPosition().x, object.getPosition().y);

    for(auto& i : views_)
        i.second.setCenter(commonCenterPosition_.x, commonCenterPosition_.y);
}

void am::Camera::setCenter(int key, const am::Vector2f& center){

    auto it { views_.find(key) }; // Iterator on the element
    assert((it != views_.end()) && "Fail no view found");

    it->second.setCenter(center.x, center.y);
}

void am::Camera::setCenter(int key, const sf::Transformable& object){

    setCenter(key, Vector2f(object.getPosition().x, object.getPosition().y));
}

void am::Camera::move(const am::Vector2f& moveVector){

    for(auto& i : views_)
        move(i.first, moveVector);
}

void am::Camera::move(int key, const am::Vector2f& moveVector){

    auto it { views_.find(key) }; // Iterator on the element
    assert((it != views_.end()) && "Fail view no found");

    it->second.move(moveVector.x, moveVector.y);
}

void am::Camera::zoom(float factor){

    for(auto& i : views_)
        zoom(i.first, factor);
}


void am::Camera::zoom(int key, float factor){

    this->operator[](key).zoom(factor);
}

void am::Camera::addView(int key, const am::Vector2f& center, const am::Vector2f& rectDim){

    views_.insert({ key, sf::View(sf::Vector2f(center.x,center.y), sf::Vector2f(rectDim.x, rectDim.y)) });
}

void am::Camera::addView(int key, const sf::View& view){

    views_.insert( {key, view} );
}

void am::Camera::setViewPosition(int key, const am::Vector4f& position){

    this->operator[](key).setViewport(sf::FloatRect(position.x, position.y, position.w, position.h));
}

void am::Camera::setViewType(int key, Type type){

    if(type == Type::None)
        setViewPosition(key, Vector4f(0, 0, 0, 0));
    else if(type == Type::Minimap)
        setViewPosition(key, Vector4f(0.75, 0.75, 0.25, 0.25));
    else if(type == Type::SplitVerticalRight)
        setViewPosition(key, Vector4f(0.5, 0, 0.5, 1));
    else if(type == Type::SplitVerticalLeft)
        setViewPosition(key, Vector4f(0, 0, 0.5, 1));
    else if(type == Type::Up)
        setViewPosition(key, Vector4f(0.5, 0, 0.75, 0.75));
}

std::size_t am::Camera::getNumberView() const{

    return std::size(views_);
}

sf::View& am::Camera::operator[](int key){

    auto it { views_.find(key) }; // Iterator on the element
    assert((it != views_.end()) && "Fail view no found"); // If the iterator has reached the end then there is no element associated to that key

    return it->second;
}
