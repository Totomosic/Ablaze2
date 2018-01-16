#include "SocketAddress.h"

namespace Ablaze
{
	namespace Networking
	{

		SocketAddress::SocketAddress(uint32_t inAddress, uint16_t inPort)
		{
			GetAsSockAddrIn()->sin_family = AF_INET;
			GetAsSockAddrIn()->sin_addr.S_un.S_addr = htonl(inAddress);
			GetAsSockAddrIn()->sin_port = htons(inPort);
		}

		SocketAddress::SocketAddress(const String& inAddress, const String& inPort)
		{
			GetAsSockAddrIn()->sin_family = AF_INET;

			addrinfo hint;
			memset(&hint, 0, sizeof(addrinfo));
			hint.ai_family = AF_INET;

			addrinfo* result = new addrinfo;
			int error = getaddrinfo(inAddress.c_str(), inPort.c_str(), &hint, &result);
			if (error != 0 && result != nullptr)
			{
				AB_ERROR("Socket Error");
				freeaddrinfo(result);
				AB_ASSERT(false, "");
			}
			else if (error != 0)
			{
				AB_ERROR("Socket Error");
				AB_ASSERT(false, "");
			}
			while (!result->ai_addr && result->ai_next)
			{
				result = result->ai_next;
			}
			if (!result->ai_addr)
			{
				AB_ERROR("Socket Error");
				freeaddrinfo(result);
				AB_ASSERT(false, "");
			}

			memcpy(&m_SockAddr, result->ai_addr, sizeof(sockaddr));

			freeaddrinfo(result);
		}

		SocketAddress::SocketAddress(const String& inAddress, uint16_t inPort) : SocketAddress(inAddress, std::to_string(inPort))
		{
		
		}

		SocketAddress::SocketAddress(const sockaddr& inSockAddr)
		{
			memcpy(&m_SockAddr, &inSockAddr, sizeof(sockaddr));
		}

		SocketAddress::SocketAddress() : SocketAddress(sockaddr())
		{

		}

		size_t SocketAddress::GetSize() const
		{
			return sizeof(sockaddr);
		}

		sockaddr_in* SocketAddress::GetAsSockAddrIn()
		{
			return reinterpret_cast<sockaddr_in*>(&m_SockAddr);
		}

	}
}