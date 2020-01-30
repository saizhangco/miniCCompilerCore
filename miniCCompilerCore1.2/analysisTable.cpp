#include "analysisTable.h"

AnalysisTable::AnalysisTable()
{
}

AnalysisTable::AnalysisTable(Token & token)
{
	mNonterminator = token;
	mItemList.clear();
}

AnalysisTable::~AnalysisTable()
{
}
