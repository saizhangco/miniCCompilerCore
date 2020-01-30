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
	list<Code> codeList;	//Դ�ļ���List����ʽ����
public:
	CodeList();
	CodeList(const string& fileName);
	~CodeList();
	void printCodeList();
	bool saveCodeListToFile(const string& fileName);
	bool readCodeListFromFile(const string& fileName);
};
