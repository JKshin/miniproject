#pragma once

enum header_id {
	START, // �ó����� ����
	STOP_FINISH,  // �ó����� ����/����
	FIRE_MISSILE, // ����ź �߻�
	ATS_POSITION, // ATS ���� ��ġ 
	MSS_POSITION, // ����ź ���� ��ġ
	INTERCEPT, // ��� ����
	INTERCEPT_FAIL // ��� ����
};

struct Position {
	double x;
	double y;
};

struct Message { // ��� �޽���
	header_id id;
	Position start_pos;
	Position end_pos;
};