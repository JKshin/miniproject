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
//	START, // �ó����� ����
//	STOP_FINISH,  // �ó����� ����/����
//	FIRE_MISSILE, // ����ź �߻�
//	ATS_POSITION, // ATS ���� ��ġ 
//	MSS_POSITION, // ����ź ���� ��ġ
//	INTERCEPT // ��� ����
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
			//�ʱ� ��ġ ���� �� �߻� ���
		}
		break;
		case STOP_FINISH:
		{
			//��ü �Ҹ�
		}
		break;

		case FIRE_MISSILE:
		{
			//�̻��� �߻�
		}
		break;

		case ATS_POSITION:
		{
			//ATS_POSITION ����
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