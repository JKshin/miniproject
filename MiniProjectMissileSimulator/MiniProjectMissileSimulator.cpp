#include "CommunicationManager.h"
#include <iostream>

int main()
{
	std::string ip = "127.0.0.1";
	short port = 7000;

	CommunicationManager commManager;
	commManager.setTcpConnectionInfo(ip, port);
	commManager.initialize();

	cin.get();
	
	
	

	return 0;
}