#include "SocketUtil.h"
#include "TCPsocket.h"
#include "UDPSocket.h"

namespace Ablaze
{
	namespace Networking
	{

		int SocketUtil::GetLastError()
		{
			return WSAGetLastError();
		}

		void SocketUtil::ReportError(const String& error)
		{
			AB_ERROR("Socket Error");
		}

		TCPsocket* SocketUtil::CreateTCPSocket(AddressFamily family)
		{
			SOCKET s = socket((int)family, SOCK_STREAM, IPPROTO_TCP);
			if (s != INVALID_SOCKET)
			{
				return new TCPsocket(s);
			}
			ReportError("Failed to create TCP socket");
			return nullptr;
		}

		UDPsocket* SocketUtil::CreateUDPSocket(AddressFamily family)
		{
			SOCKET s = socket((int)family, SOCK_DGRAM, IPPROTO_UDP);
			if (s != INVALID_SOCKET)
			{
				return new UDPsocket(s);
			}
			ReportError("Failed to create UDP socket");
			return nullptr;
		}

		TCPsocket* CreateTCPSocket(AddressFamily family)
		{
			return SocketUtil::CreateTCPSocket(family);
		}

		UDPsocket* CreateUDPSocket(AddressFamily family)
		{
			return SocketUtil::CreateUDPSocket(family);
		}

	}
}