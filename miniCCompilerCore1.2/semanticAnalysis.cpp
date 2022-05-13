#include "semanticAnalysis.h"
#include "symbol.h"
#include "fourElementType.h"
#include "functionDefinition.h"
#include <fstream>
#include "linuxStrings.h"


SemanticAnalysis::SemanticAnalysis()
{
	//cout << "开始进行语义分析:" << endl;
	mFourElementTypeList.clear();
	mVariableDefinitionList.clear();
	mFunctionDefinitionList.clear();
	mTempIdentifierList.clear();
	mErrorInfo.clear();
	breakPosiList.clear();
	continuePosiList.clear();

	// private
	variableCache.clear();
}

SemanticAnalysis::~SemanticAnalysis()
{
}
//-----------------------------------------------------------------------------------------------------------
/*
	语义分析执行函数
*/
bool SemanticAnalysis::runSemanticAnalysis(list<Token>& TokenenList)
{
	/*cout << "待分析的Tokenen串:" << endl;
	list<Token>::iterator it;
	for (it = TokenenList.begin(); it != TokenenList.end(); it++)
	{
	cout << (*it).data << endl;
	}*/
	list<Token>::iterator itAnalysisCur = TokenenList.begin();
	//int chain = 0;
	//semanticAnalysis_FB(itAnalysisCur, TokenenList,chain);
	//cout << "chain " << chain << endl;
	//if (chain != 0)
	//{
	//	int NXQ = mFourElementTypeList.size() + 1;
	//	modify_end_c(chain, NXQ);
	//}
	//FourElementTypeItem nullId;
	//FourElementType four(mFourElementTypeList.size() + 1,Sys, nullId, nullId, nullId);
	//mFourElementTypeList.push_back(four);
	
	if (!semanticAnalysisS(itAnalysisCur, TokenenList))
	{
		//cout << "完成语义分析" << endl;
		return false;
	}
	/* 打印语义分析过程
	printFourElementTypeList();	//打印中间代码（四元式表示）
	cout << "--------------------" << endl;
	cout << "错误信息" << endl;
	printErrorInfo();	//打印错误信息
	cout << "--------------------" << endl;
	cout << "用户定义变量" << endl;
	list<VariableDefinition>::iterator it = mVariableDefinitionList.begin();
	for (; it != mVariableDefinitionList.end(); it++)
	{
		(*it).printContent();
	}
	cout << "--------------------" << endl;
	cout << "函数声明或实现" << endl;
	list<FunctionDefinition>::iterator it1 = mFunctionDefinitionList.begin();
	for (; it1 != mFunctionDefinitionList.end(); it1++)
	{
		(*it1).printContent();
	}
	*/
	//判断程序是否缺少函数入口
	bool isExistProgramEnter = false;	//是否存在函数入口
	list<FunctionDefinition>::iterator itFunctionDefinitionList = mFunctionDefinitionList.begin();
	for (; itFunctionDefinitionList != mFunctionDefinitionList.end(); itFunctionDefinitionList++)
	{
		if ((*itFunctionDefinitionList).functionName == "main")
		{
			isExistProgramEnter = true;
			break;
		}
	}
	if (!isExistProgramEnter)
	{
		mErrorInfo.push_back("程序缺少函数入口");
	}
	//将四元式保存在文件中
	saveSemanticInfoToFile();
	//输出错误信息
	list<string>::iterator itErrorInfo = mErrorInfo.begin();
	for (; itErrorInfo != mErrorInfo.end(); itErrorInfo++)
	{
		cout << "Error Semantic : " << (*itErrorInfo) << endl;
	}
	if (mErrorInfo.size() > 0)
	{
		return false;
	}
	return true;
}
//----------------------------------------------------------------------------------------------------------
void SemanticAnalysis::printFourElementTypeList()
{
	cout << endl;
	list<FourElementType>::iterator it;
	for (it = mFourElementTypeList.begin(); it != mFourElementTypeList.end(); it++)
	{
		(*it).printFourElementType();
	}
	cout << endl;
}
void SemanticAnalysis::printErrorInfo()
{
	cout << "语义分析结束，存在" << mErrorInfo.size() << "错误" << endl;
	list<string>::iterator it = mErrorInfo.begin();
	for (; it != mErrorInfo.end(); it++)
	{
		cout << "error: " << (*it) << endl;
	}
}
string SemanticAnalysis::clearUpString(string str)
{
	string ret = str;
	if (str[0] == '"')
	{
		ret = str.substr(1, str.size() - 1);
	}
	if (ret[ret.size() - 1] == '"')
	{
		ret = ret.substr(0, ret.size() - 1);
	}
	//cout << ret << endl;
	return ret;
}
//将中间代码保存在文件中
void SemanticAnalysis::saveSemanticInfoToFile()
{
	ofstream outFile("analysis\\semanticAnalysis.txt");
	//语义分析结果
	outFile << "********************************************" << endl;
	outFile << "*            语义分析及中间代码            *" << endl;
	outFile << "********************************************" << endl;

	//保存错误信息
	outFile << endl;
	outFile << "--------------------------------------------" << endl;
	outFile << "错误信息" << endl;
	outFile << "语义分析结束，存在" << mErrorInfo.size() << "错误" << endl;
	list<string>::iterator it = mErrorInfo.begin();
	for (; it != mErrorInfo.end(); it++)
	{
		outFile << "error: " << (*it) << endl;
	}
	outFile << "--------------------------------------------" << endl;

	//变量定义
	outFile << endl;
	outFile << "--------------------------------------------" << endl;
	outFile << "变量定义" << endl;
	list<VariableDefinition>::iterator it1 = mVariableDefinitionList.begin();
	for (; it1 != mVariableDefinitionList.end(); it1++)
	{
		outFile << (*it1).getContent();
	}
	outFile << "--------------------------------------------" << endl;

	//函数声明或实现
	outFile << endl;
	outFile << "--------------------------------------------" << endl;
	outFile << "函数声明或实现" << endl;
	list<FunctionDefinition>::iterator it2 = mFunctionDefinitionList.begin();
	for (; it2 != mFunctionDefinitionList.end(); it2++)
	{
		outFile << (*it2).getContent();
	}
	outFile << "--------------------------------------------" << endl;

	//中间代码
	outFile << endl;
	outFile << "--------------------------------------------" << endl;
	outFile << "中间代码[四元式形式]" << endl;
	list<FourElementType>::iterator it3;
	for (it3 = mFourElementTypeList.begin(); it3 != mFourElementTypeList.end(); it3++)
	{
		//(*it).printFourElementType();
		outFile << (*it3).getFourElementType() << endl;
	}
	outFile << "--------------------------------------------" << endl;

	outFile << endl;
}
void SemanticAnalysis::modify_end_c(unsigned int pId, unsigned int c)
{	
	//将最后的指向修改为c
	unsigned int tempId = pId;
	list<FourElementType>::iterator it = this->getFourElementType(tempId);
	while (tempId > 0 && tempId <= mFourElementTypeList.size())
	{
		it = this->getFourElementType(tempId);
		if ((*it).mResult.mType == 5)
		{
			tempId = (*it).mResult.mNumber;
		}
		else
		{
			tempId = 0;
		}
	}
	(*it).mResult.mNumber = c;
}
int SemanticAnalysis::merge(unsigned int pId1, unsigned int pId2)
{
	if (pId2 <= 0 || pId2 > mFourElementTypeList.size())
		return pId1;
	else
	{
		unsigned int tempId = pId2;
		list<FourElementType>::iterator it = getFourElementType(pId2);
		while (tempId > 0 && tempId <= mFourElementTypeList.size())
		{
			list<FourElementType>::iterator it = getFourElementType(tempId);
			if ((*it).mResult.mType == 5)
			{
				tempId = (*it).mResult.mNumber;
			}
			else
			{
				tempId = 0;
			}
		}
		(*it).mResult.mNumber = pId1;
		return pId2;
	}
}
void SemanticAnalysis::backpatch(unsigned int pId, unsigned int pNum)
{
	unsigned int tempId = pId;
	while (tempId > 0 && tempId <= mFourElementTypeList.size())
	{
		list<FourElementType>::iterator it = this->getFourElementType(tempId);
		if ((*it).mResult.mType == 5)
		{
			tempId = (*it).mResult.mNumber;
			(*it).mResult.mNumber = pNum;
		}
		else
		{
			tempId = 0;
		}
	}
}
list<FourElementType>::iterator SemanticAnalysis::getFourElementType(int no)
{
	list<FourElementType>::iterator it;
	for (it = mFourElementTypeList.begin(); it != mFourElementTypeList.end(); it++)
	{
		if ((*it).mNumber == no)
			return it;
	}
	return mFourElementTypeList.end();
}
FourElementTypeItem SemanticAnalysis::newTempIdentifier()
{
	FourElementTypeItem tempIndentifier;
	tempIndentifier.mType = 3;
	tempIndentifier.mTempIdentifierName = "@Temp_" + to_string(mTempIdentifierList.size());
	mTempIdentifierList.push_back(tempIndentifier);
	return tempIndentifier;
}
char SemanticAnalysis::stringConvertCharacter(string & str)
{
	const char* tempCharArray = str.c_str();
	return tempCharArray[strlen(tempCharArray) - 2];
}
int SemanticAnalysis::stringConvertNumberOctonary(string & str)
{
	const char* tempCharArray = str.c_str();
	int result = 0;
	for (unsigned int i = 1; i < strlen(tempCharArray); i++)
	{
		result *= 8;
		result += tempCharArray[i] - '0';
	}
	return result;
}
int SemanticAnalysis::stringConvertNumberDecimalism(string & str)
{
	const char* tempCharArray = str.c_str();
	int result = 0;
	for (unsigned int i = 0; i < strlen(tempCharArray); i++)
	{
		result *= 10;
		result += tempCharArray[i] - '0';
	}
	return result;
}
int SemanticAnalysis::stringConvertNumberHexadecimal(string & str)
{
	const char* tempCharArray = str.c_str();
	int result = 0;
	for (unsigned int i = 2; i < strlen(tempCharArray); i++)
	{
		result *= 16;
		result += tempCharArray[i] - '0';
	}
	return result;
}
//---------------------------------------------------------------------------------------------------
// 全局变量定义、函数声明、函数实现
//---------------------------------------------------------------------------------------------------
/*
	S -> $
	S -> F S
*/
bool SemanticAnalysis::semanticAnalysisS(list<Token>::iterator & itAnalysisCur, list<Token>& TokenenList)
{
	if (itAnalysisCur == TokenenList.end())
	{
		//程序结束
		FourElementTypeItem nullId;
		FourElementType four(mFourElementTypeList.size() + 1, Sys, nullId, nullId, nullId);
		mFourElementTypeList.push_back(four);
		return true;
	}
	else
	{
		//分析 F
		if (!semanticAnalysisF(itAnalysisCur, TokenenList))
		{
			return false;
		}
		//分析 S
		if (!semanticAnalysisS(itAnalysisCur, TokenenList))
		{
			return false;
		}
	}
	return true;
}
/*
	F -> MT1 DT F1
*/
bool SemanticAnalysis::semanticAnalysisF(list<Token>::iterator & itAnalysisCur, list<Token>& TokenenList)
{
	GrammarTreeTmp grammarTreeTmp;
	// 分析 MT1
	grammarTreeTmp.memoryType = Keyword_extern;
	if (!semanticAnalysisMT1(itAnalysisCur, TokenenList, grammarTreeTmp.memoryType))
	{
		//分析失败
		return false;
	}
	// 分析 DT
	grammarTreeTmp.dataType = Error;
	if (!semanticAnalysisDT(itAnalysisCur, TokenenList, grammarTreeTmp.dataType))
	{
		return false;
	}
	//grammarTreeTmp.dataType = dataType;
	// 分析 F1
	int funcEnter = mFourElementTypeList.size() + 1;
	if (!semanticAnalysisF1(itAnalysisCur, TokenenList, grammarTreeTmp))
	{
		return false;
	}
	switch (grammarTreeTmp.tmpType)
	{
	case 1:
	{
		//VariableDefinition *vd = new VariableDefinition(grammarTreeTmp);
		//node->addChildToRoot(vd);
		VariableDefinition vd(grammarTreeTmp);
		mVariableDefinitionList.push_back(vd);
		break;
	}
	case 2:	//函数声明
	{
		//FunctionDefinition *fd = new FunctionDefinition(grammarTreeTmp);
		//node->addChildToRoot(fd);
		FunctionDefinition fd(grammarTreeTmp);
		fd.isComeTrue = false;
		if (!isMatchFunctionComeTrueAndDefine(fd))
		{
			//不存在
			mFunctionDefinitionList.push_back(fd);
		}
		break;
	}
	case 3:	//函数实现
	{
		//FunctionDeclaration *fd = new FunctionDeclaration(grammarTreeTmp);
		//node->addChildToRoot(fd);
		FunctionDefinition fd(grammarTreeTmp);
		fd.isComeTrue = true;
		fd.funcEnter = funcEnter;
		if (!isMatchFunctionComeTrueAndDefine(fd))
		{
			//不存在
			mFunctionDefinitionList.push_back(fd);
		}
		break;
	}
	default:
		break;
	}
	return true;
}
/*
	F1 -> VL ;
	F1 -> functionName ( PL ) F2
*/
bool SemanticAnalysis::semanticAnalysisF1(list<Token>::iterator & itAnalysisCur, list<Token>& TokenenList, GrammarTreeTmp& tmp)
{
	string functionName = (*itAnalysisCur).data;
	// 分析 ID 和 左小括号
	if ((*itAnalysisCur).type == Identifier && (++itAnalysisCur) != TokenenList.end() &&
		(*itAnalysisCur).type == Delimiter_Left_Small_Bracket)	// id ( 左小括号
	{
		curFunctionName = functionName;		//当前分析的函数名
		tmp.functionName = functionName;	//将函数名加载到tmp中去
		itAnalysisCur++;	//更新当前分析Tokenen串的位置
							//分析 PL
		if (!semanticAnalysisPL(itAnalysisCur, TokenenList, tmp.parameterList))	//分析PL，出错
		{
			return false;
		}
		//分析 右小括号
		if (itAnalysisCur == TokenenList.end())
		{
			return false;
		}
		if ((*itAnalysisCur).type != Delimiter_Right_Small_Bracket)	// ) 右小括号
		{
			return false;
		}
		itAnalysisCur++;	//更新当前分析Tokenen串的位置
		if (!semanticAnalysisF2(itAnalysisCur, TokenenList, tmp))	//分析函数体
		{
			return false;
		}
	}
	else // F1 -> VL ;
	{
		--itAnalysisCur;	//返回之前分析Tokenen串的位置
		//分析VL
		tmp.tmpType = 1;	//外部数据定义
		// tmp.variableList;
		if (!semanticAnalysisVL(itAnalysisCur, TokenenList, tmp.variableList, true))
		{
			return false;
		}
		if (itAnalysisCur == TokenenList.end())	//分析到函数末尾
		{
			return false;
		}
		//分析分好 ;
		if (Delimiter_Semicolon != (*itAnalysisCur).type)
		{
			return false;
		}
		itAnalysisCur++;
	}
	return true;
}
/*
	F2 -> { FB }
	F2 -> ;
*/
bool SemanticAnalysis::semanticAnalysisF2(list<Token>::iterator & itAnalysisCur, list<Token>& TokenenList, GrammarTreeTmp& tmp)
{
	if (itAnalysisCur == TokenenList.end())//当前分析位置是否存在
	{
		return false;
	}
	//分好
	if ((*itAnalysisCur).type == Delimiter_Semicolon)	//是否为分好
	{
		tmp.tmpType = 2;	//函数声明
		itAnalysisCur++;	//更新当前分析Tokenen串的位置
	}
	//左大括号
	else if ((*itAnalysisCur).type == Delimiter_Left_Large_Bracket)	//是否为左大括号
	{
		itAnalysisCur++;	//更新当前分析Tokenen串的位置
		tmp.tmpType = 3;	//函数实现
		// FB
		int chain = 0;
		if (!semanticAnalysis_FB(itAnalysisCur, TokenenList, chain))
		{
			return false;
		}
		if (chain != 0)
		{
			int NXQ = mFourElementTypeList.size() + 1;
			modify_end_c(chain, NXQ);
		}
		// } 右大括号
		if (itAnalysisCur == TokenenList.end())	//分析到函数末尾
		{
			return false;
		}
		if ((*itAnalysisCur).type != Delimiter_Right_Large_Bracket)	//是否为右大括号
		{
			return false;
		}
		itAnalysisCur++;//更新当前分析Tokenen串的位置

		int tmpReturn = mFourElementTypeList.size() + 1;	//tmpReturn = NXQ
		//更新returnPosi的信息
		if (returnPosiList.size() > 0)
		{
			list<int>::iterator it = returnPosiList.begin();
			for (; it != returnPosiList.end(); it++)
			{
				if ((*it) != 0)
					modify_end_c((*it), tmpReturn);
			}
			returnPosiList.clear();
		}
	}
	curFunctionName = "";;	//清空当前分析的函数名
	return true;
}
/*
	MT -> auto
	MT -> register
	MT -> MT1
*/
bool SemanticAnalysis::semanticAnalysisMT(list<Token>::iterator & itAnalysisCur, list<Token>& TokenenList, int& memoryType)
{
	if (itAnalysisCur == TokenenList.end())	//当前分析位置是否存在
	{
		return false;
	}
	if ((*itAnalysisCur).type == Keyword_auto)	//auto
	{
		memoryType = Keyword_auto;
		itAnalysisCur++;	//更新当前分析Tokenen串的位置
		return true;
	}
	else if ((*itAnalysisCur).type == Keyword_register)
	{
		memoryType = Keyword_register;
		itAnalysisCur++;	//更新当前分析Tokenen串的位置
		return true;
	}
	else if (semanticAnalysisMT1(itAnalysisCur, TokenenList, memoryType))
	{
		return true;
	}
	else
	{
		return false;
	}
}
/*
	MT1 -> extern
	MT1 -> static
	MT1 -> $
*/
bool SemanticAnalysis::semanticAnalysisMT1(list<Token>::iterator & itAnalysisCur, list<Token>& TokenenList, int& memoryType)
{
	if (itAnalysisCur == TokenenList.end())	//当前分析位置是否存在
	{
		return false;
	}
	if ((*itAnalysisCur).type == Keyword_extern)
	{
		memoryType = Keyword_extern;
		itAnalysisCur++;	//更新当前分析Tokenen串的位置
		return true;
	}
	else if ((*itAnalysisCur).type == Keyword_static)
	{
		memoryType = Keyword_static;
		itAnalysisCur++;	//更新当前分析Tokenen串的位置
		return true;
	}
	return true;
}
/*
	DT -> void
	DT -> int
	DT -> char
	DT -> float
	DT -> double
*/
bool SemanticAnalysis::semanticAnalysisDT(list<Token>::iterator & itAnalysisCur, list<Token>& TokenenList, int& dataType)
{
	if (itAnalysisCur == TokenenList.end())//当前分析位置是否存在
	{
		return false;
	}
	if ((*itAnalysisCur).type == Keyword_void)
	{
		dataType = Keyword_void;
		itAnalysisCur++;	//更新当前分析Token串的位置
		return true;
	}
	else if ((*itAnalysisCur).type == Keyword_int)
	{
		dataType = Keyword_int;
		itAnalysisCur++;	//更新当前分析Token串的位置
		return true;
	}
	else if ((*itAnalysisCur).type == Keyword_char)
	{
		//dataType = Keyword_char;
		itAnalysisCur++;	//更新当前分析Tokenen串的位置
		return true;
	}
	else if ((*itAnalysisCur).type == Keyword_float)
	{
		//dataType = Keyword_float;
		itAnalysisCur++;	//更新当前分析Tokenen串的位置
		return true;
	}
	else if ((*itAnalysisCur).type == Keyword_double)
	{
		//dataType = Keyword_double;
		itAnalysisCur++;	//更新当前分析Tokenen串的位置
		return true;
	}
	return false;
}
/*
	VL -> VD VL1
*/
bool SemanticAnalysis::semanticAnalysisVL(list<Token>::iterator & itAnalysisCur, list<Token>& TokenenList, list<VariableList>& variableList, bool isGlobal)
{
	//分析VD
	VariableList variable;
	if (!semanticAnalysisVD(itAnalysisCur, TokenenList, variable, isGlobal))
	{
		return false;
	}
	variableList.push_back(variable);
	//分析VL1
	if (!semanticAnalysisVL1(itAnalysisCur, TokenenList, variableList, isGlobal))
	{
		return false;
	}
	return true;
}
/*
	VL1 -> , VD VL1
	VL1 -> $
*/
bool SemanticAnalysis::semanticAnalysisVL1(list<Token>::iterator & itAnalysisCur, list<Token>& TokenenList, list<VariableList>& variableList, bool isGlobal)
{
	//判断是否分析到末尾
	if (itAnalysisCur == TokenenList.end())
	{
		return false;
	}
	// VL1 -> , VD VL1
	//分析是否为逗号 ,
	if (Delimiter_Comma == (*itAnalysisCur).type)
	{
		itAnalysisCur++;//更新当前分析Tokenen串的位置
		//分析VL1
		VariableList variable;
		if (!semanticAnalysisVD(itAnalysisCur, TokenenList, variable, isGlobal))
		{
			return false;
		}
		variableList.push_back(variable);
		if (!semanticAnalysisVL1(itAnalysisCur, TokenenList, variableList, isGlobal))
		{
			return false;
		}
		return true;
	}
	else
	{
		return true;
	}
}
/*
	VD -> variableName VD1
*/
bool SemanticAnalysis::semanticAnalysisVD(list<Token>::iterator & itAnalysisCur, list<Token>& TokenenList, VariableList& variable, bool isGlobal)
{
	//是否分析到Tokenen串的末尾
	if (itAnalysisCur == TokenenList.end())	//没有分析到末尾
	{
		return false;
	}
	//判断是否为ID
	if (Identifier == (*itAnalysisCur).type)
	{
		variable.varName = (*itAnalysisCur).data;
		if (isRepetDefineVariable((*itAnalysisCur).data, isGlobal))
		{
			mErrorInfo.push_back("变量 " + (*itAnalysisCur).data + " 重复定义");
		}
		variableCache.push_back((*itAnalysisCur).data);
		itAnalysisCur++;//更新当前分析Tokenen串的位置
		//分析VD1
		if (!semanticAnalysisVD1(itAnalysisCur, TokenenList, variable.initValue, variable.varName))
		{
			return false;
		}
	}
	return true;
}
/*
	VD1 -> = PR
	VD1 -> $
*/
bool SemanticAnalysis::semanticAnalysisVD1(list<Token>::iterator & itAnalysisCur, list<Token>& TokenenList, list<Token>& initValue, string variableName)
{
	//判断是否分析到Tokenen串的末尾
	if (itAnalysisCur == TokenenList.end())	//没有分析到末尾
	{
		return false;
	}
	// VD1 -> = PR
	//分析是否为等号 =
	if (Operator_Equal == (*itAnalysisCur).type)	//为等号
	{
		itAnalysisCur++; //更新当前分析Tokenen串的位置
		list<Token>::iterator it = itAnalysisCur;
		FourElementTypeItem bexpr;
		if (!semanticAnalysis_bexpr(itAnalysisCur, TokenenList, bexpr))
		{
			//outAnalysisFile << "E: 分析 PR 出错" << endl;
			return false;
		}

		if (bexpr.mType == 4)	//如果bexpr为BOOL量，需要先转换为非BOOL量
		{
			FourElementTypeItem nullId;
			FourElementTypeItem tempId = newTempIdentifier();
			FourElementTypeItem constant;
			constant.mType = 1;
			constant.mConstantType = 1;
			//真出口
			constant.mConstantInteger = 1;
			int mTC = mFourElementTypeList.size() + 1;
			FourElementType four(mFourElementTypeList.size() + 1, Equal, constant, nullId, tempId);
			mFourElementTypeList.push_back(four);
			//跳转语句
			FourElementTypeItem pFour;
			pFour.mType = 5;
			pFour.mNumber = mTC + 3;
			FourElementType four1(mFourElementTypeList.size() + 1, Jump, nullId, nullId, pFour);
			mFourElementTypeList.push_back(four1);
			//假出口
			constant.mConstantInteger = 0;
			int mFC = mFourElementTypeList.size() + 1;
			FourElementType four2(mFourElementTypeList.size() + 1, Equal, constant, nullId, tempId);
			mFourElementTypeList.push_back(four2);
			//修改四元式列表
			//cout << "mFC " << bexpr.mFC << endl;
			modify_end_c(bexpr.mTC, mTC);
			modify_end_c(bexpr.mFC, mFC);
			bexpr = tempId;
		}

		FourElementTypeItem variable;
		variable.mType = 2;
		variable.mUserIdentifierName = variableName;
		FourElementTypeItem nullId;
		FourElementType four(mFourElementTypeList.size() + 1, Equal, bexpr, nullId, variable);
		mFourElementTypeList.push_back(four);
		initValue.clear();	//清空initValue
		for (; it != itAnalysisCur; it++)
		{
			initValue.push_back(*it);
		}
	}
	else // VD1 -> $
	{
		initValue.clear();
		return true;
	}
	return true;
}
/*
	PL -> $
	PL -> PL1
*/
bool SemanticAnalysis::semanticAnalysisPL(list<Token>::iterator & itAnalysisCur, list<Token>& TokenenList, list<ParameterList>& parameterList)
{
	list<Token>::iterator tmpAnalysisCur = itAnalysisCur;
	if (semanticAnalysisPL1(itAnalysisCur, TokenenList, parameterList))
	{
		return true;
	}
	itAnalysisCur = tmpAnalysisCur;
	return true;
}
/*
	PL1 -> PD PL2
*/
bool SemanticAnalysis::semanticAnalysisPL1(list<Token>::iterator & itAnalysisCur, list<Token>& TokenenList, list<ParameterList>& parameterList)
{
	//分析PD
	ParameterList parameter;
	if (!semanticAnalysisPD(itAnalysisCur, TokenenList, parameter))	//分析PD，报错
	{
		return false;
	}
	parameterList.push_back(parameter);
	//分析PL2
	if (!semanticAnalysisPL2(itAnalysisCur, TokenenList, parameterList))	//分析PL2，报错
	{
		return false;
	}
	return true;
}
/*
	PL2 -> , PD PL2
	PL2 -> $
*/
bool SemanticAnalysis::semanticAnalysisPL2(list<Token>::iterator & itAnalysisCur, list<Token>& TokenenList, list<ParameterList>& parameterList)
{
	//判断是否分析到Tokenen串的末尾
	if (itAnalysisCur == TokenenList.end())
	{
		return false;
	}
	//判断是否为 逗号 ,
	if (Delimiter_Comma == (*itAnalysisCur).type) // PL2 -> , PD PL2
	{
		itAnalysisCur++;
		ParameterList parameter;
		if (!semanticAnalysisPD(itAnalysisCur, TokenenList, parameter))
		{
			return false;
		}
		parameterList.push_back(parameter);	//添加到List
		//继续循环PL2
		if (!semanticAnalysisPL2(itAnalysisCur, TokenenList, parameterList))
		{
			return false;
		}
	}
	else // PL2 -> $
	{
		return true;
	}
	return true;
}
/*
	PD -> DT PD1
*/
bool SemanticAnalysis::semanticAnalysisPD(list<Token>::iterator & itAnalysisCur, list<Token>& TokenenList, ParameterList& parameter)
{
	int dataType;
	if (!semanticAnalysisDT(itAnalysisCur, TokenenList, dataType))
	{
		return false;
	}
	parameter.parameterType = dataType;
	string parameterName = "";	//初始化为空字符串
	if (!semanticAnalysisPD1(itAnalysisCur, TokenenList, parameterName))
	{
		return false;
	}
	parameter.parameterName = parameterName;
	return true;
}
/*
	PD1 -> parameterName
	PD1 -> $
*/
bool SemanticAnalysis::semanticAnalysisPD1(list<Token>::iterator & itAnalysisCur, list<Token>& TokenenList, string& parameterName)
{
	if ((*itAnalysisCur).type == Identifier)
	{
		parameterName = (*itAnalysisCur).data;
		itAnalysisCur++;	//更新当前分析Tokenen串的位置
		return true;
	}
	return true;
}
//-------------------------------------------控制语句-----------------------------------------------
/*
	FB -> $
	FB -> RS FB
*/
bool SemanticAnalysis::semanticAnalysis_FB(list<Token>::iterator & itAnalysisCur, list<Token>& TokenenList, int& FB_CHAIN)
{
	list<Token>::iterator tempCur = itAnalysisCur;
	//保存现场
	list<FourElementType> tempFourElementTypeList = mFourElementTypeList;	//四元式List
	list<FourElementTypeItem> tempTempIdentifierList = mTempIdentifierList;	//临时变量List
	list<string> tempErrorInfo = mErrorInfo;	//语义错误
	//int chain = FB_CHAIN;
	if (semanticAnalysis_RS(itAnalysisCur, TokenenList, FB_CHAIN))
	{
		semanticAnalysis_FB(itAnalysisCur, TokenenList, FB_CHAIN);
		return true;
	}
	itAnalysisCur = tempCur;	//无法分析出RS，则恢复之前的位置
	//恢复现场
	mFourElementTypeList = tempFourElementTypeList;
	mTempIdentifierList = tempTempIdentifierList;
	mErrorInfo = tempErrorInfo;
	return true;
}
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
bool SemanticAnalysis::semanticAnalysis_RS(list<Token>::iterator & itAnalysisCur, list<Token>& TokenenList, int& RS_CHAIN)
{
	// 是否分析到末尾
	if (itAnalysisCur == TokenenList.end()) //没有分析到末尾
	{
		return false;
	}
	//RS CHAIN
	if (RS_CHAIN != 0)
	{
		int NXQ = mFourElementTypeList.size() + 1;//回填上一个模块的chain
		modify_end_c(RS_CHAIN, NXQ);

	}
	//------------------------------
	//分析 if
	// RS -> if ( PR ) SB RS1
	if ((*itAnalysisCur).type == Keyword_if)
	{
		itAnalysisCur++;//更新当前分析Tokenen串的位置
		//1.分析左括号
		if (itAnalysisCur == TokenenList.end())
		{
			return false;
		}
		if ((*itAnalysisCur).type != Delimiter_Left_Small_Bracket)
		{
			return false;
		}
		itAnalysisCur++;//更新当前分析Tokenen串的位置
		//2.分析PR
		FourElementTypeItem express;
		if (!semanticAnalysis_eexpr(itAnalysisCur, TokenenList, express))
		{
			//cout << (*itAnalysisCur).data << endl;
			return false;
		}
		//分析eexpr BOOL量 非BOOL量->改为BOOL量
		if (express.mType <= 0 || express.mType > 4)
		{
			return false;
		}
		if (express.mType != 4)	//如果eexpr不为BOOL量，则需要先转换为BOOL量
		{
			int mTC = mFourElementTypeList.size() + 1;
			int mFC = mFourElementTypeList.size() + 2;
			FourElementTypeItem pFour;
			pFour.mType = 5;
			pFour.mNumber = 0;
			FourElementTypeItem nullId;
			FourElementType four(mFourElementTypeList.size() + 1, Jump_Not_Zero, express, nullId, pFour);
			mFourElementTypeList.push_back(four);
			FourElementType four1(mFourElementTypeList.size() + 1, Jump, nullId, nullId, pFour);
			mFourElementTypeList.push_back(four1);
			express.mType = 4;
			express.mTC = mTC;
			express.mFC = mFC;
		}
		backpatch(express.mTC, mFourElementTypeList.size() + 1);	// backpatch(E.TC,NXQ)
		int mFC = express.mFC;	//
		//3.分析右括号
		if (itAnalysisCur == TokenenList.end())
		{
			return false;
		}
		if ((*itAnalysisCur).type != Delimiter_Right_Small_Bracket) //不为右小括号
		{
			return false;
		}
		itAnalysisCur++;//更新当前分析Tokenen串的位置
		//4.分析SB
		int SB_CHAIN = 0;
		if (!semanticAnalysis_SB(itAnalysisCur, TokenenList, SB_CHAIN))
		{
			//cout << "分析SB出错" << endl;
			return false;
		}
		//设置 SB chain
		int NXQ = mFourElementTypeList.size() + 1;
		if (SB_CHAIN != 0)
		{
			modify_end_c(SB_CHAIN, NXQ);

		}
		//modify_end_c(mFC, NXQ);
		// JUMP (j,_,_,0) (Jump,_,_0)
		FourElementTypeItem pFour;
		pFour.mType = 5;
		pFour.mNumber = 0;
		FourElementTypeItem nullId;
		FourElementType four(mFourElementTypeList.size() + 1, Jump, nullId, nullId, pFour);
		mFourElementTypeList.push_back(four);
		//RS_CHAIN = NXQ
		RS_CHAIN = NXQ;

		//5.分析RS1
		// int RS1_CHAIN = 0;
		if (!semanticAnalysis_RS1(itAnalysisCur, TokenenList, RS_CHAIN, mFC))
		{
			//cout << "分析RS1出错" << endl;
			return false;
		}
		//设置 SB chain
		/*int NXQ = mFourElementTypeList.size() + 1;
		if (RS1_CHAIN != 0)
		{
		modify_end_c(RS1_CHAIN, NXQ);

		}*/
		return true;
	}
	//------------------------------
	//分析 while
	//RS -> while (PR) SB
	else if ((*itAnalysisCur).type == Keyword_while)
	{
		itAnalysisCur++;//更新当前分析Tokenen串的位置
		//1.分析左小括号
		if (itAnalysisCur == TokenenList.end())
		{
			cout << "已经分析到Tokenen串的末尾" << endl;
			return false;
		}
		if ((*itAnalysisCur).type != Delimiter_Left_Small_Bracket)
		{
			cout << "当前位置缺少左小括号" << endl;
			return false;
		}
		itAnalysisCur++;//更新当前分析Tokenen串的位置
		//2.分析PR
		int RETURN = mFourElementTypeList.size() + 1;	//RETURN = NXQ
		int tmpContinue = RETURN;	//continue函数返回的位置 tmpContinue = RETURN
		FourElementTypeItem express;
		if (!semanticAnalysis_eexpr(itAnalysisCur, TokenenList, express))
		{
			cout << (*itAnalysisCur).data << endl;
			return false;
		}
		if (express.mType <= 0 || express.mType > 4)
		{
			return false;
		}
		if (express.mType != 4)	//如果express不为BOOL量，则需要先转换为BOOL量
		{
			int mTC = mFourElementTypeList.size() + 1;
			int mFC = mFourElementTypeList.size() + 2;
			FourElementTypeItem pFour;
			pFour.mType = 5;
			pFour.mNumber = 0;
			FourElementTypeItem nullId;
			FourElementType four(mFourElementTypeList.size() + 1, Jump_Not_Zero, express, nullId, pFour);
			mFourElementTypeList.push_back(four);
			FourElementType four1(mFourElementTypeList.size() + 1, Jump, nullId, nullId, pFour);
			mFourElementTypeList.push_back(four1);
			express.mType = 4;
			express.mTC = mTC;
			express.mFC = mFC;
		}
		//3.分析右小括号
		if (itAnalysisCur == TokenenList.end())
		{
			//cout << "已经分析到Tokenen串的末尾" << endl;
			return false;
		}
		if ((*itAnalysisCur).type != Delimiter_Right_Small_Bracket) //不为右小括号
		{
			//cout << "当前位置缺少右小括号" << endl;
			return false;
		}
		itAnalysisCur++;//更新当前分析Tokenen串的位置
		//4.分析SB
		int HEAD = mFourElementTypeList.size() + 1;	// HEAD = NXQ
		backpatch(express.mTC, HEAD);	// backpatch(E.TC,HEAD)
		RS_CHAIN = express.mFC;	// RS.CHAIN = E.FC
		int tmpBreak = RS_CHAIN;	//break函数跳出的位置 tmpBreak = E.FC
		//cout << "tmpBreak " << tmpBreak << endl;
		int SB_CHAIN = 0;	// SB_CHAIN
		if (!semanticAnalysis_SB(itAnalysisCur, TokenenList, SB_CHAIN))
		{
			return false;
		}
		//设置 SB chain
		if (SB_CHAIN != 0)
		{
			int NXQ = mFourElementTypeList.size() + 1;
			modify_end_c(SB_CHAIN, NXQ);

		}
		//更新continue_posi和break_posi位置信息
		if (continuePosiList.size() > 0)
		{
			list<int>::iterator it = continuePosiList.begin();
			for (; it != continuePosiList.end(); it++)
			{
				if ((*it) != 0)
					modify_end_c((*it), tmpContinue);
			}
			continuePosiList.clear();
		}
		if (breakPosiList.size() > 0)
		{
			list<int>::iterator it = breakPosiList.begin();
			for (; it != breakPosiList.end(); it++)
			{
				//cout << "tmpBreak " << tmpBreak << endl;
				if ((*it) != 0)
					modify_end_c((*it), tmpBreak);
			}
			breakPosiList.clear();
		}
		//RETURN E.start
		//四元式 (Jump,_,_,RETUREN)
		FourElementTypeItem pFour;
		pFour.mType = 5;
		pFour.mNumber = RETURN;
		//cout << "RETURN " << RETURN << endl;
		FourElementTypeItem nullId;
		FourElementType four(mFourElementTypeList.size() + 1, Jump, nullId, nullId, pFour);
		mFourElementTypeList.push_back(four);
		return true;
	}
	//------------------------------
	//分析 do
	//RS -> do SB while ( PR ) ;
	else if ((*itAnalysisCur).type == Keyword_do)
	{
		int HEAD = mFourElementTypeList.size() + 1;	//HEAD = NXQ
		itAnalysisCur++;//更新当前分析Tokenen串的位置
		//1.分析SB
		int SB_CHAIN = 0;
		if (!semanticAnalysis_SB(itAnalysisCur, TokenenList, SB_CHAIN))
		{
			//cout << "分析SB出错" << endl;
			return false;
		}
		//设置 SB chain
		if (SB_CHAIN != 0)
		{
			int NXQ = mFourElementTypeList.size() + 1;
			modify_end_c(SB_CHAIN, NXQ);
		}
		//2.分析while
		if (itAnalysisCur == TokenenList.end())
		{
			return false;
		}
		if ((*itAnalysisCur).type != Keyword_while)
		{
			return false;
		}
		itAnalysisCur++;//更新当前分析Tokenen串的位置
		//3.分析左小括号
		if (itAnalysisCur == TokenenList.end())
		{
			return false;
		}
		if ((*itAnalysisCur).type != Delimiter_Left_Small_Bracket)
		{
			return false;
		}
		itAnalysisCur++;//更新当前分析Tokenen串的位置
		//4.分析PR
		int tmpContinue = mFourElementTypeList.size() + 1;	//continue跳转的位置
		FourElementTypeItem express;
		if (!semanticAnalysis_eexpr(itAnalysisCur, TokenenList, express))
		{
			//cout << (*itAnalysisCur).data << endl;
			return false;
		}
		if (express.mType <= 0 || express.mType > 4)
		{
			return false;
		}
		if (express.mType != 4)	//如果express不为BOOL量，则需要先转换为BOOL量
		{
			int mTC = mFourElementTypeList.size() + 1;
			int mFC = mFourElementTypeList.size() + 2;
			FourElementTypeItem pFour;
			pFour.mType = 5;
			pFour.mNumber = 0;
			FourElementTypeItem nullId;
			FourElementType four(mFourElementTypeList.size() + 1, Jump_Not_Zero, express, nullId, pFour);
			mFourElementTypeList.push_back(four);
			FourElementType four1(mFourElementTypeList.size() + 1, Jump, nullId, nullId, pFour);
			mFourElementTypeList.push_back(four1);
			express.mType = 4;
			express.mTC = mTC;
			express.mFC = mFC;
			//cout << "express" << "eexpr> TC:" << mTC << " FC:" << mFC << endl;
		}
		int tmpBreak = express.mFC;	//break跳转的位置
		//更新 continue_posi 和 break_posi 位置信息
		if (continuePosiList.size() > 0)
		{
			list<int>::iterator it = continuePosiList.begin();
			for (; it != continuePosiList.end(); it++)
			{
				if ((*it) != 0)
					modify_end_c((*it), tmpContinue);
			}
			continuePosiList.clear();
		}
		if (breakPosiList.size() > 0)
		{
			list<int>::iterator it = breakPosiList.begin();
			for (; it != breakPosiList.end(); it++)
			{
				if ((*it) != 0)
				{
					modify_end_c((*it), tmpBreak);
				}
			}
			breakPosiList.clear();
		}
		backpatch(express.mTC, HEAD);	// backpatch(E.TC,HEAD)
		//chain
		RS_CHAIN = express.mFC;// RS.CHAIN = E.FC
		//5.分析右小括号
		if (itAnalysisCur == TokenenList.end())
		{
			return false;
		}
		if ((*itAnalysisCur).type != Delimiter_Right_Small_Bracket) //不为右小括号
		{
			return false;
		}
		itAnalysisCur++;//更新当前分析Tokenen串的位置
		//6.分析分号 ;
		if (itAnalysisCur == TokenenList.end())
		{
			return false;
		}
		if ((*itAnalysisCur).type != Delimiter_Semicolon)
		{
			return false;
		}
		itAnalysisCur++;//更新当前分析Tokenen串的位置
		return true;
	}
	//------------------------------
	//分析 for
	//RS -> for ( PR ; PR ; PR ) SB
	else if ((*itAnalysisCur).type == Keyword_for)
	{
		itAnalysisCur++;//更新当前分析Tokenen串的位置
		//1.分析左小括号
		if (itAnalysisCur == TokenenList.end())
		{
			return false;
		}
		if ((*itAnalysisCur).type != Delimiter_Left_Small_Bracket)
		{
			return false;
		}
		itAnalysisCur++;//更新当前分析Tokenen串的位置
		//2.分析PR 第一个表达式 初始化语句
		FourElementTypeItem express_1;
		if (!semanticAnalysis_eexpr(itAnalysisCur, TokenenList, express_1))
		{
			//cout << (*itAnalysisCur).data << endl;
			return false;
		}
		//分析express_1 BOOL量 非BOOL量->改为BOOL量
		if (express_1.mType <= 0 || express_1.mType > 4)
		{
			return false;
		}
		if (express_1.mType == 4)	//如果express_1为BOOL量，则需要先转换为->非BOOL量
		{
			FourElementTypeItem nullId;
			FourElementTypeItem tempId = newTempIdentifier();
			FourElementTypeItem constant;
			constant.mType = 1;
			constant.mConstantType = 1;
			//真出口
			constant.mConstantInteger = 1;
			int mTC = mFourElementTypeList.size() + 1;
			FourElementType four(mFourElementTypeList.size() + 1, Equal, constant, nullId, tempId);
			mFourElementTypeList.push_back(four);
			//跳转语句
			FourElementTypeItem pFour;
			pFour.mType = 5;
			pFour.mNumber = mTC + 3;
			FourElementType four1(mFourElementTypeList.size() + 1, Jump, nullId, nullId, pFour);
			mFourElementTypeList.push_back(four1);
			//假出口
			constant.mConstantInteger = 0;
			int mFC = mFourElementTypeList.size() + 1;
			FourElementType four2(mFourElementTypeList.size() + 1, Equal, constant, nullId, tempId);
			mFourElementTypeList.push_back(four2);
			//修改四元式列表
			//cout << "mFC " << express_1.mFC << endl;
			modify_end_c(express_1.mTC, mTC);
			modify_end_c(express_1.mFC, mFC);
			express_1 = tempId;
		}
		//3.分析分号 
		if (itAnalysisCur == TokenenList.end())
		{
			return false;
		}
		if ((*itAnalysisCur).type != Delimiter_Semicolon)	// ;
		{
			return false;
		}
		itAnalysisCur++;//更新当前分析Tokenen串的位置
		//4.分析PR 第二个表达式 判定条件
		//judge
		int JUDGE = mFourElementTypeList.size() + 1;	//JUDGE = NXQ
		//int tmpContinue = JUDGE;	//continue跳转的位置 修改为AGAIN
		FourElementTypeItem express_2;
		if (!semanticAnalysis_eexpr(itAnalysisCur, TokenenList, express_2))
		{
			cout << (*itAnalysisCur).data << endl;
			return false;
		}
		//分析express_2 BOOL量 非BOOL量->改为BOOL量
		if (express_2.mType <= 0 || express_2.mType > 4)
		{
			return false;
		}
		if (express_2.mType != 4)	//如果express_2不为BOOL量，则需要先转换为BOOL量
		{
			int mTC = mFourElementTypeList.size() + 1;
			int mFC = mFourElementTypeList.size() + 2;
			FourElementTypeItem pFour;
			pFour.mType = 5;
			pFour.mNumber = 0;
			FourElementTypeItem nullId;
			FourElementType four(mFourElementTypeList.size() + 1, Jump_Not_Zero, express_2, nullId, pFour);
			mFourElementTypeList.push_back(four);
			FourElementType four1(mFourElementTypeList.size() + 1, Jump, nullId, nullId, pFour);
			mFourElementTypeList.push_back(four1);
			express_2.mType = 4;
			express_2.mTC = mTC;
			express_2.mFC = mFC;
			//cout << "express_2" << "eexpr> TC:" << mTC << " FC:" << mFC << endl;
		}
		int chain = express_2.mFC;	// chain = PR(2).FC
		int tmpBreak = chain;	//break跳转的位置 tmpBreak = E2.FC
		int mTC = express_2.mTC;	//mTC = PR(2).TC
		//5.分析分号
		if (itAnalysisCur == TokenenList.end())
		{
			return false;
		}
		if ((*itAnalysisCur).type != Delimiter_Semicolon)	// ;
		{
			return false;
		}
		itAnalysisCur++;//更新当前分析Tokenen串的位置

		//6.分析PR 第三个表达式 循环执行表达式
		int AGAIN = mFourElementTypeList.size() + 1;	// AGAIN = NXQ
		int tmpContinue = AGAIN;	//continue跳转的位置 tmpContinue = AGAIN
		FourElementTypeItem express_3;
		if (!semanticAnalysis_eexpr(itAnalysisCur, TokenenList, express_3))
		{
			//cout << (*itAnalysisCur).data << endl;
			return false;
		}
		//分析express_3 BOOL量 非BOOL量->改为BOOL量
		if (express_3.mType <= 0 || express_3.mType > 4)
		{
			return false;
		}
		if (express_3.mType == 4)	//如果express_3为BOOL量，则需要先转换为->非BOOL量
		{
			FourElementTypeItem nullId;
			FourElementTypeItem tempId = newTempIdentifier();
			FourElementTypeItem constant;
			constant.mType = 1;
			constant.mConstantType = 1;
			//真出口
			constant.mConstantInteger = 1;
			int mTC = mFourElementTypeList.size() + 1;
			FourElementType four(mFourElementTypeList.size() + 1, Equal, constant, nullId, tempId);
			mFourElementTypeList.push_back(four);
			//跳转语句
			FourElementTypeItem pFour;
			pFour.mType = 5;
			pFour.mNumber = mTC + 3;
			FourElementType four1(mFourElementTypeList.size() + 1, Jump, nullId, nullId, pFour);
			mFourElementTypeList.push_back(four1);
			//假出口
			constant.mConstantInteger = 0;
			int mFC = mFourElementTypeList.size() + 1;
			FourElementType four2(mFourElementTypeList.size() + 1, Equal, constant, nullId, tempId);
			mFourElementTypeList.push_back(four2);
			//修改四元式列表
			//cout << "mFC " << express_1.mFC << endl;
			modify_end_c(express_3.mTC, mTC);
			modify_end_c(express_3.mFC, mFC);
			express_3 = tempId;
		}
		// JUMP (j,_,_,JUDGE)
		FourElementTypeItem pFour;
		pFour.mType = 5;
		pFour.mNumber = JUDGE;
		FourElementTypeItem nullId;
		FourElementType four(mFourElementTypeList.size() + 1, Jump, nullId, nullId, pFour);
		mFourElementTypeList.push_back(four);
		//7.分析右小括号
		if (itAnalysisCur == TokenenList.end())
		{
			return false;
		}
		if ((*itAnalysisCur).type != Delimiter_Right_Small_Bracket) //不为右小括号
		{
			return false;
		}
		itAnalysisCur++;//更新当前分析Tokenen串的位置
		int SB_start = mFourElementTypeList.size() + 1;	//SB_start = NXQ
		modify_end_c(mTC, SB_start);					//modify_end_c(mTC ,SB_start )
		//分析SB
		int SB_CHAIN = 0;
		if (!semanticAnalysis_SB(itAnalysisCur, TokenenList, SB_CHAIN))
		{
			return false;
		}
		//设置 SB chain
		if (SB_CHAIN != 0)
		{
			int NXQ = mFourElementTypeList.size() + 1;
			modify_end_c(SB_CHAIN, NXQ);

		}
		//更新 continue_posi 和 break_posi 位置信息
		if (continuePosiList.size() > 0)
		{
			list<int>::iterator it = continuePosiList.begin();
			for (; it != continuePosiList.end(); it++)
			{
				if ((*it) != 0)
					modify_end_c((*it), tmpContinue);
			}
			continuePosiList.clear();
		}
		if (breakPosiList.size() > 0)
		{
			list<int>::iterator it = breakPosiList.begin();
			for (; it != breakPosiList.end(); it++)
			{
				if ((*it) != 0)
					modify_end_c((*it), tmpBreak);
			}
			breakPosiList.clear();
		}
		// JUMP (j,_,_,AGAIN)
		pFour.mNumber = AGAIN;
		FourElementType four1(mFourElementTypeList.size() + 1, Jump, nullId, nullId, pFour);
		mFourElementTypeList.push_back(four1);
		//CHAIN
		RS_CHAIN = chain;
		return true;
	}
	//------------------------------
	//分析 break
	//RS -> break ;
	else if ((*itAnalysisCur).type == Keyword_break)
	{
		//cout << "break" << endl;
		itAnalysisCur++;//更新当前分析Tokenen串的位置
		//分析分号
		if (itAnalysisCur == TokenenList.end())
		{
			return false;
		}
		if ((*itAnalysisCur).type != Delimiter_Semicolon) //不为分号
		{
			return false;
		}
		itAnalysisCur++;//更新当前分析Tokenen串的位置
		//需要回填
		//保存回填位置 breakPosiList.Add( NXQ )
		breakPosiList.push_back(mFourElementTypeList.size() + 1);
		// JUMP (j,_,_,0)
		FourElementTypeItem pFour;
		pFour.mType = 5;
		pFour.mNumber = 0;
		FourElementTypeItem nullId;
		FourElementType four(mFourElementTypeList.size() + 1, Jump, nullId, nullId, pFour);
		mFourElementTypeList.push_back(four);
		RS_CHAIN = 0;	//RS.CHAIN = 0
		return true;
	}
	//------------------------------
	//分析 continue
	// RS -> continue;
	else if ((*itAnalysisCur).type == Keyword_continue)
	{
		itAnalysisCur++;//更新当前分析Tokenen串的位置
		//分析分号
		if (itAnalysisCur == TokenenList.end())
		{
			return false;
		}
		if ((*itAnalysisCur).type != Delimiter_Semicolon) //不为分号
		{
			return false;
		}
		itAnalysisCur++;//更新当前分析Tokenen串的位置
		//需要回填
		//保存回填位置continuePosiList.Add( NXQ )
		continuePosiList.push_back(mFourElementTypeList.size() + 1);
		// JUMP (j,_,_,0) (Jump,_,_,0)
		FourElementTypeItem pFour;
		pFour.mType = 5;
		pFour.mNumber = 0;
		FourElementTypeItem nullId;
		FourElementType four(mFourElementTypeList.size() + 1, Jump, nullId, nullId, pFour);
		mFourElementTypeList.push_back(four);
		RS_CHAIN = 0;	//RS.CHAIN = 0
		return true;
	}
	//------------------------------
	//分析 return
	//RS -> return PR ;
	else if ((*itAnalysisCur).type == Keyword_return)
	{
		itAnalysisCur++;//更新当前分析Tokenen串的位置
		//1.分析PR
		list<Token> tmpList;
		while (itAnalysisCur != TokenenList.end())
		{
			if ((*itAnalysisCur).type == Delimiter_Semicolon) //到分号结束
			{
				break;
			}
			tmpList.push_back(*itAnalysisCur);
			itAnalysisCur++; //更新当前分析Tokenen串的位置
		}
		FourElementTypeItem eexpr;
		if (!semanticAnalysis_aexpr(itAnalysisCur, TokenenList, eexpr))
		{
			//表达式分析错误
			return false;
		}
		//如果eexpr为BOOL量，需要先转换为非BOOL量
		if (eexpr.mType == 4)	//如果bexpr为BOOL量，需要先转换为非BOOL量
		{
			FourElementTypeItem nullId;
			FourElementTypeItem tempId = newTempIdentifier();
			FourElementTypeItem constant;
			constant.mType = 1;
			constant.mConstantType = 1;
			//真出口
			constant.mConstantInteger = 1;
			int mTC = mFourElementTypeList.size() + 1;
			FourElementType four(mFourElementTypeList.size() + 1, Equal, constant, nullId, tempId);
			mFourElementTypeList.push_back(four);
			//跳转语句
			FourElementTypeItem pFour;
			pFour.mType = 5;
			pFour.mNumber = mTC + 3;
			FourElementType four1(mFourElementTypeList.size() + 1, Jump, nullId, nullId, pFour);
			mFourElementTypeList.push_back(four1);
			//假出口
			constant.mConstantInteger = 0;
			int mFC = mFourElementTypeList.size() + 1;
			FourElementType four2(mFourElementTypeList.size() + 1, Equal, constant, nullId, tempId);
			mFourElementTypeList.push_back(four2);
			//修改四元式列表
			//cout << "mFC " << eexpr.mFC << endl;
			modify_end_c(eexpr.mTC, mTC);
			modify_end_c(eexpr.mFC, mFC);
			eexpr = tempId;
		}
		
		//2.分析分号
		if (itAnalysisCur == TokenenList.end())
		{
			//cout << "已经分析到Tokenen串的末尾" << endl;
			return false;
		}
		if ((*itAnalysisCur).type != Delimiter_Semicolon) //不为分号
		{
			//cout << "当前位置缺少分号" << endl;
			return false;
		}
		itAnalysisCur++;//更新当前分析Tokenen串的位置

		//需要回填
		//保存回填位置returnPosiList.Add( NXQ )
		returnPosiList.push_back(mFourElementTypeList.size() + 1);
		// JUMP (j,_,_,0) (Jump,_,_,0)
		FourElementTypeItem pFour;
		pFour.mType = 5;
		pFour.mNumber = 0;
		FourElementTypeItem nullId;
		FourElementType four(mFourElementTypeList.size() + 1, Jump, nullId, nullId, pFour);
		mFourElementTypeList.push_back(four);
		RS_CHAIN = 0;	//RS.CHAIN = 0
		return true;
	}
	/*
	//分析 goto
	else if ((*it_AnalysisCur).type == Keyword_goto)
	{
	it_AnalysisCur++;//更新当前分析Tokenen串的位置
	//分析Id
	if (it_AnalysisCur == listToken.end())
	{
	cout << "已经分析到Tokenen串的末尾" << endl;
	return false;
	}
	if ((*it_AnalysisCur).type != Identifier) //不为Id
	{
	cout << "当前位置缺少标识符" << endl;
	return false;
	}
	it_AnalysisCur++;//更新当前分析Tokenen串的位置
	}
	*/
	//分析 print
	//RS -> print ( Print
	else if ((*itAnalysisCur).type == Keyword_print)
	{
		//outAnalysisFile << "G: RS -> print ( Print" << endl;
		//outAnalysisFile << "1> 分析出 print" << endl;
		itAnalysisCur++;//更新当前分析Tokenen串的位置
						//分析 左小括号
		if (itAnalysisCur == TokenenList.end())
		{
			//outAnalysisFile << "E: 已经分析到Tokenen串的末尾" << endl;
			return false;
		}
		if ((*itAnalysisCur).type != Delimiter_Left_Small_Bracket)	//是否为左小括号
		{
			//outAnalysisFile << "E: 分析 ( 出错" << endl;
			return false;
		}
		//outAnalysisFile << "1> 分析出 (" << endl;
		itAnalysisCur++;//更新当前分析Tokenen串的位置
		if (!semanticAnalysisPrint(itAnalysisCur, TokenenList, RS_CHAIN))
		{
			//outAnalysisFile << "E: 分析 Print 出错" << endl;
			return false;
		}
		return true;
	}
	//分析 scan
	//RS -> scan ( id ) ;
	else if ((*itAnalysisCur).type == Keyword_scan)
	{
		//outAnalysisFile << "G: RS -> scan ( id ) ;" << endl;
		//outAnalysisFile << "1> 分析出 scan" << endl;
		itAnalysisCur++;//更新当前分析Tokenen串的位置
						//1.分析 左小括号
		if (itAnalysisCur == TokenenList.end())
		{
			//outAnalysisFile << "E: 已经分析到Tokenen串的末尾" << endl;
			return false;
		}
		if ((*itAnalysisCur).type != Delimiter_Left_Small_Bracket)	//是否为左小括号
		{
			//outAnalysisFile << "E: 分析 ( 出错" << endl;
			return false;
		}
		//outAnalysisFile << "1> 分析出 (" << endl;
		itAnalysisCur++;//更新当前分析Tokenen串的位置
						//2.分析 id
		if (itAnalysisCur == TokenenList.end())
		{
			//outAnalysisFile << "E: 已经分析到Tokenen串的末尾" << endl;
			return false;
		}
		if ((*itAnalysisCur).type != Identifier)	//是否为id
		{
			//outAnalysisFile << "E: 分析 id 出错" << endl;
			return false;
		}
		//outAnalysisFile << "1> 分析出 id" << endl;
		itAnalysisCur++;//更新当前分析Tokenen串的位置
						//3.分析 右小括号
		if (itAnalysisCur == TokenenList.end()) //没有分析到末尾
		{
			//outAnalysisFile << "E: 已经分析到Tokenen串的末尾" << endl;
			return false;
		}
		if ((*itAnalysisCur).type != Delimiter_Right_Small_Bracket)	//是否为右小括号
		{
			//outAnalysisFile << "E: 分析 ) 出错" << endl;
			return false;
		}
		//outAnalysisFile << "1> 分析出 )" << endl;
		itAnalysisCur++;//更新当前分析Tokenen串的位置
						//4.分析 分号
		if (itAnalysisCur == TokenenList.end()) //没有分析到末尾
		{
			//outAnalysisFile << "E: 已经分析到Tokenen串的末尾" << endl;
			return false;
		}
		if ((*itAnalysisCur).type != Delimiter_Semicolon)	//是否为分号
		{
			//outAnalysisFile << "E: 分析 ; 出错" << endl;
			return false;
		}
		//outAnalysisFile << "1> 分析出 ;" << endl;
		//it_AnalysisCur++;//更新当前分析Tokenen串的位置
		return true;
	}
	//RS -> MT DT VL ;
	else if ((*itAnalysisCur).type == Keyword_auto || (*itAnalysisCur).type == Keyword_register ||
		(*itAnalysisCur).type == Keyword_extern || (*itAnalysisCur).type == Keyword_static ||
		(*itAnalysisCur).type == Keyword_int || (*itAnalysisCur).type == Keyword_char ||
		(*itAnalysisCur).type == Keyword_float || (*itAnalysisCur).type == Keyword_double)
	{
		VariableDefinition variableDefinition;
		//分析MT
		variableDefinition.memoryType = Keyword_extern;
		if (semanticAnalysisMT(itAnalysisCur, TokenenList, variableDefinition.memoryType))
		{
			//cout << "分析MT1出错" << endl;
			//return false;
		}
		//分析DT
		variableDefinition.dataType = Error;
		if (!semanticAnalysisDT(itAnalysisCur, TokenenList, variableDefinition.dataType))
		{
			//cout << "分析DT出错" << endl;
			return false;
		}
		//分析VL
		if (!semanticAnalysisVL(itAnalysisCur, TokenenList, variableDefinition.variableList, false))
		{
			//cout << "分析VL出错" << endl;
			return false;
		}
		mVariableDefinitionList.push_back(variableDefinition);
		//分析分号
		if (itAnalysisCur == TokenenList.end())
		{
			//cout << "已经分析到Tokenen串的末尾" << endl;
			return false;
		}
		if ((*itAnalysisCur).type != Delimiter_Semicolon) //不为分号
		{
			//cout << "当前位置缺少分号" << endl;
			return false;
		}
		itAnalysisCur++;//更新当前分析Tokenen串的位置
		return true;
	}
	//PR ;
	else if (expressPreAnalysis((*itAnalysisCur).type))
	{
		//分析PR 赋值表达式 布尔表达式 逻辑表达式
		FourElementTypeItem express;
		if (!semanticAnalysis_eexpr(itAnalysisCur, TokenenList, express))
		{
			cout << (*itAnalysisCur).data << endl;
			return false;
		}
		//分析express 不为BOOL量 BOOL量->改为非BOOL量
		if (express.mType <= 0 || express.mType > 4)
		{
			return false;
		}
		if (express.mType == 4)	//如果express为BOOL量，则需要先转换为非BOOL量
		{
			FourElementTypeItem nullId;
			FourElementTypeItem tempId = newTempIdentifier();
			FourElementTypeItem constant;
			constant.mType = 1;
			constant.mConstantType = 1;
			//真出口
			constant.mConstantInteger = 1;
			int mTC = mFourElementTypeList.size() + 1;
			FourElementType four(mFourElementTypeList.size() + 1, Equal, constant, nullId, tempId);
			mFourElementTypeList.push_back(four);
			//跳转语句
			FourElementTypeItem pFour;
			pFour.mType = 5;
			pFour.mNumber = mTC + 3;
			FourElementType four1(mFourElementTypeList.size() + 1, Jump, nullId, nullId, pFour);
			mFourElementTypeList.push_back(four1);
			//假出口
			constant.mConstantInteger = 0;
			int mFC = mFourElementTypeList.size() + 1;
			FourElementType four2(mFourElementTypeList.size() + 1, Equal, constant, nullId, tempId);
			mFourElementTypeList.push_back(four2);
			//修改四元式列表
			modify_end_c(express.mTC, mTC);
			modify_end_c(express.mFC, mFC);
			express = tempId;
			//cout << "express" << "eexpr> TC:" << mTC << " FC:" << mFC << endl;
		}
		//操作链子
		//mNXQ = NXQ
		int NXQ = mFourElementTypeList.size() + 1;
		//(Jump,_,_,0)
		FourElementTypeItem pFour;
		pFour.mType = 5;
		pFour.mNumber = 0;
		FourElementTypeItem nullId;
		FourElementType four3(mFourElementTypeList.size() + 1, Jump, nullId, nullId, pFour);
		mFourElementTypeList.push_back(four3);
		//RS.CHAIN = mNXQ
		RS_CHAIN = NXQ;
		//分析分号
		if (itAnalysisCur == TokenenList.end())
		{
			cout << "已经分析到Tokenen串的末尾" << endl;
			return false;
		}
		if ((*itAnalysisCur).type != Delimiter_Semicolon) //不为分号
		{
			cout << "当前位置缺少分号" << endl;
			return false;
		}
		itAnalysisCur++;//更新当前分析Tokenen串的位置
		return true;
	}
	//判断是否为右大括号
	else if ((*itAnalysisCur).type != Delimiter_Right_Large_Bracket)
	{
		return true;
	}
	else
	{
		//cout << (*itAnalysisCur).data << " 无法识别" << endl;
		return false;
	}
	return true;
}
/*
	RS1 -> $
	RS1 -> else SB
*/
bool SemanticAnalysis::semanticAnalysis_RS1(list<Token>::iterator & itAnalysisCur, list<Token>& TokenenList, int& chain, int& FC)
{
	//是否分析到末尾
	if (itAnalysisCur == TokenenList.end()) //没有分析到末尾
	{
		return false;
	}
	// else
	if (Keyword_else != (*itAnalysisCur).type)
	{
		// TC 和 FC 合并
		modify_end_c(FC, chain);
		return true;	//不为else也是对的
	}
	itAnalysisCur++;	//更新当前分析Tokenen串的位置
	//分析SB 高能区
	//int NXQ = mFourElementTypeList.size() + 1;
	// FC = NXQ
	//modify_end_c(FC, NXQ);

	//分析SB
	if (!semanticAnalysis_SB(itAnalysisCur, TokenenList, FC))
	{
		return false;
	}
	//mNXQ = NXQ
	int NXQ = mFourElementTypeList.size() + 1;
	// gencode(j,_,_,0) (Jump,_,_,0)
	FourElementTypeItem pFour;
	pFour.mType = 5;
	pFour.mNumber = 0;
	FourElementTypeItem nullId;
	FourElementType four(mFourElementTypeList.size() + 1, Jump, nullId, nullId, pFour);
	mFourElementTypeList.push_back(four);
	// TC = NXQ
	modify_end_c(chain, NXQ);
	// RS1.CHAIN = NXQ
	chain = NXQ;

	return true;
}
/*
	SB -> RS
	SB -> { SB1 }
*/
bool SemanticAnalysis::semanticAnalysis_SB(list<Token>::iterator & itAnalysisCur, list<Token>& TokenenList, int& SB_CHAIN)
{
	if (itAnalysisCur == TokenenList.end()) //没有分析到末尾
	{
		return false;
	}
	//1.分析左大括号
	if ((*itAnalysisCur).type == Delimiter_Left_Large_Bracket)
	{
		itAnalysisCur++;//更新当前分析Tokenen串的位置
		//2.分析SB1，并处理chain
		semanticAnalysis_SB1(itAnalysisCur, TokenenList, SB_CHAIN);	//分析SB1返回值在这个位置永远为true
		//3.分析右大括号
		if (itAnalysisCur == TokenenList.end()) //没有分析到末尾
		{
			return false;
		}
		if ((*itAnalysisCur).type != Delimiter_Right_Large_Bracket)
		{
			return false;
		}
		itAnalysisCur++;//更新当前分析Tokenen串的位置
	}
	else
	{
		//1.分析RS，并处理chain
		//int chain = 0;
		if (!semanticAnalysis_RS(itAnalysisCur, TokenenList, SB_CHAIN))
		{
			return false;
		}
	}
	return true;
}
/*
	SB1 -> $
	SB1 -> RS SB1
*/
bool SemanticAnalysis::semanticAnalysis_SB1(list<Token>::iterator & itAnalysisCur, list<Token>& TokenenList, int& SB1_CHAIN)	//无论怎样都会返回true
{
	list<Token>::iterator it_tmp = itAnalysisCur;
	//分析RS
	//int chain = 0;
	if (semanticAnalysis_RS(itAnalysisCur, TokenenList, SB1_CHAIN))
	{
		//分析SB1
		semanticAnalysis_SB1(itAnalysisCur, TokenenList, SB1_CHAIN);
	}
	else
	{
		itAnalysisCur = it_tmp;
		return true;
	}
	return true;
}
/*
	Print -> string ) ;
	Print -> PR ) ;
*/
bool SemanticAnalysis::semanticAnalysisPrint(list<Token>::iterator & itAnalysisCur, list<Token>& TokenenList, int& chain)
{
	if (itAnalysisCur == TokenenList.end()) //没有分析到末尾
	{
		return false;
	}
	//分析 string ) ;
	if ((*itAnalysisCur).type == String)	//是否为字符串
	{
		FourElementTypeItem nullId;
		FourElementTypeItem  printString;
		printString.mType = 1;	//设置为常量
		printString.mConstantType = 4;	//常量类型为字符串
		printString.mPrintString = clearUpString((*itAnalysisCur).data);
		FourElementType four(mFourElementTypeList.size() + 1, Print, printString, nullId, nullId);
		mFourElementTypeList.push_back(four);

		FourElementTypeItem  pFour;
		pFour.mType = 5;
		pFour.mNumber = 0;
		FourElementType four1(mFourElementTypeList.size() + 1, Jump, nullId, nullId, pFour);
		mFourElementTypeList.push_back(four1);

		chain = mFourElementTypeList.size();

		itAnalysisCur++;//更新当前分析Tokenen串的位置
						// 分析 右小括号
		if (itAnalysisCur == TokenenList.end()) //没有分析到末尾
		{
			return false;
		}
		if ((*itAnalysisCur).type != Delimiter_Right_Small_Bracket)	//是否为右小括号
		{
			return false;
		}
		itAnalysisCur++;//更新当前分析Tokenen串的位置
						// 分析 分号
		if (itAnalysisCur == TokenenList.end()) //没有分析到末尾
		{
			return false;
		}
		if ((*itAnalysisCur).type != Delimiter_Semicolon)	//是否为分号
		{
			return false;
		}
		itAnalysisCur++;//更新当前分析Tokenen串的位置
	}
	else
	{
		FourElementTypeItem fourElementTypeItem;
		if (!semanticAnalysis_eexpr(itAnalysisCur, TokenenList, fourElementTypeItem))
		{
			//outAnalysisFile << "E: 分析 eexpr 出错" << endl;
			return false;
		}
		//处理four 常量、变量
		switch (fourElementTypeItem.mType)
		{
		case 1:	//常量
		{
			FourElementTypeItem nullId;
			FourElementTypeItem  printString;
			printString.mType = 1;	//设置为常量
			printString.mConstantType = 4;	//常量类型为字符串
			printString.mPrintString = fourElementTypeItem.mCacheBuffer;
			FourElementType four(mFourElementTypeList.size() + 1, Print, printString, nullId, nullId);
			mFourElementTypeList.push_back(four);
			break;
		}
		case 2:	//用户定义变量
		{
			FourElementTypeItem nullId;
			FourElementType four(mFourElementTypeList.size() + 1, Print, fourElementTypeItem, nullId, nullId);	//four是变量
			mFourElementTypeList.push_back(four);
			break;
		}
		case 3:	//临时变量
		{
			FourElementTypeItem nullId;
			FourElementType four(mFourElementTypeList.size() + 1, Print, fourElementTypeItem, nullId, nullId);	//four是变量
			mFourElementTypeList.push_back(four);
			break;
		}
		case 4:	//布尔表达式
		{
			//如果bexpr为BOOL量，需要先转换为非BOOL量
			FourElementTypeItem nullId;
			FourElementTypeItem tempId = newTempIdentifier();
			FourElementTypeItem constant;
			constant.mType = 1;	//设为常量
			constant.mConstantType = 4;	//设为字符串
										//真出口
			constant.mPrintString = "true";
			int mTC = mFourElementTypeList.size() + 1;
			FourElementType four(mFourElementTypeList.size() + 1, Print, constant, nullId, tempId);
			mFourElementTypeList.push_back(four);
			//跳转语句
			FourElementTypeItem pFour;
			pFour.mType = 5;
			pFour.mNumber = mTC + 3;
			FourElementType four1(mFourElementTypeList.size() + 1, Jump, nullId, nullId, pFour);
			mFourElementTypeList.push_back(four1);
			//假出口
			constant.mPrintString = "false";
			int mFC = mFourElementTypeList.size() + 1;
			FourElementType four2(mFourElementTypeList.size() + 1, Print, constant, nullId, tempId);
			mFourElementTypeList.push_back(four2);
			//修改四元式列表
			modify_end_c(fourElementTypeItem.mTC, mTC);
			modify_end_c(fourElementTypeItem.mFC, mFC);
			//fourElementTypeItem = tempId;
			break;
		}
		default:
			break;
		}

		//chain
		FourElementTypeItem nullId;
		FourElementTypeItem  pFour;
		pFour.mType = 5;
		pFour.mNumber = 0;
		FourElementType four1(mFourElementTypeList.size() + 1, Jump, nullId, nullId, pFour);
		mFourElementTypeList.push_back(four1);
		chain = mFourElementTypeList.size();

		// 分析 右小括号
		if (itAnalysisCur == TokenenList.end()) //没有分析到末尾
		{
			return false;
		}
		if ((*itAnalysisCur).type != Delimiter_Right_Small_Bracket)	//是否为右小括号
		{
			return false;
		}
		itAnalysisCur++;//更新当前分析Tokenen串的位置
		// 分析 分号
		if (itAnalysisCur == TokenenList.end()) //没有分析到末尾
		{
			return false;
		}
		if ((*itAnalysisCur).type != Delimiter_Semicolon)	//是否为分号
		{
			return false;
		}
		itAnalysisCur++;//更新当前分析Tokenen串的位置
	}
	return true;
}
//------------------------------------------表达式----------------------------------------------------------------------------
/*
	连等关键有两点：
	1、运算符的优先级跟结合性。
	2、一个赋值表达式是有值的，值就是被赋的值，比如a=3 ，这个赋值表达式的值就是3，若有b=（a=3），则b的值为3.
	例如：
	a=b=c中只有一个运算符，等号，所以优先级是一样的，而等号的结合性是从右向左的(也就是等式从右往左计算)，所以a=b=c 等同于 a=(b=c),故a=4,b=4;
*/
/*
	eexpr -> bexpr eexpr1
*/
bool SemanticAnalysis::semanticAnalysis_eexpr(list<Token>::iterator& itAnalysisCur, list<Token>& TokenenList, FourElementTypeItem& eexpr)
{
	//FourElementTypeItem bexpr;
	semanticAnalysis_bexpr(itAnalysisCur, TokenenList, eexpr);	//bexpr

	int ao = 0;
	string ao_str = "";
	//1.预先分析下一个Tokenen串是否为赋值运算符
	list<Token>::iterator tmp = itAnalysisCur;
	if (semanticAnalysis_ao(itAnalysisCur, TokenenList, ao))	//下一个Tokenen串为赋值运算符，bexpr应该为变量
	{
		switch (ao)
		{
		case 1:ao_str = "="; break;
		case 2:ao_str = "+="; break;
		case 3:ao_str = "-="; break;
		case 4:ao_str = "*="; break;
		case 5:ao_str = "/="; break;
		default:
			break;
		}
		//1.1分析bexpr是否为变量，如果不为变量则报错
		if (!(eexpr.mType == 2 || eexpr.mType == 3))	//是否为用户自定义变量或临时变量
		{
			mErrorInfo.push_back("第n行，运算符" + ao_str + "左边应该为一个变量");
			return false;	//
		}
	}//end if
	itAnalysisCur = tmp;

	if (!semanticAnalysis_eexpr1(itAnalysisCur, TokenenList, eexpr))	//eexpr1
	{
		return false;
	}
	return true;
}
/*
	eexpr1 -> ao bexpr eexpr1
	eexpr1 -> $
*/
bool SemanticAnalysis::semanticAnalysis_eexpr1(list<Token>::iterator& itAnalysisCur, list<Token>& TokenenList, FourElementTypeItem& eexpr1)
{
	int ao = 0;
	if (semanticAnalysis_ao(itAnalysisCur, TokenenList, ao))
	{
		FourElementTypeItem bexpr;
		semanticAnalysis_bexpr(itAnalysisCur, TokenenList, bexpr);	//bexpr

		//1.预先分析下一个Tokenen串是否为赋值运算符
		list<Token>::iterator tmp = itAnalysisCur;
		int ao_tmp = 0;
		string ao_str_tmp = "";
		if (semanticAnalysis_ao(itAnalysisCur, TokenenList, ao_tmp))	//bexpr应该为变量
		{
			switch (ao_tmp)
			{
			case 1:ao_str_tmp = "="; break;
			case 2:ao_str_tmp = "+="; break;
			case 3:ao_str_tmp = "-="; break;
			case 4:ao_str_tmp = "*="; break;
			case 5:ao_str_tmp = "/="; break;
			default:
				break;
			}
			//2.1分析eexpr1是否为变量，如果不为变量则报错
			if (!(bexpr.mType == 2 || bexpr.mType == 3))	//是否为用户自定义变量或临时变量
			{
				mErrorInfo.push_back("第n行，运算符" + ao_str_tmp + "左边应该为一个变量");
				return false;	//
			}
		}// end if bexpr应该为变量
		itAnalysisCur = tmp;

		if (!semanticAnalysis_eexpr1(itAnalysisCur, TokenenList, bexpr))	//bexpr
		{
			return false;
		}
		//赋值操作，自右向左，将bexpr变量赋值给eexpr1
		if (bexpr.mType >= 1 && bexpr.mType <= 4)
		{
			if (bexpr.mType == 4)	//如果bexpr为BOOL量，需要先转换为非BOOL量
			{
				FourElementTypeItem nullId;
				FourElementTypeItem tempId = newTempIdentifier();
				FourElementTypeItem constant;
				constant.mType = 1;
				constant.mConstantType = 1;
				//真出口
				constant.mConstantInteger = 1;
				int mTC = mFourElementTypeList.size() + 1;
				FourElementType four(mFourElementTypeList.size() + 1, Equal, constant, nullId, tempId);
				mFourElementTypeList.push_back(four);
				//跳转语句
				FourElementTypeItem pFour;
				pFour.mType = 5;
				pFour.mNumber = mTC + 3;
				FourElementType four1(mFourElementTypeList.size() + 1, Jump, nullId, nullId, pFour);
				mFourElementTypeList.push_back(four1);
				//假出口
				constant.mConstantInteger = 0;
				int mFC = mFourElementTypeList.size() + 1;
				FourElementType four2(mFourElementTypeList.size() + 1, Equal, constant, nullId, tempId);
				mFourElementTypeList.push_back(four2);
				//修改四元式列表
				cout << "mFC " << bexpr.mFC << endl;
				modify_end_c(bexpr.mTC, mTC);
				modify_end_c(bexpr.mFC, mFC);
				bexpr = tempId;
			}
			switch (ao)	// =
			{
			case 1:
			{
				FourElementTypeItem nullId;
				FourElementType four(mFourElementTypeList.size() + 1, Equal, bexpr, nullId, eexpr1);
				mFourElementTypeList.push_back(four);
				break;
			}
			case 2:	// +=
			{
				FourElementTypeItem tempId = newTempIdentifier();
				FourElementTypeItem nullId;
				FourElementType four(mFourElementTypeList.size() + 1, Plus, eexpr1, bexpr, tempId);
				mFourElementTypeList.push_back(four);
				FourElementType four1(mFourElementTypeList.size() + 1, Equal, tempId, nullId, eexpr1);
				mFourElementTypeList.push_back(four1);
				break;
			}
			case 3:	//	-=
			{
				FourElementTypeItem tempId = newTempIdentifier();
				FourElementTypeItem nullId;
				FourElementType four(mFourElementTypeList.size() + 1, Minus, eexpr1, bexpr, tempId);
				mFourElementTypeList.push_back(four);
				FourElementType four1(mFourElementTypeList.size() + 1, Equal, tempId, nullId, eexpr1);
				mFourElementTypeList.push_back(four1);
				break;
			}
			case 4:	//	*=
			{
				FourElementTypeItem tempId = newTempIdentifier();
				FourElementTypeItem nullId;
				FourElementType four(mFourElementTypeList.size() + 1, Multiply, eexpr1, bexpr, tempId);
				mFourElementTypeList.push_back(four);
				FourElementType four1(mFourElementTypeList.size() + 1, Equal, tempId, nullId, eexpr1);
				mFourElementTypeList.push_back(four1);
				break;
			}
			case 5:	// /=
			{
				FourElementTypeItem tempId = newTempIdentifier();
				FourElementTypeItem nullId;
				FourElementType four(mFourElementTypeList.size() + 1, Divide, eexpr1, bexpr, tempId);
				mFourElementTypeList.push_back(four);
				FourElementType four1(mFourElementTypeList.size() + 1, Equal, tempId, nullId, eexpr1);
				mFourElementTypeList.push_back(four1);
				break;
			}
			default:
				break;
			}//end switch
		}
	}
	return true;
}
/*
	ao -> =
	ao -> +=
	ao -> -=
	ao -> *=
	ao -> /=
*/
bool SemanticAnalysis::semanticAnalysis_ao(list<Token>::iterator& itAnalysisCur, list<Token>& TokenenList, int& ao)
{
	if (itAnalysisCur == TokenenList.end())
		return false;
	if ((*itAnalysisCur).type == Operator_Equal)	// =
	{
		itAnalysisCur++;
		ao = 1;
	}
	else if ((*itAnalysisCur).type == Operator_Plus_Equal)	// +=
	{
		itAnalysisCur++;
		ao = 2;
	}
	else if ((*itAnalysisCur).type == Operator_Minus_Equal)	// -=
	{
		itAnalysisCur++;
		ao = 3;
	}
	else if ((*itAnalysisCur).type == Operator_Multiply_Equal)	// *=
	{
		itAnalysisCur++;
		ao = 4;
	}
	else if ((*itAnalysisCur).type == Operator_Divide_Equal)	// /=
	{
		itAnalysisCur++;
		ao = 5;
	}
	else
	{
		return false;
	}
	return true;
}
/*
	bexpr -> bterm bexpr1
*/
bool SemanticAnalysis::semanticAnalysis_bexpr(list<Token>::iterator& itAnalysisCur, list<Token>& TokenenList, FourElementTypeItem& bexpr)
{
	//FourElementTypeItem bterm;
	if (!semanticAnalysis_bterm(itAnalysisCur, TokenenList, bexpr))	//bterm
	{
		return false;
	}
	if (!semanticAnalysis_bexpr1(itAnalysisCur, TokenenList, bexpr))	//bexpr1
	{
		return false;
	}
	return true;
}
/*
	bexpr1 -> || bterm bexpr1
	bexpr1 -> $
*/
bool SemanticAnalysis::semanticAnalysis_bexpr1(list<Token>::iterator& itAnalysisCur, list<Token>& TokenenList, FourElementTypeItem& bexpr1)
{
	if (itAnalysisCur == TokenenList.end())
		return false;
	if ((*itAnalysisCur).type == Operator_Or)	// ||
	{
		FourElementTypeItem bexpr1_tmp;
		//1.判断bexpr1是否为BOOL量
		if (bexpr1.mType != 4)	//如果不为BOOL量，则需要先转换为BOOL量
		{
			int mTC = mFourElementTypeList.size() + 1;
			int mFC = mFourElementTypeList.size() + 2;
			FourElementTypeItem pFour;
			pFour.mType = 5;
			pFour.mNumber = 0;
			FourElementTypeItem nullId;
			FourElementType four(mFourElementTypeList.size() + 1, Jump_Not_Zero, bexpr1, nullId, pFour);
			mFourElementTypeList.push_back(four);
			FourElementType four1(mFourElementTypeList.size() + 1, Jump, nullId, nullId, pFour);
			mFourElementTypeList.push_back(four1);
			bexpr1.mType = 4;
			bexpr1.mTC = mTC;
			bexpr1.mFC = mFC;
		}
		int NXQ = mFourElementTypeList.size() + 1;
		backpatch(bexpr1.mFC, NXQ);
		int mTC = bexpr1.mTC;
		//cout << "bterm :" << bexpr1.mTC << " " << bexpr1.mFC << endl;

		itAnalysisCur++;
		FourElementTypeItem bterm;
		if (!semanticAnalysis_bterm(itAnalysisCur, TokenenList, bterm))	//bterm
		{
			return false;
		}
		//1.判断bterm是否为BOOL量
		if (bterm.mType != 4)	//如果不为BOOL量，则需要先转换为BOOL量
		{
			int mTC = mFourElementTypeList.size() + 1;
			int mFC = mFourElementTypeList.size() + 2;
			FourElementTypeItem pFour;
			pFour.mType = 5;
			pFour.mNumber = 0;
			FourElementTypeItem nullId;
			FourElementType four(mFourElementTypeList.size() + 1, Jump_Not_Zero, bterm, nullId, pFour);
			mFourElementTypeList.push_back(four);
			FourElementType four1(mFourElementTypeList.size() + 1, Jump, nullId, nullId, pFour);
			mFourElementTypeList.push_back(four1);
			bterm.mType = 4;
			bterm.mTC = mTC;
			bterm.mFC = mFC;
		}
		bexpr1_tmp.mType = 4;
		bexpr1_tmp.mFC = bterm.mFC;
		bexpr1_tmp.mTC = merge(mTC, bterm.mTC);
		backpatch(bexpr1_tmp.mTC, mFourElementTypeList.size() + 1);
		bexpr1_tmp.mTC = mFourElementTypeList.size() + 1;
		FourElementTypeItem pFour;
		pFour.mType = 5;
		pFour.mNumber = 0;
		FourElementTypeItem nullId;
		FourElementType four(mFourElementTypeList.size() + 1, Jump, nullId, nullId, pFour);
		mFourElementTypeList.push_back(four);


		//cout << "bexpr1_tmp mTC:" << bexpr1_tmp.mTC << "  mFC:" << bexpr1_tmp.mFC << endl;

		if (!semanticAnalysis_bexpr1(itAnalysisCur, TokenenList, bexpr1_tmp))	//bexpr1
		{
			return false;
		}
		bexpr1 = bexpr1_tmp;
	}
	return true;
}
/*
	bterm -> rexpr bterm1
*/
bool SemanticAnalysis::semanticAnalysis_bterm(list<Token>::iterator& itAnalysisCur, list<Token>& TokenenList, FourElementTypeItem& bterm)
{
	//FourElementTypeItem rterm;
	//semanticAnalysis_rexpr(itAnalysisCur,TokenenList);	//rexpr
	if (!semanticAnalysis_rexpr(itAnalysisCur, TokenenList, bterm))	//rterm
	{
		return false;
	}
	//cout << rterm.mFC << "    " << rterm.mTC << endl;
	if (!semanticAnalysis_bterm1(itAnalysisCur, TokenenList, bterm))	//bterm1
	{
		return false;
	}
	return true;
}
/*
	bterm1 -> && rexpr bterm1
	bterm1 -> $
*/
bool SemanticAnalysis::semanticAnalysis_bterm1(list<Token>::iterator& itAnalysisCur, list<Token>& TokenenList, FourElementTypeItem& bterm1)
{
	// bterm1 && rterm
	if (itAnalysisCur == TokenenList.end())
		return false;
	if ((*itAnalysisCur).type == Operator_And)	// &&
	{
		FourElementTypeItem bterm1_tmp;
		//1.判断bterm1是否为BOOL量
		if (bterm1.mType != 4)	//如果不为BOOL量，则需要先转换为BOOL量
		{
			int mTC = mFourElementTypeList.size() + 1;
			int mFC = mFourElementTypeList.size() + 2;
			FourElementTypeItem pFour;
			pFour.mType = 5;
			pFour.mNumber = 0;
			FourElementTypeItem nullId;
			FourElementType four(mFourElementTypeList.size() + 1, Jump_Not_Zero, bterm1, nullId, pFour);
			mFourElementTypeList.push_back(four);
			FourElementType four1(mFourElementTypeList.size() + 1, Jump, nullId, nullId, pFour);
			mFourElementTypeList.push_back(four1);
			bterm1.mType = 4;
			bterm1.mTC = mTC;
			bterm1.mFC = mFC;
		}
		int NXQ = mFourElementTypeList.size() + 1;
		backpatch(bterm1.mTC, NXQ);
		int mFC = bterm1.mFC;

		itAnalysisCur++;
		FourElementTypeItem rterm;
		if (!semanticAnalysis_rexpr(itAnalysisCur, TokenenList, rterm))	//rterm
		{
			return false;
		}
		//cout << "rterm -> mType " << rterm.mType << endl;
		//2.判断term是否为BOOL量
		if (rterm.mType != 4)	//如果rterm不为BOOL量，则需要先转换为BOOL量
		{
			//2.1将rterm转换为BOOL量
			int mTC = mFourElementTypeList.size() + 1;
			int mFC = mFourElementTypeList.size() + 2;
			FourElementTypeItem pFour;
			pFour.mType = 5;
			pFour.mNumber = 0;
			FourElementTypeItem nullId;
			FourElementType four(mFourElementTypeList.size() + 1, Jump_Not_Zero, rterm, nullId, pFour);
			mFourElementTypeList.push_back(four);
			FourElementType four1(mFourElementTypeList.size() + 1, Jump, nullId, nullId, pFour);
			mFourElementTypeList.push_back(four1);
			rterm.mType = 4;
			rterm.mTC = mTC;
			rterm.mFC = mFC;
			//转换结束
		}
		bterm1_tmp.mType = 4;
		bterm1_tmp.mTC = rterm.mTC;
		//cout << bterm1.mFC << "  " << rterm.mFC << endl;
		bterm1_tmp.mFC = merge(mFC, rterm.mFC);
		//cout << "bterm1_tmp mTC:" << bterm1_tmp.mTC << "  mFC:" << bterm1_tmp.mFC << endl;

		if (!semanticAnalysis_bterm1(itAnalysisCur, TokenenList, bterm1_tmp))	//bterm1
		{
			return false;
		}
		bterm1 = bterm1_tmp;
	}
	return true;
}
/*
	rexpr -> aexpr rexpr1
*/
bool SemanticAnalysis::semanticAnalysis_rexpr(list<Token>::iterator& itAnalysisCur, list<Token>& TokenenList, FourElementTypeItem& rterm)
{
	if (!semanticAnalysis_aexpr(itAnalysisCur, TokenenList, rterm))	//aexpr
	{
		return false;
	}
	if (!semanticAnalysis_rexpr1(itAnalysisCur, TokenenList, rterm))	//rterm1
	{
		return false;
	}
	return true;
}
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
bool SemanticAnalysis::semanticAnalysis_rexpr1(list<Token>::iterator& itAnalysisCur, list<Token>& TokenenList, FourElementTypeItem& rterm1)
{
	if (itAnalysisCur == TokenenList.end())
		return false;
	if ((*itAnalysisCur).type == Operator_Less_Than)	// <
	{
		itAnalysisCur++;
		FourElementTypeItem aexpr;
		if (!semanticAnalysis_aexpr(itAnalysisCur, TokenenList, aexpr))	//aexpr
		{
			return false;
		}

		//前方高能
		int mTC = mFourElementTypeList.size() + 1;
		int mFC = mFourElementTypeList.size() + 2;
		FourElementTypeItem pFour;
		pFour.mType = 5;
		pFour.mNumber = 0;
		FourElementTypeItem nullId;
		FourElementType four(mFourElementTypeList.size() + 1, Jump_Less_Than, rterm1, aexpr, pFour);
		mFourElementTypeList.push_back(four);
		FourElementType four1(mFourElementTypeList.size() + 1, Jump, nullId, nullId, pFour);
		mFourElementTypeList.push_back(four1);
		rterm1.mType = 4;
		rterm1.mTC = mTC;
		rterm1.mFC = mFC;

	}
	else if ((*itAnalysisCur).type == Operator_More_Than) // >
	{
		itAnalysisCur++;
		FourElementTypeItem aexpr;
		if (!semanticAnalysis_aexpr(itAnalysisCur, TokenenList, aexpr))	//aexpr
		{
			return false;
		}

		//前方高能
		int mTC = mFourElementTypeList.size() + 1;
		int mFC = mFourElementTypeList.size() + 2;
		FourElementTypeItem pFour;
		pFour.mType = 5;
		pFour.mNumber = 0;
		FourElementTypeItem nullId;
		FourElementType four(mFourElementTypeList.size() + 1, Jump_More_Than, rterm1, aexpr, pFour);
		mFourElementTypeList.push_back(four);
		FourElementType four1(mFourElementTypeList.size() + 1, Jump, nullId, nullId, pFour);
		mFourElementTypeList.push_back(four1);
		rterm1.mType = 4;
		rterm1.mTC = mTC;
		rterm1.mFC = mFC;

	}
	else if ((*itAnalysisCur).type == Operator_Less_Than_Equal)	// <=
	{
		itAnalysisCur++;
		FourElementTypeItem aexpr;
		if (!semanticAnalysis_aexpr(itAnalysisCur, TokenenList, aexpr))	//aexpr
		{
			return false;
		}

		//前方高能
		int mTC = mFourElementTypeList.size() + 1;
		int mFC = mFourElementTypeList.size() + 2;
		FourElementTypeItem pFour;
		pFour.mType = 5;
		pFour.mNumber = 0;
		FourElementTypeItem nullId;
		FourElementType four(mFourElementTypeList.size() + 1, Jump_Less_Than_Equal, rterm1, aexpr, pFour);
		mFourElementTypeList.push_back(four);
		FourElementType four1(mFourElementTypeList.size() + 1, Jump, nullId, nullId, pFour);
		mFourElementTypeList.push_back(four1);
		rterm1.mType = 4;
		rterm1.mTC = mTC;
		rterm1.mFC = mFC;

	}
	else if ((*itAnalysisCur).type == Operator_More_Than_Equal)	// >=
	{
		itAnalysisCur++;
		FourElementTypeItem aexpr;
		if (!semanticAnalysis_aexpr(itAnalysisCur, TokenenList, aexpr))	//aexpr
		{
			return false;
		}

		//前方高能
		int mTC = mFourElementTypeList.size() + 1;
		int mFC = mFourElementTypeList.size() + 2;
		FourElementTypeItem pFour;
		pFour.mType = 5;
		pFour.mNumber = 0;
		FourElementTypeItem nullId;
		FourElementType four(mFourElementTypeList.size() + 1, Jump_More_Than_Equal, rterm1, aexpr, pFour);
		mFourElementTypeList.push_back(four);
		FourElementType four1(mFourElementTypeList.size() + 1, Jump, nullId, nullId, pFour);
		mFourElementTypeList.push_back(four1);
		rterm1.mType = 4;
		rterm1.mTC = mTC;
		rterm1.mFC = mFC;
	}
	//修改文法后添加的内容
	else if ((*itAnalysisCur).type == Operator_Not_Equal_To)	// !=
	{
		itAnalysisCur++;
		FourElementTypeItem aexpr;
		if (!semanticAnalysis_aexpr(itAnalysisCur, TokenenList, aexpr))	//aexpr
		{
			return false;
		}

		//前方高能
		int mTC = mFourElementTypeList.size() + 1;
		int mFC = mFourElementTypeList.size() + 2;
		FourElementTypeItem pFour;
		pFour.mType = 5;
		pFour.mNumber = 0;
		FourElementTypeItem nullId;
		FourElementType four(mFourElementTypeList.size() + 1, Jump_Not_Equal_To, rterm1, aexpr, pFour);
		mFourElementTypeList.push_back(four);
		FourElementType four1(mFourElementTypeList.size() + 1, Jump, nullId, nullId, pFour);
		mFourElementTypeList.push_back(four1);
		rterm1.mType = 4;
		rterm1.mTC = mTC;
		rterm1.mFC = mFC;
	}
	else if ((*itAnalysisCur).type == Operator_Is_Equal) // ==
	{
		itAnalysisCur++;
		FourElementTypeItem aexpr;
		if (!semanticAnalysis_aexpr(itAnalysisCur, TokenenList, aexpr))	//aexpr
		{
			return false;
		}

		//前方高能
		int mTC = mFourElementTypeList.size() + 1;
		int mFC = mFourElementTypeList.size() + 2;
		FourElementTypeItem pFour;
		pFour.mType = 5;
		pFour.mNumber = 0;
		FourElementTypeItem nullId;
		FourElementType four(mFourElementTypeList.size() + 1, Jump_Is_Equal, rterm1, aexpr, pFour);
		mFourElementTypeList.push_back(four);
		FourElementType four1(mFourElementTypeList.size() + 1, Jump, nullId, nullId, pFour);
		mFourElementTypeList.push_back(four1);
		rterm1.mType = 4;
		rterm1.mTC = mTC;
		rterm1.mFC = mFC;
	}
	return true;
}
/*
	aexpr -> term aexpr1
*/
bool SemanticAnalysis::semanticAnalysis_aexpr(list<Token>::iterator& itAnalysisCur, list<Token>& TokenenList, FourElementTypeItem& aexpr)
{
	if (!semanticAnalysis_term(itAnalysisCur, TokenenList, aexpr))	//term
	{
		return false;
	}
	if (!semanticAnalysis_aexpr1(itAnalysisCur, TokenenList, aexpr))	//aexpr1
	{
		return false;
	}
	return true;
}
/*
	aexpr1 -> + term aexpr1
	aexpr1 -> - term aexpr1
	aexpr1 -> $
*/
bool SemanticAnalysis::semanticAnalysis_aexpr1(list<Token>::iterator& itAnalysisCur, list<Token>& TokenenList, FourElementTypeItem& aexpr1)
{
	if (itAnalysisCur == TokenenList.end())
		return false;
	if ((*itAnalysisCur).type == Operator_Plus) // +
	{
		itAnalysisCur++;
		FourElementTypeItem term;
		if (!semanticAnalysis_term(itAnalysisCur, TokenenList, term))	//term
		{
			return false;
		}
		if (aexpr1.mType == 1 && term.mType == 1)
		{
			switch (aexpr1.mConstantType)
			{
			case 1:	//int
			{
				switch (term.mConstantType)
				{
				case 1:	//int
				{
					aexpr1.mConstantInteger += term.mConstantInteger;
					break;
				}
				case 2:	//float
				{
					aexpr1.mConstantType = 2;
					aexpr1.mConstantFloat = aexpr1.mConstantInteger + term.mConstantFloat;
					break;
				}
				case 3:	//char
				{
					aexpr1.mConstantInteger += term.mConstantChar;
					break;
				}
				default:
					break;
				}
				break;
			}
			case 2:	//float
			{
				switch (term.mConstantType)
				{
				case 1:	//int
				{
					aexpr1.mConstantFloat += term.mConstantInteger;
					break;
				}
				case 2:	//float
				{
					aexpr1.mConstantFloat += term.mConstantFloat;
					break;
				}
				case 3:	//char
				{
					aexpr1.mConstantFloat += term.mConstantChar;
					break;
				}
				default:
					break;
				}
				break;
			}
			case 3:	//char
			{
				switch (term.mConstantType)
				{
				case 1:	//int
				{
					aexpr1.mConstantType = 1;
					aexpr1.mConstantInteger = aexpr1.mConstantChar + term.mConstantInteger;
					break;
				}
				case 2:	//float
				{
					aexpr1.mConstantType = 2;
					aexpr1.mConstantFloat = aexpr1.mConstantChar + term.mConstantFloat;
					break;
				}
				case 3:	//char
				{
					aexpr1.mConstantType = 1;
					aexpr1.mConstantInteger = aexpr1.mConstantChar + term.mConstantChar;
					break;
				}
				default:
					break;
				}
				break;
			}
			default:
				break;
			}
		}
		else
		{
			FourElementTypeItem tempId = newTempIdentifier();
			FourElementType four(mFourElementTypeList.size() + 1, Plus, aexpr1, term, tempId);
			mFourElementTypeList.push_back(four);
			aexpr1 = tempId;
		}
		semanticAnalysis_aexpr1(itAnalysisCur, TokenenList, aexpr1);	//aexpr1
	}
	else if ((*itAnalysisCur).type == Operator_Minus) // -
	{
		itAnalysisCur++;
		FourElementTypeItem term;
		if (!semanticAnalysis_term(itAnalysisCur, TokenenList, term))	//term
		{
			return false;
		}
		if (aexpr1.mType == 1 && term.mType == 1)
		{
			switch (aexpr1.mConstantType)
			{
			case 1:	//int
			{
				switch (term.mConstantType)
				{
				case 1:	//int
				{
					aexpr1.mConstantInteger -= term.mConstantInteger;
					break;
				}
				case 2:	//float
				{
					aexpr1.mConstantType = 2;
					aexpr1.mConstantFloat = aexpr1.mConstantInteger - term.mConstantFloat;
					break;
				}
				case 3:	//char
				{
					aexpr1.mConstantInteger -= term.mConstantChar;
					break;
				}
				default:
					break;
				}
				break;
			}
			case 2:	//float
			{
				switch (term.mConstantType)
				{
				case 1:	//int
				{
					aexpr1.mConstantFloat -= term.mConstantInteger;
					break;
				}
				case 2:	//float
				{
					aexpr1.mConstantFloat -= term.mConstantFloat;
					break;
				}
				case 3:	//char
				{
					aexpr1.mConstantFloat -= term.mConstantChar;
					break;
				}
				default:
					break;
				}
				break;
			}
			case 3:	//char
			{
				switch (term.mConstantType)
				{
				case 1:	//int
				{
					aexpr1.mConstantType = 1;
					aexpr1.mConstantInteger = aexpr1.mConstantChar - term.mConstantInteger;
					break;
				}
				case 2:	//float
				{
					aexpr1.mConstantType = 2;
					aexpr1.mConstantFloat = aexpr1.mConstantChar - term.mConstantFloat;
					break;
				}
				case 3:	//char
				{
					aexpr1.mConstantType = 1;
					aexpr1.mConstantInteger = aexpr1.mConstantChar - term.mConstantChar;
					break;
				}
				default:
					break;
				}
				break;
			}
			default:
				break;
			}
		}
		else
		{
			FourElementTypeItem tempId = newTempIdentifier();
			FourElementType four(mFourElementTypeList.size() + 1, Minus, aexpr1, term, tempId);
			mFourElementTypeList.push_back(four);
			aexpr1 = tempId;
		}
		semanticAnalysis_aexpr1(itAnalysisCur, TokenenList, aexpr1);	//aexpr1
	}
	return true;
}
/*
	term -> factor term1
*/
bool SemanticAnalysis::semanticAnalysis_term(list<Token>::iterator& itAnalysisCur, list<Token>& TokenenList, FourElementTypeItem& term)
{
	if (!semanticAnalysis_factor(itAnalysisCur, TokenenList, term))//factor
	{
		return false;
	}
	if (!semanticAnalysis_term1(itAnalysisCur, TokenenList, term))	//term1
	{
		return false;
	}
	return true;
}
/*
	term1 -> * factor term1
	term1 -> / factor term1
	term1 -> % factor term1
	term1 -> $
*/
bool SemanticAnalysis::semanticAnalysis_term1(list<Token>::iterator& itAnalysisCur, list<Token>& TokenenList, FourElementTypeItem& term1)
{
	// 判断term1和factor是否都为常量，如果为常量则计算出它们的值
	//FourElementTypeItem term1;
	int op = 0;
	if (itAnalysisCur == TokenenList.end())
		return false;
	if ((*itAnalysisCur).type == Operator_Multiply || (*itAnalysisCur).type == Operator_Divide || (*itAnalysisCur).type == Operator_Mod)	// * / %
	{
		switch ((*itAnalysisCur).type)
		{
		case Operator_Multiply:
			op = Multiply;
			break;
		case Operator_Divide:
			op = Divide;
			break;
		case Operator_Mod:
			op = Mod;
			break;
		default:
			break;
		}
		itAnalysisCur++;
		FourElementTypeItem factor;
		semanticAnalysis_factor(itAnalysisCur, TokenenList, factor);//factor
		//factor.printFourElementTypeItem();
		//语义分析：运算符%的左右操作数必须都为int型
		if (factor.mType == 1 && term1.mType == 1)	//直接计算，将得到的结果赋值给term1
		{
			if (term1.mConstantType == 1)	//是否为int类型
			{
				switch (op)
				{
				case Multiply:
				{
					switch (factor.mConstantType)
					{
					case 1:	//int
						term1.mConstantInteger *= factor.mConstantInteger;
						break;
					case 2:	//float
					{
						term1.mConstantType = 2;
						term1.mConstantFloat = term1.mConstantInteger * factor.mConstantFloat;
						break;
					}
					case 3:	//char
					{
						term1.mConstantInteger *= factor.mConstantChar;
						break;
					}
					default:
						break;
					}
					break;
				}
				case Divide:
				{
					switch (factor.mConstantType)
					{
					case 1:	//int
						term1.mConstantInteger /= factor.mConstantInteger;
						break;
					case 2:	//float
					{
						term1.mConstantType = 2;
						term1.mConstantFloat = term1.mConstantInteger / factor.mConstantFloat;
						break;
					}
					case 3:	//char
						term1.mConstantInteger /= factor.mConstantChar;
						break;
					default:
						break;
					}
					break;
				}
				case Mod:
				{
					//运算符%右边应给为int类型
					switch (factor.mConstantType)
					{
					case 1:	//int
						term1.mConstantInteger %= factor.mConstantInteger;
						break;
					case 2:	//float
					{
						//运算符%右边应给为int类型
						mErrorInfo.push_back("运算符%右边操作数必须为int型");
						return false;	//返回
						break;
					}
					case 3:	//char
						term1.mConstantInteger %= factor.mConstantChar;
						break;
					default:
						break;
					}
					break;
				}
				default:
					break;
				}
			}
			else if (term1.mConstantType == 2) //是否为float类型
			{
				switch (op)
				{
				case Multiply:
				{
					switch (factor.mConstantType)
					{
					case 1:
						term1.mConstantFloat *= factor.mConstantInteger;
						break;
					case 2:
						term1.mConstantFloat *= factor.mConstantFloat;
						break;
					case 3:
						term1.mConstantFloat *= factor.mConstantChar;
						break;
					default:
						break;
					}
					break;
				}
				case Divide:
				{
					switch (factor.mConstantType)
					{
					case 1:
						term1.mConstantFloat /= factor.mConstantInteger;
						break;
					case 2:
						term1.mConstantFloat /= factor.mConstantFloat;
						break;
					case 3:
						term1.mConstantFloat /= factor.mConstantChar;
						break;
					default:
						break;
					}
					break;
				}
				case Mod:
				{
					//运算符%左边应给为int类型
					mErrorInfo.push_back("运算符%左边操作数必须为int型");
					return false;	//返回
					break;
				}
				default:
					break;
				}
			}
			else    //为char类型
			{
				switch (op)
				{
				case Multiply:
				{
					switch (factor.mConstantType)
					{
					case 1://int
					{
						term1.mConstantType = 1;
						term1.mConstantInteger = term1.mConstantChar * factor.mConstantInteger;
						break;
					}
					case 2: //float
					{
						term1.mConstantType = 2;
						term1.mConstantFloat = term1.mConstantChar * factor.mConstantFloat;
						break;
					}
					case 3:	//char
					{
						term1.mConstantType = 1;
						term1.mConstantInteger = term1.mConstantChar * factor.mConstantChar;
						break;
					}
					default:
						break;
					}
					break;
				}
				case Divide:
				{
					switch (factor.mConstantType)
					{
					case 1://int
					{
						term1.mConstantType = 1;
						term1.mConstantInteger = term1.mConstantChar / factor.mConstantInteger;
						break;
					}
					case 2: //float
					{
						term1.mConstantType = 2;
						term1.mConstantFloat = term1.mConstantChar / factor.mConstantFloat;
						break;
					}
					case 3:	//char
					{
						term1.mConstantType = 1;
						term1.mConstantInteger = term1.mConstantChar / factor.mConstantChar;
						break;
					}
					default:
						break;
					}
					break;
				}
				case Mod:
				{
					switch (factor.mConstantType)
					{
					case 1://int
					{
						term1.mConstantType = 1;
						term1.mConstantInteger = term1.mConstantChar % factor.mConstantInteger;
						break;
					}
					case 2: //float
					{
						//运算符%右边应给为int类型
						mErrorInfo.push_back("运算符%右边操作数必须为int型");
						return false;	//返回
						break;
					}
					case 3:	//char
					{
						term1.mConstantType = 1;
						term1.mConstantInteger = term1.mConstantChar % factor.mConstantChar;
						break;
					}
					default:
						break;
					}
					break;
				}
				default:
					break;
				}
			}
		}
		else
		{
			FourElementTypeItem tempId = newTempIdentifier();
			//这个位置要检查 term1 和 factor定义类型，尤其是运算符%
			FourElementType four(mFourElementTypeList.size() + 1, op, term1, factor, tempId);
			mFourElementTypeList.push_back(four);
			term1 = tempId;
		}
		semanticAnalysis_term1(itAnalysisCur, TokenenList, term1);	//term1
	}
	return true;
}
/*
	factor -> ! ael
	factor -> ael
*/
bool SemanticAnalysis::semanticAnalysis_factor(list<Token>::iterator& itAnalysisCur, list<Token>& TokenenList, FourElementTypeItem& factor)
{
	bool isNot = false;
	if (itAnalysisCur == TokenenList.end())
		return false;
	if ((*itAnalysisCur).type == Operator_Not)	// !
	{
		itAnalysisCur++;
		isNot = true;
	}
	FourElementTypeItem ael;
	if (!semanticAnalysis_ael(itAnalysisCur, TokenenList, ael))
	{
		return false;
	}
	factor = ael;
	if (isNot)
	{
		switch (ael.mType)
		{
		case 1://常量
		{
			switch (ael.mConstantType)
			{
			case 1://整型
				ael.mConstantInteger == 0 ? ael.mConstantInteger = 1 : ael.mConstantInteger = 0;
				break;
			case 2://浮点型
				ael.mConstantFloat == 0.0 ? ael.mConstantFloat = 1.0 : ael.mConstantFloat == 0.0;
				break;
			case 3://字符型
				ael.mConstantChar == 0 ? ael.mConstantChar = 1 : ael.mConstantChar = 0;
				break;
			default:
				break;
			}
			factor = ael;
			break;
		}
		case 2:	//用户定义的变量
		{
			FourElementTypeItem tempId = newTempIdentifier();
			FourElementTypeItem nullId;
			FourElementType four(mFourElementTypeList.size() + 1, IsNot, ael, nullId, tempId);
			mFourElementTypeList.push_back(four);
			factor = tempId;
			break;
		}
		case 3:	//临时变量
		{
			FourElementTypeItem tempId = newTempIdentifier();
			FourElementTypeItem nullId;
			FourElementType four(mFourElementTypeList.size() + 1, IsNot, ael, nullId, tempId);
			mFourElementTypeList.push_back(four);
			factor = tempId;
			break;
		}
		case 4:	//BOOL变量
		{
			int mTC = factor.mTC;
			int mFC = factor.mFC;
			factor.mTC = mFC;
			factor.mFC = mTC;
		}
		default:
			break;
		}
	}
	return true;
}
/*
	ael -> ( bexpr )
	ael -> root
*/
bool SemanticAnalysis::semanticAnalysis_ael(list<Token>::iterator& itAnalysisCur, list<Token>& TokenenList, FourElementTypeItem& ael)
{
	if (itAnalysisCur == TokenenList.end())
		return false;
	if ((*itAnalysisCur).type == Delimiter_Left_Small_Bracket)	//左小括号
	{
		itAnalysisCur++;
		// bexpr
		semanticAnalysis_bexpr(itAnalysisCur, TokenenList, ael);	//bexpr
		if (itAnalysisCur == TokenenList.end())
			return false;
		if ((*itAnalysisCur).type == Delimiter_Right_Small_Bracket)	//右小括号
		{
			itAnalysisCur++;
		}
	}
	else
	{
		semanticAnalysis_root(itAnalysisCur, TokenenList, ael);
	}
	return true;
}


