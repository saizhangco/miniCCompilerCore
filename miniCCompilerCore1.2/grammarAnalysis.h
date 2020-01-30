#pragma once
#include <iostream>
#include <list>
#include <fstream>
using namespace std;
#include "Token.h"
#include "LL_1_Analysis.h"
#include "node.h"
#include "tree.h"
#include "grammarTreeTmp.h"
#include "functionDefinition.h"
#include "variableDefinition.h"

#define TokenUnknown 0x00 //Token����δ֪
#define TokenLose 0x01 //Token��ʧ
#define TokenExcess 0x02 //Token����
#define TokenMismatch 0x03 //Tokenƥ��


class GrammarAnalysis
{
public:
	list<string> grammarError;	//���������﷨����
								//����һ���﷨��
	Tree* grammarTree;
	int count;
private:
	bool analysis_express_using_LL1;
	bool analysis_function_body_using_LL1;
	bool analysis_miniC_using_LL1;
	ofstream outAnalysisFile;
	LL_1_Analysis* grammar_for_miniC;	//ָ��������ڹ��캯���г�ʼ�����������������ͷ�
	LL_1_Analysis* grammar_for_function_body;
	LL_1_Analysis* grammar_for_expression;
	LL_1_Analysis* grammar_for_miniC_2;	//ʹ��LL1Ԥ����������ո��º���ķ�����
public:
	GrammarAnalysis();
	~GrammarAnalysis();
	bool grammarAnalysisUsingLL1WithoutGlobalVariable(list<Token>& listToken);	//��ʹ��LL1Ԥ�����������miniC���ԣ����ܰ���ȫ�ֱ�����
	bool grammarAnalysisUsingRecursiveDescentAndLL1_1(list<Token>& listToken);	//ʹ�õݹ��½���LL1Ԥ�����������miniC���ԣ�LL1�����������ڲ��﷨
	bool grammarAnalysisUsingRecursiveDescentAndLL1_2(list<Token>& listToken);	//ʹ�õݹ��½���LL1Ԥ�����������miniC���ԣ�LL1���������ʽ
	bool grammarAnalysisUsingRecursiveDescent(list<Token>& TokenenList);		//��ʹ�õݹ��½�����miniC����
	bool grammarAnalysisUsingLL1_2(list<Token>& listToken);						//ʹ��LL1Ԥ��������ո��º���ķ�����
	void printGrammarTree();
private:
	//---------------------------------------------------------------------------------------------------
	// ȫ�ֱ������塢��������������ʵ��
	//---------------------------------------------------------------------------------------------------
	/*
		S -> $
		S -> F S
	*/
	bool grammarAnalysisS(list<Token>::iterator& it_AnalysisCur, list<Token>& listToken, Node* node);
	/*
		F -> MT1 DT S1
	*/
	bool grammarAnalysisF(list<Token>::iterator& it_AnalysisCur, list<Token>& listToken, Node* node);
	/*
		F1 -> VL ;
		F1 -> functionName ( PL ) F2
	*/
	bool grammarAnalysisF1(list<Token>::iterator& it_AnalysisCur, list<Token>& listToken, GrammarTreeTmp& tmp);
	/*
		F2 -> { FB }
		F2 -> ;
	*/
	bool grammarAnalysisF2(list<Token>::iterator& it_AnalysisCur, list<Token>& listToken, GrammarTreeTmp& tmp);
	/*
		MT -> auto
		MT -> register
		MT -> MT1
	*/
	bool grammarAnalysisMT(list<Token>::iterator& it_AnalysisCur, list<Token>& listToken, int& memoryType);
	/*
		MT1 -> extern
		MT1 -> static
		MT1 -> $
	*/
	bool grammarAnalysisMT1(list<Token>::iterator& it_AnalysisCur, list<Token>& listToken, int& memoryType);
	/*
		DT -> void
		DT -> int
		DT -> char
		DT -> float
		DT -> double
	*/
	bool grammarAnalysisDT(list<Token>::iterator& it_AnalysisCur, list<Token>& listToken, int& dataType);
	/*
		VL -> VD VL1
	*/
	bool grammarAnalysisVL(list<Token>::iterator& it_AnalysisCur, list<Token>& listToken, list<VariableList>& variableList);
	/*
		VL1 -> , VD VL1
		VL1 -> $
	*/
	bool grammarAnalysisVL1(list<Token>::iterator& it_AnalysisCur, list<Token>& listToken, list<VariableList>& variableList);
	/*
		VD -> variableName VD1
	*/
	bool grammarAnalysisVD(list<Token>::iterator& it_AnalysisCur, list<Token>& listToken, VariableList& variable);
	/*
		VD1 -> = PR
		VD1 -> $
	*/
	bool grammarAnalysisVD1(list<Token>::iterator& it_AnalysisCur, list<Token>& listToken, list<Token>& initValue);
	/*
		PL -> $
		PL -> PL1
	*/
	bool grammarAnalysisPL(list<Token>::iterator& it_AnalysisCur, list<Token>& listToken, list<ParameterList>& parameterList);
	/*
		PL1 -> PD PL2
	*/
	bool grammarAnalysisPL1(list<Token>::iterator& it_AnalysisCur, list<Token>& listToken, list<ParameterList>& parameterList);
	/*
		PL2 -> , PD PL2
		PL2 -> $
	*/
	bool grammarAnalysisPL2(list<Token>::iterator& it_AnalysisCur, list<Token>& listToken, list<ParameterList>& parameterList);
	/*
		PD -> DT PD1
	*/
	bool grammarAnalysisPD(list<Token>::iterator& it_AnalysisCur, list<Token>& listToken, ParameterList& parameter);
	/*
		PD1 -> parameterName
		PD1 -> $
	*/
	bool grammarAnalysisPD1(list<Token>::iterator& it_AnalysisCur, list<Token>& listToken, string& parameterName);
	//---------------------------------------------------------------------------------------------------
	// FB��������
	//---------------------------------------------------------------------------------------------------
	/*
		FB -> $
		FB -> RS FB
	*/
	bool grammarAnalysisFB(list<Token>::iterator& it_AnalysisCur, list<Token>& listToken);
	/*
		RS -> MT DT VL ;
		RS -> PR ;
		RS -> if ( PR ) SB RS1
		RS -> while ( PR ) SB
		RS -> do SB while ( PR ) ;
		RS -> for ( PR ,PR ,PR ) SB
		RS -> break ;
		RS -> continue ;
		RS -> return PR ;
		RS -> print ( Print
		RS -> scan ( id ) ;
	*/
	bool grammarAnalysisRS(list<Token>::iterator& it_AnalysisCur, list<Token>& listToken);
	/*
		RS1 -> $
		RS1 -> else SB
	*/
	bool grammarAnalysisRS1(list<Token>::iterator& it_AnalysisCur, list<Token>& listToken);
	/*
		SB -> RS
		SB -> { SB1 }
	*/
	bool grammarAnalysisSB(list<Token>::iterator& it_AnalysisCur, list<Token>& listToken);
	/*
		SB1 -> $
		SB1 -> RS SB1
	*/
	bool grammarAnalysisSB1(list<Token>::iterator& it_AnalysisCur, list<Token>& listToken);
	/*
		Print -> string ) ;
		Print -> PR ) ;
	*/
	bool grammarAnalysisPrint(list<Token>::iterator& it_AnalysisCur, list<Token>& listToken);
	//---------------------------------------------------------------------------------------------------
	// ���ʽ����
	//---------------------------------------------------------------------------------------------------
	/*
		eexpr -> bexpr eexpr1
	*/
	bool grammarAnalysis_eexpr(list<Token>::iterator& itAnalysisCur, list<Token>& TokenenList);
	/*
		eexpr1 -> ao bexpr eexpr1
		eexpr1 -> $
	*/
	bool grammarAnalysis_eexpr1(list<Token>::iterator& itAnalysisCur, list<Token>& TokenenList);
	/*
		ao -> =
		ao -> +=
		ao -> -=
		ao -> *=
		ao -> /=
	*/
	bool grammarAnalysis_ao(list<Token>::iterator& itAnalysisCur, list<Token>& TokenenList);
	/*
		bexpr -> bterm bexpr1
	*/
	bool grammarAnalysis_bexpr(list<Token>::iterator& itAnalysisCur, list<Token>& TokenenList);
	/*
		bexpr1 -> || bterm bexpr1
		bexpr1 -> $
	*/
	bool grammarAnalysis_bexpr1(list<Token>::iterator& itAnalysisCur, list<Token>& TokenenList);
	/*
		bterm -> rterm bterm1
	*/
	bool grammarAnalysis_bterm(list<Token>::iterator& itAnalysisCur, list<Token>& TokenenList);
	/*
		bterm1 -> && rexpr bterm1
		bterm1 -> $
	*/
	bool grammarAnalysis_bterm1(list<Token>::iterator& itAnalysisCur, list<Token>& TokenenList);
	/*
		rexpr -> aexpr rexpr1
	*/
	bool grammarAnalysis_rexpr(list<Token>::iterator& itAnalysisCur, list<Token>& TokenenList);
	/*
		rexpr1 -> < aexpr
		rexpr1 -> > aexpr
		rexpr1 -> <= aexpr
		rexpr1 -> <= aexpr
		rexpr1 -> != aexpr
		rexpr1 -> == aexpr
		rexpr1 -> $
	*/
	bool grammarAnalysis_rexpr1(list<Token>::iterator& itAnalysisCur, list<Token>& TokenenList);
	/*
		aexpr -> term aexpr1
	*/
	bool grammarAnalysis_aexpr(list<Token>::iterator& itAnalysisCur, list<Token>& TokenenList);
	/*
		aexpr1 -> + term aexpr1
		aexpr1 -> - term aexpr1
		aexpr1 -> $
	*/
	bool grammarAnalysis_aexpr1(list<Token>::iterator& itAnalysisCur, list<Token>& TokenenList);
	/*
		term -> factor term1
	*/
	bool grammarAnalysis_term(list<Token>::iterator& itAnalysisCur, list<Token>& TokenenList);
	/*
		term1 -> * factor term1
		term1 -> / factor term1
		term1 -> % factor term1
		term1 -> $
	*/
	bool grammarAnalysis_term1(list<Token>::iterator& itAnalysisCur, list<Token>& TokenenList);
	/*
		factor -> ! ael
		factor -> ael
	*/
	bool grammarAnalysis_factor(list<Token>::iterator& itAnalysisCur, list<Token>& TokenenList);
	/*
		ael -> ( bexpr )
		ael -> root
	*/
	bool grammarAnalysis_ael(list<Token>::iterator& itAnalysisCur, list<Token>& TokenenList);
	/*
		root -> id(����)
		root -> ����(�˽��ơ�ʮ���ơ�ʮ������)
		root -> ������( С����ָ�� )
		root -> ������ BOOL
		root -> �ַ���
	*/
	bool grammarAnalysis_root(list<Token>::iterator& itAnalysisCur, list<Token>& TokenenList);
	/*
		BOOL -> true
		BOOL -> false
	*/
	bool grammarAnalysisBOOL(list<Token>::iterator& itAnalysisCur, list<Token>& TokenenList);

	//�Ƿ�Ϊ���ʽԤ����
	bool expressPreAnalysis(int type);
	//ʶ���﷨����
	int recogniseGrammarError(list<Token>::iterator& itAnalysisCur,int curType,int nextType);
};