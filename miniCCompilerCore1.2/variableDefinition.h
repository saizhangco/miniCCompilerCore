#pragma once
/**
* 命名空间: None
*
* 功 能： 变量定义
* 类 名： VariableDefinition    extend Node
*
* Ver  2016-06-10  张赛  定义变量定义类
                         包含：存储类别、数据类型、变量表列、作用域
* ───────────────────────────────────
* V0.02 2016-06-10 张赛 2版
*
* Copyright (c) 2015 Lir Corporation. All rights reserved.
*┌──────────────────────────────────┐
*│　此技术信息为本公司机密信息，未经本公司书面同意禁止向第三方披露．　│
*│　版权所有：*****有限公司 　　　              　　　　　　　　　　　│
*└──────────────────────────────────┘
*/
#include <iostream>
#include <list>
using namespace std;
#include "node.h"
#include "variableList.h"
#include "grammarTreeTmp.h"


class VariableDefinition :public Node
{
public:
	int memoryType;						//存储类别
	int dataType;						//数据类型
	list<VariableList> variableList;	//变量表列
	string actionScope;					//作用域
public:
	VariableDefinition();
	VariableDefinition(GrammarTreeTmp& tmp);
	~VariableDefinition();
	void printContent();
	string getContent();
};
