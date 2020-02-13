#include<iostream>
#include<cmath>
#include<functional>
#include"MissileManager.h"
#include"MissionManager.h"
#include"CommunicationManager.h"
#include<Windows.h>

using namespace std;

MissileManager* MissileManager::missile;

MissileManager* MissileManager::getInstance() {
	if (!missile) {
		missile = new MissileManager();
		missile->stateOfObject = true;
	}
	return missile;
}

void MissileManager::missileManagerFuntion(void* args) {
	
	MissionManager* missionManager = MissionManager::getInstance();
	while (!missile->isFinish) {
		missile->movecoordinate(*missionManager->getPositionOfATS());
		missionManager->CheckHit(missile->currentPosition);
		missile->sendPosition();
		Sleep(1000);
	}
}

void MissileManager::movecoordinate(Point PositionOfATS) { //endPosition = ATS 좌표

	//ATS의 이전위치와 현재위치로 ATS의 속력과 방향 계산
	ATS_theta_est = atan2(PositionOfATS.y - PositionTempATS.y, PositionOfATS.x - PositionTempATS.x);
	ATS_v_est = sqrt(pow(PositionOfATS.x - PositionTempATS.x, 2) + pow(PositionOfATS.y - PositionTempATS.y, 2));

	//ATS와 MSS 사이의 현재 거리
	distanceFromMSSToATS = sqrt(pow(PositionOfATS.x - currentPosition.x, 2) + pow(PositionOfATS.y - currentPosition.y, 2));

	// ATS 예상위치
	PositionEstimateATS.x = PositionOfATS.x + (distanceFromMSSToATS / 200) * ATS_v_est * cos(ATS_theta_est);
	PositionEstimateATS.y = PositionOfATS.y + (distanceFromMSSToATS / 200) * ATS_v_est * cos(ATS_theta_est);

	// MSS 각도
	MSS_theta = atan2(PositionEstimateATS.y - currentPosition.y, PositionEstimateATS.x - currentPosition.x);

	// MSS 각도에 의한 좌표값
	currentPosition.x = currentPosition.x + velocity * cos(MSS_theta);
	currentPosition.y = currentPosition.y + velocity * sin(MSS_theta);

	//MissionManager로 넘겨야하는 값
	PositionTempATS.x = PositionOfATS.x;
	PositionTempATS.y = PositionOfATS.y;

	cout << "currentPosition.x = " << currentPosition.x << "currentPosition.y = " << currentPosition.y << endl;
	cout << "PositionTempATS.x = " << PositionTempATS.x << "PositionTempATS.y = " << PositionTempATS.y << endl;

}

void MissileManager::start() {
	velocity = 20;
	period = 1000;
	PositionTempATS.x, PositionTempATS.y = 0;
	missile->missileManagerThread = new std::thread(std::bind(&MissileManager::missileManagerFuntion, this, placeholders::_1), nullptr);
}

void MissileManager::stop() {
	stateOfObject = false;
	missile->isFinish = true;
	missile->~MissileManager(); // 소멸자
}

void MissileManager::sendPosition() {
	CommunicationManager commManager;
	Message message;
	Point currentPoint;
	message.id = MSS_POSITION;
	message.start_pos = missile->currentPosition;
	commManager.sendMessage(message);

}

void MissileManager::initStartPosition(Point startposition) {
	currentPosition = startposition;

}

//
//int main() {
//
//	MissileManager hayoon;
//
//	hayoon.start();
//	Point startPosition = { 10.0, 20.0 };
//	Point AFSPosition = { 150.0, 200.0 };
//	hayoon.initStartPosition(startPosition);
//
//	while (1) {
//		AFSPosition.x += 10;
//		AFSPosition.y += 10;
//		hayoon.movecoordinate(AFSPosition);
//	}
//	return 0;
//}