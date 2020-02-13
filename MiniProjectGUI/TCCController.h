#pragma once
#include <iostream>
#include "CommunicationManager.h"
#include "msg.h"

using namespace std;

class TCCController
{
public:

	void setScenario(int ats_cur_x, int ats_cur_y,
		int ats_end_x, int ats_end_y, int mss_start_x, int mss_start_y); // 시나리오 설정 및 배포

	struct Position getAtsCurPosition() { return atsCurPosition; };
	struct Position getAtsEndPosition() { return atsEndPosition; };
	struct Position getMssStartPosition() { return mssCurPosition; };

	//@재권 추가
	struct Position getMssCurPosition() { return mssCurPosition; };
	
	void setAtsCurPosition(Position atsCurPosition) {
		this->atsCurPosition = atsCurPosition;
	}
	
	void setMssCurPosition(Position mssCurPosition) {
		this->mssCurPosition = mssCurPosition;
	}
	///////////////////////////////////////////////////////

	bool startScenario(); // 시나리오 시작
	bool stopScenario(); // 시나리오 중지
	void finishScenario(); // 시나리오 종료

	static TCCController* getInstance();

	void drawATS();
	void drawMSS();
	void displayStatus();
	void checkIntercept(bool);
	bool getCheckHit();
	void fireMissile();

private:
	TCCController();
	Position atsCurPosition;
	Position atsEndPosition;
	Position mssCurPosition;
	
	bool checkHit;

	static TCCController* tccController;
};