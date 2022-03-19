#include "stdafx.h"
#include "ArriveSteering.h"
#include "character.h"


ArriveSteering::ArriveSteering(Character* _character, Params _params) :
	character(_character),
	params(_params)
{
	target = params.targetPosition;
}




USVec2D ArriveSteering::GetSteering() {

	
	if (character != nullptr) {

		desiredVel = target - character->GetLoc();
		float maxVel = desiredVel.Length() <= params.dest_radius ? 0.f : params.max_velocity;

		if (desiredVel.Length() < params.arrive_radius) {
			float factor = desiredVel.Length() / params.arrive_radius;
			maxVel *= factor;
		}

		desiredVel.NormSafe();
		desiredVel *= maxVel;

		acceleration = desiredVel - character->GetLinearVelocity();
		acceleration.NormSafe();

		steering = acceleration * params.max_acceleration;
		return steering;
	}
	
}



void ArriveSteering::DrawDebug() const {

	MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get();

	// Velocity
	USVec2D position = character->GetLoc();
	USVec2D delta = position + desiredVel;

	gfxDevice.SetPenColor(0.f, 1.f, 0.f, 1.f);
	MOAIDraw::DrawLine(position.mX, position.mY, delta.mX, delta.mY);

	//Acceleration
	delta = position + steering;

	gfxDevice.SetPenColor(1.f, 0.f, 0.f, 1.f);
	MOAIDraw::DrawLine(position.mX, position.mY, delta.mX, delta.mY);


}