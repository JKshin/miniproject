#include "CommunicationManager.h"


CommunicationManager::CommunicationManager()
{
	ncomm = &NComm::getInstance();
}

CommunicationManager::~CommunicationManager()
{
	ncomm = nullptr;
}

void CommunicationManager::onConnected(NTcpSession& session)
{
	std::cout << "Connected to server " << session.getPeerAddress() << endl;
	this->session = &session;
	tcpConnected = true;
}

void CommunicationManager::onDisconnected(NTcpSession& session)
{
	std::cout << "Disonnected from server " << session.getPeerAddress() << endl;
	this->session = nullptr;
	tcpConnected = false;
}

//enum header_id {
//	START, // 시나리오 시작
//	STOP_FINISH,  // 시나리오 중지/종료
//	FIRE_MISSILE, // 유도탄 발사
//	ATS_POSITION, // ATS 현재 위치 
//	MSS_POSITION, // 유도탄 현재 위치
//	INTERCEPT // 요격 여부
//};
//
//struct Point {
//	double x;
//	double y;
//};
//
//struct Message {
//	header_id id;
//	Point start_pos;
//	Point end_pos;
//};

void CommunicationManager::onReceiveData(NTcpSession& session)
{
	Message Message;

	session.recv((unsigned char*)& Message, sizeof(Message));

	do{
		switch (Message.id)
		{
		case START:
		{
			//초기 위치 설정 및 발사 대기
		}
		break;
		case STOP_FINISH:
		{
			//객체 소멸
		}
		break;

		case FIRE_MISSILE:
		{
			//미사일 발사
		}
		break;

		case ATS_POSITION:
		{
			//ATS_POSITION 갱신
		}
		break;
		}
	}while (Message.id != STOP_FINISH);
}

bool CommunicationManager::initialize()
{
	bool init = true;
	this->tcpClient = new NTcpClient(this->tcpConnIP, this->tcpPort);

	tcpClient->setTcpConnectionEvent(this);
	tcpClient->setTcpReceiveDataEvent(this);

	if (!ncomm->registerTcpClient(tcpClient))
	{
		init = false;
	}

	return init;
}

void CommunicationManager::sendMessage(Message message)
{
	if (session != nullptr)
		session->send((unsigned char*)& message, sizeof(Message));
}

void CommunicationManager::setTcpConnectionInfo(std::string ip, ushort port)
{
	tcpConnIP = ip;
	tcpPort = port;
}