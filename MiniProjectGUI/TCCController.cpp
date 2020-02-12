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
	mssCurPosition.x = 0.0f;
	mssCurPosition.y = 0.0f;
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

	//@재권 수정
	//this->mssStartPosition.x = mss_start_x;
	//this->mssStartPosition.y = mss_start_y;
	this->mssCurPosition.x = mss_start_x;
	this->mssCurPosition.y = mss_start_y;
}


bool TCCController::startScenario() // 시나리오 시작
{
	CommunicationManager* comm = CommunicationManager::getInstance();
	//@신재권 추가
	Message message;
	////////////////
	if (comm->connect())
	{
		//comm->setPosition();
		//@신재권 추가 및 수정
		message.id = START;
		message.start_pos = atsCurPosition;
		message.end_pos = atsEndPosition;
		//comm->send(START)
		comm->send(message);//시나리오 시작 알리기
		//////////////////////////////////////////////////////
	}

	return true;
}

bool TCCController::stopScenario() // 시나리오 중지
{
	CommunicationManager* comm = CommunicationManager::getInstance();

	//comm->send(STOP_FINISH);
	return true;
}

void TCCController::finishScenario() // 시나리오 종료
{
	CommunicationManager* comm = CommunicationManager::getInstance();
	//@신재권 추가
	Message message;
	//@신재권 추가 및 수정
	message.id = STOP_FINISH;
	//comm->send(STOP_FINISH)
	comm->send(message);//시나리오 종료 알리기
	//////////////////////////////////////////////////////
}

void TCCController::drawATS()
{
	CommunicationManager* comm = CommunicationManager::getInstance();
	CMiniProjectGUIDlg* projectGUIDlg = CMiniProjectGUIDlg::getInstance();

	//@신재권 수정
	//atsCurPosition = comm->getAtsCurPosition();
	//atsEndPosition = comm->getAtsEndPosition();
	//////////////////////////////////////////////

	projectGUIDlg->setPosition();
	projectGUIDlg->atsDraw();
}
void TCCController::drawMSS()
{
	CommunicationManager* comm = CommunicationManager::getInstance();
	CMiniProjectGUIDlg* projectGUIDlg = CMiniProjectGUIDlg::getInstance();

	//@신재권 수정
	//atsCurPosition = comm->getAtsCurPosition();
	//atsEndPosition = comm->getAtsEndPosition();
	//mssStartPosition = comm->getMssStartPosition();
	/////////////////////////////////////////////////

	projectGUIDlg->setPosition();
	projectGUIDlg->mssDraw();
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