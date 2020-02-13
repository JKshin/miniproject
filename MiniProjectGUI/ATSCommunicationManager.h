#pragma once
#include "CommunicationManager.h"
class ATSCommunicationManager:public CommunicationManager
{
private:
	static ATSCommunicationManager* atsComm;
public:
	static CommunicationManager* getInstance();
	void onReceiveData(NTcpSession& session) override;
};

