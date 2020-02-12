#pragma once
#include<iostream>
#include<cmath>
#include<functional>
#include "MissionManager.h"
#include "CommunicationManager.h"

using namespace std;

MissionManager* MissionManager::mission;

MissionManager* MissionManager::getInstance() {
	if (!mission) {
		mission = new MissionManager();
		mission->stateOfObject = true;
	}
	return mission;
}

//void MissionManager::missionManagerFuntion(void* args) {
//	while (!mission->isFinish) {
//		mission->movecoordinate(*missionManager->getPositionOfATS());
//		Sleep(1000);
//	}
//}

void MissionManager::setPositionOfATS(Point PositionOfATS) { //ats 좌표를 ttc에서 받아 갱신.
	positionOfATS = PositionOfATS;
}

Point* MissionManager::getPositionOfATS(void) { //갱신된 데이터를 미사일 매니저에서 가져가기 위해서
	return &positionOfATS;
}

bool MissionManager::CheckHit(Point PositionOfMSS) {

	if(sqrt(pow(positionOfATS.x - positionOfMSS.x, 2) + pow(positionOfATS.y 
		- positionOfMSS.y, 2)) < targetRange){
		isHit = true;
		return isHit;
		}
	
	return isHit;
}

//distanceFromMSSToATS = sqrt(pow(ATS_x - MissilePosition_X, 2) 
//+ pow(ATS_y - MissilePosition_Y, 2)); //ATS와 MSS 사이의 현재 거리

void MissionManager::start(){
	targetRange = 10;
	isHit = false;
}

void MissionManager::stop(){
	stateOfObject = false;
	//mission->~MissionManager();
}

void MissionManager::sendHitEventToTCC() {
	Message message;
	CommunicationManager* commManager = CommunicationManager::getInstance();
	message.id = INTERCEPT;
	commManager->sendMessage(message);
}

