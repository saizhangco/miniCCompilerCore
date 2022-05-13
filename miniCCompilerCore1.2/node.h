#pragma once
/**
* �����ռ�: None
*
* �� �ܣ� �����
* �� ���� Node
*
* Ver  2016-06-10  ����  �������ࡢ���Ժͷ���
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
#include <string>
using namespace std;
class Node
{
public:
	string data;
	Node* left;
	Node* right;
public:
	Node()
	{
		left = nullptr;
		right = nullptr;
	}
	~Node() {};
	virtual void printContent();
	bool addLeftChild(string data);		//�������
	bool addRightChild(string data);	//����ҽ��
	void addChildToRoot(Node* node);	//��Ӻ��ӵ����ڵ�
};
