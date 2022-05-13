#pragma once
#include <iostream>

using namespace std;

class Code
{
public:
	int no;	//从1开始计数
	string line;	//一行代码的内容
public:
	Code();	//默认无参构造函数，内置初始化代码
	Code(int n, string l);	//含有两个参数的构造函数
};
