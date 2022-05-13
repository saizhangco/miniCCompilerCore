#pragma once
/**
* 命名空间: None
*
* 功 能： miniC语言文法
* 类 名： Grammar
*
* Ver  2016-06-10  张赛  定义miniC语言文法数据结构类型、属性和方法
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
#include "production.h"

class Grammar
{
public:
	list<Token> mNonterminator;
	list<Token> mTerminator;
	list<Production> mProduction;
	Token mStarter;

public:
	Grammar();
	Grammar(const string& fileName);
	~Grammar();
	bool isTerminator(const string& s);	//是否为终结符
	bool isTerminator(const int& t);	//是否为终结符
	bool isNonterminator(const string& s);	//是否为非终结符
	void printGrammar();	//打印文法
private:
	bool loadProductionsFromFile(const string& fileName);	//加载表达式
	bool loadNonterminatorSetSelf();	//自动加载非终结符集
	bool loadTerminatorSetSelf();	//自动加载终结符集
	bool refreshProduction();	//刷新文法的产生式

	bool getProductionFromTokenList(list<Token>& tokenList);
	bool existInNonterminatorSet(const string& s);
	bool existInTerminatorSet(const string& s);

};
