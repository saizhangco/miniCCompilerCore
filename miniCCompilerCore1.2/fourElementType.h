#pragma once
#include <iostream>
using namespace std;
#include "fourElementTypeItem.h"

#define IsNot 0x10 // !
#define Multiply 0x11	// *
#define Divide 0x12	// /
#define Mod 0x13	// %
#define Plus 0x14	//+
#define Minus 0x15	//-
#define Jump 0x16   // j
#define Jump_Less_Than 0x17 // j<
#define Jump_More_Than 0x18	// j>
#define Jump_Less_Than_Equal 0x19	// j<=
#define Jump_More_Than_Equal 0x1A	// j>=
#define Jump_Not_Equal_To 0x1B	// j!=
#define Jump_Is_Equal 0x1C	// j==
#define Jump_Not_Zero 0x1D	// jnz
#define Equal 0x1E	//=
#define Sys 0x1F	//sys
#define FuncEnter 0x20	//�������
#define FuncExit 0x21	//��������
#define Print 0x22	//print���

class FourElementType
{
public:
	int mNumber;	//��� ��1��ʼ����ʼ��Ϊ0
	int mOperation;	//������
	FourElementTypeItem mArg1;
	FourElementTypeItem mArg2;
	FourElementTypeItem mResult;

	//�����Ż�����ʹ�õ�����
	int mOptimizationType;	//�Ż����� 0-���Ż� 1-ɾ�� 2-�޸�
	FourElementTypeItem mResultBack;	//����
public:
	FourElementType();
	FourElementType(int number, int operation, FourElementTypeItem& arg1, FourElementTypeItem& arg2, FourElementTypeItem& result);
	~FourElementType();
	void printFourElementType();
	string getFourElementType();
	string getOperationContent();
};