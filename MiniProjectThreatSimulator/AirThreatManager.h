#pragma once
#include "msg.h"
#include <thread>

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
	void sendInterceptFailMessage();
	void initStartAndEndPosition(Point startPosition, Point endPosition);
	static AirThreatManager* getInstance();
	void airThreatFuntion(void* args);
	
private:
	double velocity; // �ð��� �ӵ�
	bool stateOfObject; // ��ü ���� �Ҹ� 0, 1
	int period; // �ֱ�
	bool isFinish;
	bool isSafe;
	Point startPosition;
	Point currentPosition; // ���� ATS ��ġ ��
	Point endPosition; // ������ ��ġ ��
	static AirThreatManager* airThreat;	
	std::thread* airThreatThread;
};