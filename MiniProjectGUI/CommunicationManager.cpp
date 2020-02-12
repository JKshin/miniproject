#include "pch.h"
#include "CommunicationManager.h"
#include "TCCController.h"

CommunicationManager* CommunicationManager::comm;

CommunicationManager* CommunicationManager::getInstance()
{
	if (!comm) {
		comm = new CommunicationManager();
	}

	return comm;
}

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
	Message msg;
	TCCController* tccController = TCCController::getInstance();
	
	session.recv((unsigned char*)& msg, sizeof(Message));

	switch (message.id) {
	case ATS_POSITION:
		// 공중위협 좌표 정보를 읽어온다.
		memcpy(&msg, &message, sizeof(Message));
		
		//@재권 수정
		//(comm->atsCurPosition).x = message.start_pos.x;
		//(comm->atsCurPosition).y = message.start_pos.y;
		tccController->setAtsCurPosition(message.start_pos);
		////////////////////////////////////////////////////
		
		//@신재권 슈도코드 추가
		//공중 위협으로부터 위치를 수신 받았으므로 그대로 미사일에게 해당 정보를 송신한다.
		msg.id = ATS_POSITION;
		//msg.start_pos은 그대로 남아있다.
		send(msg);


		tccController->drawATS();

		

		break;

	case MSS_POSITION:
		// 유도탄 좌표 정보를 읽어온다.
		memcpy(&msg, &message, sizeof(Message));

		//@재권 수정
		//(comm->mssStartPosition).x = message.start_pos.x;
		//(comm->mssStartPosition).y = message.start_pos.y;
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

//@신재권 수정
//void CommunicationManager::send(header_id id) {
//////////////////////////////////////////////////
void CommunicationManager::send(Message message) {
	//@신재권 수정
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

//@신재권 수정
//void CommunicationManager::setPosition() {
//	TCCController* tccController = TCCController::getInstance();
//
//	atsCurPosition = tccController->getAtsCurPosition();
//	atsEndPosition = tccController->getAtsEndPosition();
//	mssStartPosition = tccController->getMssStartPosition();
//};
/////////////////////////////////////////////////////////////////