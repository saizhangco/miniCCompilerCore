#pragma once
#include <list>
using namespace std;
#include "token.h"
#include "analysisTableItem.h"
class AnalysisTable
{
public:
	Token mNonterminator;		//���ս��
	list<AnalysisTableItem> mItemList;	//������������
public:
	AnalysisTable();
	AnalysisTable(Token& token);
	~AnalysisTable();
private:

};
