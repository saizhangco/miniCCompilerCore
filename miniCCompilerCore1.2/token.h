#pragma once
#include <iostream>
#include <string>
using namespace std;


class Token
{
public:
	int lineNo;
	string data;
	int type;
	bool isLexical;
public:
	Token();
	Token(string d, int t);
	Token(int no,string d, int t, bool isLexical);
	~Token();
	void printToken();
};
