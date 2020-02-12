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
	double velocity; // �ð��� �ӵ�
	bool stateOfObject; // ��ü ���� �Ҹ� 0, 1
	int period; // �ֱ�
	bool isFinish;
	Point startPosition;
	Point currentPosition; // ���� ATS ��ġ ��
	Point endPosition; // ������ ��ġ ��
	static AirThreatManager* airThreat;


};