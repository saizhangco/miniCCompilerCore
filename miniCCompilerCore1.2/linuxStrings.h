#ifdef __linux__

#pragma once

#include <strings.h>
#include <cstring>


int strcmp(const char * s1,const char *s2) 
{
	return strcasecmp(s1,s2);
}
 

#endif
