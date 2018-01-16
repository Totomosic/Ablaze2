#pragma once
#include <WinSock2.h>
#include <WS2tcpip.h>

#define SCK_VERSION 0x0202

namespace Ablaze
{
	namespace Networking
	{

		enum class AddressFamily
		{
			INET = AF_INET,
			INET6 = AF_INET6
		};

	}
}