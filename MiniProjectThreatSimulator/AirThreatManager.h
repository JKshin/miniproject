#pragma once


struct Point {
	double x;
	double y;
};

struct RelativePoint {
	double radian;
	double distance;
};


class AirThreatManager {
public:
	void movecoordinate();
	void start();
	void stop();
	void sendPosition();
	void initStartAndEndPosition(Point currentPosition, Point endPosition);
	\
private:
	double velocity; // �ð��� �ӵ�
	bool stateOfObject; // ��ü ���� �Ҹ� 0, 1
	int period; // �ֱ�
	bool isFinish;
	Point startPosition;
	Point currentPosition; // ���� ATS ��ġ ��
	Point endPosition; // ������ ��ġ ��

};