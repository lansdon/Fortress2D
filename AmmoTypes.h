#pragma once
class AmmoTypes
{
public:
	AmmoTypes(void);
	~AmmoTypes(void);

	// Toggle Ammo Types on or off
	void setArrowNormal(bool bTrue = true) { _arrow_normal = bTrue; }
	void setArrowFire(bool bTrue = true) { _arrow_fire = bTrue; }
	void setCannonBallNormal(bool bTrue = true) { _cannonball_normal = bTrue; }
	void setCannonBallFire(bool bTrue = true) { _cannonball_fire = bTrue; }
	
	// Fine 
	bool useArrowNormal() { return _arrow_normal; }
	bool useArrowFire() { return _arrow_fire; }
	bool useCannonBallNormal() { return _cannonball_normal; }
	bool useCannonBallFire() { return _cannonball_fire; }



private:

	// Types of ammo
	bool _arrow_fire;
	bool _arrow_normal;
	bool _cannonball_normal;
	bool _cannonball_fire;


};

