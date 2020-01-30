#include "analysisTableItem.h"

AnalysisTableItem::AnalysisTableItem()
{
}


AnalysisTableItem::AnalysisTableItem(Token & token, Production & production)
{
	mTerminator = token;
	mProduction = production;
}

AnalysisTableItem::~AnalysisTableItem()
{

}