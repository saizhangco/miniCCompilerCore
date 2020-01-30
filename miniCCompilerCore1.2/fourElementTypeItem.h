#pragma once
#include <iostream>
#include <string>
using namespace std;


class FourElementTypeItem
{
public:
	int mType;	// 0-��ʼ�� 1-���� 2-�û�����ı��� 3-��ʱ���� 4-�������ʽ 5-��Ԫʽָ��
	int mConstantType;	//�������� 1-���� 2-������ 3-�ַ��� 4-�ַ�����(ֻ����print�������õ�)

	int mConstantInteger;	//���ͳ���
	float mConstantFloat;	//�����ͳ���
	char mConstantChar;		//�ַ��ͳ���

	string mUserIdentifierName;	//���������
	string mTempIdentifierName;	//��ʱ������

	int mTC;	//���ʽ�������
	int mFC;	//���ʽ�ļٳ���
	int mNumber;	//��һ����Ԫʽ
	string mPrintString;
	string mCacheBuffer;
public:
	FourElementTypeItem();
	~FourElementTypeItem();
	void printFourElementTypeItem();
	string getContent();
};