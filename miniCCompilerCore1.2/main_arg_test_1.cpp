#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;
#include "lexicalAnalysis.h"
#include "grammarAnalysis.h"
#include "semanticAnalysis.h"
#include "codeOptimization.h"
#include "objectCodeGeneration_x86.h"
#include "FileOperation.h"

#define GramAnal_1 0x1		//使用LL1预测分析方法进行语法分析，不分析全局变量定义
#define GramAnal_2 0x10		//LL1预测分析法分析函数体，其余使用递归下降分析
#define GramAnal_3 0x100	//LL1预测分析法分析表达式，其余使用递归下降分析
#define GramAnal_4 0x1000	//全部使用递归下降分析
#define GramAnal_5 0x10000	//LL1使用优化的文法进行语法分析

int StringConvertInteger(string arg_string)
{
	int result = 0;
	const char *cs = arg_string.c_str();
	for (unsigned int i = 0; i < arg_string.size(); i++)
	{
		result *= 10;
		result += cs[i] - '0';
	}
	return result;
}

bool GramAnalWithArg(int arg,LexicalAnalysis& lexical)
{
	if ((arg & 1) > 0)
	{
		//使用LL1预测分析方法进行语法分析，不分析全局变量定义
		GrammarAnalysis ga_1;			//语法分析 这种分析方法有局限性
		ga_1.grammarAnalysisUsingLL1WithoutGlobalVariable(lexical.mTokenList);
	}
	if ((arg & 2) > 0)
	{
		//LL1预测分析法分析函数体，其余使用递归下降分析
		GrammarAnalysis ga_2;			//语法分析
		if (!ga_2.grammarAnalysisUsingRecursiveDescentAndLL1_1(lexical.mTokenList))
		{
			cout << "语法分析[LL1分析函数体和递归下降],存在语法错误" << endl;
			return false;
		}
	}
	if ((arg & 4) > 0)
	{
		//LL1预测分析法分析表达式，其余使用递归下降分析
		GrammarAnalysis ga_3;			//语法分析
		if (!ga_3.grammarAnalysisUsingRecursiveDescentAndLL1_2(lexical.mTokenList))
		{
			cout << "语法分析[LL1分析表达式和递归下降],存在语法错误" << endl;
			return false;
		}
	}
	if ((arg & 8) > 0)
	{
		//全部使用递归下降分析
		GrammarAnalysis ga_4;			//语法分析
		if (!ga_4.grammarAnalysisUsingRecursiveDescent(lexical.mTokenList))
		{
			cout << "语法分析[递归下降],存在语法错误" << endl;
			return false;
		}
	}
	if( (arg & 16) > 0 )
	{
		//LL1按照更新的文法进行语法分析
		GrammarAnalysis ga_5;
		if (!ga_5.grammarAnalysisUsingLL1_2(lexical.mTokenList))
		{
			cout << "语法分析[LL1预测分析,更新文法]，存在语法错误" << endl;
			return false;
		}
	}
	return true;
}

