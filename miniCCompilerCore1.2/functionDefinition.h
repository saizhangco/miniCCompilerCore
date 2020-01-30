#pragma once
#include <iostream>
#include <string>
#include <list>
using namespace std;
#include "node.h"
#include "parameterList.h"
#include "grammarTreeTmp.h"


class FunctionDefinition : public Node
{
public:
	int memoryType;			//�洢����
	int returnType;			//����ֵ����
	string functionName;	//������
	list<ParameterList> parameterList; //�����б�
	bool isComeTrue;					//�Ƿ�Ϊ����ʵ��  true-����ʵ�� false-��������
	int funcEnter;						//�������м�������
public:
	FunctionDefinition();
	FunctionDefinition(int t, string n);
	FunctionDefinition(GrammarTreeTmp tmp);
	~FunctionDefinition();
	void printContent();
	string getContent();
};