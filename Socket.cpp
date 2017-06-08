#include "Socket.h"

/* class : IPEndPoint Function Definitions */

/* private functions */

DWORD IPEndPoint::_GetIPv4AddressFromString(string __IPv4AddressString)
{
	DWORD result = inet_addr(__IPv4AddressString.c_str());
	if (result == INADDR_NONE)
	{
		throw Exception("IPv4 address format is illegal.");
	}
	return result;
}

/* private functions end */

/* public functions */

IPEndPoint::IPEndPoint() : _IPv4Address(0), _Port(0) { }

IPEndPoint::IPEndPoint(DWORD __IPv4Address, WORD __Port) : _IPv4Address(__IPv4Address), _Port(__Port) { }

IPEndPoint::IPEndPoint(string __IPv4AddressString, WORD __Port) : _Port(htons(__Port))
{
	_IPv4Address = _GetIPv4AddressFromString(__IPv4AddressString);
}

DWORD IPEndPoint::IPv4Address()
{
	return _IPv4Address;
}

WORD IPEndPoint::Port()
{
	return _Port;
}

string IPEndPoint::ToString()
{
	in_addr tmp;
	tmp.s_addr = _IPv4Address;
	return (string)inet_ntoa(tmp) + ':' + _Port;
}

/* public functions end */

/* class : IPEndPoint Functions Definitions end */

/* class : Socket Functions Definitions */

/* public functions */

Socket::Socket(int __Domain, int __Type, int __Protocol)
{
	_Domain = __Domain;
	_Type = __Type;
	_Protocol = __Protocol;
	_SystemSocket = socket(__Domain, __Type, __Protocol);
	if (_SystemSocket == -1)
	{
		throw Exception("Socket cannot be created.\nWe are sorry, but no more information can be provided.");
	}
}

IPEndPoint Socket::LocalEndPoint()
{
	return _LocalEndPoint;
}

IPEndPoint Socket::RemoteEndPoint()
{
	return _RemoteEndPoint;
}

void Socket::Bind(IPEndPoint __LocalEndPoint)
{
	_LocalEndPoint = __LocalEndPoint;
	sockaddr_in addr;
	addr.sin_family = _Domain;
	addr.sin_addr.s_addr = _LocalEndPoint.IPv4Address();
	addr.sin_port = _LocalEndPoint.Port();
	int ret = bind(_SystemSocket, (sockaddr*)&addr, sizeof(addr));
	if (ret == -1)
	{
		throw Exception("Socket::Bind() failed.\nWe are sorry, but no more information can be provided.");
	}
}

void Socket::Listen(int __Backlog)
{
	int ret = listen(_SystemSocket, __Backlog);
	if (ret == -1)
	{
		throw Exception("Socket::Listen() failed.\nWe are sorry, but no more information can be provided.");
	}
}

Socket Socket::Accept()
{
	sockaddr_in addr;
	socklen_t len = sizeof(addr);
	int sock = accept(_SystemSocket, (sockaddr*)&addr, &len);
	if (sock == -1)
	{
		throw SocketException("Socket::Accept() failed.\nWe are sorry, but no more information can be provided.");
	}
	Socket result = *this;
	result._SystemSocket = sock;
	result._RemoteEndPoint = IPEndPoint(addr.sin_addr.s_addr, addr.sin_port);
	return result;
}

void Socket::Receive(BYTE *__Buffer, size_t __Length)
{
	recv(_SystemSocket, __Buffer, __Length, 0);
}

void Socket::Send(BYTE *__Buffer, size_t __Length)
{
	send(_SystemSocket, __Buffer, __Length, 0);
}

void Socket::Close()
{
	close(_SystemSocket);
}

/* public functions end */

/* class : Socket Functions Definitions end */
