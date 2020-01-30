#pragma once

/**
* 命名空间: None
*
* 功 能： 定义树型结构
* 类 名： Tree
*
* Ver 2016-06-10 张赛 定义类、属性和方法
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
#include "node.h"


class Tree
{
public:
	Node* root;
public:
	Tree();
	~Tree();
	void printTree(Node* node);	//在控制台打印Tree型结构内容
	void deleteNodes(Node* node);	//删除树形数据结构中的所有结点
};