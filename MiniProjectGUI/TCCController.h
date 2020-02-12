#pragma once
#include <iostream>
#include "CommunicationManager.h"
#include "msg.h"

using namespace std;

class TCCController
{
public:

	void setScenario(int ats_cur_x, int ats_cur_y,
		int ats_end_x, int ats_end_y, int mss_start_x, int mss_start_y); // �ó����� ���� �� ����

	struct Position getAtsCurPosition() { return atsCurPosition; };
	struct Position getAtsEndPosition() { return atsEndPosition; };
	struct Position getMssStartPosition() { return mssStartPosition; };

	bool startScenario(); // �ó����� ����
	bool stopScenario(); // �ó����� ����
	void finishScenario(); // �ó����� ����

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