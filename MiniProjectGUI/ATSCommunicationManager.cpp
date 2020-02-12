#include "pch.h"
#include "ATSCommunicationManager.h"
#include "MSSCommunicationManager.h"
#include "TCCController.h"

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
	TCCController* tccController = TCCController::getInstance();
	Message msg;
	session.recv((unsigned char*)& msg, sizeof(Message));

	switch (message.id) {
	case ATS_POSITION:
		// �������� ��ǥ ������ �о�´�.
		memcpy(&msg, &message, sizeof(Message));

		tccController->setAtsCurPosition(message.start_pos);
		////////////////////////////////////////////////////

		//@����� �����ڵ� �߰�
		//���� �������κ��� ��ġ�� ���� �޾����Ƿ� �״�� �̻��Ͽ��� �ش� ������ �۽��Ѵ�.
		msg.id = ATS_POSITION;
		//msg.start_pos�� �״�� �����ִ�.
		mssComm->send(msg);
		tccController->drawATS();



		break;
	}
}