#pragma once
#include <iostream>
using namespace std;
#include "objectCodeGeneration.h"
#include "fourElementType.h"
#include "fourElementTypeItem.h"
#include "semanticAnalysis.h"

class ObjectCodeGeneration_x86 : public ObjectCodeGeneration
{
public:
	list<Code> mSchemaDefinition;	//ģʽ����
	list<Code> mIncludeLib;			//include includelib
	list<Code> m_data;				// .data
	list<Code> m_code;				// .code
private:
	int mPrintStringCount;
public:
	ObjectCodeGeneration_x86();
	~ObjectCodeGeneration_x86();
	//void runObjectCodeGeneration_x86(list<FourElementType>& fetList);
	void runObjectCodeGeneration_x86(SemanticAnalysis semantic);
	//��Ŀ����뱣�浽�ļ���
	void outFile(string fileName);	//��׺������Ϊ .asm
	void compiler();
	void run();
private:
	void object_analysisFourElementType(FourElementType& fourElementTypeItem);
	void object_schemaDefinition();
	void object_includeLib();
};
//�������� ��� -> ��ִ�г���(.EXE)
//���� 
//run.bat arg1 �ڲ�����pause