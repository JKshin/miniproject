#pragma once

#include <nFramework/NComm/NCommCommon.h>
#include <nFramework/NComm/NTcpSession.h>

namespace nframework
{
namespace ncomm
{

class NCOMMDLL_API NTcpReceiveDataEvent
{
public:
	NTcpReceiveDataEvent(void){}
	~NTcpReceiveDataEvent(void){}

	virtual void onReceiveData(NTcpSession& session) = 0;
};

}	// namespace ncomm
}	// namespace nframework