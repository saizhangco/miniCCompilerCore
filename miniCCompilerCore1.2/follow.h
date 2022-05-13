#pragma once
#include <iostream>
#include <list>
using namespace std;
#include "token.h"

class Follow
{
public:
	Token mNonterminator;
	list<Token> mFollow;
	list<Token> mOther;

public:
	Follow();
	Follow(Token& token);
	~Follow();
};
