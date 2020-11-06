#include "phyEntity.hpp"

PhyEntity::PhyEntity() : PhyEntity(Vector2f(0,0), 0)
{}

PhyEntity::PhyEntity(const Vector2f& velocityVector, float mass) : velocityVector_(velocityVector), mass_(mass)
{}

void PhyEntity::setVelocityMax(const Vector2f& velocity){

    velocityMax_ = velocity;
}

void PhyEntity::setVelocity(const Vector2f& velocityVector){

    velocityVector_ = velocityVector;

    /*if(velocityVector_.x > velocityMax_.x)
        velocityVector_.x = velocityMax_.x;
    if(velocityVector_.y > velocityMax_.y)
        velocityVector_.y = velocityMax_.y;*/
}

void PhyEntity::setMass(float mass){

    mass_ = mass;
}

void PhyEntity::impulse(const Vector2f& impulseVector, float norm) {

    setVelocity(Vector2f(velocityVector_.x + impulseVector.x * norm / mass_, velocityVector_.y + impulseVector.y * norm / mass_));
}

Vector2f PhyEntity::getVelocity() const{

    return velocityVector_;
}

float PhyEntity::getMass() const{

    return mass_;
}
