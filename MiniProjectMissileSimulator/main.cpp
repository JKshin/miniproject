#include "MissileManager.h"
#include "MissionManager.h"
#include "CommunicationManager.h"

int main() {
	int a;
	//@����� ����
	ushort port;
	CommunicationManager* commManager = CommunicationManager::getInstance();
	MissionManager* missionManager = MissionManager::getInstance();
	MissileManager* misileManager = MissileManager::getInstance();
	cout << "port : ";
	cin >> port;
	commManager->setTcpConnectionInfo("127.0.0.1", port);
	commManager->initialize();
	cin >> a;
	return 0;
}