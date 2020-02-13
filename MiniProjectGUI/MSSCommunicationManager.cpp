#include "pch.h"
#include "MSSCommunicationManager.h"
#include "ATSCommunicationManager.h"
#include "TCCController.h"
#include "MiniProjectGUIDlg.h"

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
	CMiniProjectGUIDlg* guiDlg = CMiniProjectGUIDlg::getInstance();
	Message msg;
	session.recv((unsigned char*)& msg, sizeof(Message));
	//guiDlg->Alert(L"Received Data!");
	switch (msg.id) {
	case MSS_POSITION:
		//guiDlg->Alert(L"Received MSS_POSITION!");
		// ����ź ��ǥ ������ �о�´�.

		tccController->setMssCurPosition(msg.start_pos);
		////////////////////////////////////////////////////

		//tccController->drawMSS();
		break;
	case INTERCEPT:
		//guiDlg->Alert(L"Received INTERCEPT!");
		// ��� ���� UI�� �˸�
		tccController->displayEvent();
		message.id = STOP_FINISH;
		session.send((unsigned char*)& message, sizeof(Message));
		atsComm->send(message);

		//@����� �����ڵ� �߰�
		//�̻��Ϸκ��� ��� ��ȣ�� �� ���̹Ƿ� ���α׷��� �����ϰ� ��ü�� �Ҹ��Ű��� �޽����� �̻��ϰ� ��� �������� ����.
		break;
	}
}