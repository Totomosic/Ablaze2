#include "TCPsocket.h"

namespace Ablaze
{
	namespace Networking
	{

		TCPsocket::TCPsocket(SOCKET socket) : Object(),
			m_Socket(socket)
		{
		
		}

		TCPsocket::~TCPsocket()
		{
			// Shutdown??
			closesocket(m_Socket);
		}

		int TCPsocket::Bind(const SocketAddress& address)
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

		int TCPsocket::Listen(int backlog)
		{
			int err = listen(m_Socket, backlog);
			if (err < 0)
			{
				int res = WSAGetLastError();
				AB_ERROR("Socket Error");
				return -res;
			}
			return NO_ERROR;
		}

		TCPsocket* TCPsocket::Accept(SocketAddress* outFromAddr)
		{
			int length = outFromAddr->GetSize();
			SOCKET newSocket = 0;
			if (outFromAddr != nullptr)
			{
				newSocket = accept(m_Socket, &outFromAddr->m_SockAddr, &length);
			}
			else
			{
				SocketAddress* temp = &SocketAddress();
				newSocket = accept(m_Socket, &temp->m_SockAddr, &length);
			}
			if (newSocket != INVALID_SOCKET)
			{
				return new TCPsocket(newSocket);
			}
			AB_ERROR("Socket Error");
			return nullptr;
		}

		int TCPsocket::Connect(const SocketAddress& address)
		{
			int err = connect(m_Socket, &address.m_SockAddr, address.GetSize());
			if (err < 0)
			{
				int res = WSAGetLastError();
				AB_ERROR("Socket Error");
				return -res;
			}
			return NO_ERROR;
		}

		int TCPsocket::Send(const void* data, int dataLength)
		{
			int bytesSent = send(m_Socket, static_cast<const char*>(data), dataLength, 0);
			if (bytesSent < 0)
			{
				int error = WSAGetLastError();
				AB_ERROR("Socket send error");
				return -error;
			}
			return bytesSent;
		}

		int TCPsocket::Receive(void* buffer, int bufLength)
		{
			int bytesReceived = recv(m_Socket, static_cast<char*>(buffer), bufLength, 0);
			if (bytesReceived < 0)
			{
				int error = WSAGetLastError();
				AB_ERROR("Socket send error");
				return -error;
			}
			return bytesReceived;
		}

		String TCPsocket::ToString() const
		{
			return "TCPsocket";
		}

	}
}