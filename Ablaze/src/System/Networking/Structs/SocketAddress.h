#pragma once
#include "Common.h"
#include "System\Networking\NetworkIncludes.h"

namespace Ablaze
{
	namespace Networking
	{

		struct AB_API SocketAddress
		{
		public:
			sockaddr m_SockAddr;

		public:
			SocketAddress(uint32_t inAddress, uint16_t inPort);
			SocketAddress(const String& inAddress, const String& inPort);
			SocketAddress(const String& inAddress, uint16_t inPort);
			SocketAddress(const sockaddr& inSockAddr);
			SocketAddress();

			size_t GetSize() const;

		private:
			sockaddr_in* GetAsSockAddrIn();

		};

	}
}