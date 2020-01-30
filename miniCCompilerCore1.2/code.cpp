#include "code.h"

Code::Code()
{
	no = 0;
	line = "";
}

Code::Code(int n, string l)
{
	this->no = n;
	this->line = l;
}