int main(int argc, char** argv)
{
	//至少为3个参数
	if (argc < 3)
	{
		cout << "错误：缺少参数" << endl;
		cout << "format : program path command [gram_arg]" <<endl;
		return 1;
	}
	else
	{
		system("analysis\\clear.bat");	//清空analysis文件夹下的分析文件
		string path(argv[1]);	//path
		CodeList code(path);

		//词法分析
		if (!strcmp(argv[2], "lexical"))
		{
			LexicalAnalysis lexical;	//词法分析
			int lexicalErrorCount = lexical.runLexicalAnalysis(code);
			if (lexicalErrorCount > 0 )
			{
				cout << "Lexical词法分析结束，存在" << lexicalErrorCount << "个词法错误" << endl;
				fprintf(stderr,"Lexical Error\n");
			}
			else
			{
				cout << "Lexical词法分析完成，无词法错误" << endl;
			}
		}

		//语法分析
		else if (!strcmp(argv[2], "grammar"))
		{	
			//词法分析
			string gram_arg(argv[3]);//语法分析参数
			LexicalAnalysis lexical;	
			int lexicalErrorCount = lexical.runLexicalAnalysis(code);
			if (lexicalErrorCount > 0)
			{
				cout << "Lexical词法分析结束，存在" << lexicalErrorCount << "个词法错误" << endl;
				fprintf(stderr, "Lexical Error\n");
				return 1;
			}
			else
			{
				cout << "Lexical词法分析完成，无词法错误" << endl;
			}
			//语法分析
			int gram_arg_int = StringConvertInteger(gram_arg);
			cout << gram_arg_int << endl;
			if (GramAnalWithArg(gram_arg_int,lexical))
			{
				cout << "语法分析完成，无语法错误" << endl;
			}
			else
			{
				fprintf(stderr, "Grammar Error\n");
			}
		}

		//语义分析
		else if (!strcmp(argv[2], "semantic"))
		{
			//cout << "semantic 语义分析" << endl;
			//词法分析
			LexicalAnalysis lexical;	
			int lexicalErrorCount = lexical.runLexicalAnalysis(code);
			if (lexicalErrorCount > 0)
			{
				cout << "Lexical词法分析结束，存在" << lexicalErrorCount << "个词法错误" << endl;
				fprintf(stderr, "Lexical Error\n");
				return 1;
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
				fprintf(stderr, "Grammar Error\n");
				return 1;
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
				fprintf(stderr, "Semantic Error\n");
				return 1;
			}
			else
			{
				cout << "语义分析，存在语义错误" << endl;
			}
		}

		//代码优化
		else if (!strcmp(argv[2], "optimization"))
		{
			//词法分析
			LexicalAnalysis lexical;
			int lexicalErrorCount = lexical.runLexicalAnalysis(code);
			if (lexicalErrorCount > 0)
			{
				cout << "Lexical词法分析结束，存在" << lexicalErrorCount << "个词法错误" << endl;
				fprintf(stderr, "Lexical Error\n");
				return 1;
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
				fprintf(stderr, "Grammar Error\n");
				return 1;
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
				fprintf(stderr, "Semantic Error\n");
				return 1;
			}
			else
			{
				cout << "语义分析，存在语义错误" << endl;
			}
			//代码优化
			CodeOptimization optimization;
			if (!optimization.runCodeOptimization(semantic))
			{
				cout << "Optimization代码优化失败" << endl;
				fprintf(stderr, "Optimization Error\n");
				return 1;
			}
			else
			{
				cout << "Optimization代码优化成功" << endl;
			}
		}

		//目标代码生成
		else if (!strcmp(argv[2], "object"))
		{
			//cout << "object 目标代码生成" << endl;
			//词法分析
			LexicalAnalysis lexical;
			int lexicalErrorCount = lexical.runLexicalAnalysis(code);
			if (lexicalErrorCount > 0)
			{
				cout << "Lexical词法分析结束，存在" << lexicalErrorCount << "个词法错误" << endl;
				fprintf(stderr, "Lexical Error\n");
				return 1;
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
				fprintf(stderr, "Grammar Error\n");
				return 1;
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
				fprintf(stderr, "Semantic Error\n");
				return 1;
			}
			else
			{
				cout << "语义分析，存在语义错误" << endl;
			}
			//代码优化
			CodeOptimization optimization;
			if (!optimization.runCodeOptimization(semantic))
			{
				cout << "Optimization代码优化失败" << endl;
				fprintf(stderr, "Optimization Error\n");
				return 1;
			}
			else
			{
				cout << "Optimization代码优化成功" << endl;
			}
			//目标代码生成
			ObjectCodeGeneration_x86 objectCodeGeneration;	
			objectCodeGeneration.runObjectCodeGeneration_x86(semantic);
		}

		//平台编译
		else if (!strcmp(argv[2], "compiler"))
		{
			//cout << "Windows x86 平台编译" << endl;
			//词法分析
			LexicalAnalysis lexical;
			int lexicalErrorCount = lexical.runLexicalAnalysis(code);
			if (lexicalErrorCount > 0)
			{
				cout << "Lexical词法分析结束，存在" << lexicalErrorCount << "个词法错误" << endl;
				fprintf(stderr, "Lexical Error\n");
				return 1;
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
				fprintf(stderr, "Grammar Error\n");
				return 1;
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
				fprintf(stderr, "Semantic Error\n");
				return 1;
			}
			else
			{
				cout << "语义分析，存在语义错误" << endl;
			}
			//代码优化
			CodeOptimization optimization;
			if (!optimization.runCodeOptimization(semantic))
			{
				cout << "Optimization代码优化失败" << endl;
				fprintf(stderr, "Optimization Error\n");
				return 1;
			}
			else
			{
				cout << "Optimization代码优化成功" << endl;
			}
			//目标代码生成
			ObjectCodeGeneration_x86 objectCodeGeneration;
			objectCodeGeneration.runObjectCodeGeneration_x86(semantic);
			cout << "####  编译程序" << endl;
			system("compiler_link.bat");	//编译连接汇编代码成可执行文件
		}

		//运行程序
		else if (!strcmp(argv[2], "run"))
		{
			//词法分析
			LexicalAnalysis lexical;
			int lexicalErrorCount = lexical.runLexicalAnalysis(code);
			if (lexicalErrorCount > 0)
			{
				cout << "Lexical词法分析结束，存在" << lexicalErrorCount << "个词法错误" << endl;
				fprintf(stderr, "Lexical Error\n");
				return 1;
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
				fprintf(stderr, "Grammar Error\n");
				return 1;
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
				fprintf(stderr, "Semantic Error\n");
				return 1;
			}
			else
			{
				cout << "语义分析，存在语义错误" << endl;
			}
			//代码优化
			CodeOptimization optimization;
			if (!optimization.runCodeOptimization(semantic))
			{
				cout << "Optimization代码优化失败" << endl;
				fprintf(stderr, "Optimization Error\n");
				return 1;
			}
			else
			{
				cout << "Optimization代码优化成功" << endl;
			}
			//目标代码生成
			ObjectCodeGeneration_x86 objectCodeGeneration;
			objectCodeGeneration.runObjectCodeGeneration_x86(semantic);
			cout << "####  编译程序" << endl;
			system("compiler_link.bat");	//编译连接汇编代码成可执行文件
			cout << "####  运行程序" << endl;
			system("run.bat");				//运行程序
		}
	}
	return 0;
}