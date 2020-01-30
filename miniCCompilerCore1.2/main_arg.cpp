#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;
#include "lexicalAnalysis.h"
#include "grammarAnalysis.h"
#include "semanticAnalysis.h"
#include "objectCodeGeneration_x86.h"
#include "FileOperation.h"

#define GramAnal_1 0x1		//使用LL1预测分析方法进行语法分析，不分析全局变量定义
#define GramAnal_2 0x10		//LL1预测分析法分析函数体，其余使用递归下降分析
#define GramAnal_3 0x100	//LL1预测分析法分析表达式，其余使用递归下降分析
#define GramAnal_4 0x1000	//全部使用递归下降分析
#define GramAnal_5 0x10000	//LL1使用优化的文法进行语法分析

int main_arg(int argc, char** argv)
{
	if (argc < 3)
	{
		return 1;
	}
	else
	{
		system("analysis\\clear.bat");
		string source(argv[1]);
		CodeList code(source);
		//cout << source << endl;
		if (!strcmp(argv[2], "lexical"))
		{
			cout << "词法分析" << endl;
			LexicalAnalysis lexical;	//词法分析
			lexical.runLexicalAnalysis(code);
		}
		else if (!strcmp(argv[2], "grammar"))
		{
			cout << "语法分析" << endl;
			LexicalAnalysis lexical;	//词法分析
			lexical.runLexicalAnalysis(code);
			if (argc < 4)
			{
				//GrammarAnaly ga_1;			//语法分析 这种分析方法有局限性
				//ga_1.grammarAnalysisUsingLL1WithoutGlobalVariable(lexical.tokList);
				GrammarAnalysis ga_2;			//语法分析
				if (!ga_2.grammarAnalysisUsingRecursiveDescentAndLL1_1(lexical.mTokenList))
				{
					cout << "语法分析[LL1分析函数体和递归下降],存在语法错误" << endl;
					return 1;
				}
				GrammarAnalysis ga_3;			//语法分析
				if (!ga_3.grammarAnalysisUsingRecursiveDescentAndLL1_2(lexical.mTokenList))
				{
					cout << "语法分析[LL1分析表达式和递归下降],存在语法错误" << endl;
					return 1;
				}
				GrammarAnalysis ga_4;			//语法分析
				if (!ga_4.grammarAnalysisUsingRecursiveDescent(lexical.mTokenList))
				{
					cout << "语法分析[递归下降],存在语法错误" << endl;
					return 1;
				}
			}
			else
			{
				if (!strcmp(argv[3], "1"))
				{
					GrammarAnalysis ga;			//语法分析
					if (!ga.grammarAnalysisUsingLL1WithoutGlobalVariable(lexical.mTokenList))
					{
						cout << "语法分析[完全LL1分析,不分析全局变量],存在语法错误" << endl;
						return 1;
					}
				}
				else if (!strcmp(argv[3], "2"))
				{
					GrammarAnalysis ga;			//语法分析
					if (!ga.grammarAnalysisUsingRecursiveDescentAndLL1_1(lexical.mTokenList))
					{
						cout << "语法分析[LL1分析函数体和递归下降],存在语法错误" << endl;
						return 1;
					}
				}
				else if (!strcmp(argv[3], "4"))
				{
					GrammarAnalysis ga;			//语法分析
					if (!ga.grammarAnalysisUsingRecursiveDescentAndLL1_2(lexical.mTokenList))
					{
						cout << "语法分析[LL1分析表达式和递归下降],存在语法错误" << endl;
						return 1;
					}
				}
				else if (!strcmp(argv[3], "8"))
				{
					GrammarAnalysis ga;			//语法分析
					if (!ga.grammarAnalysisUsingRecursiveDescent(lexical.mTokenList))
					{
						cout << "语法分析[递归下降],存在语法错误" << endl;
						return 1;
					}
				}
				else if (!strcmp(argv[3], "15"))
				{
					//GrammarAnaly ga_1;			//语法分析 这种分析方法有局限性
					//ga_1.grammarAnalysisUsingLL1WithoutGlobalVariable(lexical.tokList);
					GrammarAnalysis ga_2;			//语法分析
					if (!ga_2.grammarAnalysisUsingRecursiveDescentAndLL1_1(lexical.mTokenList))
					{
						cout << "语法分析[LL1分析函数体和递归下降],存在语法错误" << endl;
						return 1;
					}
					GrammarAnalysis ga_3;			//语法分析
					if (!ga_3.grammarAnalysisUsingRecursiveDescentAndLL1_2(lexical.mTokenList))
					{
						cout << "语法分析[LL1分析表达式和递归下降],存在语法错误" << endl;
						return 1;
					}
					GrammarAnalysis ga_4;			//语法分析
					if (!ga_4.grammarAnalysisUsingRecursiveDescent(lexical.mTokenList))
					{
						cout << "语法分析[递归下降],存在语法错误" << endl;
						return 1;
					}
				}
			}
		}
		else if (!strcmp(argv[2], "semantic"))
		{
			cout << "语义分析" << endl;
			LexicalAnalysis lexical;	//词法分析
			lexical.runLexicalAnalysis(code);
			GrammarAnalysis ga;			//语法分析
			if (!ga.grammarAnalysisUsingRecursiveDescent(lexical.mTokenList))
			{
				cout << "语法分析[递归下降],存在语法错误" << endl;
				return 1;
			}
			SemanticAnalysis semantic;					//语义分析
			if (!semantic.runSemanticAnalysis(lexical.mTokenList))
			{
				cout << "语义分析，存在语义错误" << endl;
				return 1;
			}
		}
		else if (!strcmp(argv[2], "object"))
		{
			cout << "目标代码生成" << endl;
			LexicalAnalysis lexical;	//词法分析
			lexical.runLexicalAnalysis(code);
			GrammarAnalysis ga;			//语法分析
			if (!ga.grammarAnalysisUsingRecursiveDescent(lexical.mTokenList))
			{
				cout << "语法分析[递归下降],存在语法错误" << endl;
				return 1;
			}
			SemanticAnalysis semantic;					//语义分析
			if (!semantic.runSemanticAnalysis(lexical.mTokenList))
			{
				cout << "语义分析，存在语义错误" << endl;
				return 1;
			}
			ObjectCodeGeneration_x86 objectCodeGeneration;	//目标代码生成
			objectCodeGeneration.runObjectCodeGeneration_x86(semantic);
			objectCodeGeneration.outFile("analysis\\object");
		}
		else if (!strcmp(argv[2], "compiler"))
		{
			cout << "Windows x86 平台编译" << endl;
			LexicalAnalysis lexical;	//词法分析
			GrammarAnalysis ga;			//语法分析
			if (!ga.grammarAnalysisUsingRecursiveDescent(lexical.mTokenList))
			{
				cout << "语法分析[递归下降],存在语法错误" << endl;
				return 1;
			}
			SemanticAnalysis semantic;					//语义分析
			if (!semantic.runSemanticAnalysis(lexical.mTokenList))
			{
				cout << "语义分析，存在语义错误" << endl;
				return 1;
			}
			ObjectCodeGeneration_x86 objectCodeGeneration;	//目标代码生成
			objectCodeGeneration.runObjectCodeGeneration_x86(semantic);
			objectCodeGeneration.outFile("analysis\\object");
			cout << "####  编译程序" << endl;
			system("compiler_link.bat");	//编译连接汇编代码成可执行文件
		}
	}
	return 0;
}