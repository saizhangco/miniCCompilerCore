#pragma once
#include <iostream>
#include <list>
using namespace std;
#include "token.h"
#include "analysisTableItem.h"

class First
{
public:
	Token mNonterminator;			//���ս��
	list<AnalysisTableItem> mFirst;	//Ԥ���������
	list<AnalysisTableItem> mOther;	//Ԥ���������

public:
	First();
	First(Token& token);
	~First();
	int getOtherSize();
};