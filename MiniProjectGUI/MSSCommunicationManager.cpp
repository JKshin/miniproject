#include "pch.h"
#include "MSSCommunicationManager.h"
#include "ATSCommunicationManager.h"
#include "TCCController.h"

MSSCommunicationManager* MSSCommunicationManager::mssComm;

CommunicationManager* MSSCommunicationManager::getInstance()
{
	if (!mssComm) {
		mssComm = new MSSCommunicationManager();
	}

	return mssComm;
}

void MSSCommunicationManager::onReceiveData(NTcpSession& session) {
	CommunicationManager* atsComm = ATSCommunicationManager::getInstance();
	TCCController* tccController = TCCController::getInstance();
	Message msg;
	session.recv((unsigned char*)& msg, sizeof(Message));

	switch (message.id) {
	case MSS_POSITION:
		// 유도탄 좌표 정보를 읽어온다.
		memcpy(&msg, &message, sizeof(Message));

		tccController->setMssCurPosition(message.start_pos);
		////////////////////////////////////////////////////

		tccController->drawMSS();
		break;
	case INTERCEPT:
		cout << "요격" << endl;
		// 요격 여부 UI에 알림
		tccController->displayEvent();

		//@신재권 슈도코드 추가
		//미사일로부터 요격 신호가 온 것이므로 프로그램을 종료하고 객체를 소멸시키라는 메시지를 미사일과 대공 위협에게 전달.
		break;
	}
}