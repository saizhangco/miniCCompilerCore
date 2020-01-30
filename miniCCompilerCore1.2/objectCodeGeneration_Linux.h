#pragma once
#include <iostream>
#include <list>
using namespace std;
#include "code.h"
class ObjectCodeGeneration_Linux
{
private:
	// section
	list<Code> _data;
	list<Code> _bss;
	list<Code> _text;
public:
	ObjectCodeGeneration_Linux();
	~ObjectCodeGeneration_Linux();

private:
	void object_initial();
};


