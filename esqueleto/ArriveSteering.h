#pragma once
#include <params.h>

class Character;

class ArriveSteering
{
	Character* character;
	Params params;
	USVec2D target;

	USVec2D desiredVel;
	USVec2D acceleration;
	USVec2D steering;

public:
	ArriveSteering(Character* _character, Params _params);

	USVec2D GetSteering();

	void DrawDebug() const;

};

