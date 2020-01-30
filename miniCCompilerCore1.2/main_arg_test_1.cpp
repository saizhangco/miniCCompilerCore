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

#define GramAnal_1 0x1		//ʹ��LL1Ԥ��������������﷨������������ȫ�ֱ�������
#define GramAnal_2 0x10		//LL1Ԥ����������������壬����ʹ�õݹ��½�����
#define GramAnal_3 0x100	//LL1Ԥ��������������ʽ������ʹ�õݹ��½�����
#define GramAnal_4 0x1000	//ȫ��ʹ�õݹ��½�����
#define GramAnal_5 0x10000	//LL1ʹ���Ż����ķ������﷨����

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
		//ʹ��LL1Ԥ��������������﷨������������ȫ�ֱ�������
		GrammarAnalysis ga_1;			//�﷨���� ���ַ��������о�����
		ga_1.grammarAnalysisUsingLL1WithoutGlobalVariable(lexical.mTokenList);
	}
	if ((arg & 2) > 0)
	{
		//LL1Ԥ����������������壬����ʹ�õݹ��½�����
		GrammarAnalysis ga_2;			//�﷨����
		if (!ga_2.grammarAnalysisUsingRecursiveDescentAndLL1_1(lexical.mTokenList))
		{
			cout << "�﷨����[LL1����������͵ݹ��½�],�����﷨����" << endl;
			return false;
		}
	}
	if ((arg & 4) > 0)
	{
		//LL1Ԥ��������������ʽ������ʹ�õݹ��½�����
		GrammarAnalysis ga_3;			//�﷨����
		if (!ga_3.grammarAnalysisUsingRecursiveDescentAndLL1_2(lexical.mTokenList))
		{
			cout << "�﷨����[LL1�������ʽ�͵ݹ��½�],�����﷨����" << endl;
			return false;
		}
	}
	if ((arg & 8) > 0)
	{
		//ȫ��ʹ�õݹ��½�����
		GrammarAnalysis ga_4;			//�﷨����
		if (!ga_4.grammarAnalysisUsingRecursiveDescent(lexical.mTokenList))
		{
			cout << "�﷨����[�ݹ��½�],�����﷨����" << endl;
			return false;
		}
	}
	if( (arg & 16) > 0 )
	{
		//LL1���ո��µ��ķ������﷨����
		GrammarAnalysis ga_5;
		if (!ga_5.grammarAnalysisUsingLL1_2(lexical.mTokenList))
		{
			cout << "�﷨����[LL1Ԥ�����,�����ķ�]�������﷨����" << endl;
			return false;
		}
	}
	return true;
}

