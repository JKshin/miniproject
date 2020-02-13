#include "pch.h"
#include "ATSCommunicationManager.h"
#include "MSSCommunicationManager.h"
#include "TCCController.h"
#include "MiniProjectGUIDlg.h"

ATSCommunicationManager* ATSCommunicationManager::atsComm;

CommunicationManager* ATSCommunicationManager::getInstance()
{
	if (!atsComm) {
		atsComm = new ATSCommunicationManager();
	}

	return atsComm;
}

void ATSCommunicationManager::onReceiveData(NTcpSession& session) {
	CommunicationManager* mssComm = MSSCommunicationManager::getInstance();
	CMiniProjectGUIDlg* guiDlg = CMiniProjectGUIDlg::getInstance();
	TCCController* tccController = TCCController::getInstance();
	Message msg;
	session.recv((unsigned char*)& msg, sizeof(Message));

	switch (msg.id) {
	case ATS_POSITION:
		// 공중위협 좌표 정보를 읽어온다.
		//guiDlg->Alert(L"Received ATS_POSITION!");

		tccController->setAtsCurPosition(msg.start_pos);
		////////////////////////////////////////////////////

		//@신재권 슈도코드 추가
		//공중 위협으로부터 위치를 수신 받았으므로 그대로 미사일에게 해당 정보를 송신한다.
		msg.id = ATS_POSITION;
		//msg.start_pos은 그대로 남아있다.
		mssComm->send(msg);
		tccController->drawATS();



		break;
	}
}