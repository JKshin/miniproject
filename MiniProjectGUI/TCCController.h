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
	struct Position getMssStartPosition() { return mssStartPosition; };

	bool startScenario(); // 시나리오 시작
	bool stopScenario(); // 시나리오 중지
	void finishScenario(); // 시나리오 종료

	static TCCController* getInstance();

	void drawATS();
	void drawMSS();
	void displayStatus();
	void displayEvent();
	void fireMissile();

private:
	TCCController();

	Position atsCurPosition;
	Position atsEndPosition;
	Position mssStartPosition;

	static TCCController* tccController;

	//CMiniProjectGUIDlg* cGUIDlg;
	//DisplayController* displayController;
};