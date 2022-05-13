#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <stack>
using namespace std;
#include "first.h"
#include "follow.h"
#include "analysisTable.h"
#include "LL_1_AnalysisItem.h"
#include "LL_1_Analysis.h"
#include "grammar.h"
#include "fileOperation.h"


class LL_1_Analysis
{
public:
	list<First> firstSet;	//First集
	list<Follow> followSet;	//Follow集
	list<AnalysisTable> analysisTable;//预测分析表
	list<LL_1_AnalysisItem> analysisResult;	//预测分析结果
	Grammar g;
	bool isReady;			//是否可以进行语法分析
public:
	LL_1_Analysis();	//无参构造函数
	LL_1_Analysis(const string& fileName);
	~LL_1_Analysis();	//析构函数
	bool initFirstSet(Grammar& g);		//通过文法初始化First集
	bool initFollowSet(Grammar& g);	//通过文法初始化Follow集
	bool initAnalysisTable(Grammar& g);	//通过First集和Follow集初始化预测分析表
	bool runGrammarAnalysis(list<Token>& list);	//使用LL_1预测分析表进行语法分析
	bool writeAnalysisTableBinary(const string& at_name);	//将AnalysisTable以二进制的方式保存到文件中
	bool readAnalysisTableBinary(const string& at_name);	//将AnalysisTable以二进制的方式从文件中读取

	bool existInListTok(list<Token>& tok, string& s) const;	//在list<Tok>是否存在

	bool existInFirstSet(string& d);
	bool existInFollowSet(string& d);
	bool existTokInTokList(list<Token>& tok, string& s);
	bool existTokInTokVector(vector<Token>& tok, string& s);
	bool existATItemInATItemList(list<AnalysisTableItem>& item, string& s);
	bool existATItemInATItemList(list<AnalysisTableItem>& item, const char* s);
	bool existATItemInATItemList(list<AnalysisTableItem>& item, int& t);

	void printFirstSet();	//打印First集
	void printFollowSet();	//打印Follow集
	void printFirstSetFormat_1();	//按照格式一打印First集
	void printFollowSetFormat_1();	//按照格式一打印Follow集
	void printAnalysisTable();	//打印预测分析表
	void printAnalysisResult();	//打印预测分析结果
	void saveAnalysisResultToFile(ofstream& fout);
private:
	list<First>::iterator getFirstAsNonterminator(string& s);
	list<Follow>::iterator getFollowAsNonterminator(string& s);
	list<AnalysisTable>::iterator getAnalysisTableAsNonterminator(string& s);
	list<AnalysisTableItem>::iterator getATItemAsNonterminator(list<AnalysisTable>::iterator& it_at, string& s);
	list<AnalysisTableItem>::iterator getATItemAsNonterminator(list<AnalysisTable>::iterator& it_at, int& t);
	string getTokStackData(stack<Token>& stack_t);
	unsigned int getIntLength(int num);
};
