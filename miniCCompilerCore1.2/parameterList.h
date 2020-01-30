#pragma once

/**
* 命名空间: None
*
* 功 能： 参数列表类
* 类 名： ParameterList
*
* Ver  2016-06-10  张赛  定义参数项数据结构
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
using namespace std;


class ParameterList
{
public:
	int parameterType;		//参数类型
	string parameterName;	//参数名
public:
	ParameterList();
	~ParameterList();
};