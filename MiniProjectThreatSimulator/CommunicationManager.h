#pragma once

#include "msg.h"
#include <nFramework/NComm/NCommMain.h>
#include <string>
#include <map>
#include <functional>
#include <vector>
#include <string>

using namespace nframework::ncomm;

typedef unsigned char byte;
typedef unsigned short ushort;
typedef unsigned int uint;

class CommunicationManager : public NTcpConnectionEvent, public NTcpReceiveDataEvent
{
public:
	CommunicationManager();
	~CommunicationManager();

	// overriding methods : NComm
	void onConnected(NTcpSession& ssesion) override;
	void onDisconnected(NTcpSession& session) override;
	void onReceiveData(NTcpSession& session) override;

	// normal methods
	void setTcpConnectionInfo(std::string ip, ushort port);
	bool initialize();
	void release();
	static CommunicationManager* getInstance();
	void sendMessage(Message message);

private:
	NComm* ncomm = nullptr;
	NTcpClient* tcpClient = nullptr;
	NTcpSession* session = nullptr;
	static CommunicationManager* commManager;

	bool tcpConnected = false;
	std::string tcpConnIP;
	ushort tcpPort;	
	CommunicationManager() {};
	~CommunicationManager() {};
};

