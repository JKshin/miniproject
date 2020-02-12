#pragma once

#include <string>
#include "NCommCommon.h"

namespace nframework
{
namespace ncomm
{

class NCOMMDLL_API NUdpReceiveDatagramEvent
{
public:
	NUdpReceiveDatagramEvent(void){ maxDatagramLength = 65535; }
	~NUdpReceiveDatagramEvent(void){}

	virtual void onReceiveDatagram(std::string remoteAddress, unsigned short remotePort, unsigned char* data, unsigned short length) = 0;

public:
	std::string		remoteAddress;
	unsigned short	remotePort;
	unsigned short	maxDatagramLength;
};

}	// namespace ncomm
}	// namespace nframework