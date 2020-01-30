#pragma once
#include <iostream>
#include <fstream>
using namespace std;
#include "semanticAnalysis.h"

class CodeOptimization
{
public:
	CodeOptimization();
	~CodeOptimization();
	//ִ�д����Ż�
	bool runCodeOptimization(SemanticAnalysis& semantic);
private:
	list<FourElementType>::iterator findItFourElementTypeItem(int m_nResult, SemanticAnalysis& semantic);
	int findItFourElementTypeRemove(int m_nResult, SemanticAnalysis& semantic);
	bool saveCodeOptimizationToFile(SemanticAnalysis& semantic,const string& fileName);
};