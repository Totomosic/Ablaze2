#include "UDPsocket.h"

namespace Ablaze
{
	namespace Networking
	{

		UDPsocket::UDPsocket(SOCKET socket) : Object(),
			m_Socket(socket)
		{

		}

		UDPsocket::~UDPsocket()
		{
			closesocket(m_Socket);
		}

		int UDPsocket::Bind(const SocketAddress& address)
		{
			int error = bind(m_Socket, &address.m_SockAddr, address.GetSize());
			if (error != 0)
			{
				int err = WSAGetLastError();
				AB_ERROR("Socket bind error");
				return err;
			}
			return NO_ERROR;
		}

		int UDPsocket::SendTo(const void* data, int dataLength, const SocketAddress& to)
		{
			int bytesSent = sendto(m_Socket, static_cast<const char*>(data), dataLength, 0, &to.m_SockAddr, to.GetSize());
			if (bytesSent >= 0)
			{
				return bytesSent;
			}
			else
			{
				int err = WSAGetLastError();
				AB_ERROR("Socket send error");
				return -err;
			}
		}

		int UDPsocket::ReceiveFrom(void* buffer, int bufLength, SocketAddress* outFromAddr)
		{
			int fromLength = outFromAddr->GetSize();
			int readCount = 0;
			if (outFromAddr != nullptr)
			{
				readCount = recvfrom(m_Socket, static_cast<char*>(buffer), bufLength, 0, &outFromAddr->m_SockAddr, &fromLength);
			}
			else
			{
				SocketAddress* temp = &SocketAddress();
				readCount = recvfrom(m_Socket, static_cast<char*>(buffer), bufLength, 0, &temp->m_SockAddr, &fromLength);
			}
			if (readCount >= 0)
			{
				return readCount;
			}
			else
			{
				int err = WSAGetLastError();
				AB_ERROR("Socket read error");
				return -err;
			}
		}

		String UDPsocket::ToString() const
		{
			return "UDPsocket";
		}

	}
}