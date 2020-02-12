#pragma once

#include <nFramework/NComm/NCommCommon.h>
#include <nFramework/NComm/NTcpSession.h>

namespace nframework
{
namespace ncomm
{

class NCOMMDLL_API NTcpConnectionEvent
{
public:
	NTcpConnectionEvent(void){}
	~NTcpConnectionEvent(void){}

	virtual void onConnected(NTcpSession& session) = 0;
	virtual void onDisconnected(NTcpSession& session) = 0;
};

}	// namespace ncomm
}	// namespace nframework