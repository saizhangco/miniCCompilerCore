#pragma once
#include <iostream>
#include <list>
using namespace std;
#include "variableList.h"
#include "parameterList.h"


class GrammarTreeTmp
{
public:
	int tmpType;			// 1-外部数据定义 2-函数声明 3-函数实现
	int memoryType;			//存储类型
	int dataType;			//数据类型
	string functionName;	//函数名
	list<VariableList> variableList;
	list<ParameterList> parameterList;
public:
	GrammarTreeTmp();
	~GrammarTreeTmp();
};