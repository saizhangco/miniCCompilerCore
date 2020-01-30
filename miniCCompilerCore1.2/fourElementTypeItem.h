#pragma once
#include <iostream>
#include <string>
using namespace std;


class FourElementTypeItem
{
public:
	int mType;	// 0-初始化 1-常量 2-用户定义的变量 3-临时变量 4-布尔表达式 5-四元式指针
	int mConstantType;	//常量类型 1-整型 2-浮点型 3-字符型 4-字符串型(只会在print函数中用到)

	int mConstantInteger;	//整型常量
	float mConstantFloat;	//浮点型常量
	char mConstantChar;		//字符型常量

	string mUserIdentifierName;	//程序变量名
	string mTempIdentifierName;	//临时变量名

	int mTC;	//表达式的真出口
	int mFC;	//表达式的假出口
	int mNumber;	//下一个四元式
	string mPrintString;
	string mCacheBuffer;
public:
	FourElementTypeItem();
	~FourElementTypeItem();
	void printFourElementTypeItem();
	string getContent();
};