#pragma once
#include "msg.h"
#include <thread>

struct RelativePoint {
	double radian;
	double distance;
};


class MissileManager {
public:
	MissileManager() {};
	~MissileManager() {};
	void movecoordinate(Point endPosition);
	void start();
	void stop();
	void sendPosition();
	void sendInterceptMessage();
	void initStartPosition(Point currentPosition);
	static MissileManager* getInstance();
	void missileManagerFuntion(void* args);
	Point getCurrentPosition() { return currentPosition; };

private:
	double velocity; // 시간당 속도
	bool stateOfObject; // 객체 생성 소멸 0, 1
	bool isFinish;

	int period; // 주기

	Point startPosition; //시작 위치 값
	Point currentPosition; // 현재 ATS 위치 값
	Point endPosition; // 목적지 위치 값
	Point PositionTempATS; //ATS 임시 저장 위치
	Point PositionEstimateATS; // ATS 예상 위치

	double ATS_theta; //각도
	double MSS_theta; //각도 
	double distanceFromMSSToATS; // 둘 사이 거리
	double ATS_v_est, ATS_theta_est;

	static MissileManager* missile;
	std::thread* missileManagerThread;

};