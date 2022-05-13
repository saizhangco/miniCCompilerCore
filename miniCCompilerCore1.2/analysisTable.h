#pragma once
#include <list>
using namespace std;
#include "token.h"
#include "analysisTableItem.h"
class AnalysisTable
{
public:
	Token mNonterminator;		//非终结符
	list<AnalysisTableItem> mItemList;	//分析表项链表
public:
	AnalysisTable();
	AnalysisTable(Token& token);
	~AnalysisTable();
private:

};
