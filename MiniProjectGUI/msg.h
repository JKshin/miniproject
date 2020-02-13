#pragma once

enum header_id {
	START, // 시나리오 시작
	STOP_FINISH,  // 시나리오 중지/종료
	FIRE_MISSILE, // 유도탄 발사
	ATS_POSITION, // ATS 현재 위치 
	MSS_POSITION, // 유도탄 현재 위치
	INTERCEPT, // 요격 여부
	INTERCEPT_FAIL // 요격 여부
};

struct Position {
	double x;
	double y;
};

struct Message { // 통신 메시지
	header_id id;
	Position start_pos;
	Position end_pos;
};