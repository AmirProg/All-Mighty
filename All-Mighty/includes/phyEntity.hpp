#ifndef PHYENTITY_HPP_INCLUDED
#define PHYENTITY_HPP_INCLUDED

#include "vector.hpp"

/******************************************
*
*
* ~ PhyEntity class ~
*
* Represents a physical entity which can be
* submitted to some physical laws
*
*
*******************************************/

namespace am {

    class PhyEntity {

    public:
        PhyEntity();
        PhyEntity(const PhyEntity&) = default;
        PhyEntity& operator=(const PhyEntity&) = default;
        PhyEntity(PhyEntity&&) noexcept = default;
        PhyEntity& operator=(PhyEntity&&) noexcept = default;
        PhyEntity(const Vector2f& velocityVector, float mass);
        virtual ~PhyEntity() = default;
        void setVelocity(const Vector2f&);
        void setVelocityMax(const Vector2f&);
        void setMass(float mass);
        void impulse(const Vector2f& impulseVector, float norm); // Add an impulse on a physical entity (jump ?)
        Vector2f getVelocity() const;
        float getMass() const;

    private:
        Vector2f velocityVector_;
        Vector2f velocityMax_;
        float mass_;
    };
}

#endif // PHYENTITY_HPP_INCLUDED
