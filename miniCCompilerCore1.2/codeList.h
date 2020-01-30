#pragma once
#include <iostream>
#include <list>
#include <string>
#include <fstream>
#include "code.h"
using namespace std;

class CodeList
{
public:
	list<Code> codeList;	//源文件以List的形式保存
public:
	CodeList();
	CodeList(const string& fileName);
	~CodeList();
	void printCodeList();
	bool saveCodeListToFile(const string& fileName);
	bool readCodeListFromFile(const string& fileName);
};
