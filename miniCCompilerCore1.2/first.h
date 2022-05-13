#pragma once
#include <iostream>
#include <list>
using namespace std;
#include "token.h"
#include "analysisTableItem.h"

class First
{
public:
	Token mNonterminator;			//非终结符
	list<AnalysisTableItem> mFirst;	//预测分析表项
	list<AnalysisTableItem> mOther;	//预测分析表项

public:
	First();
	First(Token& token);
	~First();
	int getOtherSize();
};
