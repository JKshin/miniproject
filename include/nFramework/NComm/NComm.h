#pragma once
#include <nFramework/NComm/NCommCommon.h>
#include <nFramework/NComm/NTcpConnectionEvent.h>
#include <cstdlib>
#include <asio/asio.hpp>
#include <set>
#include <functional>

namespace nframework
{
namespace ncomm
{


class NTcpServer;
class NTcpClient;
class NTcpSession;
class NUdp;
class NBufferPool;

class NCOMMDLL_API NComm : public NTcpConnectionEvent
{
public:
	NComm();
	~NComm();

	static NComm& getInstance();

	bool registerTcpServer(NTcpServer*);
	bool registerTcpClient(NTcpClient*, unsigned int timeout = 0);	// timeout은 millisec 단위	
	bool removeTcpServer(NTcpServer*);
	bool removeTcpClient(NTcpClient*);
	bool registerUdp(NUdp*);
	bool removeUdp(NUdp*);

	void stop();

	inline asio::io_service* getIOService() { return &_io_service; }	

	virtual void onConnected(NTcpSession& session);
	virtual void onDisconnected(NTcpSession& session);

private:
	// Singleton Object
	static void createInstance();
	static void releaseInstance();
	static void onDeadReference();
	static void killNComm();

	// run loop
	void runLoop(void* argv);

private:
	static NComm*			_singleton;		// singleton
	static bool				_destroyed;		// singleton object destroy 여부
	asio::io_service		_io_service;	// asio io_service 객체

	std::set<NTcpClient*>	_setClient;		// NTcpClient 객체 집합
	std::set<NTcpServer*>	_setServer;		// NTcpServer 객체 집합
	std::set<NUdp*>			_setUdp;		// NUdp 객체 집합
	
	bool					_continueLoop;

	NBufferPool*			_bufferPool;
};

}	// namespace ncomm
}	// namespace nframework