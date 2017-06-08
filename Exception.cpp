#include "Exception.h"

/* class : Exception Function Definitions */

/* public functions */

Exception::Exception(string __Message) : _Message(__Message)
{
}

string Exception::Message()
{
	return _Message;
}

/* public functions end */

/* class : Exception Function Definitions end */

/* class : IPAddressFormatException Function Definitions */

/* public functions */

IPAddressFormatException::IPAddressFormatException(string __Message) : Exception(__Message)
{
}

/* public functions end */

/* class : IPAddressFormatException Function Definitions end */

/* class : SocketException Function Definitions */

/* public functions */

SocketException::SocketException(string __Message) : Exception(__Message)
{
}

/* public functions end */

/* class : SocketException Function Definitions end */
