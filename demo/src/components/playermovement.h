#pragma once

#include <ceppengine/components/component.h>
#include <ceppengine/math/vector3.h>

class PlayerMovement : public cepp::Component
{
    public:
        PlayerMovement();

        virtual std::string typeName() const;

        bool canMove() const;
        void setCanMove(bool canMove);

        float speed() const;
        void setSpeed(float speed);

        cepp::Vector3 minBounds() const;
        void setMinBounds(const cepp::Vector3 &bounds);

        cepp::Vector3 maxBounds() const;
        void setMaxBounds(const cepp::Vector3 &bounds);

        cepp::Vector3 movementDirection() const;

    protected:
        virtual void update(float deltaTime);

    private:
        bool mCanMove;
        float mSpeed;
        cepp::Vector3 mMinBounds, mMaxBounds, mMovementDirection;
};
