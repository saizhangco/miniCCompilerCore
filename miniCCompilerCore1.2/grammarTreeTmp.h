#pragma once
#include <iostream>
#include <list>
using namespace std;
#include "variableList.h"
#include "parameterList.h"


class GrammarTreeTmp
{
public:
	int tmpType;			// 1-�ⲿ���ݶ��� 2-�������� 3-����ʵ��
	int memoryType;			//�洢����
	int dataType;			//��������
	string functionName;	//������
	list<VariableList> variableList;
	list<ParameterList> parameterList;
public:
	GrammarTreeTmp();
	~GrammarTreeTmp();
};