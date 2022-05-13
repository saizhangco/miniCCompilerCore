#pragma once
#include <iostream>
#include <list>
using namespace std;
#include "token.h"
#include "fourElementType.h"
#include "fourElementTypeItem.h"
#include "variableDefinition.h"
#include "functionDefinition.h"

/*
语义错误：
	1.判断程序是否缺少函数入口
	语义分析及中间代码生成
	1.分析出函数的定义和实现，函数定义和实现保存在函数定义列表中
	2.分析出变量的定义，并将变量的定义保存在变量定义列表中
	3.判断变量是否重复定义，判断时分为全局变量和局部变量
	//变量只能定义在函数开始部分
	//全为局部变量不能重复
	//全为全局变量不能重复
	//局部变量会屏蔽全局变量
	//重复定义错误
	4.函数声明和函数实现是否匹配
	5.函数声明、函数实现是否重复定义
*/

class SemanticAnalysis	//语义分析及中间代码生成
{
public:
	list<FourElementType> mFourElementTypeList;	//四元式List
	list<VariableDefinition> mVariableDefinitionList;	//用户定义变量List
	list<FunctionDefinition> mFunctionDefinitionList;	//函数定义
	list<FourElementTypeItem> mTempIdentifierList;		//临时变量List
	list<string> mErrorInfo;	//语义错误
	list<int> breakPosiList;	//break 跳出的位置
	list<int> continuePosiList;	//continue 跳出的位置
	list<int> returnPosiList;	//return 返回的位置
private:
	list<string> variableCache;
	string curFunctionName;		//当前分析的函数名
public:
	SemanticAnalysis();
	~SemanticAnalysis();
	bool runSemanticAnalysis(list<Token>& TokenenList);	//执行语法分析
	void printFourElementTypeList();
	void printErrorInfo();
private:
	string clearUpString(string str);	//去掉字符串的双引号
	void saveSemanticInfoToFile();
	void modify_end_c(unsigned int pId, unsigned int c);
	int merge(unsigned int pId1, unsigned int pId2);
	void backpatch(unsigned int pId, unsigned int pNum);
	list<FourElementType>::iterator getFourElementType(int no);
	FourElementTypeItem newTempIdentifier();
	char stringConvertCharacter(string& str);
	int stringConvertNumberOctonary(string& str);
	int stringConvertNumberDecimalism(string& str);
	int stringConvertNumberHexadecimal(string& str);
	//---------------------------------------------------------------------------------------------------
	// 全局变量定义、函数声明、函数实现
	//---------------------------------------------------------------------------------------------------
	/*
		S -> $
		S -> F S
	*/
	bool semanticAnalysisS(list<Token>::iterator& itAnalysisCur, list<Token>& TokenenList);
	/*
		F -> MT1 DT F1
	*/
	bool semanticAnalysisF(list<Token>::iterator& itAnalysisCur, list<Token>& TokenenList);
	/*
		F1 -> VL ;
		F1 -> functionName ( PL ) F2
	*/
	bool semanticAnalysisF1(list<Token>::iterator& itAnalysisCur, list<Token>& TokenenList, GrammarTreeTmp& tmp);
	/*
		F2 -> { FB }
		F2 -> ;
	*/
	bool semanticAnalysisF2(list<Token>::iterator& itAnalysisCur, list<Token>& TokenenList, GrammarTreeTmp& tmp);
	/*
		MT -> auto
		MT -> register
		MT -> MT1
	*/
	bool semanticAnalysisMT(list<Token>::iterator& itAnalysisCur, list<Token>& TokenenList, int& memoryType);
	/*
		MT1 -> extern
		MT1 -> static
		MT1 -> $
	*/
	bool semanticAnalysisMT1(list<Token>::iterator& itAnalysisCur, list<Token>& TokenenList, int& memoryType);
	/*
		DT -> void
		DT -> int
		DT -> char
		DT -> float
		DT -> double
	*/
	bool semanticAnalysisDT(list<Token>::iterator& itAnalysisCur, list<Token>& TokenenList, int& dataType);
	/*
		VL -> VD VL1
	*/
	bool semanticAnalysisVL(list<Token>::iterator& itAnalysisCur, list<Token>& TokenenList, list<VariableList>& variableList, bool isGlobal);
	/*
		VL1 -> , VD VL1
		VL1 -> $
	*/
	bool semanticAnalysisVL1(list<Token>::iterator& itAnalysisCur, list<Token>& TokenenList, list<VariableList>& variableList, bool isGlobal);
	/*
		VD -> variableName VD1
	*/
	bool semanticAnalysisVD(list<Token>::iterator& itAnalysisCur, list<Token>& TokenenList, VariableList& variable, bool isGlobal);
	/*
		VD1 -> = PR
		VD1 -> $
	*/
	bool semanticAnalysisVD1(list<Token>::iterator& itAnalysisCur, list<Token>& TokenenList, list<Token>& initValue,string variableName);
	/*
		PL -> $
		PL -> PL1
	*/
	bool semanticAnalysisPL(list<Token>::iterator& itAnalysisCur, list<Token>& TokenenList, list<ParameterList>& parameterList);
	/*
		PL1 -> PD PL2
	*/
	bool semanticAnalysisPL1(list<Token>::iterator& itAnalysisCur, list<Token>& TokenenList, list<ParameterList>& parameterList);
	/*
		PL2 -> , PD PL2
		PL2 -> $
	*/
	bool semanticAnalysisPL2(list<Token>::iterator& itAnalysisCur, list<Token>& TokenenList, list<ParameterList>& parameterList);
	/*
		PD -> DT PD1
	*/
	bool semanticAnalysisPD(list<Token>::iterator& itAnalysisCur, list<Token>& TokenenList, ParameterList& parameter);
	/*
		PD1 -> parameterName
		PD1 -> $
	*/
	bool semanticAnalysisPD1(list<Token>::iterator& itAnalysisCur, list<Token>& TokenenList, string& parameterName);
	//------------------------------控制语句----------------------------------------------------------
	/*
		FB -> $
		FB -> RS FB
	*/
	bool semanticAnalysis_FB(list<Token>::iterator& itAnalysisCur, list<Token>& TokenenList, int& FB_CHAIN);
	/*
		RS -> MT1 DT VL ;
		RS -> PR ;
		RS -> if ( PR ) SB RS1
		RS -> while ( PR ) SB
		RS -> do SB while ( PR ) ;
		RS -> for ( PR ; PR ; PR ) SB
		RS -> break ;
		RS -> continue ;
		RS -> return PR ;
		RS -> print ( Print
		RS -> scan ( id ) ;
	*/
	bool semanticAnalysis_RS(list<Token>::iterator& itAnalysisCur, list<Token>& TokenenList, int& RS_CHAIN);
	/*
		RS1 -> $
		RS1 -> else SB
	*/
	bool semanticAnalysis_RS1(list<Token>::iterator& itAnalysisCur, list<Token>& TokenenList, int& TC, int& FC);
	/*
		SB -> RS
		SB -> { SB1 }
	*/
	bool semanticAnalysis_SB(list<Token>::iterator& itAnalysisCur, list<Token>& TokenenList, int& SB_CHAIN);
	/*
		SB1 -> $
		SB1 -> RS SB1
	*/
	bool semanticAnalysis_SB1(list<Token>::iterator& itAnalysisCur, list<Token>& TokenenList, int& SB1_CHAIN);
	/*
		Print -> string ) ;
		Print -> PR ) ;
	*/
	bool semanticAnalysisPrint(list<Token>::iterator& itAnalysisCur, list<Token>& TokenenList, int& chain);
	//-------------------------------表达式-----------------------------------------------------------
	/*
		eexpr -> bexpr eexpr1
	*/
	bool semanticAnalysis_eexpr(list<Token>::iterator& itAnalysisCur, list<Token>& TokenenList, FourElementTypeItem& eexpr);
	/*
		eexpr1 -> ao bexpr eexpr1
		eexpr1 -> $
	*/
	bool semanticAnalysis_eexpr1(list<Token>::iterator& itAnalysisCur, list<Token>& TokenenList, FourElementTypeItem& eexpr1);
	/*
		ao -> =
		ao -> +=
		ao -> -=
		ao -> *=
		ao -> /=
	*/
	bool semanticAnalysis_ao(list<Token>::iterator& itAnalysisCur, list<Token>& TokenenList, int& ao);
	/*
		bexpr -> bterm bexpr1
	*/
	bool semanticAnalysis_bexpr(list<Token>::iterator& itAnalysisCur, list<Token>& TokenenList, FourElementTypeItem& bexpr);
	/*
		bexpr1 -> || bterm bexpr1
		bexpr1 -> $
	*/
	bool semanticAnalysis_bexpr1(list<Token>::iterator& itAnalysisCur, list<Token>& TokenenList, FourElementTypeItem& bexpr1);
	/*
		bterm -> rexpr bterm1
	*/
	bool semanticAnalysis_bterm(list<Token>::iterator& itAnalysisCur, list<Token>& TokenenList, FourElementTypeItem& bterm);
	/*
		bterm1 -> && rexpr bterm1
		bterm1 -> $
	*/
	bool semanticAnalysis_bterm1(list<Token>::iterator& itAnalysisCur, list<Token>& TokenenList, FourElementTypeItem& bterm1);
	/*
		rexpr -> aexpr rexpr1
	*/
	bool semanticAnalysis_rexpr(list<Token>::iterator& itAnalysisCur, list<Token>& TokenenList, FourElementTypeItem& rterm);
	/*
		rexpr1 -> < aexpr
		rexpr1 -> > aexpr
		rexpr1 -> <= aexpr
		rexpr1 -> <= aexpr
		rexpr1 -> != aexpr
		rexpr1 -> == aexpr
		rexpr1 -> $
		//前4个运算符和后面2个运算符的优先级确实是不一样的，但是这6个运算符都不能连接，因此写在一起是可以的，之前的设计是错误
	*/
	bool semanticAnalysis_rexpr1(list<Token>::iterator& itAnalysisCur, list<Token>& TokenenList, FourElementTypeItem& rterm1);
	/*
		aexpr -> term aexpr1
	*/
	bool semanticAnalysis_aexpr(list<Token>::iterator& itAnalysisCur, list<Token>& TokenenList, FourElementTypeItem& aexpr);
	/*
		aexpr1 -> + term aexpr1
		aexpr1 -> - term aexpr1
		aexpr1 -> $
	*/
	bool semanticAnalysis_aexpr1(list<Token>::iterator& itAnalysisCur, list<Token>& TokenenList, FourElementTypeItem& aexpr1);
	/*
		term -> factor term1
	*/
	bool semanticAnalysis_term(list<Token>::iterator& itAnalysisCur, list<Token>& TokenenList, FourElementTypeItem& term);
	/*
		term1 -> * factor term1
		term1 -> / factor term1
		term1 -> % factor term1
		term1 -> $
	*/
	bool semanticAnalysis_term1(list<Token>::iterator& itAnalysisCur, list<Token>& TokenenList, FourElementTypeItem& term1);
	/*
		factor -> ! ael
		factor -> ael
	*/
	bool semanticAnalysis_factor(list<Token>::iterator& itAnalysisCur, list<Token>& TokenenList, FourElementTypeItem& factor);
	/*
		ael -> ( bexpr )
		ael -> root
	*/
	bool semanticAnalysis_ael(list<Token>::iterator& itAnalysisCur, list<Token>& TokenenList, FourElementTypeItem& ael);
	/*
		root -> id
		root -> 整型(八进制、十进制、十六进制)
		root -> 浮点型( 小数、指数 )
		root -> 布尔型
		root -> 字符型
		-- root -> 字符串型 字符数组
	*/
	bool semanticAnalysis_root(list<Token>::iterator& itAnalysisCur, list<Token>& TokenenList, FourElementTypeItem& root);
	/*
		BOOL -> true
		BOOL -> false
	*/
	bool semanticAnalysis_BOOL(list<Token>::iterator& itAnalysisCur, list<Token>& TokenenList, FourElementTypeItem& BOOL);

	//-----------------------------------其他辅助函数------------------------------------------
	//判断是否为表达式预分析
	bool expressPreAnalysis(int type);

	//判断是否为用户定义变量
	bool isUserVariableDefinition(string variableName);

	//判断变量是否重复定义
	bool isRepetDefineVariable(string variableName, bool isGlobal);

	//判断函数声明和函数实现是否匹配
	bool isMatchFunctionComeTrueAndDefine(FunctionDefinition fd);
};
