#pragma once
/**
* 命名空间: None
*
* 功 能： 结点类
* 类 名： Node
*
* Ver  2016-06-10  张赛  定义结点类、属性和方法
* ───────────────────────────────────
* V0.02 2016-06-10 张赛 2版
*
* Copyright (c) 2015 Lir Corporation. All rights reserved.
*┌──────────────────────────────────┐
*│　此技术信息为本公司机密信息，未经本公司书面同意禁止向第三方披露．　│
*│　版权所有：*****有限公司 　　　              　　　　　　　　　　　│
*└──────────────────────────────────┘
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
	bool addLeftChild(string data);		//添加左结点
	bool addRightChild(string data);	//添加右结点
	void addChildToRoot(Node* node);	//添加孩子到根节点
};
