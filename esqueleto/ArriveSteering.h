#pragma once
#include <params.h>

class AlignToMovement;
class Character;

struct SteeringResult
{
    USVec2D Linear;
    float Angular;

    SteeringResult(const USVec2D& linear = USVec2D(0.f, 0.f), float angular = 0.f)
        : Linear(linear), Angular(angular) {}

    SteeringResult operator+(const SteeringResult& other)
    {
        SteeringResult result;
        result.Linear = Linear + other.Linear;
        result.Angular = Angular + other.Angular;
        return result;
    }

    void operator+=(const SteeringResult& other)
    {
        Linear += other.Linear;
        Angular += other.Angular;
    }
};



class ArriveSteering
{
	Character* character;
	Params params;
	USVec2D target;

	USVec2D desiredVel;
	USVec2D acceleration;
	USVec2D steering;

    AlignToMovement* alignToMovementDelegate;
    SteeringResult steeringResult;

public:
	ArriveSteering(Character* _character, Params _params);

    // P2
	USVec2D GetSteering();
    // P4
    SteeringResult GetSteeringResult();

	void DrawDebug() const;

    void SetDelegate(AlignToMovement* _alignToMovementDelegate) { 
        alignToMovementDelegate = _alignToMovementDelegate; 
    }

    SteeringResult CallDelegate() const;

protected:
    

};

