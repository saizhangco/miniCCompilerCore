#include "follow.h"

Follow::Follow()
{
}

Follow::Follow(Token & token)
{
	mNonterminator = token;
	mFollow.clear();
	mOther.clear();
}

Follow::~Follow()
{
}