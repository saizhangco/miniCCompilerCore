#pragma once
#include <list>
using namespace std;
#include "token.h"
#include "production.h"
class AnalysisTableItem
{
public:
	Token mTerminator;		//�ս��
	Production mProduction;	//����ʽ
public:
	AnalysisTableItem();
	AnalysisTableItem(Token& token, Production& production);
	~AnalysisTableItem();
};
