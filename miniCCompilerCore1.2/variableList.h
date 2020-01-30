#pragma once
/**
* 命名空间: None
*
* 功 能： 变量列表
* 类 名： VariableList
*
* Ver  2016-06-10  张赛  定义变量列表，变量列表包括变量名和初始化值的属性。
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
#include "token.h"


class VariableList
{
public:
	string varName;			//变量名
	list<Token> initValue;	//初始化值
public:
	VariableList();			//构造函数
	~VariableList();		//析构函数
};