#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;
#include "lexicalAnalysis.h"
#include "grammarAnalysis.h"
#include "semanticAnalysis.h"
#include "objectCodeGeneration_x86.h"
#include "FileOperation.h"
#include "codeOptimization.h"

int StringConvertInteger_1(string arg_string)
{
	int result = 0;
	const char *cs = arg_string.c_str();
	for (unsigned int i = 0; i < arg_string.length(); i++)
	{
		result *= 10;
		result += cs[i] - '0';
	}
	return result;
}

void main_0517()
{
	//cout << StringConvertInteger_1("1234") <<endl;
	bool lexicalError = false;
	bool grammarError = false;
	bool semanticError = false;
	string path("path.txt");	//path
	CodeList code(path);
	string gram_arg("");//语法分析参数
						
	//词法分析
	LexicalAnalysis lexical;
	int lexicalErrorCount = lexical.runLexicalAnalysis(code);
	if (lexicalErrorCount > 0)
	{
		cout << "Lexical词法分析结束，存在" << lexicalErrorCount << "个词法错误" << endl;
		return;
		//lexicalError = true;
	}
	else
	{
		cout << "Lexical词法分析完成，无词法错误" << endl;
	}
	//语法分析
	GrammarAnalysis ga_5;
	if (!ga_5.grammarAnalysisUsingLL1_2(lexical.mTokenList))
	{
		cout << "语法分析[LL1预测分析,更新文法]，存在语法错误" << endl;
		return ;
		//grammarError = true;
	}
	//语义分析
	SemanticAnalysis semantic;
	if (!grammarError && !semantic.runSemanticAnalysis(lexical.mTokenList))
	{
		cout << "语义分析，存在语义错误" << endl;
		//return 1;
		semanticError = true;
	}
	//代码优化
	CodeOptimization codeOptimization;
	if (!semanticError && codeOptimization.runCodeOptimization(semantic))
	{

	}
	system("pause");
}

void main_0528()
{
	system("analysis\\clear.bat");	//清空analysis文件夹下的分析文件
	string path("path.txt");	//path
	CodeList code(path);

	LexicalAnalysis lexical;
	int lexicalErrorCount = lexical.runLexicalAnalysis(code);
	if (lexicalErrorCount > 0)
	{
		cout << "Lexical词法分析结束，存在" << lexicalErrorCount << "个词法错误" << endl;
		system("pause");
	}
	else
	{
		cout << "Lexical词法分析完成，无词法错误" << endl;
	}
	//语法分析
	GrammarAnalysis grammar;
	if (!grammar.grammarAnalysisUsingLL1_2(lexical.mTokenList))
	{
		cout << "Grammar语法分析结束，存在" << grammar.grammarError.size() << "个语法错误" << endl;
		system("pause");
	}
	else
	{
		cout << "Grammar语法分析完成，无语法错误" << endl;
	}
	//语义分析及中间代码生成
	SemanticAnalysis semantic;					//语义分析
	if (!semantic.runSemanticAnalysis(lexical.mTokenList))
	{
		cout << "Semantic语义分析结束，存在" << semantic.mErrorInfo.size() << "个语义错误" << endl;
		system("pause");
	}
	else
	{
		cout << "Semantic语义分析完成，无语义错误" << endl;
	}
	//代码优化
	CodeOptimization optimization;
	if (!optimization.runCodeOptimization(semantic))
	{
		cout << "Optimization代码优化失败" << endl;
		system("pause");
	}
	else
	{
		cout << "Optimization代码优化成功" << endl;
	}
	//目标代码生成
	ObjectCodeGeneration_x86 objectCodeGeneration;
	objectCodeGeneration.runObjectCodeGeneration_x86(semantic);
	system("pause");
	cout << "####  编译程序" << endl;
	system("compiler_link.bat");	//编译连接汇编代码成可执行文件
	cout << "####  运行程序" << endl;
	system("run.bat");				//运行程序
	
}