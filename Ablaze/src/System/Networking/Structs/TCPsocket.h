#pragma once
#include "SocketAddress.h"

namespace Ablaze
{
	namespace Networking
	{
		
		class AB_API TCPsocket : public Object
		{
		private:
			SOCKET m_Socket;

		public:
			TCPsocket(SOCKET socket);
			~TCPsocket();

			int Bind(const SocketAddress& address);
			int Listen(int backlog = 32);
			TCPsocket* Accept(SocketAddress* outFromAddress);
			int Connect(const SocketAddress& address);
			int Send(const void* data, int dataLength);
			int Receive(void* buffer, int bufLength);

			String ToString() const override;

		};

	}
}