#pragma once
#include "CommunicationManager.h"
class MSSCommunicationManager:public CommunicationManager
{
private:
	static MSSCommunicationManager* mssComm;
public:
	static CommunicationManager* getInstance();
	void onReceiveData(NTcpSession& session) override;
};

