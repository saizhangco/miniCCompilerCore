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
	int mCurrentLine;//��ǰ��
public:
	list<Token> mTokenList;	//Token��
	list<LexicalAnalysisAnimation> mLexicalAnalysisAnimation;	//�����ű�
	bool analysisGrammar;
public:
	LexicalAnalysis();
	~LexicalAnalysis();
	int runLexicalAnalysis(CodeList& codeList);	//ִ�дʷ���������
	void printTokenList();
	void printLexicalAnalysisAnimationList();
	//3.�ʷ��������ĳ���
	//����ֵ Token ��ǰ����β���
	//�������
	/*
		1.�Իس�'\n'���ڵ�ǰ���������ַ����ս��'\0'�����������������ַ���ʽ�����Ļ���
		�Ͳ����ڿ����ַ����ս����
		2������ս����ǰ��ֿ� �ո�ˮƽ�Ʊ�����س�
	*/
	void lexical_core(Code code , bool& isBlockAnnotation,bool isAnalysisAnimation);
private:
	
	//4.ͨ��������ַ����жϸ��ַ����Ƿ�Ϊ��� 0 ���ǽ��
	//                                       ��0 �ǽ��
	int getDelimiterType(char c);

	
	//5.ͨ������ı������������ص���ʶ��Ľ��
	int getLexicalType(int numberChange, int flag, char* tp, bool& isLexical);


	//6������ʶ����ĵ��ʣ�����ǹؼ����򷵻عؼ������
	int getIdentifierType(const char* tp);


	//7����������������
	int getOperatorType(const char* tp);


	//8.�ڴʷ����������У�����ʷ������������������
	void loadLexicalAnalysisAnimationInfo(int lineNo, int start, int end, int type, bool isLexical);


	//9.������Ĵʷ������������ݱ��浽�ļ���
	bool saveLexicalAnalysisAnimationListToFile(const string& fileName);

	//10.��Token�����浽�ļ���
	bool saveTokenListToFile(const string& fileName);
};