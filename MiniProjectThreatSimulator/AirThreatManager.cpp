#include<iostream>
#include<cmath>
#include<functional>
#include"AirThreatManager.h"
using namespace std;

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
	//Point startPosition = { 10.0, 20.0 };
	//Point endPosition = { 30.0, 40.0 };
	velocity = 1;
	period = 1000;

}
void AirThreatManager::stop() {

	stateOfObject = false;
}

void AirThreatManager::sendPosition() {


}

void AirThreatManager::initStartAndEndPosition(Point startposition, Point endposition) {
	startPosition = startposition;
	currentPosition = startposition;
	endPosition = endposition;
}
