#include "Utility.h"

namespace Utility
{
	string operator + (const string &str, unsigned short num)
	{
		string tmp;
		while (num > 0)
		{
			tmp = (char)(num % 10 + '0') + tmp;
			num /= 10;
		}
		return str + (tmp == "" ? "0" : tmp);
	}
}
