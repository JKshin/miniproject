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
	bool stateOfObject; // ��ü ���� �Ҹ� 0, 1

	static MissionManager* getInstance();

private:
	bool isHit;
	Point positionOfATS;
	Point positionOfMSS;
	float targetRange;
	static MissionManager* mission;


};