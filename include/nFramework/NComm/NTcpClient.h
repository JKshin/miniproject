#pragma once
#include <nFramework/NComm/NCommCommon.h>
#include <nFramework/NComm/NTcpConnectionEvent.h>
#include <nFramework/NComm/NTcpSession.h>
#include <string>
#include <asio/asio.hpp>

namespace nframework
{
//class NThreadPool;

namespace ncomm
{

class NTcpConnectionEvent;
class NTcpReceiveDataEvent;

class NCOMMDLL_API NTcpClient : public NTcpConnectionEvent
{
public:
	NTcpClient(std::string serverAddr, unsigned short serverPort);	
	NTcpClient(std::string serverAddr, unsigned short serverPort, bool isTryToReconnect);
	~NTcpClient(void);

	virtual void				onConnected(NTcpSession& session);
	virtual void				onDisconnected(NTcpSession& session);

private:	
	NTcpClient(){};	
	inline void					setAsioIoService(asio::io_service* s) { _io_service = s; }

	bool						connect(unsigned int timeout = 0);
	bool						disconnect();	

	void						reconnectThread(void* arg);

public:
	inline void					setTcpConnectionEvent(NTcpConnectionEvent* e) { _c_event = e; }
	inline void					setTcpReceiveDataEvent(NTcpReceiveDataEvent* e) { _r_event = e; }

	inline bool					isDisconnecting() { return _disconnecting; }

	inline NTcpSession*			getTcpSession() { return _session; }

	inline void					setBufferSize(size_t s) { _bufferSize = s; }
	inline size_t				getBufferSize() { return _bufferSize; }

	size_t						send(unsigned char* data, size_t dataLength);
	size_t						recv(unsigned char* data, size_t dataLength);
	
private:
	friend class NComm;

	asio::io_service*	_io_service;

	NTcpConnectionEvent*		_c_event;
	NTcpReceiveDataEvent*		_r_event;

	NTcpSession*				_session;

	bool						_connected;

	std::string					_serverAddress;
	unsigned short				_serverPort;

	size_t						_bufferSize;

	//NThreadPool*				_threadPool;
	bool						_isTryToReconnect;
	bool						_disconnecting;
};

}	// namespace ncomm
}	// namespace nframework