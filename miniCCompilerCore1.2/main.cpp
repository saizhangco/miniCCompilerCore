#include <iostream>
using namespace std;
#include "symbol.h"
#include "codeList.h"
#include "lexicalAnalysis.h"
#include "grammar.h"
void main_0420()
{
	cout << "--miniC Compiler Core 1.2--" << endl;
	cout << Keyword_auto << endl;
	CodeList codeList;
	codeList.readCodeListFromFile("tmp\\code.txt");
	//codeList.printCodeList();
	LexicalAnalysis lexicalAnalysis;
	if(!lexicalAnalysis.runLexicalAnalysis(codeList))
	{
		cout << "´Ê·¨·ÖÎö´æÔÚ´íÎó" << endl;
	}
	lexicalAnalysis.printTokenList();
	lexicalAnalysis.printLexicalAnalysisAnimationList();
	Grammar grammar("tmp\\grammar.txt");
	grammar.printGrammar();
	system("pause");
}