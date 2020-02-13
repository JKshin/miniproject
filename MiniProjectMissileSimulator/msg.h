#pragma once
// msg.h
enum header_id {
	START, // �ó����� ����
	STOP_FINISH,  // �ó����� ����/����
	FIRE_MISSILE, // ����ź �߻�
	ATS_POSITION, // ATS ���� ��ġ 
	MSS_POSITION, // ����ź ���� ��ġ
	INTERCEPT, // ��� ����
	INTERCEPT_FAIL // ��� ����
};

struct Point {
	double x;
	double y;
};

struct Message {
	header_id id;
	Point start_pos;
	Point end_pos;
};
