#pragma once
// msg.h
enum header_id {
	START, // 시나리오 시작
	STOP_FINISH,  // 시나리오 중지/종료
	FIRE_MISSILE, // 유도탄 발사
	ATS_POSITION, // ATS 현재 위치 
	MSS_POSITION, // 유도탄 현재 위치
	INTERCEPT, // 요격 여부
	INTERCEPT_FAIL // 요격 여부
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
