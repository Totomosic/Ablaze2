#pragma once
#include "SocketAddress.h"

namespace Ablaze
{
	namespace Networking
	{

		class AB_API UDPsocket : public Object
		{
		private:
			SOCKET m_Socket;

		public:
			UDPsocket(SOCKET socket);
			~UDPsocket();

			int Bind(const SocketAddress& address);
			int SendTo(const void* data, int dataLength, const SocketAddress& to);
			int ReceiveFrom(void* buffer, int bufLength, SocketAddress* outFromAddr);

			String ToString() const override;

		};

	}
}