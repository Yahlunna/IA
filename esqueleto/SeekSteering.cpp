#include "stdafx.h"
#include "SeekSteering.h"
#include "character.h"

USVec2D SeekSteering::GetSteering(float max_acceleration)
{
	if (character != nullptr) 
	{
		desiredDirection = target - character->GetLoc();
		// calcular accelearacion necesaria para conseguir esa velocidad:
		// resta entre velocidad deseada y actual
		requiredAcc = desiredDirection - character->GetLinearVelocity();
		// Máxima acceleración: 
		// normalizar vector y escalar por la maxima velocidad
		requiredAcc.NormSafe();
		Acc = requiredAcc * max_acceleration;

		return Acc;
		
	}
	return USVec2D();
}


void SeekSteering::DrawDebug() const
{
	MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get();

	// Desired velocity
	USVec2D position = character->GetLoc();
	
	USVec2D delta = position + desiredDirection;

	gfxDevice.SetPenColor(0.f, 1.f, 0.f, 1.f);
	MOAIDraw::DrawLine(position.mX, position.mY, delta.mX, delta.mY);

	// Acceleration
	delta = position + Acc;

	gfxDevice.SetPenColor(1.f, 0.f, 0.f, 1.f);
	MOAIDraw::DrawLine(position.mX, position.mY, delta.mX, delta.mY);
}



