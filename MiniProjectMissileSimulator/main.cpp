#include "MissileManager.h"
#include "MissionManager.h"
#include "CommunicationManager.h"

int main() {
	int a;
	CommunicationManager* commManager = CommunicationManager::getInstance();
	MissionManager* missionManager = MissionManager::getInstance();
	MissileManager* misileManager = MissileManager::getInstance();
	commManager->setTcpConnectionInfo("127.0.0.1", 5000);
	commManager->initialize();
	cin >> a;
	return 0;
}