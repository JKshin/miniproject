#pragma once
#include "msg.h"

struct RelativePoint {
	double radian;
	double distance;
};

class AirThreatManager {
public:
	AirThreatManager() {};
	~AirThreatManager() {};
	void movecoordinate();
	void start();
	void stop();
	void sendPosition();
	void initStartAndEndPosition(Point startPosition, Point endPosition);
	static AirThreatManager* getInstance();
	
private:
	double velocity; // 시간당 속도
	bool stateOfObject; // 객체 생성 소멸 0, 1
	int period; // 주기
	bool isFinish;
	Point startPosition;
	Point currentPosition; // 현재 ATS 위치 값
	Point endPosition; // 목적지 위치 값
	static AirThreatManager* airThreat;


};