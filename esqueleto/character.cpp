#include <stdafx.h>
#include "character.h"
#include <tinyxml.h>

#include "SeekSteering.h"
#include "ArriveSteering.h"
#include "AlignSteering.h"
#include "AlignToMovement.h"

#include <params.h>
#include <iostream>


Character::Character() : mLinearVelocity(0.0f, 0.0f), mAngularVelocity(0.0f)
{
	RTTI_BEGIN
		RTTI_EXTEND(MOAIEntity2D)
	RTTI_END
}

Character::~Character()
{

}

void Character::OnStart()
{
    ReadParams("params.xml", mParams);
	seekSteering = new SeekSteering(this, mParams.targetPosition);
	arriveSteering = new ArriveSteering(this, mParams);
	alignSteering = new AlignSteering(this, &mParams);
	alignToMovement = new AlignToMovement(this, mParams);

	arriveSteering->SetDelegate(alignToMovement);
}

void Character::OnStop()
{

}

void Character::OnUpdate(float step)
{

	USVec2D distance = GetLoc() - mParams.targetPosition;

	/** P1) Seek */
	//USVec2D steering = seekSteering->GetSteering(mParams.max_acceleration);
	//mLinearVelocity += steering * step;
	//SetLoc(GetLoc() + (mLinearVelocity * step));

	/** P2) Arrive */
	//USVec2D steering = arriveSteering->GetSteering();
	//mLinearVelocity += steering * step;
	//SetLoc(GetLoc() + (mLinearVelocity * step));

	/** P3) Align */
	//const float fsteering = alignSteering->GetSteering();
	//mAngularVelocity += fsteering * step;
	//float rotation = GetRot();
	//rotation += mAngularVelocity * step;
	//SetRot(rotation);

	/** P4) Arrive con AlignToMovement como delegado */
	SteeringResult steeringResult = arriveSteering->GetSteeringResult();
	mLinearVelocity += steeringResult.Linear * step;
	mAngularVelocity += steeringResult.Angular * step;
	SetLoc(GetLoc() + mLinearVelocity * step);
	SetRot(GetRot() + mAngularVelocity * step);

}

void Character::DrawDebug()
{
	MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get();

	/* P1) Seek */
	//gfxDevice.SetPenColor(0.6f, 0.3f, 0.2f, 1.f);
	//MOAIDraw::DrawPoint(mParams.targetPosition.mX, mParams.targetPosition.mY);
	//MOAIDraw::DrawEllipseOutline(mParams.targetPosition.mX, mParams.targetPosition.mY, mParams.dest_radius,mParams.dest_radius, 25);
	//seekSteering->DrawDebug();
	

	/** P2) Arrive */
	gfxDevice.SetPenColor(0.6f, 0.3f, 0.2f, 1.f);
	MOAIDraw::DrawPoint(mParams.targetPosition.mX, mParams.targetPosition.mY);
	MOAIDraw::DrawEllipseOutline(mParams.targetPosition.mX, mParams.targetPosition.mY, mParams.dest_radius,mParams.dest_radius, 25);
	gfxDevice.SetPenColor(0.6f, 0.45f, 0.4f, 1.f);
	MOAIDraw::DrawEllipseOutline(mParams.targetPosition.mX, mParams.targetPosition.mY, mParams.arrive_radius, mParams.arrive_radius, 25);
	gfxDevice.SetPenColor(1.f, 1.f, 1.f, 1.f);
	MOAIDraw::DrawLine(GetLoc().mX, GetLoc().mY, GetLoc().mX + mLinearVelocity.mX, GetLoc().mY + mLinearVelocity.mY);
	arriveSteering->DrawDebug();


	/** P3) Align */
	// Show current rotation
	//gfxDevice.SetPenColor(0.7f, 1.f, 0.2f, 1.f);
	//float currentRotation = alignSteering->ToRadians(GetRot());
	//USVec2D delta = USVec2D(cosf(currentRotation), sinf(currentRotation)) * 50.f + GetLoc();
	//MOAIDraw::DrawLine(GetLoc().mX, GetLoc().mY, delta.mX, delta.mY);
	//alignSteering->DrawDebug();

}





// Lua configuration

void Character::RegisterLuaFuncs(MOAILuaState& state)
{
	MOAIEntity2D::RegisterLuaFuncs(state);
	
	luaL_Reg regTable [] = {
		{ "setLinearVel",			_setLinearVel},
		{ "setAngularVel",			_setAngularVel},
		{ NULL, NULL }
	};

	luaL_register(state, 0, regTable);
}

int Character::_setLinearVel(lua_State* L)
{
	MOAI_LUA_SETUP(Character, "U")
	
	float pX = state.GetValue<float>(2, 0.0f);
	float pY = state.GetValue<float>(3, 0.0f);
	self->SetLinearVelocity(pX, pY);
	return 0;	
}

int Character::_setAngularVel(lua_State* L)
{
	MOAI_LUA_SETUP(Character, "U")
	
	float angle = state.GetValue<float>(2, 0.0f);
	self->SetAngularVelocity(angle);

	return 0;
}
	