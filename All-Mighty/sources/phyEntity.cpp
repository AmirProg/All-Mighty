#include "phyEntity.hpp"

am::PhyEntity::PhyEntity() : PhyEntity(Vector2f(0,0), 0)
{}

am::PhyEntity::PhyEntity(const Vector2f& velocityVector, float mass) : velocityVector_(velocityVector), mass_(mass)
{}

void am::PhyEntity::setVelocityMax(const Vector2f& velocity){

    velocityMax_ = velocity;
}

void am::PhyEntity::setVelocity(const Vector2f& velocityVector){

    velocityVector_ = velocityVector;

    /*if(velocityVector_.x > velocityMax_.x)
        velocityVector_.x = velocityMax_.x;
    if(velocityVector_.y > velocityMax_.y)
        velocityVector_.y = velocityMax_.y;*/
}

void am::PhyEntity::setMass(float mass){

    mass_ = mass;
}

void am::PhyEntity::impulse(const Vector2f& impulseVector, float norm) {

    setVelocity(Vector2f(velocityVector_.x + impulseVector.x * norm / mass_, velocityVector_.y + impulseVector.y * norm / mass_));
}

am::Vector2f am::PhyEntity::getVelocity() const{

    return velocityVector_;
}

float am::PhyEntity::getMass() const{

    return mass_;
}
