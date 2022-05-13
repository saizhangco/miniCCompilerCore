#pragma once
#include <iostream>
#include <string>
#include <list>
using namespace std;
#include "node.h"
#include "parameterList.h"
#include "grammarTreeTmp.h"


class FunctionDefinition : public Node
{
public:
	int memoryType;			//存储类型
	int returnType;			//返回值类型
	string functionName;	//函数名
	list<ParameterList> parameterList; //参数列表
	bool isComeTrue;					//是否为函数实现  true-函数实现 false-函数声明
	int funcEnter;						//函数的中间代码入口
public:
	FunctionDefinition();
	FunctionDefinition(int t, string n);
	FunctionDefinition(GrammarTreeTmp tmp);
	~FunctionDefinition();
	void printContent();
	string getContent();
};
