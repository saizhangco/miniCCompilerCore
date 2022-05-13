#include "token.h"

Token::Token()
{
	this->data.clear();//清空data中保存的内容
	this->type = -1;//默认初始化为 -1
}

Token::Token(string d, int t)
{
	this->data = d;
	this->type = t;
	this->isLexical = true;
}

Token::Token(int no,string d, int t, bool isLexical)
{
	this->lineNo = no;
	this->data = d;
	this->type = t;
	this->isLexical = isLexical;
}

Token::~Token()
{
}

void Token::printToken()
{
	cout << lineNo << "\t" << data << "\t" << type << "\t" << (isLexical ? "true" : "false") << endl;
}
