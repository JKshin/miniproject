#pragma once
#include<iostream>
#include<cmath>
#include<functional>
#include "MissionManager.h"
#include "MissileManager.h"

using namespace std;

MissionManager* MissionManager::mission;

MissionManager* MissionManager::getInstance() {
	if (!mission) {
		mission = new MissionManager();
		mission->stateOfObject = true;
	}
	return mission;
}

void MissionManager::setPositionOfATS(Point PositionOfATS) { //ats 좌표를 ttc에서 받아 갱신.
	positionOfATS = PositionOfATS;

}

void MissionManager::getPositionOfATS(Point* PositionOfMSS) { //갱신된 데이터를 미사일 매니저에서 가져가기 위해서

}

bool MissionManager::CheckHit(Point PositionOfMSS) {

}

void MissionManager::sendHitEventToTCC() {

}

