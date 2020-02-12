#include "pch.h"
#include "CommunicationManager.h"
#include "TCCController.h"
#include "MiniProjectGUIDlg.h"

//@����� ����
//CommunicationManager* CommunicationManager::comm;
//
//CommunicationManager* CommunicationManager::getInstance()
//{
//	if (!comm) {
//		comm = new CommunicationManager();
//	}
//
//	return comm;
//}

CommunicationManager::CommunicationManager() {
	ncomm = &NComm::getInstance();
}

CommunicationManager::~CommunicationManager() {
	ncomm = nullptr;
}

void CommunicationManager::onConnected(NTcpSession& session) {
	cout << "Connected to server " << session.getPeerAddress() << endl;
	this->session = &session;
	tcp_connected = true;

	// isEnd = false;
}

void CommunicationManager::onDisconnected(NTcpSession& session) {
	cout << "Disonnected from server " << session.getPeerAddress() << endl;
	this->session = nullptr;
	tcp_connected = false;
}

void CommunicationManager::onReceiveData(NTcpSession& session) {
	CMiniProjectGUIDlg* guiDlg = CMiniProjectGUIDlg::getInstance();
	Message msg;
	session.recv((unsigned char*)& msg, sizeof(Message));
	guiDlg->Alert(L"Received CommMessage!");
	//@����� ����
	//�� �Լ��� ����
}

void CommunicationManager::setTcpConnectionInfo(string ip, ushort port)
{
	tcpConnIP = ip;
	tcpPort = port;
}

bool CommunicationManager::connect()
{
	bool init = true;

	this->tcpServer = new NTcpServer(this->tcpConnIP, this->tcpPort);

	tcpServer->setTcpConnectionEvent(this);
	tcpServer->setTcpReceiveDataEvent(this);

	if (!ncomm->registerTcpServer(tcpServer))
	{
		init = false;
	}

	return init;
}

void CommunicationManager::disconnect()
{
	if (tcpServer)
	{
		ncomm->removeTcpServer(tcpServer);
		tcpServer = nullptr;
	}
}

//@����� ����
//void CommunicationManager::send(header_id id) {
//////////////////////////////////////////////////
void CommunicationManager::send(Message message) {
	//@����� ����
	//message.id = id;
	//////////////////

	/*switch (id) {
	case START:

		break;
	case STOP_FINISH:

		break;
	case FIRE_MISSILE:
		
		break;
	case ATS_POSITION:
		
		break;
	}*/

	if (session != nullptr) {
		session->send((unsigned char*)&message, sizeof(Message));
	}
}

void CommunicationManager::receive() {

}

//@����� ����
//void CommunicationManager::setPosition() {
//	TCCController* tccController = TCCController::getInstance();
//
//	atsCurPosition = tccController->getAtsCurPosition();
//	atsEndPosition = tccController->getAtsEndPosition();
//	mssStartPosition = tccController->getMssStartPosition();
//};
/////////////////////////////////////////////////////////////////