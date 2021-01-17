#ifndef BLOCK_H
#define BLOCK_H

class Vehicle;

class Block
{
public:
	Block();

    int getPalladium();
	void setPalladium(int);

	int getIridium();
	void setIridium(int);

	int getPlatinum();
	void setPlatinum(int);

	float getDifficulty();
	void setDifficulty(float);

	bool getAvoid();
	void setAvoid(bool);

	Vehicle* getCurVehicle();
	void setCurVehicle(Vehicle*);

	bool getOccupied();

private:
	int palladium;
	int iridium;
	int platinum;
	float difficulty;
	bool avoid;

	Vehicle* curVehicle;
};

#endif