#include "AirThreatManager.h"
#include "CommunicationManager.h"

int main() {
	int a;
	CommunicationManager* commManager = CommunicationManager::getInstance();
	AirThreatManager* airThreatManager = AirThreatManager::getInstance();
	commManager->setTcpConnectionInfo("127.0.0.1", 5000);
	commManager->initialize();
	cin >> a;
	return 0;
}