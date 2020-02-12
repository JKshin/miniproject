#pragma once
#include <nFramework/NComm/NCommCommon.h>

#include <asio/asio.hpp>
#include <asio/asio/placeholders.hpp>

#include <string>
#include <deque>
#include <mutex>

using namespace std;

namespace nframework
{
namespace ncomm
{

class NTcpConnectionEvent;
class NTcpReceiveDataEvent;

class NCOMMDLL_API NTcpSession
{
private:
	NTcpSession(asio::io_service& io_service);
	~NTcpSession(void);

	friend class NTcpServer;
	friend class NTcpClient;

public:	
	bool			disconnect();
	inline bool		getConnected() { return _connected; }
	
	std::string		getPeerAddress();
	unsigned short	getPeerPort();
	std::string		getLocalAddress();
	unsigned short	getLocalPort();
	asio::ip::tcp::socket&	getSocket() { return _tcp_socket; }
	int				getSocketHandle();
	void			setBufferSize(size_t s) { _bufferSize = s; }

	void			registerConnectionEventCallback(NTcpConnectionEvent*);
	void			registerReceiveDataEventCallback(NTcpReceiveDataEvent*);

	size_t			send(unsigned char* data, size_t dataLength);
	size_t			recv(unsigned char* data, size_t dataLength);

	void			start();

private:
	bool			connect(std::string serverAddress, unsigned short serverPort, unsigned int timeout = 0);	

	void			readSome();

	void			handle_connect(const asio::error_code& ec);
	void			handle_read(const asio::error_code& error, size_t bytes_transferred);
	void			handle_write(const asio::error_code& error);

	void			block_thread(unsigned int timeout);

public:
	unsigned int					_number;

private:
	bool							_connected;
	asio::ip::tcp::socket	_tcp_socket;
	deque<NTcpConnectionEvent*>		_connectionEvent;
	NTcpReceiveDataEvent*			_receiveDataEvent;
	asio::io_service*		_io_service;
	
	bool							_asyncConnectResult;
	bool							_asyncWaitTimeout;

	size_t							_bufferSize;	
	
	struct BufferInfo {
		unsigned char*			data;
		size_t			bytesTransferred;
		unsigned int	dataOffset;

		BufferInfo() {
			data = NULL;
			bytesTransferred = 0;
			dataOffset = 0;
		}
	};
	std::deque<BufferInfo>				_dataQueue;

	bool								_valid;

	std::mutex							_mutex;
};

}	// namespace ncomm
}	// namespace nframework