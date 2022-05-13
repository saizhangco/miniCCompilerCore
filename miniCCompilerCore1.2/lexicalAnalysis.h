#pragma once
#include <iostream>
#include <list>
#include <fstream>
#include "codeList.h"
#include "token.h"
#include "lexicalAnalysisAnimation.h"
#include "symbol.h"
using namespace std;

class LexicalAnalysis
{
private:
	int mCurrentLine;//当前行
public:
	list<Token> mTokenList;	//Token串
	list<LexicalAnalysisAnimation> mLexicalAnalysisAnimation;	//分析脚本
	bool analysisGrammar;
public:
	LexicalAnalysis();
	~LexicalAnalysis();
	int runLexicalAnalysis(CodeList& codeList);	//执行词法分析程序
	void printTokenList();
	void printLexicalAnalysisAnimationList();
	//3.词法分析核心程序
	//返回值 Token 当前处理尾结点
	//处理规则
	/*
		1.以回车'\n'，在当前程序下是字符串终结符'\0'结束，如果按照逐个字符方式分析的话，
		就不用在考虑字符串终结符了
		2。处理空界符，前后分开 空格、水平制表符、回车
	*/
	void lexical_core(Code code , bool& isBlockAnnotation,bool isAnalysisAnimation);
private:
	
	//4.通过传入的字符，判断该字符的是否为界符 0 不是界符
	//                                       非0 是界符
	int getDelimiterType(char c);

	
	//5.通过传入的变量分析，返回单词识别的结果
	int getLexicalType(int numberChange, int flag, char* tp, bool& isLexical);


	//6。传入识别出的单词，如果是关键词则返回关键词类别
	int getIdentifierType(const char* tp);


	//7。获得运算符的类型
	int getOperatorType(const char* tp);


	//8.在词法分析过程中，构造词法分析动画所需的数据
	void loadLexicalAnalysisAnimationInfo(int lineNo, int start, int end, int type, bool isLexical);


	//9.将构造的词法分析动画数据保存到文件中
	bool saveLexicalAnalysisAnimationListToFile(const string& fileName);

	//10.将Token串保存到文件中
	bool saveTokenListToFile(const string& fileName);
};
