#include "force.hpp"
#include <iostream>
Force::Force(Type type) : type_(type), time_(StopWatch::Accuracy::Seconds) {

    if (type_ == Type::Gravity) {
        norm_ = 9.81;
        dir_ = Vector2f(0, -1);
    }

    time_.start();
    update();
}

Force::Force(float norm, const Vector2f& dir) : norm_(norm), dir_(dir), time_(StopWatch::Accuracy::Seconds){

    time_.start();
    update();
}

Force::~Force()
{ entities_.clear(); }

void Force::addEntity(ConcreteEntity& concreteEntity){

    entities_.push_back(concreteEntity);
    update();
}

void Force::setNorm(float norm){

    norm_ = norm;
    update();
}

void Force::setDirection(const Vector2f& dir){

    dir_ = dir;
    update();
}

void Force::reset() {
      
    time_.restart();
}

Vector2f Force::getMoveVector() const{

    return Vector2f(-norm_*dir_.x, -norm_*dir_.y);
}

void Force::apply(ConcreteEntity& entity){

    float delta{ static_cast<float>(time_.getElapsedTime()) };

    Vector2f accel{ norm_ , norm_ };
    Vector2f velocity{ accel.x * delta, accel.y * delta };

    entity.second().setVelocity(Vector2f(velocity.x + entity.second().getVelocity().x, velocity.y + entity.second().getVelocity().y));

    entity.first().setPosition(entity.first().getPosition().x + dir_.x * entity.second().getVelocity().x,
                               entity.first().getPosition().y - dir_.y * entity.second().getVelocity().y);
}

void Force::update(){

    for(auto& i : entities_)
        apply(i.get());
}
