#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include <moaicore/MOAIEntity2D.h>
#include <params.h>

class SeekSteering;
class ArriveSteering;
class AlignSteering;

class Character: public MOAIEntity2D
{
public:
    DECL_LUA_FACTORY(Character)
protected:
	virtual void OnStart();
	virtual void OnStop();
	virtual void OnUpdate(float step);	// This
public:
	virtual void DrawDebug();	// This

	Character();
	~Character();
	
	void SetLinearVelocity(float x, float y) { mLinearVelocity.mX = x; mLinearVelocity.mY = y;}
	void SetAngularVelocity(float angle) { mAngularVelocity = angle;}
	
	USVec2D GetLinearVelocity() const { return mLinearVelocity;}
	float GetAngularVelocity() const { return mAngularVelocity;}
private:
	USVec2D mLinearVelocity;
	float mAngularVelocity;
	
	Params mParams;

	SeekSteering* seekSteering;	// P1 ) seek;
	ArriveSteering* arriveSteering; // P2) arrive;
	AlignSteering* alignSteering;




	USVec2D target;


	
	// Lua configuration
public:
	virtual void RegisterLuaFuncs(MOAILuaState& state);
private:
	static int _setLinearVel(lua_State* L);
	static int _setAngularVel(lua_State* L);
};

#endif