#include "concreteEntity.hpp"

am::ConcreteEntity::ConcreteEntity(sf::Transformable& transEntity, PhyEntity& phyEntity) : entity_(std::make_pair(std::ref(transEntity), std::ref(phyEntity)))
{}

void am::ConcreteEntity::bindTransEntity(sf::Transformable& transEntity){

    entity_.first = transEntity;
}
void am::ConcreteEntity::bindPhyEntity(PhyEntity& phyEntity){

    entity_.second = phyEntity;
}

void am::ConcreteEntity::move(){

    entity_.first.move(entity_.second.getVelocity().x, entity_.second.getVelocity().y);
}

sf::Transformable& am::ConcreteEntity::first(){

    return entity_.first;
}

am::PhyEntity& am::ConcreteEntity::second(){

    return entity_.second;
}
