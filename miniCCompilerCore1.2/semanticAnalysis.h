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
�������
	1.�жϳ����Ƿ�ȱ�ٺ������
	����������м��������
	1.�����������Ķ����ʵ�֣����������ʵ�ֱ����ں��������б���
	2.�����������Ķ��壬���������Ķ��屣���ڱ��������б���
	3.�жϱ����Ƿ��ظ����壬�ж�ʱ��Ϊȫ�ֱ����;ֲ�����
	//����ֻ�ܶ����ں�����ʼ����
	//ȫΪ�ֲ����������ظ�
	//ȫΪȫ�ֱ��������ظ�
	//�ֲ�����������ȫ�ֱ���
	//�ظ��������
	4.���������ͺ���ʵ���Ƿ�ƥ��
	5.��������������ʵ���Ƿ��ظ�����
*/

class SemanticAnalysis	//����������м��������
{
public:
	list<FourElementType> mFourElementTypeList;	//��ԪʽList
	list<VariableDefinition> mVariableDefinitionList;	//�û��������List
	list<FunctionDefinition> mFunctionDefinitionList;	//��������
	list<FourElementTypeItem> mTempIdentifierList;		//��ʱ����List
	list<string> mErrorInfo;	//�������
	list<int> breakPosiList;	//break ������λ��
	list<int> continuePosiList;	//continue ������λ��
	list<int> returnPosiList;	//return ���ص�λ��
private:
	list<string> variableCache;
	string curFunctionName;		//��ǰ�����ĺ�����
public:
	SemanticAnalysis();
	~SemanticAnalysis();
	bool runSemanticAnalysis(list<Token>& TokenenList);	//ִ���﷨����
	void printFourElementTypeList();
	void printErrorInfo();
private:
	string clearUpString(string str);	//ȥ���ַ�����˫����
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
	// ȫ�ֱ������塢��������������ʵ��
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
	//------------------------------�������----------------------------------------------------------
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
	//-------------------------------���ʽ-----------------------------------------------------------
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
		//ǰ4��������ͺ���2������������ȼ�ȷʵ�ǲ�һ���ģ�������6����������������ӣ����д��һ���ǿ��Եģ�֮ǰ������Ǵ���
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
		root -> ����(�˽��ơ�ʮ���ơ�ʮ������)
		root -> ������( С����ָ�� )
		root -> ������
		root -> �ַ���
		-- root -> �ַ����� �ַ�����
	*/
	bool semanticAnalysis_root(list<Token>::iterator& itAnalysisCur, list<Token>& TokenenList, FourElementTypeItem& root);
	/*
		BOOL -> true
		BOOL -> false
	*/
	bool semanticAnalysis_BOOL(list<Token>::iterator& itAnalysisCur, list<Token>& TokenenList, FourElementTypeItem& BOOL);

	//-----------------------------------������������------------------------------------------
	//�ж��Ƿ�Ϊ���ʽԤ����
	bool expressPreAnalysis(int type);

	//�ж��Ƿ�Ϊ�û��������
	bool isUserVariableDefinition(string variableName);

	//�жϱ����Ƿ��ظ�����
	bool isRepetDefineVariable(string variableName, bool isGlobal);

	//�жϺ��������ͺ���ʵ���Ƿ�ƥ��
	bool isMatchFunctionComeTrueAndDefine(FunctionDefinition fd);
};
