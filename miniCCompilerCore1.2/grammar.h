#pragma once
/**
* �����ռ�: None
*
* �� �ܣ� miniC�����ķ�
* �� ���� Grammar
*
* Ver  2016-06-10  ����  ����miniC�����ķ����ݽṹ���͡����Ժͷ���
* ����������������������������������������������������������������������
* V0.02 2016-06-10 ���� 2��
*
* Copyright (c) 2015 Lir Corporation. All rights reserved.
*������������������������������������������������������������������������
*�����˼�����ϢΪ����˾������Ϣ��δ������˾����ͬ���ֹ���������¶������
*������Ȩ���У�*****���޹�˾ ������              ������������������������
*������������������������������������������������������������������������
*/
#include <iostream>
#include <list>
using namespace std;
#include "token.h"
#include "production.h"

class Grammar
{
public:
	list<Token> mNonterminator;
	list<Token> mTerminator;
	list<Production> mProduction;
	Token mStarter;

public:
	Grammar();
	Grammar(const string& fileName);
	~Grammar();
	bool isTerminator(const string& s);	//�Ƿ�Ϊ�ս��
	bool isTerminator(const int& t);	//�Ƿ�Ϊ�ս��
	bool isNonterminator(const string& s);	//�Ƿ�Ϊ���ս��
	void printGrammar();	//��ӡ�ķ�
private:
	bool loadProductionsFromFile(const string& fileName);	//���ر��ʽ
	bool loadNonterminatorSetSelf();	//�Զ����ط��ս����
	bool loadTerminatorSetSelf();	//�Զ������ս����
	bool refreshProduction();	//ˢ���ķ��Ĳ���ʽ

	bool getProductionFromTokenList(list<Token>& tokenList);
	bool existInNonterminatorSet(const string& s);
	bool existInTerminatorSet(const string& s);

};
