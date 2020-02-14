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

void MissionManager::setPositionOfATS(Point PositionOfATS) { //ats ��ǥ�� ttc���� �޾� ����.
	positionOfATS = PositionOfATS;
}
void MissionManager::setPositionOfMSS(Point PositionOfMSS) { //ats ��ǥ�� ttc���� �޾� ����.
	positionOfMSS = PositionOfMSS;
}

Point* MissionManager::getPositionOfATS(void) { //���ŵ� �����͸� �̻��� �Ŵ������� �������� ���ؼ�
	return &positionOfATS;
}

bool MissionManager::CheckHit(Point PositionOfMSS) {
	double diff = sqrt(pow(positionOfATS.x - positionOfMSS.x, 2) + pow(positionOfATS.y - positionOfMSS.y, 2));
	cout << "I'm a Missile : Distance : " << diff << endl<<endl;
	if(diff < targetRange){
		cout << "I'm a Missile : INTERCEPT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl << endl;
		isHit = true;
	}
	
	return isHit;
}

//distanceFromMSSToATS = sqrt(pow(ATS_x - MissilePosition_X, 2) 
//+ pow(ATS_y - MissilePosition_Y, 2)); //ATS�� MSS ������ ���� �Ÿ�

void MissionManager::start(){
	targetRange = 3;
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

