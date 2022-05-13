#pragma once
/**
* �����ռ�: None
*
* �� �ܣ� ��������
* �� ���� VariableDefinition    extend Node
*
* Ver  2016-06-10  ����  �������������
                         �������洢����������͡��������С�������
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
#include "node.h"
#include "variableList.h"
#include "grammarTreeTmp.h"


class VariableDefinition :public Node
{
public:
	int memoryType;						//�洢���
	int dataType;						//��������
	list<VariableList> variableList;	//��������
	string actionScope;					//������
public:
	VariableDefinition();
	VariableDefinition(GrammarTreeTmp& tmp);
	~VariableDefinition();
	void printContent();
	string getContent();
};
