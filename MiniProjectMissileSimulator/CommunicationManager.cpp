#include "CommunicationManager.h"
#include "MissileManager.h"
#include "MissionManager.h"

CommunicationManager* CommunicationManager::commManager;

CommunicationManager* CommunicationManager::getInstance() {
	if (!commManager) {
		commManager = new CommunicationManager();
	}
	return commManager;
}

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
	Message message;
	MissionManager* missionManager = MissionManager::getInstance();
	MissileManager* missileManager = MissileManager::getInstance();

	session.recv((unsigned char*)& message, sizeof(Message));

	do {
		switch (message.id)
		{
			//START, // �ó����� ����
			//	STOP_FINISH,  // �ó����� ����/����
			//	FIRE_MISSILE, // ����ź �߻�
			//	ATS_POSITION, // ATS ���� ��ġ 
			//	MSS_POSITION, // ����ź ���� ��ġ
			//	INTERCEPT // ��� ����
		case START:
		{
			//�ʱ� ��ġ �� ���� ��ġ ���� �� �̷�
			cout << "START!!!" << endl;
			missileManager->initStartPosition(message.start_pos);

		}
		break;
		case FIRE_MISSILE:
		{
			missileManager->start();
			missionManager->start();
		}
		break;
		case ATS_POSITION:
		{
			missionManager->setPositionOfATS(message.start_pos);
		}
		break;
		case STOP_FINISH:
		{
			missileManager->stop();
			missionManager->stop();
			//��ü �Ҹ�
		}
		break;
		}
	} while (message.id != STOP_FINISH);
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