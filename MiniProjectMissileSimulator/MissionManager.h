#pragma once
#include"MissileManager.h"

struct Point {
	double x;
	double y;
};

class MissionManager {
public:
	void setPositionOfATS(Point positionOfATS);
	void getPositionOfATS(Point* PositionOfATS);
	bool CheckHit(Point PositionOfMSS);
	void sendHitEventToTCC();
	bool stateOfObject; // 按眉 积己 家戈 0, 1

	static MissionManager* getInstance();

private:
	bool isHit;
	Point positionOfATS;
	Point positionOfMSS;
	float targetRange;
	static MissionManager* mission;


};