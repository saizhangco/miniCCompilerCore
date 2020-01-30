#pragma once
#include <iostream>
#include <list>
using namespace std;
#include "token.h"

class LL_1_AnalysisItem
{
public:
	int id;
	string analysisStack;
	string leftString;
	string deduceProd;	//推导所用产生式或匹配
public:
	LL_1_AnalysisItem();
	LL_1_AnalysisItem(int id, string& stack_t, list<Token>& list_t, string& dp);
	~LL_1_AnalysisItem();
};