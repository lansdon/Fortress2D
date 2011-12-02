#pragma once
class Vector3
{
public:
	Vector3(void);
	Vector3(double x, double y, double z);
	~Vector3(void);
	double x() { return posX; }
	double y() { return posY; }
	double z() { return posZ; }
	void set(double x, double y, double z) { posX = x; posY = y; posZ = z; }


private:
	double posX, posY, posZ;
};

