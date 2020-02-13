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
	double velocity; // �ð��� �ӵ�
	bool stateOfObject; // ��ü ���� �Ҹ� 0, 1
	bool isFinish;

	int period; // �ֱ�

	Point startPosition; //���� ��ġ ��
	Point currentPosition; // ���� ATS ��ġ ��
	Point endPosition; // ������ ��ġ ��
	Point PositionTempATS; //ATS �ӽ� ���� ��ġ
	Point PositionEstimateATS; // ATS ���� ��ġ

	double ATS_theta; //����
	double MSS_theta; //���� 
	double distanceFromMSSToATS; // �� ���� �Ÿ�
	double ATS_v_est, ATS_theta_est;

	static MissileManager* missile;
	std::thread* missileManagerThread;

};