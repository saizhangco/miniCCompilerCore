#pragma once
#include <iostream>
#include <list>
#include <fstream>
using namespace std;
#include "token.h"
#include "LL_1_Analysis.h"
#include "node.h"
#include "tree.h"
#include "grammarTreeTmp.h"
#include "functionDefinition.h"
#include "variableDefinition.h"

#define TokenUnknown 0x00 //Token错误未知
#define TokenLose 0x01 //Token丢失
#define TokenExcess 0x02 //Token多余
#define TokenMismatch 0x03 //Token匹配


class GrammarAnalysis
{
public:
	list<string> grammarError;	//用来保存语法错误
								//建立一个语法树
	Tree* grammarTree;
	int count;
private:
	bool analysis_express_using_LL1;
	bool analysis_function_body_using_LL1;
	bool analysis_miniC_using_LL1;
	ofstream outAnalysisFile;
	LL_1_Analysis* grammar_for_miniC;	//指针变量会在构造函数中初始化，在析构函数中释放
	LL_1_Analysis* grammar_for_function_body;
	LL_1_Analysis* grammar_for_expression;
	LL_1_Analysis* grammar_for_miniC_2;	//使用LL1预测分析法按照更新后的文法分析
public:
	GrammarAnalysis();
	~GrammarAnalysis();
	bool grammarAnalysisUsingLL1WithoutGlobalVariable(list<Token>& listToken);	//仅使用LL1预测分析，分析miniC语言（不能包含全局变量）
	bool grammarAnalysisUsingRecursiveDescentAndLL1_1(list<Token>& listToken);	//使用递归下降和LL1预测分析，分析miniC语言，LL1分析函数体内部语法
	bool grammarAnalysisUsingRecursiveDescentAndLL1_2(list<Token>& listToken);	//使用递归下降和LL1预测分析，分析miniC语言，LL1仅分析表达式
	bool grammarAnalysisUsingRecursiveDescent(list<Token>& TokenenList);		//仅使用递归下降分析miniC语言
	bool grammarAnalysisUsingLL1_2(list<Token>& listToken);						//使用LL1预测分析按照更新后的文法分析
	void printGrammarTree();
private:
	//---------------------------------------------------------------------------------------------------
	// 全局变量定义、函数声明、函数实现
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
	// FB分析函数
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
	// 表达式分析
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
		root -> id(变量)
		root -> 整型(八进制、十进制、十六进制)
		root -> 浮点型( 小数、指数 )
		root -> 布尔型 BOOL
		root -> 字符型
	*/
	bool grammarAnalysis_root(list<Token>::iterator& itAnalysisCur, list<Token>& TokenenList);
	/*
		BOOL -> true
		BOOL -> false
	*/
	bool grammarAnalysisBOOL(list<Token>::iterator& itAnalysisCur, list<Token>& TokenenList);

	//是否为表达式预分析
	bool expressPreAnalysis(int type);
	//识别语法错误
	int recogniseGrammarError(list<Token>::iterator& itAnalysisCur,int curType,int nextType);
};
