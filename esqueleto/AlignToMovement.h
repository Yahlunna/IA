#pragma once
#include "ArriveSteering.h"
#include "params.h"

class AlignToMovement
{
    Character* character;
    SteeringResult steeringResult;
    Params params;
public:
    AlignToMovement(Character* _character, Params _params);

    virtual SteeringResult GetSteering();
    virtual void DrawDebug();

    

protected:
    float angularVelocityDesired;



};

