#include "Exception.h"
#include "Utility.h"

#include <string>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>

using namespace std;
using namespace Utility;

typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned int DWORD;

class IPEndPoint
{
private:
	DWORD _IPv4Address;
	WORD _Port;

	DWORD _GetIPv4AddressFromString(string __IPv4AddressString);

public:
	IPEndPoint();
	IPEndPoint(DWORD __IPv4Address, WORD __Port);
	IPEndPoint(string __IPv4AddressString, WORD __Port);
	
	DWORD IPv4Address();
	WORD Port();
	
	string ToString();
};

class Socket
{
private:
	int _SystemSocket;
	int _Domain;
	int _Type;
	int _Protocol;
	
	IPEndPoint _LocalEndPoint;
	IPEndPoint _RemoteEndPoint;

public:
	Socket(int __Domain, int __Type, int __Protocol);

	IPEndPoint LocalEndPoint();
	IPEndPoint RemoteEndPoint();
	
	void Bind(IPEndPoint __LocalEndPoint);
	void Listen(int __Backlog);
	Socket Accept();
	void Receive(BYTE *__Buffer, size_t __Length);
	void Send(BYTE *__Buffer, size_t __Length);
	void Close();
};