/*
	root -> id
	root -> 整型(八进制、十进制、十六进制)
	root -> 浮点型( 小数、指数 )
	root -> BOOL 布尔型
	root -> 字符型
	//root -> 字符串型 这在print位置用到
*/
bool SemanticAnalysis::semanticAnalysis_root(list<Token>::iterator& itAnalysisCur, list<Token>& TokenenList, FourElementTypeItem& root)
{
	if (itAnalysisCur == TokenenList.end())
		return false;
	if ((*itAnalysisCur).type == Identifier)	//id
	{
		if (!isUserVariableDefinition((*itAnalysisCur).data))
		{
			mErrorInfo.push_back("变量 \"" + (*itAnalysisCur).data + "\" 未定义");
		}
		root.mType = 2;	//用户定义的变量
		root.mUserIdentifierName = (*itAnalysisCur).data;
		itAnalysisCur++;
	}
	else if ((*itAnalysisCur).type == Character)	//字符
	{
		root.mType = 1;	//常量
		root.mConstantType = 3;	//字符型
		root.mConstantChar = stringConvertCharacter((*itAnalysisCur).data);
		itAnalysisCur++;
	}
	else if ((*itAnalysisCur).type == String)	//字符串
	{
		//不分析这个地方，字符串就是N个字符的组合
		itAnalysisCur++;
	}
	else if ((*itAnalysisCur).type == Number_Octonary)	//整型 八进制
	{
		root.mCacheBuffer = (*itAnalysisCur).data;	//整型的字符串形式添加到缓存中
		root.mType = 1;//常量
		root.mConstantType = 1;	//整型
		root.mConstantInteger = stringConvertNumberOctonary((*itAnalysisCur).data);
		itAnalysisCur++;
	}
	else if ((*itAnalysisCur).type == Number_Decimalism)	//整型 十进制
	{
		root.mCacheBuffer = (*itAnalysisCur).data;	//整型的字符串形式添加到缓存中
		root.mType = 1;//常量
		root.mConstantType = 1;	//整型
		root.mConstantInteger = stringConvertNumberDecimalism((*itAnalysisCur).data);
		itAnalysisCur++;
	}
	else if ((*itAnalysisCur).type == Number_Hexadecimal)	//整型 十六进制
	{
		root.mCacheBuffer = (*itAnalysisCur).data;	//整型的字符串形式添加到缓存中
		root.mType = 1;//常量
		root.mConstantType = 1;	//整型
		root.mConstantInteger = stringConvertNumberHexadecimal((*itAnalysisCur).data);
		itAnalysisCur++;
	}
	else if ((*itAnalysisCur).type == Number_Decimals)	//浮点型 小数
	{
		itAnalysisCur++;
	}
	else if ((*itAnalysisCur).type == Number_Exponent)	//浮点型 指数
	{
		itAnalysisCur++;
	}
	else if (semanticAnalysis_BOOL(itAnalysisCur, TokenenList, root))
	{
	}
	else
	{
		return false;
	}
	//root.printFourElementTypeItem();
	return true;
}
/*
	BOOL -> true
	BOOL -> false
*/
bool SemanticAnalysis::semanticAnalysis_BOOL(list<Token>::iterator& itAnalysisCur, list<Token>& TokenenList, FourElementTypeItem& BOOL)
{
	if (itAnalysisCur == TokenenList.end())
		return false;
	if ((*itAnalysisCur).type == Keyword_true)
	{
		itAnalysisCur++;
		BOOL.mType = 1;	//常量
		BOOL.mConstantType = 1;	//整型
		BOOL.mConstantInteger = 1;
	}
	else if ((*itAnalysisCur).type == Keyword_false)
	{
		itAnalysisCur++;
		BOOL.mType = 1;	//常量
		BOOL.mConstantType = 1;	//整型
		BOOL.mConstantInteger = 0;
	}
	else
	{
		return false;
	}
	return true;
}

