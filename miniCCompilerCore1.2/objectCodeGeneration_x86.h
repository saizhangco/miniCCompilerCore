#pragma once
#include <iostream>
using namespace std;
#include "objectCodeGeneration.h"
#include "fourElementType.h"
#include "fourElementTypeItem.h"
#include "semanticAnalysis.h"

class ObjectCodeGeneration_x86 : public ObjectCodeGeneration
{
public:
	list<Code> mSchemaDefinition;	//模式定义
	list<Code> mIncludeLib;			//include includelib
	list<Code> m_data;				// .data
	list<Code> m_code;				// .code
private:
	int mPrintStringCount;
public:
	ObjectCodeGeneration_x86();
	~ObjectCodeGeneration_x86();
	//void runObjectCodeGeneration_x86(list<FourElementType>& fetList);
	void runObjectCodeGeneration_x86(SemanticAnalysis semantic);
	//将目标代码保存到文件中
	void outFile(string fileName);	//后缀名保存为 .asm
	void compiler();
	void run();
private:
	void object_analysisFourElementType(FourElementType& fourElementTypeItem);
	void object_schemaDefinition();
	void object_includeLib();
};
//编译链接 汇编 -> 可执行程序(.EXE)
//运行 
//run.bat arg1 内部包含pause
