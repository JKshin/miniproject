#include "pch.h"
#include "TCCController.h"
#include "CommunicationManager.h"
#include "MiniProjectGUIDlg.h"

TCCController* TCCController::tccController = nullptr;

TCCController::TCCController()
{
	atsCurPosition.x = 0.0f;
	atsCurPosition.y = 0.0f;
	atsEndPosition.x = 0.0f;
	atsEndPosition.y = 0.0f;
	mssStartPosition.x = 0.0f;
	mssStartPosition.y = 0.0f;
}

TCCController* TCCController::getInstance()
{
	if (tccController == nullptr) {
		tccController = new TCCController();
	}

	return tccController;
}


void TCCController::setScenario(
	int ats_cur_x, int ats_cur_y,
	int ats_end_x, int ats_end_y,
	int mss_start_x, int mss_start_y) // 시나리오 설정 및 배포
{
	this->atsCurPosition.x = ats_cur_x;
	this->atsCurPosition.y = ats_cur_y;

	this->atsEndPosition.x = ats_end_x;
	this->atsEndPosition.y = ats_end_y;

	this->mssStartPosition.x = mss_start_x;
	this->mssStartPosition.y = mss_start_y;
}


bool TCCController::startScenario() // 시나리오 시작
{
	CommunicationManager* comm = CommunicationManager::getInstance();

	if (comm->connect())
	{
		comm->setPosition();
		comm->send(START);//시나리오 시작 알리기
	}

	return true;
}

bool TCCController::stopScenario() // 시나리오 중지
{
	CommunicationManager* comm = CommunicationManager::getInstance();

	comm->send(STOP_FINISH);
	return true;
}

void TCCController::finishScenario() // 시나리오 종료
{
	CommunicationManager* comm = CommunicationManager::getInstance();

	comm->send(STOP_FINISH);
}

void TCCController::drawATS()
{
	//CMiniProjectGUIDlg
}
void TCCController::drawMSS()
{

}
void TCCController::displayStatus()
{

}
void TCCController::displayEvent()
{

}
void TCCController::fireMissile()
{

}