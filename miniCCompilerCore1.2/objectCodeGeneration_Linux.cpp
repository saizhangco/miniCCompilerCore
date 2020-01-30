
#include "objectCodeGeneration_Linux.h"

ObjectCodeGeneration_Linux::ObjectCodeGeneration_Linux()
{
}

ObjectCodeGeneration_Linux::~ObjectCodeGeneration_Linux()
{
}

void ObjectCodeGeneration_Linux::object_initial()
{
	string code = "";
	// .section .data
	code = ".section .data";
	_data.push_back(Code(0,code));
	// .section .bss
	code = ".section .bss";
	_bss.push_back(Code(0,code));
	// .section .text
	//     .global _start
	// _start:
	code = ".section .text";
	_text.push_back(Code(0,code));
	code = "\t.global _start";
	_text.push_back(Code(0, code));
	code = "_start:";
	_text.push_back(Code(0, code));
}
