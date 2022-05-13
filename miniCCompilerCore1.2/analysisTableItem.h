#pragma once
#include <list>
using namespace std;
#include "token.h"
#include "production.h"
class AnalysisTableItem
{
public:
	Token mTerminator;		//终结符
	Production mProduction;	//产生式
public:
	AnalysisTableItem();
	AnalysisTableItem(Token& token, Production& production);
	~AnalysisTableItem();
};
