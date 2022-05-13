#pragma once
#include <iostream>
using namespace std;
#include "codeList.h"
/*
目标代码生成
输入
1.中间代码 或者是 代码优化后的中间代码
输出
1.目标代码 相关平台的汇编代码
2.可执行文件
*/
class ObjectCodeGeneration
{
public:
	CodeList mObjectCode;
public:
	ObjectCodeGeneration();
	~ObjectCodeGeneration();
};
