#pragma once
class Character;

class SeekSteering
{
	Character* character;
	USVec2D target;

	USVec2D desiredDirection;
	USVec2D requiredAcc;
	USVec2D Acc;


public:

	SeekSteering(Character* _character, USVec2D _target) :
		character(_character),
		target(_target)
	{}


	//Character, target location. Returns acc.
	USVec2D GetSteering(float max_acceleration);

	void DrawDebug() const;

};

