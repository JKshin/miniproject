#include<iostream>
#include<cmath>
#include<functional>
#include "AirThreatManager.h"
#include "CommunicationManager.h"
using namespace std;

AirThreatManager* AirThreatManager::airThreat;

double GetDistanceFromPoints(Point start, Point end) // 시작 - 목적지 간의 거리
{
	return sqrt(pow(end.x - start.x, 2) + pow(end.y - start.y, 2));
}

double GetAngleFromPoints(Point start, Point end) {
	return atan2(end.y - start.y, end.x - start.x);
}

Point GetPointFromAngleAndDistance(RelativePoint relativePoint) // 목적지까지 방향으로 이동(설정된 속도에 따른 방향으로) 했을 때 어느 위치에 있는지 반환
{
	Point point;
	point.x = relativePoint.distance * cos(relativePoint.radian);
	point.y = relativePoint.distance * sin(relativePoint.radian);
	return point; // 현재 위치 즉, send 해야하는 위치값  send()
}

void AirThreatManager::airThreatFuntion(void* args){
	while (!airThreat->isFinish) {
		airThreat->movecoordinate();
		airThreat->sendPosition();
		Sleep(100);
	}
}

AirThreatManager* AirThreatManager::getInstance() {
	if (!airThreat) {
		airThreat = new AirThreatManager();
		airThreat->stateOfObject = true;
	}
	return airThreat;
}

void AirThreatManager::movecoordinate() {
	RelativePoint currentRelativePoint;
	Point moveDistance;

	currentRelativePoint.radian = GetAngleFromPoints(currentPosition, endPosition); //현재 각도
	currentRelativePoint.distance = velocity * period / 1000.0; // 이동 거리
	moveDistance = GetPointFromAngleAndDistance(currentRelativePoint); // x,y만큼 이동해야하는 값

	currentPosition.x += moveDistance.x;
	currentPosition.y += moveDistance.y;

	double distanceFromStartPositionToEndPosition = GetDistanceFromPoints(startPosition, endPosition);
	double distanceFromStartPositionToCurrentPosition = GetDistanceFromPoints(startPosition, currentPosition);
	if (distanceFromStartPositionToEndPosition < distanceFromStartPositionToCurrentPosition)
		currentPosition = endPosition;

	cout << "currentPosition.x = " << currentPosition.x << "currentPosition.y = " << currentPosition.y << endl;

}



void AirThreatManager::start() {
	velocity = 1;
	period = 1000;
	airThreat->airThreatThread = new std::thread(std::bind(&AirThreatManager::airThreatFuntion, this, placeholders::_1), nullptr);
}
void AirThreatManager::stop() {
	stateOfObject = false;
	airThreat->isFinish = true;
	Sleep(1000);
	airThreat->~AirThreatManager(); // 소멸자
}

void AirThreatManager::sendPosition() {
	CommunicationManager* commManager = CommunicationManager::getInstance();
	Message message;
	message.id = ATS_POSITION;	
	message.start_pos = airThreat->currentPosition;
	commManager->sendMessage(message);
}

void AirThreatManager::initStartAndEndPosition(Point startposition, Point endposition) {
	startPosition = startposition;
	currentPosition = startposition;
	endPosition = endposition;
}
