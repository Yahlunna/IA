#include "stdafx.h"
#include "SeekSteering.h"
#include "character.h"

USVec2D SeekSteering::GetSteering(float max_acceleration, bool isTriggered)
{
	if (character != nullptr) 
	{
		if (isTriggered) {
			// velocidad deseada: 
			// resta entre pos del target y pos del personaje
			desiredVel = target - character->GetLoc();
			// calcular accelearacion necesaria para conseguir esa velocidad:
			// resta entre velocidad deseada y actual
			requiredAcc = desiredVel - character->GetLinearVelocity();
			// Máxima acceleración: 
			// normalizar vector y escalar por la maxima velocidad
			requiredAcc.NormSafe();
			maxAcc = requiredAcc * max_acceleration;

			return maxAcc;
		}
		else
		{
			desiredVel.mX = 0.f; desiredVel.mY = 0.f;
			maxAcc.mX = 0.f; maxAcc.mY = 0.f;
			return maxAcc;
		}

	
	}
	return USVec2D();
}


void SeekSteering::DrawDebug() const
{
	MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get();

	// Desired velocity
	USVec2D position = character->GetLoc();
	USVec2D delta = position + desiredVel;
	gfxDevice.SetPenColor(1.f, 0.f, 0.f, 1.f);
	MOAIDraw::DrawLine(position.mX, position.mY, delta.mX, delta.mY);

	// Acceleration
	delta = position + maxAcc;
	gfxDevice.SetPenColor(0.f, 1.f, 0.f, 1.f);
	MOAIDraw::DrawLine(position.mX, position.mY, delta.mX, delta.mY);
}



