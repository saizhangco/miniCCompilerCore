#include "grammar.h"
#include "symbol.h"
#include "codeList.h"
#include "lexicalAnalysis.h"
#include <algorithm>
Grammar::Grammar()
{
	//成员变量初始化
	this->mNonterminator.clear();
	this->mTerminator.clear();
	this->mProduction.clear();

	//加载表达式
	if (!loadProductionsFromFile("grammar\\grammar.txt"))//grammar
	{
		cout << "Error : " << "加载表达式错误" << endl;
	}
	//开始符
	Token token((*mProduction.begin()).left.data, Grammar_Nonterminator);
	mStarter = token;
	//加载非终结符
	loadNonterminatorSetSelf();
	//加载终结符
	loadTerminatorSetSelf();
	//刷新文法的产生式
	refreshProduction();
	//打印文法
	//printGram();
	
}

Grammar::Grammar(const string & fileName)
{
	//成员变量初始化
	this->mNonterminator.clear();
	this->mTerminator.clear();
	this->mProduction.clear();
	//加载表达式
	if (!loadProductionsFromFile(fileName))//grammar
	{
		cout << "Error : " << "加载表达式错误" << endl;
	}
	//开始符
	Token tok((*mProduction.begin()).left.data, Grammar_Nonterminator);
	mStarter = tok;
	//加载非终结符
	loadNonterminatorSetSelf();
	//加载终结符
	loadTerminatorSetSelf();
	//刷新文法的产生式
	refreshProduction();
	//打印文法
	//printGram();
}

Grammar::~Grammar()
{

}

bool Grammar::loadProductionsFromFile(const string& fileName)
{
	//1.从指定文件中读取出文法表达式[未处理前]
	CodeList codeList;
	if (!codeList.readCodeListFromFile(fileName))// fileName().data() OK
	{
		cout << "读取" << fileName << "文件失败" << endl;
		return false;
	}
	list<Code>::iterator it_code = codeList.codeList.begin();
	for (; it_code != codeList.codeList.end(); it_code++) 
	{
		//2.单行的词法分析
		bool isBlockAnnotation = false;
		LexicalAnalysis lexicalAnalysis;
		lexicalAnalysis.analysisGrammar = true;	//设置当前分析文法
		lexicalAnalysis.lexical_core((*it_code), isBlockAnnotation, false);
		//3.根据Token串的结果分析出文法
		getProductionFromTokenList(lexicalAnalysis.mTokenList);
	}
	//打印验证表达式构造是否准确
	//for_each(Production.begin(), Production.end(), [](const Prod& p) { p.printProdLine(); });

	return true;
}

bool Grammar::loadNonterminatorSetSelf()
{
	for (list<Production>::iterator it = mProduction.begin(); it != mProduction.end(); it++)
	{
		if (!existInNonterminatorSet((*it).left.data)) //在非终结符中不存在
		{
			Token tok((*it).left.data, Grammar_Nonterminator);
			mNonterminator.push_back(tok);
		}
	}
	return true;
}

bool Grammar::loadTerminatorSetSelf()
{
	for (list<Production>::iterator it = mProduction.begin(); it != mProduction.end(); it++)
	{
		for (list<Token>::iterator it1 = (*it).right.begin(); it1 != (*it).right.end(); it1++)
		{
			if ((*it1).data != "$")//非终结符集中出去 $
			{
				if (!existInNonterminatorSet((*it1).data) && !existInTerminatorSet((*it1).data))//在非终结符中不存在，且在终结符中也不存在
				{
					mTerminator.push_back((*it1));//添加到终结符
				}
			}
		}
	}
	return true;
}

bool Grammar::refreshProduction()
{
	for (list<Production>::iterator it = mProduction.begin(); it != mProduction.end(); it++)
	{
		if (this->isNonterminator((*it).left.data))
		{
			(*it).left.type = Grammar_Nonterminator;
		}
		list<Token>::iterator it_t;
		for (it_t = (*it).right.begin(); it_t != (*it).right.end(); it_t++)
		{
			if (this->isNonterminator((*it_t).data))
			{
				(*it_t).type = Grammar_Nonterminator;
			}

		}
	}
	return true;
}

void Grammar::printGrammar()
{
	cout << endl;
	cout << "====================" << endl;
	cout << mStarter.data << endl;
	cout << "--------------------" << endl;
	for_each(mProduction.begin(), mProduction.end(), [](const Production& p) { p.printProdLine(); });
	cout << "--------------------" << endl;
	for_each(mNonterminator.begin(), mNonterminator.end(), [](const Token& t) { cout << t.data << " "; });
	cout << endl;
	cout << "--------------------" << endl;
	for_each(mTerminator.begin(), mTerminator.end(), [](const Token& t) { cout << t.data << " "; });
	cout << endl;
	cout << "====================" << endl;
	cout << endl;
}

bool Grammar::getProductionFromTokenList(list<Token>& tokenList)
{
	if (tokenList.size() <= 0)
		return false;
	list<Token>::iterator it_token = tokenList.begin();
	Production p;
	p.left = *it_token;
	//cout << "-------" << p.left.data << endl;
	it_token++;
	if (it_token == tokenList.end() || (*it_token).type != Operator_Arrows)
		return false;
	it_token++;
	for (; it_token != tokenList.end(); it_token++) 
	{
		p.right.push_back(*it_token);
	}
	mProduction.push_back(p);
	return true;
}

bool Grammar::existInNonterminatorSet(const string & s)
{
	list<Token>::iterator it;
	for (it = mNonterminator.begin(); it != mNonterminator.end(); it++)
	{
		if ((*it).data == s)
			return true;
	}
	return false;
}

bool Grammar::existInTerminatorSet(const string & s)
{
	list<Token>::iterator it;
	for (it = mTerminator.begin(); it != mTerminator.end(); it++)
	{
		if ((*it).data == s)
			return true;
	}
	return false;
}

bool Grammar::isTerminator(const string & s)
{
	list<Token>::iterator it;
	for (it = mTerminator.begin(); it != mTerminator.end(); it++)
	{
		if ((*it).data == s)
			return true;
	}
	return false;
}

bool Grammar::isTerminator(const int & t)
{
	list<Token>::iterator it;
	for (it = mTerminator.begin(); it != mTerminator.end(); it++)
	{
		if ((*it).type == t)
			return true;
	}
	return false;
}

bool Grammar::isNonterminator(const string & s)
{
	list<Token>::iterator it;
	for (it = mNonterminator.begin(); it != mNonterminator.end(); it++)
	{
		if ((*it).data == s)
			return true;
	}
	return false;
}