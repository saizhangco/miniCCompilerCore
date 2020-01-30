#include "LL_1_AnalysisItem.h"

LL_1_AnalysisItem::LL_1_AnalysisItem()
{
}

LL_1_AnalysisItem::LL_1_AnalysisItem(int id, string& stack_t, list<Token>& list_t, string & dp)
{
	this->id = id;
	this->analysisStack.clear();
	this->leftString.clear();
	this->deduceProd.clear();
	this->analysisStack = stack_t;
	for (list<Token>::iterator it = list_t.begin(); it != list_t.end(); it++)
	{
		this->leftString += (*it).data;
	}
	this->deduceProd = dp;
}

LL_1_AnalysisItem::~LL_1_AnalysisItem()
{
}