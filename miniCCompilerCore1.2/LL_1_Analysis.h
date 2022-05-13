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
	list<First> firstSet;	//First��
	list<Follow> followSet;	//Follow��
	list<AnalysisTable> analysisTable;//Ԥ�������
	list<LL_1_AnalysisItem> analysisResult;	//Ԥ��������
	Grammar g;
	bool isReady;			//�Ƿ���Խ����﷨����
public:
	LL_1_Analysis();	//�޲ι��캯��
	LL_1_Analysis(const string& fileName);
	~LL_1_Analysis();	//��������
	bool initFirstSet(Grammar& g);		//ͨ���ķ���ʼ��First��
	bool initFollowSet(Grammar& g);	//ͨ���ķ���ʼ��Follow��
	bool initAnalysisTable(Grammar& g);	//ͨ��First����Follow����ʼ��Ԥ�������
	bool runGrammarAnalysis(list<Token>& list);	//ʹ��LL_1Ԥ�����������﷨����
	bool writeAnalysisTableBinary(const string& at_name);	//��AnalysisTable�Զ����Ƶķ�ʽ���浽�ļ���
	bool readAnalysisTableBinary(const string& at_name);	//��AnalysisTable�Զ����Ƶķ�ʽ���ļ��ж�ȡ

	bool existInListTok(list<Token>& tok, string& s) const;	//��list<Tok>�Ƿ����

	bool existInFirstSet(string& d);
	bool existInFollowSet(string& d);
	bool existTokInTokList(list<Token>& tok, string& s);
	bool existTokInTokVector(vector<Token>& tok, string& s);
	bool existATItemInATItemList(list<AnalysisTableItem>& item, string& s);
	bool existATItemInATItemList(list<AnalysisTableItem>& item, const char* s);
	bool existATItemInATItemList(list<AnalysisTableItem>& item, int& t);

	void printFirstSet();	//��ӡFirst��
	void printFollowSet();	//��ӡFollow��
	void printFirstSetFormat_1();	//���ո�ʽһ��ӡFirst��
	void printFollowSetFormat_1();	//���ո�ʽһ��ӡFollow��
	void printAnalysisTable();	//��ӡԤ�������
	void printAnalysisResult();	//��ӡԤ��������
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
