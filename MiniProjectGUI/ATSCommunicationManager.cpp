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
		// �������� ��ǥ ������ �о�´�.
		tccController->setAtsCurPosition(msg.start_pos);

		//���� �������κ��� ��ġ�� ���� �޾����Ƿ� �״�� �̻��Ͽ��� �ش� ������ �۽��Ѵ�.
		msg.id = ATS_POSITION;

		//msg.start_pos�� �״�� �����ִ�.
		mssComm->send(msg);
		break;

	case INTERCEPT_FAIL:
		//�Ķ���Ͱ� 2 = ����.
		tccController->checkIntercept(2);
		msg.id = STOP_FINISH;
		mssComm->send(msg);
		session.send((unsigned char*)& msg, sizeof(Message));
	}
}