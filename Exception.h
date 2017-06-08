#include <string>

using namespace std;

class Exception
{
private:
	string _Message;

public:
	Exception(string __Message);
	
	string Message();
};

class IPAddressFormatException : Exception
{
public:
	IPAddressFormatException(string __Message);
};

class SocketException : Exception
{
public:
	SocketException(string __Message);
};
