#include "stdafx.h"
#include "AlignSteering.h"
#include "character.h"

AlignSteering::AlignSteering(Character* _character, Params* _params) : 
	character(_character),
	params(_params),
	desiredVelocity(0.f),
	steering(0.f)
{

}


float AlignSteering::GetSteering() {

    if (character != nullptr) {


        float maxVelocity = ToRadians(params->max_angular_velocity);
        float maxAcceleration = ToRadians(params->max_angular_acceleration);
        float target = ToRadians(params->targetRotation);
        float arriveRadius = ToRadians(params->angular_arrive_radius);
        float destRadius = ToRadians(params->angular_dest_radius);

        // Character vars
        float currentRotation = ToRadians(character->GetRot());
        float currentAngularVelocity = ToRadians(character->GetAngularVelocity());


        NormalizeAngle(maxVelocity);
        NormalizeAngle(maxAcceleration);
        NormalizeAngle(arriveRadius);
        NormalizeAngle(destRadius);
        NormalizeAngle(currentRotation);
        NormalizeAngle(currentAngularVelocity);

        const float deltaRotation = target - currentRotation;
        //printf("Target: % f\n", target);
        desiredVelocity = deltaRotation > 0 ? 1.f : -1.f;
        if (abs(deltaRotation) < destRadius)
        {
            maxVelocity = 0.f;
        }
        else if (abs(deltaRotation) < arriveRadius)
        {
            const float factor = abs(deltaRotation) / arriveRadius;
            maxVelocity *= factor;
        }
        desiredVelocity *= maxVelocity;

        steering = desiredVelocity - currentAngularVelocity > 0.f ? 1.f : -1.f;
        steering *= maxAcceleration;

        return ToDegrees(steering);
    }
    return 0.f;

}


void AlignSteering::NormalizeAngle(float& angleInRadians)
{
    if (angleInRadians < -static_cast<float>(PI) || angleInRadians > static_cast<float>(PI))
    {
        const int rounds = static_cast<int>(fmodf(angleInRadians, PI));
        angleInRadians += 2 * static_cast<float>(PI) * -1.f * static_cast<float>(rounds);
    }
}

float AlignSteering::ToRadians(float angleInDegrees)
{
    return angleInDegrees * static_cast<float>(PI) / 180.f;
}

float AlignSteering::ToDegrees(float angleInRadians)
{
    return angleInRadians * 180.f / static_cast<float>(PI);
}


void AlignSteering::DrawDebug() {
    MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get();
    gfxDevice.SetPenColor(USColorVec(1.f, 0.0f, 0.f, 1.f));
    USVec2D position = character->GetLoc();
    float target = ToRadians(params->targetRotation);
    NormalizeAngle(target);

    USVec2D delta = position + USVec2D(cosf(desiredVelocity), sinf(desiredVelocity)) * 50.f;

    MOAIDraw::DrawLine(position.mX, position.mY, delta.mX, delta.mY);
    
}