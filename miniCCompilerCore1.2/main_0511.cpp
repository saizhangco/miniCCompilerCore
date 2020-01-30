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
	string gram_arg("");//�﷨��������
						
	//�ʷ�����
	LexicalAnalysis lexical;
	int lexicalErrorCount = lexical.runLexicalAnalysis(code);
	if (lexicalErrorCount > 0)
	{
		cout << "Lexical�ʷ���������������" << lexicalErrorCount << "���ʷ�����" << endl;
		return;
		//lexicalError = true;
	}
	else
	{
		cout << "Lexical�ʷ�������ɣ��޴ʷ�����" << endl;
	}
	//�﷨����
	GrammarAnalysis ga_5;
	if (!ga_5.grammarAnalysisUsingLL1_2(lexical.mTokenList))
	{
		cout << "�﷨����[LL1Ԥ�����,�����ķ�]�������﷨����" << endl;
		return ;
		//grammarError = true;
	}
	//�������
	SemanticAnalysis semantic;
	if (!grammarError && !semantic.runSemanticAnalysis(lexical.mTokenList))
	{
		cout << "��������������������" << endl;
		//return 1;
		semanticError = true;
	}
	//�����Ż�
	CodeOptimization codeOptimization;
	if (!semanticError && codeOptimization.runCodeOptimization(semantic))
	{

	}
	system("pause");
}

void main_0528()
{
	system("analysis\\clear.bat");	//���analysis�ļ����µķ����ļ�
	string path("path.txt");	//path
	CodeList code(path);

	LexicalAnalysis lexical;
	int lexicalErrorCount = lexical.runLexicalAnalysis(code);
	if (lexicalErrorCount > 0)
	{
		cout << "Lexical�ʷ���������������" << lexicalErrorCount << "���ʷ�����" << endl;
		system("pause");
	}
	else
	{
		cout << "Lexical�ʷ�������ɣ��޴ʷ�����" << endl;
	}
	//�﷨����
	GrammarAnalysis grammar;
	if (!grammar.grammarAnalysisUsingLL1_2(lexical.mTokenList))
	{
		cout << "Grammar�﷨��������������" << grammar.grammarError.size() << "���﷨����" << endl;
		system("pause");
	}
	else
	{
		cout << "Grammar�﷨������ɣ����﷨����" << endl;
	}
	//����������м��������
	SemanticAnalysis semantic;					//�������
	if (!semantic.runSemanticAnalysis(lexical.mTokenList))
	{
		cout << "Semantic�����������������" << semantic.mErrorInfo.size() << "���������" << endl;
		system("pause");
	}
	else
	{
		cout << "Semantic���������ɣ����������" << endl;
	}
	//�����Ż�
	CodeOptimization optimization;
	if (!optimization.runCodeOptimization(semantic))
	{
		cout << "Optimization�����Ż�ʧ��" << endl;
		system("pause");
	}
	else
	{
		cout << "Optimization�����Ż��ɹ�" << endl;
	}
	//Ŀ���������
	ObjectCodeGeneration_x86 objectCodeGeneration;
	objectCodeGeneration.runObjectCodeGeneration_x86(semantic);
	system("pause");
	cout << "####  �������" << endl;
	system("compiler_link.bat");	//�������ӻ�����ɿ�ִ���ļ�
	cout << "####  ���г���" << endl;
	system("run.bat");				//���г���
	
}