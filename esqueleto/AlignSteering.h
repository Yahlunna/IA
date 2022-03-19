#pragma once
#include "params.h"

class Character;


class AlignSteering
{
	Character* character;
	Params* params;
	float desiredVelocity;
	float steering;

public:

	AlignSteering(Character* _character, Params* _params);

	float GetSteering();

	static void NormalizeAngle(float& angleInRadians);
	static float ToRadians(float angleInDegrees);
	static float ToDegrees(float angleInRadians);

	void DrawDebug();

};

