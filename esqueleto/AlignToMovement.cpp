#include "stdafx.h"
#include "AlignToMovement.h"


#include "character.h"

namespace Math
{
    void NormalizeRadAngle(float& angleInRadians)
    {
        if (angleInRadians < -static_cast<float>(PI) || angleInRadians > static_cast<float>(PI))
        {
            const int rounds = static_cast<int>(fmodf(angleInRadians, PI));
            angleInRadians += 2 * static_cast<float>(PI) * -1.f * static_cast<float>(rounds);
        }
    }

    void NormalizeDegAngle(float& angleInDegrees)
    {
        if (angleInDegrees < -180.f || angleInDegrees > 180.f)
        {
            const int rounds = static_cast<int>(fmodf(angleInDegrees, 180.f));
            angleInDegrees += 2 * 180.f * -1.f * static_cast<float>(rounds);
        }
    }

    float ToRadians(float angleInDegrees)
    {
        return angleInDegrees * static_cast<float>(PI) / 180.f;
    }

    float ToDegrees(float angleInRadians)
    {
        return angleInRadians * 180.f / static_cast<float>(PI);
    }
}




AlignToMovement::AlignToMovement(Character* _character, Params _params) :
    character(_character),
    params(_params)
{}

SteeringResult AlignToMovement::GetSteering()
{
    if (character != nullptr)
    {
        // Calculate target rotation
        const USVec2D nextLinearVelocity = character->GetLinearVelocity();
        float target = Math::ToDegrees(atan2f(nextLinearVelocity.mY, nextLinearVelocity.mX));

        // Params vars to radians
        float maxVelocity = params.max_angular_velocity;
        float maxAcceleration = params.max_angular_acceleration;
        float arriveRadius = params.angular_arrive_radius;
        float destRadius = params.angular_dest_radius;

        // Character vars
        float currentRotation = character->GetRot();
        float currentAngularVelocity = character->GetAngularVelocity();

        // Normalize angles
        Math::NormalizeDegAngle(maxVelocity);
        Math::NormalizeDegAngle(maxAcceleration);
        Math::NormalizeDegAngle(target);
        Math::NormalizeDegAngle(arriveRadius);
        Math::NormalizeDegAngle(destRadius);
        Math::NormalizeDegAngle(currentRotation);
        Math::NormalizeDegAngle(currentAngularVelocity);

        const float deltaRotation = target - currentRotation;
        angularVelocityDesired = deltaRotation > 0 ? 1.f : -1.f;
        if (abs(deltaRotation) < destRadius)
        {
            maxVelocity = 0.f;
        }
        else if (abs(deltaRotation) < arriveRadius)
        {
            const float factor = abs(deltaRotation) / arriveRadius;
            maxVelocity *= factor;
        }
        angularVelocityDesired *= maxVelocity;

        steeringResult.Angular = angularVelocityDesired - currentAngularVelocity > 0.f ? 1.f : -1.f;
        steeringResult.Angular *= maxAcceleration;


        return steeringResult;
    }
    return SteeringResult();
}

void AlignToMovement::DrawDebug() {}

