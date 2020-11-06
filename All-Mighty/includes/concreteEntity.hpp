#ifndef CONCRETEENTITY_HPP_INCLUDED
#define CONCRETEENTITY_HPP_INCLUDED

#include "visualEntity.hpp"
#include "phyEntity.hpp"
#include "nonCopyable.hpp"
#include <utility>
#include <functional>
#include <SFML/Graphics.hpp>

/*****************************************************************
*
*
* ~ ConcreteEntity class ~
*
* Bind a sf::Transformable object and a PhyEntity object
*
* You can use the PhyLaw class on ConcreteEntity objects.
*
*
*****************************************************************/

class ConcreteEntity : NonCopyable{

public:
    ConcreteEntity() = delete;
    ConcreteEntity(sf::Transformable& transEntity, PhyEntity& phyEntity);
    ConcreteEntity(ConcreteEntity&&) noexcept = default;
    ConcreteEntity& operator=(ConcreteEntity&&) noexcept = default;
    virtual ~ConcreteEntity() = default;
    void bindTransEntity(sf::Transformable& transEntity);
    void bindPhyEntity(PhyEntity& phyEntity);
    void move(); // Move the concrete entity according to the velocity of the physcal object and the laws the object is submitted to
    sf::Transformable& first(); // Gives the Transformable object
    PhyEntity& second(); // Gives the Physic object

private:
    std::pair<sf::Transformable&, PhyEntity&> entity_;
};

#endif // CONCRETEENTITY_HPP_INCLUDED
