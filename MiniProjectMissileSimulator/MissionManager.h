#pragma once
#include "msg.h"
#include <thread>


class MissionManager {
public:
	void setPositionOfATS(Point positionOfATS);
	Point* getPositionOfATS(void);
	bool CheckHit(Point PositionOfMSS);
	void setPositionOfMSS(Point PositionOfMSS);
	void sendHitEventToTCC();
	void start();
	void stop();
	bool stateOfObject; // 按眉 积己 家戈 0, 1
	
	static MissionManager* getInstance();

private:
	bool isHit;
	Point positionOfATS;
	Point positionOfMSS;
	float targetRange;
	static MissionManager* mission;


};