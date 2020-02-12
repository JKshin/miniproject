#pragma once

#include <string>
#include <asio/asio.hpp>
#include "NCommCommon.h"

namespace nframework
{
namespace ncomm
{

class NUdpReceiveDatagramEvent;
class NUdp;

class NUdpReceiveDatagramHandler
{
public:
	NUdpReceiveDatagramHandler(void);
	NUdpReceiveDatagramHandler(unsigned short bufferSize);
	~NUdpReceiveDatagramHandler(void);	

	void handle_receive(const asio::error_code& error, size_t bytes_transferred);

	inline void setID(unsigned int id) { _id = id; }
	inline void setUdpObject(NUdp* udp) { _udpObj = udp; }
	inline void setEventListener(NUdpReceiveDatagramEvent* e) { _eventListner = e; }
	inline unsigned char* getBuffer() { return _buffer; }
	inline unsigned short getBufferSize() { return _bufferSize; }

public:
	asio::ip::udp::endpoint	_senderEndpoint;

private:
	unsigned int					_id;
	unsigned char*					_buffer;
	unsigned short					_bufferSize;

	NUdpReceiveDatagramEvent*		_eventListner;
	NUdp*							_udpObj;
};

}	// namespace ncomm
}	// namespace nframework