#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;
#include "lexicalAnalysis.h"
#include "grammarAnalysis.h"
#include "semanticAnalysis.h"
#include "objectCodeGeneration_x86.h"
#include "FileOperation.h"

#define GramAnal_1 0x1		//ʹ��LL1Ԥ��������������﷨������������ȫ�ֱ�������
#define GramAnal_2 0x10		//LL1Ԥ����������������壬����ʹ�õݹ��½�����
#define GramAnal_3 0x100	//LL1Ԥ��������������ʽ������ʹ�õݹ��½�����
#define GramAnal_4 0x1000	//ȫ��ʹ�õݹ��½�����
#define GramAnal_5 0x10000	//LL1ʹ���Ż����ķ������﷨����

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
			cout << "�ʷ�����" << endl;
			LexicalAnalysis lexical;	//�ʷ�����
			lexical.runLexicalAnalysis(code);
		}
		else if (!strcmp(argv[2], "grammar"))
		{
			cout << "�﷨����" << endl;
			LexicalAnalysis lexical;	//�ʷ�����
			lexical.runLexicalAnalysis(code);
			if (argc < 4)
			{
				//GrammarAnaly ga_1;			//�﷨���� ���ַ��������о�����
				//ga_1.grammarAnalysisUsingLL1WithoutGlobalVariable(lexical.tokList);
				GrammarAnalysis ga_2;			//�﷨����
				if (!ga_2.grammarAnalysisUsingRecursiveDescentAndLL1_1(lexical.mTokenList))
				{
					cout << "�﷨����[LL1����������͵ݹ��½�],�����﷨����" << endl;
					return 1;
				}
				GrammarAnalysis ga_3;			//�﷨����
				if (!ga_3.grammarAnalysisUsingRecursiveDescentAndLL1_2(lexical.mTokenList))
				{
					cout << "�﷨����[LL1�������ʽ�͵ݹ��½�],�����﷨����" << endl;
					return 1;
				}
				GrammarAnalysis ga_4;			//�﷨����
				if (!ga_4.grammarAnalysisUsingRecursiveDescent(lexical.mTokenList))
				{
					cout << "�﷨����[�ݹ��½�],�����﷨����" << endl;
					return 1;
				}
			}
			else
			{
				if (!strcmp(argv[3], "1"))
				{
					GrammarAnalysis ga;			//�﷨����
					if (!ga.grammarAnalysisUsingLL1WithoutGlobalVariable(lexical.mTokenList))
					{
						cout << "�﷨����[��ȫLL1����,������ȫ�ֱ���],�����﷨����" << endl;
						return 1;
					}
				}
				else if (!strcmp(argv[3], "2"))
				{
					GrammarAnalysis ga;			//�﷨����
					if (!ga.grammarAnalysisUsingRecursiveDescentAndLL1_1(lexical.mTokenList))
					{
						cout << "�﷨����[LL1����������͵ݹ��½�],�����﷨����" << endl;
						return 1;
					}
				}
				else if (!strcmp(argv[3], "4"))
				{
					GrammarAnalysis ga;			//�﷨����
					if (!ga.grammarAnalysisUsingRecursiveDescentAndLL1_2(lexical.mTokenList))
					{
						cout << "�﷨����[LL1�������ʽ�͵ݹ��½�],�����﷨����" << endl;
						return 1;
					}
				}
				else if (!strcmp(argv[3], "8"))
				{
					GrammarAnalysis ga;			//�﷨����
					if (!ga.grammarAnalysisUsingRecursiveDescent(lexical.mTokenList))
					{
						cout << "�﷨����[�ݹ��½�],�����﷨����" << endl;
						return 1;
					}
				}
				else if (!strcmp(argv[3], "15"))
				{
					//GrammarAnaly ga_1;			//�﷨���� ���ַ��������о�����
					//ga_1.grammarAnalysisUsingLL1WithoutGlobalVariable(lexical.tokList);
					GrammarAnalysis ga_2;			//�﷨����
					if (!ga_2.grammarAnalysisUsingRecursiveDescentAndLL1_1(lexical.mTokenList))
					{
						cout << "�﷨����[LL1����������͵ݹ��½�],�����﷨����" << endl;
						return 1;
					}
					GrammarAnalysis ga_3;			//�﷨����
					if (!ga_3.grammarAnalysisUsingRecursiveDescentAndLL1_2(lexical.mTokenList))
					{
						cout << "�﷨����[LL1�������ʽ�͵ݹ��½�],�����﷨����" << endl;
						return 1;
					}
					GrammarAnalysis ga_4;			//�﷨����
					if (!ga_4.grammarAnalysisUsingRecursiveDescent(lexical.mTokenList))
					{
						cout << "�﷨����[�ݹ��½�],�����﷨����" << endl;
						return 1;
					}
				}
			}
		}
		else if (!strcmp(argv[2], "semantic"))
		{
			cout << "�������" << endl;
			LexicalAnalysis lexical;	//�ʷ�����
			lexical.runLexicalAnalysis(code);
			GrammarAnalysis ga;			//�﷨����
			if (!ga.grammarAnalysisUsingRecursiveDescent(lexical.mTokenList))
			{
				cout << "�﷨����[�ݹ��½�],�����﷨����" << endl;
				return 1;
			}
			SemanticAnalysis semantic;					//�������
			if (!semantic.runSemanticAnalysis(lexical.mTokenList))
			{
				cout << "��������������������" << endl;
				return 1;
			}
		}
		else if (!strcmp(argv[2], "object"))
		{
			cout << "Ŀ���������" << endl;
			LexicalAnalysis lexical;	//�ʷ�����
			lexical.runLexicalAnalysis(code);
			GrammarAnalysis ga;			//�﷨����
			if (!ga.grammarAnalysisUsingRecursiveDescent(lexical.mTokenList))
			{
				cout << "�﷨����[�ݹ��½�],�����﷨����" << endl;
				return 1;
			}
			SemanticAnalysis semantic;					//�������
			if (!semantic.runSemanticAnalysis(lexical.mTokenList))
			{
				cout << "��������������������" << endl;
				return 1;
			}
			ObjectCodeGeneration_x86 objectCodeGeneration;	//Ŀ���������
			objectCodeGeneration.runObjectCodeGeneration_x86(semantic);
			objectCodeGeneration.outFile("analysis\\object");
		}
		else if (!strcmp(argv[2], "compiler"))
		{
			cout << "Windows x86 ƽ̨����" << endl;
			LexicalAnalysis lexical;	//�ʷ�����
			GrammarAnalysis ga;			//�﷨����
			if (!ga.grammarAnalysisUsingRecursiveDescent(lexical.mTokenList))
			{
				cout << "�﷨����[�ݹ��½�],�����﷨����" << endl;
				return 1;
			}
			SemanticAnalysis semantic;					//�������
			if (!semantic.runSemanticAnalysis(lexical.mTokenList))
			{
				cout << "��������������������" << endl;
				return 1;
			}
			ObjectCodeGeneration_x86 objectCodeGeneration;	//Ŀ���������
			objectCodeGeneration.runObjectCodeGeneration_x86(semantic);
			objectCodeGeneration.outFile("analysis\\object");
			cout << "####  �������" << endl;
			system("compiler_link.bat");	//�������ӻ�����ɿ�ִ���ļ�
		}
	}
	return 0;
}