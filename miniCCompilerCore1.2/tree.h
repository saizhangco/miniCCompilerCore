#pragma once

/**
* �����ռ�: None
*
* �� �ܣ� �������ͽṹ
* �� ���� Tree
*
* Ver 2016-06-10 ���� �����ࡢ���Ժͷ���
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
#include "node.h"


class Tree
{
public:
	Node* root;
public:
	Tree();
	~Tree();
	void printTree(Node* node);	//�ڿ���̨��ӡTree�ͽṹ����
	void deleteNodes(Node* node);	//ɾ���������ݽṹ�е����н��
};