#pragma once
/**
* �����ռ�: None
*
* �� �ܣ� �ķ�����ʽ��
* �� ���� Production
*
* Ver 2016-06-10 ���� �����ķ�����ʽ�ࡢ���Ժͷ���
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
class Production
{
public:
	Token left;
	list<Token> right;
public:
	Production();
	~Production();
	void printProdLine() const;	//��ӡ���ʽ
	string getProd() const;		//���ַ�������ʽ��ȡ���ʽ
};