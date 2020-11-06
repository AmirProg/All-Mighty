#include "concreteEntity.hpp"

ConcreteEntity::ConcreteEntity(sf::Transformable& transEntity, PhyEntity& phyEntity) : entity_(std::make_pair(std::ref(transEntity), std::ref(phyEntity)))
{}

void ConcreteEntity::bindTransEntity(sf::Transformable& transEntity){

    entity_.first = transEntity;
}
void ConcreteEntity::bindPhyEntity(PhyEntity& phyEntity){

    entity_.second = phyEntity;
}

void ConcreteEntity::move(){

    entity_.first.move(entity_.second.getVelocity().x, entity_.second.getVelocity().y);
}

sf::Transformable& ConcreteEntity::first(){

    return entity_.first;
}

PhyEntity& ConcreteEntity::second(){

    return entity_.second;
}
