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
		// ����ź ��ǥ ������ �о�´�.
		memcpy(&msg, &message, sizeof(Message));

		tccController->setMssCurPosition(message.start_pos);
		////////////////////////////////////////////////////

		tccController->drawMSS();
		break;
	case INTERCEPT:
		cout << "���" << endl;
		// ��� ���� UI�� �˸�
		tccController->displayEvent();

		//@����� �����ڵ� �߰�
		//�̻��Ϸκ��� ��� ��ȣ�� �� ���̹Ƿ� ���α׷��� �����ϰ� ��ü�� �Ҹ��Ű��� �޽����� �̻��ϰ� ��� �������� ����.
		break;
	}
}