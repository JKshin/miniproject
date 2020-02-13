#pragma once
#include "msg.h"
#include <nFramework/NComm/NCommMain.h>
#include <iostream>
#include <string>

using namespace std;
using namespace nframework::ncomm;

typedef unsigned char byte;
typedef unsigned int uint;
typedef unsigned short ushort;


class CommunicationManager : public NTcpConnectionEvent, public NTcpReceiveDataEvent {
//@신재권 수정
//private:
protected:

	Message message; // 통신 메시지
	header_id header;

	NComm* ncomm = nullptr;
	NTcpServer* tcpServer = nullptr;
	NTcpSession* session = nullptr;

	string tcpConnIP;
	ushort tcpPort;

	static CommunicationManager* comm;

	// Constructor, Destructor
	CommunicationManager();
	~CommunicationManager();
public:
	bool tcp_connected = false;

	// overriding methods
	void onConnected(NTcpSession& session) override;
	void onDisconnected(NTcpSession& session) override;
	void onReceiveData(NTcpSession& session) override;

	// normal methods
	void setTcpConnectionInfo(string ip, ushort port);
	bool connect();
	void disconnect();

	void send(Message message);
	void receive();

	//@신재권 수정
	//static CommunicationManager* getInstance();


};
