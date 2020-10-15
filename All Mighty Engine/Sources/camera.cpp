#include "camera.hpp"

Camera::Camera(const Camera&& camera) : commonCenterPosition_(std::move(camera.commonCenterPosition_)),
                                        views_(std::move(camera.views_))
{}

Camera& Camera::operator=(const Camera&& camera){

    *this = std::move(camera);
    return *this;
}

Camera::~Camera(){

    views_.clear();
}

void Camera::setCenter(const Vector2u& center){

    commonCenterPosition_ = center;

    for(auto& i : views_)
        i.second.setCenter(commonCenterPosition_.x, commonCenterPosition_.y);
}

void Camera::setCenter(const sf::Transformable& object){

    commonCenterPosition_ = Vector2u(object.getPosition().x, object.getPosition().y);

    for(auto& i : views_)
        i.second.setCenter(commonCenterPosition_.x, commonCenterPosition_.y);
}

void Camera::setCenter(int key, const Vector2u& center){

    auto it { views_.find(key) }; // Iterator on the element
    assert((it != views_.end()) && "Fail no view found");

    it->second.setCenter(center.x, center.y);
}

void Camera::setCenter(int key, const sf::Transformable& object){

    auto it { views_.find(key) }; // Iterator on the element
    assert((it != views_.end()) && "Fail no view found");

    it->second.setCenter(object.getPosition().x, object.getPosition().y);
}

void Camera::move(const Vector2f& moveVector){

    for(auto& i : views_)
        move(i.first, moveVector);
}

void Camera::move(int key, const Vector2f& moveVector){

    auto it { views_.find(key) }; // Iterator on the element
    assert((it != views_.end()) && "Fail view no found");

    it->second.move(moveVector.x, moveVector.y);
}

void Camera::zoom(float factor){

    for(auto& i : views_)
        zoom(i.first, factor);
}


void Camera::zoom(int key, float factor){

    this->operator[](key).zoom(factor);
}

void Camera::addView(int key, const Vector2u& center, const Vector2u& rectDim){

    views_.insert({ key, sf::View(sf::Vector2f(center.x,center.y), sf::Vector2f(rectDim.x, rectDim.y)) });
}

void Camera::addView(int key, const sf::View& view){

    views_.insert( {key, view} );
}

void Camera::setViewPosition(int key, const Vector4f& position){

    this->operator[](key).setViewport(sf::FloatRect(position.x, position.y, position.w, position.h));
}

void Camera::setViewType(int key, Type type){

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

int Camera::getNumberView() const{

    return std::size(views_);
}

sf::View& Camera::operator[](int key){

    auto it { views_.find(key) }; // Iterator on the element
    assert((it != views_.end()) && "Fail view no found"); // If the iterator has reached the end then there is no element associated to that key

    return it->second;
}