bool SemanticAnalysis::expressPreAnalysis(int type)
{
	// ! ( id 整型(八，十，十六) 浮点(小，指) true false char
	if (type == Operator_Not || type == Identifier || type == Number_Octonary
		|| type == Number_Decimalism || type == Number_Hexadecimal || type == Number_Decimals
		|| type == Number_Exponent || type == Keyword_true || type == Keyword_false || type == Character)
	{
		return true;
	}
	return false;
}

bool SemanticAnalysis::isUserVariableDefinition(string variableName)
{
	list<VariableDefinition>::iterator it = mVariableDefinitionList.begin();
	for (; it != mVariableDefinitionList.end(); it++)
	{
		list<VariableList>::iterator it_vl = (*it).variableList.begin();
		for (; it_vl != (*it).variableList.end(); it_vl++)
		{
			if ((*it_vl).varName == variableName)
			{
				return true;
			}
		}
	}
	return false;
}
// true-重复 false-不重复
bool SemanticAnalysis::isRepetDefineVariable(string variableName, bool isGlobal)
{
	list<VariableDefinition>::iterator it = mVariableDefinitionList.begin();
	for (; it != mVariableDefinitionList.end(); it++)
	{
		list<VariableList>::iterator it_vl = (*it).variableList.begin();
		for (; it_vl != (*it).variableList.end(); it_vl++)
		{
			if ((*it_vl).varName == variableName)
			{
				if (isGlobal && (*it).actionScope == "@Global")
				{
					return true;
				}
				else if (!isGlobal && (*it).actionScope != "@Global")
				{
					return true;
				}
			}
		}
	}
	list<string>::iterator it_cache = variableCache.begin();
	for (; it_cache != variableCache.end(); it_cache++)
	{
		if ((*it_cache) == variableName)
		{
			return true;
		}
	}
	return false;
}
//判断函数声明和函数实现是否匹配
// true-匹配 false-不匹配
bool SemanticAnalysis::isMatchFunctionComeTrueAndDefine(FunctionDefinition fd)
{
	//函数名相同 返回值类型相同 参数个数相同 每个参数类型相同
	list<FunctionDefinition>::iterator it = mFunctionDefinitionList.begin();
	for (; it != mFunctionDefinitionList.end(); it++)
	{
		bool isMatch = false;
		if ((*it).functionName == fd.functionName && (*it).returnType == fd.returnType && (*it).parameterList.size() == fd.parameterList.size())
		{
			isMatch = true;
			list<ParameterList>::iterator it_it = (*it).parameterList.begin();
			list<ParameterList>::iterator it_fd = fd.parameterList.begin();
			for (unsigned int i = 0; i < fd.parameterList.size(); i++)
			{
				if ((*it_it).parameterType != (*it_fd).parameterType)
				{
					isMatch = false;
					break;
				}
			}
		}
		if (isMatch)
		{
			if ((*it).isComeTrue == fd.isComeTrue)
			{
				//重复定义的错误
				mErrorInfo.push_back("函数 " + fd.functionName + " 重复定义");
			}
			if (fd.isComeTrue)	//是函数实现
				(*it).funcEnter = fd.funcEnter;
			return true;	//存在[有可能是重复定义，不添加到list中]
		}
	}
	return false;
}
