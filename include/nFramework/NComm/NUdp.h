#pragma once

#include <nFramework/NComm/NCommCommon.h>
#include <set>
#include <asio/asio.hpp>
#include <list>
#include <mutex>

namespace nframework
{
	namespace ncomm
	{

		class NUdpReceiveDatagramEvent;
		class NUdpReceiveDatagramHandler;

		// UDP는 TCP와 달리 session의 개념이 없으므로 NUdp 클래스가 소켓관리, 데이터 송수신 처리를 모두 담당한다.
		class NCOMMDLL_API NUdp

		{

		public:
			NUdp(std::string localAddress, unsigned short localport , std::string remoteAddress, unsigned short remoteport, CastType castType);
			NUdp(unsigned short port, CastType castType);	
			NUdp(std::string localAddress, unsigned short port, CastType castType);	

		private:	
			NUdp(void){}
			~NUdp(void);
			inline void					setAsioIoService(asio::io_service* s) { _io_service = s; }
			bool						open();
			void						close();

			// 2013-02-18 이용헌 추가
			void						receiveSome();
			void						receiveSomeAsync();	
			void						handle_receive(const asio::error_code& error, size_t bytes_transferred);

		public:
			void						receiveSomeAsync(unsigned int i);

			size_t						sendTo(unsigned char* data, size_t dataLength);
			size_t						recvFrom(unsigned char* data, size_t dataLength);
			size_t						sendTo(unsigned char* data, size_t dataLength, std::string remoteAddress, unsigned short remoteport);
			size_t						recvFrom(unsigned char* data, size_t dataLength, std::string remoteAddress, unsigned short remoteport);

			// 2013-02-18 이용헌 추가
			// receive event 객체 설정은 udp socket open이전에 이루어저야 하므로 NComm::registerUDP 이전에 호출해야 한다.
			inline void					setReceiveDatagramEvent(NUdpReceiveDatagramEvent* e) { _receiveEvent = e; }
			void						addReceiveDatagramEvent(NUdpReceiveDatagramEvent* e, std::string remoteAddress, unsigned short remoteport);


			inline void					setMulticastAddress(std::string addr) { _multicastAddress = asio::ip::address::from_string(addr); }
			inline void					setMulticastPort(unsigned short port) { _multicastPort = port; }
		private:
			friend class NComm;
			asio::io_service*	_io_service;
			asio::ip::udp::socket*	_udp_socket;

			std::string					_LAddress;
			unsigned short				_LPort;

			std::string					_RAddress;
			unsigned short				_RPort;

			CastType					_CastType;
			asio::ip::udp::endpoint _receiverEndpoint;
			asio::ip::udp::endpoint _senderEndpoint;

			bool						_valid;			

			NUdpReceiveDatagramEvent*	_receiveEvent;
			unsigned char*				_receivedDatagram;
			unsigned char*				_receivedDatagramForHandler;
			unsigned short				_receivedDatagramLength;

			std::vector<NUdpReceiveDatagramHandler*> _handlerList;


			asio::ip::address	_multicastAddress;
			unsigned short				_multicastPort;

			std::mutex					_mutex;
		};

	}	// namespace ncomm
}	// namespace nframework