int main(int argc, char** argv)
{
	//����Ϊ3������
	if (argc < 3)
	{
		cout << "����ȱ�ٲ���" << endl;
		cout << "format : program path command [gram_arg]" <<endl;
		return 1;
	}
	else
	{
		system("analysis\\clear.bat");	//���analysis�ļ����µķ����ļ�
		string path(argv[1]);	//path
		CodeList code(path);

		//�ʷ�����
		if (!strcmp(argv[2], "lexical"))
		{
			LexicalAnalysis lexical;	//�ʷ�����
			int lexicalErrorCount = lexical.runLexicalAnalysis(code);
			if (lexicalErrorCount > 0 )
			{
				cout << "Lexical�ʷ���������������" << lexicalErrorCount << "���ʷ�����" << endl;
				fprintf(stderr,"Lexical Error\n");
			}
			else
			{
				cout << "Lexical�ʷ�������ɣ��޴ʷ�����" << endl;
			}
		}

		//�﷨����
		else if (!strcmp(argv[2], "grammar"))
		{	
			//�ʷ�����
			string gram_arg(argv[3]);//�﷨��������
			LexicalAnalysis lexical;	
			int lexicalErrorCount = lexical.runLexicalAnalysis(code);
			if (lexicalErrorCount > 0)
			{
				cout << "Lexical�ʷ���������������" << lexicalErrorCount << "���ʷ�����" << endl;
				fprintf(stderr, "Lexical Error\n");
				return 1;
			}
			else
			{
				cout << "Lexical�ʷ�������ɣ��޴ʷ�����" << endl;
			}
			//�﷨����
			int gram_arg_int = StringConvertInteger(gram_arg);
			cout << gram_arg_int << endl;
			if (GramAnalWithArg(gram_arg_int,lexical))
			{
				cout << "�﷨������ɣ����﷨����" << endl;
			}
			else
			{
				fprintf(stderr, "Grammar Error\n");
			}
		}

		//�������
		else if (!strcmp(argv[2], "semantic"))
		{
			//cout << "semantic �������" << endl;
			//�ʷ�����
			LexicalAnalysis lexical;	
			int lexicalErrorCount = lexical.runLexicalAnalysis(code);
			if (lexicalErrorCount > 0)
			{
				cout << "Lexical�ʷ���������������" << lexicalErrorCount << "���ʷ�����" << endl;
				fprintf(stderr, "Lexical Error\n");
				return 1;
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
				fprintf(stderr, "Grammar Error\n");
				return 1;
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
				fprintf(stderr, "Semantic Error\n");
				return 1;
			}
			else
			{
				cout << "��������������������" << endl;
			}
		}

		//�����Ż�
		else if (!strcmp(argv[2], "optimization"))
		{
			//�ʷ�����
			LexicalAnalysis lexical;
			int lexicalErrorCount = lexical.runLexicalAnalysis(code);
			if (lexicalErrorCount > 0)
			{
				cout << "Lexical�ʷ���������������" << lexicalErrorCount << "���ʷ�����" << endl;
				fprintf(stderr, "Lexical Error\n");
				return 1;
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
				fprintf(stderr, "Grammar Error\n");
				return 1;
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
				fprintf(stderr, "Semantic Error\n");
				return 1;
			}
			else
			{
				cout << "��������������������" << endl;
			}
			//�����Ż�
			CodeOptimization optimization;
			if (!optimization.runCodeOptimization(semantic))
			{
				cout << "Optimization�����Ż�ʧ��" << endl;
				fprintf(stderr, "Optimization Error\n");
				return 1;
			}
			else
			{
				cout << "Optimization�����Ż��ɹ�" << endl;
			}
		}

		//Ŀ���������
		else if (!strcmp(argv[2], "object"))
		{
			//cout << "object Ŀ���������" << endl;
			//�ʷ�����
			LexicalAnalysis lexical;
			int lexicalErrorCount = lexical.runLexicalAnalysis(code);
			if (lexicalErrorCount > 0)
			{
				cout << "Lexical�ʷ���������������" << lexicalErrorCount << "���ʷ�����" << endl;
				fprintf(stderr, "Lexical Error\n");
				return 1;
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
				fprintf(stderr, "Grammar Error\n");
				return 1;
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
				fprintf(stderr, "Semantic Error\n");
				return 1;
			}
			else
			{
				cout << "��������������������" << endl;
			}
			//�����Ż�
			CodeOptimization optimization;
			if (!optimization.runCodeOptimization(semantic))
			{
				cout << "Optimization�����Ż�ʧ��" << endl;
				fprintf(stderr, "Optimization Error\n");
				return 1;
			}
			else
			{
				cout << "Optimization�����Ż��ɹ�" << endl;
			}
			//Ŀ���������
			ObjectCodeGeneration_x86 objectCodeGeneration;	
			objectCodeGeneration.runObjectCodeGeneration_x86(semantic);
		}

		//ƽ̨����
		else if (!strcmp(argv[2], "compiler"))
		{
			//cout << "Windows x86 ƽ̨����" << endl;
			//�ʷ�����
			LexicalAnalysis lexical;
			int lexicalErrorCount = lexical.runLexicalAnalysis(code);
			if (lexicalErrorCount > 0)
			{
				cout << "Lexical�ʷ���������������" << lexicalErrorCount << "���ʷ�����" << endl;
				fprintf(stderr, "Lexical Error\n");
				return 1;
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
				fprintf(stderr, "Grammar Error\n");
				return 1;
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
				fprintf(stderr, "Semantic Error\n");
				return 1;
			}
			else
			{
				cout << "��������������������" << endl;
			}
			//�����Ż�
			CodeOptimization optimization;
			if (!optimization.runCodeOptimization(semantic))
			{
				cout << "Optimization�����Ż�ʧ��" << endl;
				fprintf(stderr, "Optimization Error\n");
				return 1;
			}
			else
			{
				cout << "Optimization�����Ż��ɹ�" << endl;
			}
			//Ŀ���������
			ObjectCodeGeneration_x86 objectCodeGeneration;
			objectCodeGeneration.runObjectCodeGeneration_x86(semantic);
			cout << "####  �������" << endl;
			system("compiler_link.bat");	//�������ӻ�����ɿ�ִ���ļ�
		}

		//���г���
		else if (!strcmp(argv[2], "run"))
		{
			//�ʷ�����
			LexicalAnalysis lexical;
			int lexicalErrorCount = lexical.runLexicalAnalysis(code);
			if (lexicalErrorCount > 0)
			{
				cout << "Lexical�ʷ���������������" << lexicalErrorCount << "���ʷ�����" << endl;
				fprintf(stderr, "Lexical Error\n");
				return 1;
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
				fprintf(stderr, "Grammar Error\n");
				return 1;
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
				fprintf(stderr, "Semantic Error\n");
				return 1;
			}
			else
			{
				cout << "��������������������" << endl;
			}
			//�����Ż�
			CodeOptimization optimization;
			if (!optimization.runCodeOptimization(semantic))
			{
				cout << "Optimization�����Ż�ʧ��" << endl;
				fprintf(stderr, "Optimization Error\n");
				return 1;
			}
			else
			{
				cout << "Optimization�����Ż��ɹ�" << endl;
			}
			//Ŀ���������
			ObjectCodeGeneration_x86 objectCodeGeneration;
			objectCodeGeneration.runObjectCodeGeneration_x86(semantic);
			cout << "####  �������" << endl;
			system("compiler_link.bat");	//�������ӻ�����ɿ�ִ���ļ�
			cout << "####  ���г���" << endl;
			system("run.bat");				//���г���
		}
	}
	return 0;
}