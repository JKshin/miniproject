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

void MissionManager::setPositionOfATS(Point PositionOfATS) { //ats ��ǥ�� ttc���� �޾� ����.
	positionOfATS = PositionOfATS;

}

void MissionManager::getPositionOfATS(Point* PositionOfMSS) { //���ŵ� �����͸� �̻��� �Ŵ������� �������� ���ؼ�

}

bool MissionManager::CheckHit(Point PositionOfMSS) {

}

void MissionManager::sendHitEventToTCC() {

}

