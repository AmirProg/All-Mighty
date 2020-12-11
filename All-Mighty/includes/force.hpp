#ifndef FORCE_HPP_INCLUDED
#define FORCE_HPP_INCLUDED

#include "concreteEntity.hpp"
#include "stopWatch.hpp"
#include <functional>

/**************************************************************************************
*
* ~ Force class ~
*
* => Gives physical forces
*
* You can add a ConcreteEntity object then the Force object will be applied to it
*
* Ex : Gravity Force :
*
* Force gravity { Force::Type::Perso, 9.81, Vector2f(0, -1) };
* -> Notice that you can create it like : Force gravity { Force::Type::Gravity };
*
* gravity.addEntity(entity1);
* gravity.addEntity(entity2);
*
* => In the main loop : gravity.update();
*
**************************************************************************************/

namespace am {

    class Force : NonCopyable {

    public:

        enum class Type { None, Gravity, Perso }; // Pre-type (some classics forces) (TODO)

        Force() = default;
        Force(Type type);
        Force(float norm, const Vector2f& dir);
        virtual ~Force();
        void addEntity(ConcreteEntity& concreteEntity); // Add an entity to the Vector
        void setNorm(float norm); // Sets the norm of the vector
        void setDirection(const Vector2f& dir); // Sets the direction of the vector
        void reset();
        Vector2f getMoveVector() const;
        void apply(ConcreteEntity& entity); // It will apply the force every seconds to one entity
        void update(); // Apply the force to every subject entities

    private:
        Type type_; // The type of the law
        float norm_;
        Vector2f dir_;
        std::vector<std::reference_wrapper<ConcreteEntity>> entities_; // Entities subject to the law
        StopWatch time_;
    };
}

#endif // FORCE_HPP_INCLUDED
