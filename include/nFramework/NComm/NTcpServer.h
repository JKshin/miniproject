#pragma once
#include <nFramework/NComm/NCommCommon.h>
#include <nFramework/NComm/NTcpConnectionEvent.h>
#include <nFramework/NComm/NTcpSession.h>
#include <set>
#include <asio/asio.hpp>


namespace nframework
{
namespace ncomm
{

class NTcpConnectionEvent;
class NTcpReceiveDataEvent;

class NCOMMDLL_API NTcpServer : public NTcpConnectionEvent
{
public:
	NTcpServer(std::string serverAddr, unsigned short serverPort);	
	NTcpServer(unsigned short serverPort);	

	virtual void				onConnected(NTcpSession& session);
	virtual void				onDisconnected(NTcpSession& session);

private:
	NTcpServer(void){}
	~NTcpServer(void);
	inline void					setAsioIoService(asio::io_service* s) { _io_service = s; }

	bool						accept();
	bool						stopServer();

	void						handle_accept(NTcpSession* new_session, const asio::error_code& error);

public:	
	inline void					setTcpConnectionEvent(NTcpConnectionEvent* e) { _c_event = e; }
	inline void					setTcpReceiveDataEvent(NTcpReceiveDataEvent* e) { _r_event = e; }

	inline void					setBufferSize(size_t s) { _bufferSize = s; }
	inline size_t				getBufferSize() { return _bufferSize; }

private:
	friend class NComm;
	asio::io_service*	_io_service;
	asio::ip::tcp::acceptor*	_acceptor;

	NTcpConnectionEvent*		_c_event;
	NTcpReceiveDataEvent*		_r_event;

	std::set<NTcpSession*>		_setSession;

	std::string					_address;
	unsigned short				_port;
	bool						_startServer;

	size_t						_bufferSize;
};

}	// namespace ncomm
}	// namespace nframework