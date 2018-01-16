#pragma once
#include "Common.h"
#include "System\Networking\NetworkIncludes.h"

namespace Ablaze
{
	namespace Networking
	{

		class TCPsocket;
		class UDPsocket;

		class AB_API SocketUtil
		{
		public:
			SocketUtil() = delete;

			static int GetLastError();
			static void ReportError(const String& error);

			static TCPsocket* CreateTCPSocket(AddressFamily family);
			static UDPsocket* CreateUDPSocket(AddressFamily family);

		};

		TCPsocket* CreateTCPSocket(AddressFamily family = AddressFamily::INET);
		UDPsocket* CreateUDPSocket(AddressFamily family = AddressFamily::INET);

	}
}