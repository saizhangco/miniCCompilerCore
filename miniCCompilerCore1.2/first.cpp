#include "first.h"

First::First()
{
}

First::First(Token & token)
{
	mNonterminator = token;
	mFirst.clear();
	mOther.clear();
}

First::~First()
{
}

int First::getOtherSize()
{
	list<AnalysisTableItem>::iterator it;
	int count = 0;
	for (it = mOther.begin(); it != mOther.end(); it++)
	{
		if ((*it).mTerminator.data != "")
			count++;
	}
	return count;
}
