#pragma once
/**
* 命名空间: None
*
* 功 能： 文法产生式类
* 类 名： Production
*
* Ver 2016-06-10 张赛 定义文法产生式类、属性和方法
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
class Production
{
public:
	Token left;
	list<Token> right;
public:
	Production();
	~Production();
	void printProdLine() const;	//打印表达式
	string getProd() const;		//以字符串的形式获取表达式
};
