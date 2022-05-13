#include "grammarAnalysis.h"
#include "symbol.h"

GrammarAnalysis::GrammarAnalysis()
{
	grammarTree = new Tree();
	count = 0;
	analysis_express_using_LL1 = false;
	analysis_function_body_using_LL1 = false;
	analysis_miniC_using_LL1 = false;
	// LL_1_Analysis
	//grammar_for_miniC_2 = new LL_1_Analysis("grammar\\grammar_for_miniC_2.txt");
	//grammar_for_miniC = new LL_1_Analysis("grammar\\grammar_for_miniC.txt");
	//grammar_for_function_body = new LL_1_Analysis("grammar\\grammar_for_function_body.txt");
	//grammar_for_expression = new LL_1_Analysis("grammar\\grammar_for_expression.txt");
	
}

GrammarAnalysis::~GrammarAnalysis()
{
	delete grammarTree;
	//delete grammar_for_miniC;
	//delete grammar_for_function_body;
	//delete grammar_for_expression;
	//delete grammar_for_miniC_2;
}
//1.
//仅使用LL1预测分析，分析miniC语言（不能包含全局变量）
bool GrammarAnalysis::grammarAnalysisUsingLL1WithoutGlobalVariable(list<Token>& listToken)
{
	ofstream fout("analysis\\grammarAnalysisUsingLL1.txt");
	grammar_for_miniC = new LL_1_Analysis("grammar\\grammar_for_miniC.txt");
	fout << "********************************************" << endl;
	fout << "*        LL1预测分析,不分析全局变量        *" << endl;
	fout << "********************************************" << endl;
	if ((*grammar_for_miniC).runGrammarAnalysis(listToken))
	{
		//cout << endl << "分析成功" << endl << endl;
		//(*grammar_for_miniC).printAnalysisResult();
		(*grammar_for_miniC).saveAnalysisResultToFile(fout);	//将LL1预测分析结果保存在文件中
		//return true;
	}
	else
	{
		//cout << endl << "语法分析错误" << endl << endl;
		delete grammar_for_miniC;
		return false;
	}
	delete grammar_for_miniC;
	fout.close();
	return true;
}
//2.
//使用递归下降和LL1预测分析，分析miniC语言，LL1分析 函数体
bool GrammarAnalysis::grammarAnalysisUsingRecursiveDescentAndLL1_1(list<Token>& listToken)
{
	outAnalysisFile.open("analysis\\grammarAnalysisUsingRecursiveDescentAndLL1_1.txt");
	grammar_for_function_body = new LL_1_Analysis("grammar\\grammar_for_function_body.txt");
	analysis_function_body_using_LL1 = true;
	outAnalysisFile << "********************************************" << endl;
	outAnalysisFile << "*  LL1预测分析函数定义、实现，全局变量定义 *" << endl;
	outAnalysisFile << "*            递归下降分析函数体            *" << endl;
	outAnalysisFile << "********************************************" << endl;
	list<Token>::iterator it_AnalysisCur = listToken.begin();
	grammarTree->root->data = "语法分析树";	//语法分析树初始化
	if (grammarAnalysisS(it_AnalysisCur, listToken, grammarTree->root))
	{
		//cout << endl << "分析成功" << endl << endl;
		//return true;
	}
	else
	{
		//cout << endl << "语法分析错误" << endl << endl;
		delete grammar_for_function_body;
		return false;
	}
	delete grammar_for_function_body;
	outAnalysisFile.close();
	return true;
}
//3.
//使用递归下降和LL1预测分析，分析miniC语言，LL1仅分析 表达式
bool GrammarAnalysis::grammarAnalysisUsingRecursiveDescentAndLL1_2(list<Token>& listToken)
{
	outAnalysisFile.open("analysis\\grammarAnalysisUsingRecursiveDescentAndLL1_2.txt");
	grammar_for_expression = new LL_1_Analysis("grammar\\grammar_for_expression.txt");
	analysis_express_using_LL1 = true;
	outAnalysisFile << "********************************************" << endl;
	outAnalysisFile << "*             LL1预测分析表达式            *" << endl;
	outAnalysisFile << "*            递归下降分析其他语法          *" << endl;
	outAnalysisFile << "********************************************" << endl;
	list<Token>::iterator it_AnalysisCur = listToken.begin();
	grammarTree->root->data = "语法分析树";	//语法分析树初始化
	if (grammarAnalysisS(it_AnalysisCur, listToken, grammarTree->root))
	{
		//cout << endl << "分析成功" << endl << endl;
		//return true;
	}
	else
	{
		//cout << endl << "语法分析错误" << endl << endl;
		delete grammar_for_expression;
		return false;
	}
	delete grammar_for_expression;
	outAnalysisFile.close();
	return true;
}
//4.
//仅使用递归下降分析miniC语言
bool GrammarAnalysis::grammarAnalysisUsingRecursiveDescent(list<Token>& TokenenList)
{
	outAnalysisFile.open("analysis\\grammarAnalysisUsingRecursiveDescent.txt");
	outAnalysisFile << "********************************************" << endl;
	outAnalysisFile << "*             递归下降语法分析             *" << endl;
	outAnalysisFile << "********************************************" << endl;

	list<Token>::iterator it_AnalysisCur = TokenenList.begin();
	grammarTree->root->data = "语法分析树";	//语法分析树初始化
	if (grammarAnalysisS(it_AnalysisCur, TokenenList, grammarTree->root))
	{
		//cout << endl << "分析成功" << endl << endl;
		//ll1.printAnalysisResult();
		//grammar_for_function_body.printAnalysisResult();
		//return true;
	}
	else
	{
		//cout << endl << "语法分析错误" << endl << endl;
		return false;
	}
	outAnalysisFile.close();
	return true;
}
//5.
//使用LL1预测分析法按照更新后的文法分析
bool GrammarAnalysis::grammarAnalysisUsingLL1_2(list<Token>& listToken)
{
	//analysis\\grammarAnalysisUsingLL1_2.txt
	grammar_for_miniC_2 = new LL_1_Analysis("grammar\\grammar_for_miniC_2.txt");
	ofstream fout("analysis\\grammarAnalysisUsingLL1_2.txt");
	fout << "********************************************" << endl;
	fout << "*         LL1预测分析,更新后的文法         *" << endl;
	fout << "********************************************" << endl;
	if ((*grammar_for_miniC_2).runGrammarAnalysis(listToken))
	{
		//cout << endl << "LL1预测分析使用更新后的文法，分析成功" << endl << endl;
		//(*grammar_for_miniC_2).printAnalysisResult();
		(*grammar_for_miniC_2).saveAnalysisResultToFile(fout);
	}
	else
	{
		//cout << endl << "语法分析错误" << endl << endl;
		delete grammar_for_miniC_2;
		return false;
	}
	delete grammar_for_miniC_2;
	fout.close();
	return true;
}

void GrammarAnalysis::printGrammarTree()
{
	grammarTree->printTree(grammarTree->root);
}
//---------------------------------------------------------------------------------------------------
// 全局变量定义、函数声明、函数实现
//---------------------------------------------------------------------------------------------------
/*
	S -> $
	S -> F S
*/
bool GrammarAnalysis::grammarAnalysisS(list<Token>::iterator & it_AnalysisCur, list<Token>& listToken, Node* node)
{
	if (it_AnalysisCur == listToken.end())
	{
		outAnalysisFile << "G: S -> $" << endl;
		return true;
	}
	else
	{
		outAnalysisFile << "G: S -> F S" << endl;
		if (!grammarAnalysisF(it_AnalysisCur, listToken, node))
		{
			outAnalysisFile << "E: 分析 F 出错" << endl;
			return false;
		}
		if (!grammarAnalysisS(it_AnalysisCur, listToken, node))
		{
			outAnalysisFile << "E: 分析 S 出错" << endl;
			return false;
		}
	}
	return true;
}
/*
	F -> MT1 DT F1
*/
bool GrammarAnalysis::grammarAnalysisF(list<Token>::iterator & it_AnalysisCur, list<Token>& listToken, Node* node)
{
	outAnalysisFile << "G: F -> MT1 DT F1" << endl;
	GrammarTreeTmp grammarTreeTmp;
	// 分析 MT1
	int memoryType = Keyword_extern;
	if (grammarAnalysisMT1(it_AnalysisCur, listToken, memoryType))
	{
		//cout << "分析MT1成功" << endl;
	}
	// 分析 DT
	int dataType = Error;
	if (grammarAnalysisDT(it_AnalysisCur, listToken, dataType))
	{
		//cout << "分析DT成功" << endl;
	}
	grammarTreeTmp.dataType = dataType;
	// 分析 F1
	if (!grammarAnalysisF1(it_AnalysisCur, listToken, grammarTreeTmp))
	{
		outAnalysisFile << "E: 分析 F1 出错" << endl;
		return false;
	}
	switch (grammarTreeTmp.tmpType)
	{
	case 1:
	{
		VariableDefinition *vd = new VariableDefinition(grammarTreeTmp);
		node->addChildToRoot(vd);
		break;
	}
	case 2:	//函数声明
	{
		FunctionDefinition *fd = new FunctionDefinition(grammarTreeTmp);
		(*fd).isComeTrue = false;
		node->addChildToRoot(fd);
		break;
	}
	case 3:	//函数实现
	{
		FunctionDefinition *fd = new FunctionDefinition(grammarTreeTmp);
		(*fd).isComeTrue = true;
		node->addChildToRoot(fd);
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
bool GrammarAnalysis::grammarAnalysisF1(list<Token>::iterator & it_AnalysisCur, list<Token>& listToken, GrammarTreeTmp& tmp)
{
	string functionName = (*it_AnalysisCur).data;
	// 分析 ID 和 左小括号
	if ((*it_AnalysisCur).type == Identifier && (++it_AnalysisCur) != listToken.end() &&
		(*it_AnalysisCur).type == Delimiter_Left_Small_Bracket)	// id ( 左小括号
	{
		outAnalysisFile << "G: F1 -> functionName ( PL ) F2" << endl;
		//cout << "函数名：" << functionName << endl;
		outAnalysisFile << "1> 分析出 functionName " << functionName << endl;
		outAnalysisFile << "1> 分析出 (" << endl;
		tmp.functionName = functionName;	//将函数名加载到tmp中去
		it_AnalysisCur++;	//更新当前分析Tokenen串的位置
							//分析 PL
		if (!grammarAnalysisPL(it_AnalysisCur, listToken, tmp.parameterList))	//分析PL，出错
		{
			outAnalysisFile << "E: 分析 PL 出错" << endl;
			return false;
		}
		//分析 右小括号
		if (it_AnalysisCur == listToken.end())
		{
			outAnalysisFile << "E: 已经分析到Tokenen串的末尾" << endl;
			return false;
		}
		if ((*it_AnalysisCur).type != Delimiter_Right_Small_Bracket)	// ) 右小括号
		{
			outAnalysisFile << "E: 分析 ) 出错" << endl;
			return false;
		}
		outAnalysisFile << "1> 分析出 )" << endl;
		it_AnalysisCur++;	//更新当前分析Tokenen串的位置
		if (!grammarAnalysisF2(it_AnalysisCur, listToken, tmp))	//分析函数体
		{
			outAnalysisFile << "E: 分析 F2 出错" << endl;
			return false;
		}
	}
	else // F1 -> VL ;
	{
		outAnalysisFile << "G: F1 -> VL ;" << endl;
		--it_AnalysisCur;	//返回之前分析Tokenen串的位置
							//分析VL
		tmp.tmpType = 1;	//外部数据定义
		if (!grammarAnalysisVL(it_AnalysisCur, listToken, tmp.variableList))
		{
			outAnalysisFile << "E: 分析 VL 出错" << endl;
			return false;
		}
		if (it_AnalysisCur == listToken.end())	//分析到函数末尾
		{
			outAnalysisFile << "E: 已经分析到Tokenen串的末尾" << endl;
			return false;
		}
		//分析分好 ;
		if (Delimiter_Semicolon != (*it_AnalysisCur).type)
		{
			outAnalysisFile << "E: 分析 ; 出错" << endl;
			return false;
		}
		outAnalysisFile << "1> 分析出 ;" << endl;
		it_AnalysisCur++;
	}
	return true;
}
/*
	F2 -> { FB }
	F2 -> ;
*/
bool GrammarAnalysis::grammarAnalysisF2(list<Token>::iterator& it_AnalysisCur, list<Token>& listToken, GrammarTreeTmp& tmp)
{
	if (it_AnalysisCur == listToken.end())//当前分析位置是否存在
	{
		outAnalysisFile << "E: 已经分析到Tokenen串的末尾" << endl;
		return false;
	}
	if ((*it_AnalysisCur).type == Delimiter_Semicolon)	//是否为分好
	{
		outAnalysisFile << "G: F2 -> ;" << endl;
		tmp.tmpType = 2;	//函数声明
							//cout << "函数声明分析结束" << endl;
		it_AnalysisCur++;	//更新当前分析Tokenen串的位置
	}
	else if ((*it_AnalysisCur).type == Delimiter_Left_Large_Bracket)	//是否为左大括号
	{
		outAnalysisFile << "G: F2 -> { FB }" << endl;
		it_AnalysisCur++;	//更新当前分析Tokenen串的位置
		tmp.tmpType = 3;	//函数实现
		if (analysis_function_body_using_LL1)
		{
			list<Token> tempList;
			int countFindRightLargeBracket = 0;	//找到右大括号的个数
			while (it_AnalysisCur != listToken.end())
			{
				if ((*it_AnalysisCur).type == Delimiter_Right_Large_Bracket)	//是否为右大括号
				{	//跳出while循环，更新当前分析Tokenen串的位置
					countFindRightLargeBracket++;	//找到右大括号
					if (countFindRightLargeBracket == 1)
					{
						it_AnalysisCur++;	//更新当前分析Tokenen串的位置
						break;
					}
					else
					{
						tempList.push_back(*it_AnalysisCur);	//将Tokenen串添加到List缓存中
						it_AnalysisCur++;	//更新当前分析Tokenen串的位置
					}
				}
				else if ((*it_AnalysisCur).type == Delimiter_Left_Large_Bracket)	//是否为左大括号
				{
					tempList.push_back(*it_AnalysisCur);	//将Tokenen串添加到List缓存中
					it_AnalysisCur++;	//更新当前分析Tokenen串的位置
					countFindRightLargeBracket--;
				}
				else
				{
					tempList.push_back(*it_AnalysisCur);	//将Tokenen串添加到List缓存中
					it_AnalysisCur++;	//更新当前分析Tokenen串的位置
				}
			}
			if (!(*grammar_for_function_body).runGrammarAnalysis(tempList))
			{
				//cout << "函数体存在错误" << endl;
				(*grammar_for_function_body).printAnalysisResult();
				return false;
			}
			(*grammar_for_function_body).saveAnalysisResultToFile(outAnalysisFile);
			if (countFindRightLargeBracket != 1)
			{
				//cout << "缺少右大括号" << endl;
			}
		}
		else
		{
			// FB
			if (!grammarAnalysisFB(it_AnalysisCur, listToken))
			{
				outAnalysisFile << "E: 分析 FB 出错" << endl;
				return false;
			}
			// } 右大括号
			if (it_AnalysisCur == listToken.end())	//分析到函数末尾
			{
				outAnalysisFile << "E: 已经分析到Tokenen串的末尾" << endl;
				return false;
			}
			if ((*it_AnalysisCur).type != Delimiter_Right_Large_Bracket)	//是否为右大括号
			{
				outAnalysisFile << "E: 分析 } 出错" << endl;
				return false;
			}
			it_AnalysisCur++;//更新当前分析Tokenen串的位置
			outAnalysisFile << "1> 分析出 }" << endl;
		}
	}
	return true;
}
/*
	MT -> auto
	MT -> register
	MT -> MT1
*/
bool GrammarAnalysis::grammarAnalysisMT(list<Token>::iterator & it_AnalysisCur, list<Token>& listToken, int & memoryType)
{
	if (it_AnalysisCur == listToken.end())	//当前分析位置是否存在
	{
		outAnalysisFile << "E: 已经分析到Tokenen串的末尾" << endl;
		return false;
	}
	if ((*it_AnalysisCur).type == Keyword_auto)	//auto
	{
		outAnalysisFile << "G: MT -> auto" << endl;
		outAnalysisFile << "1> 分析出 auto" << endl;
		memoryType = Keyword_auto;
		it_AnalysisCur++;	//更新当前分析Tokenen串的位置
		return true;
	}
	else if ((*it_AnalysisCur).type == Keyword_register)
	{
		outAnalysisFile << "G: MT -> register" << endl;
		outAnalysisFile << "1> 分析出 register" << endl;
		memoryType = Keyword_register;
		it_AnalysisCur++;	//更新当前分析Tokenen串的位置
		return true;
	}
	else if (grammarAnalysisMT1(it_AnalysisCur, listToken, memoryType))
	{
		return true;
	}
	else
	{
		outAnalysisFile << "E: 分析 MT1 出错" << endl;
		return false;
	}
}
/*
	MT1 -> extern
	MT1 -> static
	MT1 -> $
*/
bool GrammarAnalysis::grammarAnalysisMT1(list<Token>::iterator & it_AnalysisCur, list<Token>& listToken, int& memoryType)
{
	if (it_AnalysisCur == listToken.end())	//当前分析位置是否存在
	{
		outAnalysisFile << "E: 已经分析到Tokenen串的末尾" << endl;
		return false;
	}
	if ((*it_AnalysisCur).type == Keyword_extern)
	{
		outAnalysisFile << "G: MT1 -> extern" << endl;
		outAnalysisFile << "1> 分析出 extern" << endl;
		memoryType = Keyword_extern;
		it_AnalysisCur++;	//更新当前分析Tokenen串的位置
		return true;
	}
	else if ((*it_AnalysisCur).type == Keyword_static)
	{
		outAnalysisFile << "G: MT1 -> static" << endl;
		outAnalysisFile << "1> 分析出 static" << endl;
		memoryType = Keyword_static;
		it_AnalysisCur++;	//更新当前分析Tokenen串的位置
		return true;
	}
	outAnalysisFile << "G: MT1 -> $" << endl;
	return true;
}
/*
	DT -> void
	DT -> int
	DT -> char
	DT -> float
	DT -> double
*/
bool GrammarAnalysis::grammarAnalysisDT(list<Token>::iterator & it_AnalysisCur, list<Token>& listToken, int& dataType)
{
	if (it_AnalysisCur == listToken.end())//当前分析位置是否存在
	{
		outAnalysisFile << "已经分析到Tokenen串的末尾" << endl;
		return false;
	}
	if ((*it_AnalysisCur).type == Keyword_void)
	{
		outAnalysisFile << "G: DT -> void" << endl;
		outAnalysisFile << "1> 分析出 void" << endl;
		dataType = Keyword_void;
		it_AnalysisCur++;	//更新当前分析Tokenen串的位置
		return true;
	}
	else if ((*it_AnalysisCur).type == Keyword_int)
	{
		outAnalysisFile << "G: DT -> int" << endl;
		outAnalysisFile << "1> 分析出 int" << endl;
		dataType = Keyword_int;
		it_AnalysisCur++;	//更新当前分析Tokenen串的位置
		return true;
	}
	else if ((*it_AnalysisCur).type == Keyword_char)
	{
		outAnalysisFile << "G: DT -> char" << endl;
		outAnalysisFile << "1> 分析出 char" << endl;
		dataType = Keyword_char;
		it_AnalysisCur++;	//更新当前分析Tokenen串的位置
		return true;
	}
	else if ((*it_AnalysisCur).type == Keyword_float)
	{
		outAnalysisFile << "G: DT -> float" << endl;
		outAnalysisFile << "1> 分析出 float" << endl;
		dataType = Keyword_float;
		it_AnalysisCur++;	//更新当前分析Tokenen串的位置
		return true;
	}
	else if ((*it_AnalysisCur).type == Keyword_double)
	{
		outAnalysisFile << "G: DT -> double" << endl;
		outAnalysisFile << "1> 分析出 double" << endl;
		dataType = Keyword_double;
		it_AnalysisCur++;	//更新当前分析Tokenen串的位置
		return true;
	}
	return false;
}
/*
	VL -> VD VL1
*/
bool GrammarAnalysis::grammarAnalysisVL(list<Token>::iterator & it_AnalysisCur, list<Token>& listToken, list<VariableList>& variableList)
{
	outAnalysisFile << "G: VL -> VD VL1" << endl;
	//分析VD
	VariableList variable;
	if (!grammarAnalysisVD(it_AnalysisCur, listToken, variable))
	{
		outAnalysisFile << "E: 分析 VD 出错" << endl;
		return false;
	}
	variableList.push_back(variable);
	//分析VL1
	if (!grammarAnalysisVL1(it_AnalysisCur, listToken, variableList))
	{
		outAnalysisFile << "E: 分析 VL1 出错" << endl;
		return false;
	}
	return true;
}
/*
	VL1 -> , VD VL1
	VL1 -> $
*/
bool GrammarAnalysis::grammarAnalysisVL1(list<Token>::iterator & it_AnalysisCur, list<Token>& listToken, list<VariableList>& variableList)
{
	//判断是否分析到末尾
	if (it_AnalysisCur == listToken.end())
	{
		outAnalysisFile << "E: 已经分析到Tokenen串的末尾" << endl;
		return false;
	}
	// VL1 -> , VD VL1
	//分析是否为逗号 ,
	if (Delimiter_Comma == (*it_AnalysisCur).type)
	{
		outAnalysisFile << "G: VL1 -> , VD VL1" << endl;
		it_AnalysisCur++;//更新当前分析Tokenen串的位置
						 //分析VL1
		VariableList variable;
		if (!grammarAnalysisVD(it_AnalysisCur, listToken, variable))
		{
			outAnalysisFile << "E: 分析 VD 出错" << endl;
			return false;
		}
		variableList.push_back(variable);
		if (!grammarAnalysisVL1(it_AnalysisCur, listToken, variableList))
		{
			outAnalysisFile << "E: 分析 VL1 出错" << endl;
			return false;
		}
		return true;
	}
	else
	{
		// VL1 -> $
		outAnalysisFile << "G: VL1 -> $" << endl;
		return true;
	}
}
/*
	VD -> variableName VD1
*/
bool GrammarAnalysis::grammarAnalysisVD(list<Token>::iterator & it_AnalysisCur, list<Token>& listToken, VariableList& variable)
{
	//是否分析到Tokenen串的末尾
	if (it_AnalysisCur == listToken.end())	//没有分析到末尾
	{
		outAnalysisFile << "E; 已经分析到Tokenen串的末尾" << endl;
		return false;
	}
	//判断是否为ID
	if (Identifier == (*it_AnalysisCur).type)
	{
		outAnalysisFile << "1> 分析出 variableName " << (*it_AnalysisCur).data << endl;
		variable.varName = (*it_AnalysisCur).data;
		it_AnalysisCur++;//更新当前分析Tokenen串的位置
						 //分析VD1
		if (!grammarAnalysisVD1(it_AnalysisCur, listToken, variable.initValue))
		{
			outAnalysisFile << "E: 分析 VD1 出错" << endl;
			return false;
		}
	}
	return true;
}

/*
	VD1 -> = PR (后面通常是以 逗号 或 分号 结束的)
	VD1 -> $
*/
bool GrammarAnalysis::grammarAnalysisVD1(list<Token>::iterator & it_AnalysisCur, list<Token>& listToken, list<Token>& initValue)
{
	//判断是否分析到Tokenen串的末尾
	if (it_AnalysisCur == listToken.end())	//没有分析到末尾
	{
		outAnalysisFile << "E: 已经分析到Tokenen串的末尾" << endl;
		return false;
	}
	// VD1 -> = PR
	//分析是否为等号 =
	if (Operator_Equal == (*it_AnalysisCur).type)	//为等号
	{
		outAnalysisFile << "G: VD1 -> = PR" << endl;
		outAnalysisFile << "1> 分析出 =" << endl;
		//使用LL(1)预测分析法分析表达式
		if (analysis_express_using_LL1)
		{
			list<Token> tmpList;
			tmpList.push_back(*(--it_AnalysisCur));  //将Id添加到List中
			++it_AnalysisCur;
			tmpList.push_back(*it_AnalysisCur); //将赋值符号添加到List中
			it_AnalysisCur++;//更新当前分析Tokenen串的位置
							 //分析PR
			while (it_AnalysisCur != listToken.end())
			{
				if ((*it_AnalysisCur).type == Delimiter_Semicolon || (*it_AnalysisCur).type == Delimiter_Comma)	//逗号 或 分号
				{
					break;
				}
				tmpList.push_back(*it_AnalysisCur); //复制到List中
				initValue.push_back(*it_AnalysisCur);
				it_AnalysisCur++; //更新当前分析Tokenen串的位置
			}
			if ((*grammar_for_expression).runGrammarAnalysis(tmpList))
			{
				//cout << endl << "分析PR成功" << endl;
				(*grammar_for_expression).saveAnalysisResultToFile(outAnalysisFile);
			}
			else
			{
				//cout << endl << "分析PR，存在语法错误" << endl;
				return false;
			}
		}
		//使用递归下降的方法分析表达式
		else
		{
			it_AnalysisCur++; //更新当前分析Tokenen串的位置
			if (!grammarAnalysis_bexpr(it_AnalysisCur, listToken))
			{
				outAnalysisFile << "E: 分析 PR 出错" << endl;
				return false;
			}
		}
	}
	else // VD1 -> $
	{
		outAnalysisFile << "G: VD1 -> $" << endl;
		return true;
	}
	return true;
}
/*
	PL -> $
	PL -> PL1
*/
bool GrammarAnalysis::grammarAnalysisPL(list<Token>::iterator & it_AnalysisCur, list<Token>& listToken, list<ParameterList>& parameterList)
{
	list<Token>::iterator tmp_AnalysisCur = it_AnalysisCur;
	if (grammarAnalysisPL1(it_AnalysisCur, listToken, parameterList))
	{
		outAnalysisFile << "G: PL -> PL1" << endl;
		//cout << "分析PL1成功" << endl;
		return true;
	}
	//cout << "分析PL1失败，返回原来分析位置" << endl;
	it_AnalysisCur = tmp_AnalysisCur;
	outAnalysisFile << "G: PL -> $" << endl;
	return true;
}
/*
	PL1 -> PD PL2
*/
bool GrammarAnalysis::grammarAnalysisPL1(list<Token>::iterator & it_AnalysisCur, list<Token>& listToken, list<ParameterList>& parameterList)
{
	outAnalysisFile << "G: PL1 -> PD PL2" << endl;
	//分析PD
	ParameterList parameter;
	if (!grammarAnalysisPD(it_AnalysisCur, listToken, parameter))	//分析PD，报错
	{
		outAnalysisFile << "E: 分析 PD 出错" << endl;
		return false;
	}
	parameterList.push_back(parameter);
	//分析PL2
	if (!grammarAnalysisPL2(it_AnalysisCur, listToken, parameterList))	//分析PL2，报错
	{
		outAnalysisFile << "E: 分析 PL2 出错" << endl;
		return false;
	}
	return true;
}
/*
	PL2 -> , PD PL2
	PL2 -> $
*/
bool GrammarAnalysis::grammarAnalysisPL2(list<Token>::iterator & it_AnalysisCur, list<Token>& listToken, list<ParameterList>& parameterList)
{
	//判断是否分析到Tokenen串的末尾
	if (it_AnalysisCur == listToken.end())
	{
		outAnalysisFile << "已经分析到Tokenen串的末尾" << endl;
		return false;
	}
	//判断是否为 逗号 ,
	if (Delimiter_Comma == (*it_AnalysisCur).type) // PL2 -> , PD PL2
	{
		outAnalysisFile << "G: PL2 -> , PD PL2" << endl;
		outAnalysisFile << "1> 分析出 ," << endl;
		it_AnalysisCur++;
		ParameterList parameter;
		if (!grammarAnalysisPD(it_AnalysisCur, listToken, parameter))
		{
			outAnalysisFile << "E: 分析 PD 出错" << endl;
			return false;
		}
		parameterList.push_back(parameter);	//添加到List
											//继续循环PL2
		if (!grammarAnalysisPL2(it_AnalysisCur, listToken, parameterList))
		{
			outAnalysisFile << "E: 分析 PL2 出错" << endl;
			return false;
		}
	}
	else // PL2 -> $
	{
		outAnalysisFile << "G: PL2 -> $" << endl;
		return true;
	}
	return true;
}
/*
	PD -> DT PD1
*/
bool GrammarAnalysis::grammarAnalysisPD(list<Token>::iterator & it_AnalysisCur, list<Token>& listToken, ParameterList& parameter)
{
	outAnalysisFile << "G: PD -> DT PD1" << endl;
	int dataType;
	if (!grammarAnalysisDT(it_AnalysisCur, listToken, dataType))
	{
		outAnalysisFile << "E: 分析 DT 出错" << endl;
		return false;
	}
	parameter.parameterType = dataType;
	string parameterName = "";	//初始化为空字符串
	if (!grammarAnalysisPD1(it_AnalysisCur, listToken, parameterName))
	{
		outAnalysisFile << "E: 分析 PD1 出错" << endl;
		return false;
	}
	parameter.parameterName = parameterName;
	return true;
}
/*
	PD1 -> parameterName
	PD1 -> $
*/
bool GrammarAnalysis::grammarAnalysisPD1(list<Token>::iterator& it_AnalysisCur, list<Token>& listToken, string& parameterName)
{
	if ((*it_AnalysisCur).type == Identifier)
	{
		outAnalysisFile << "G: PD1 -> parameterName" << endl;
		outAnalysisFile << "1> 分析出 parameterName " << (*it_AnalysisCur).data << endl;
		parameterName = (*it_AnalysisCur).data;
		it_AnalysisCur++;	//更新当前分析Tokenen串的位置
		return true;
	}
	outAnalysisFile << "G: PD1 -> $" << endl;
	return true;
}
/*
	FB -> $
	FB -> RS FB
*/
bool GrammarAnalysis::grammarAnalysisFB(list<Token>::iterator & it_AnalysisCur, list<Token>& listToken)
{
	list<Token>::iterator tempCur = it_AnalysisCur;
	if (grammarAnalysisRS(it_AnalysisCur, listToken))
	{
		outAnalysisFile << "G: FB -> RS FB" << endl;
		//cout << "分析RS出错" << endl;
		grammarAnalysisFB(it_AnalysisCur, listToken);
		return true;
	}
	it_AnalysisCur = tempCur;	//无法分析出RS，则恢复之前的位置
	outAnalysisFile << "G: FB -> $" << endl;
	return true;
}
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
bool GrammarAnalysis::grammarAnalysisRS(list<Token>::iterator & it_AnalysisCur, list<Token>& listToken)
{
	// 是否分析到末尾
	if (it_AnalysisCur == listToken.end()) //没有分析到末尾
	{
		outAnalysisFile << "E: 已经分析到Tokenen串的末尾" << endl;
		return false;
	}
	//分析 if
	// RS -> if ( PR ) SB RS1
	if ((*it_AnalysisCur).type == Keyword_if)
	{
		outAnalysisFile << "G: RS -> if ( PR ) SB RS1" << endl;
		outAnalysisFile << "1> 分析出 if" << endl;
		it_AnalysisCur++;//更新当前分析Tokenen串的位置
						 //分析左括号
		if (it_AnalysisCur == listToken.end())
		{
			outAnalysisFile << "E: 已经分析到Tokenen串的末尾" << endl;
			return false;
		}
		if ((*it_AnalysisCur).type != Delimiter_Left_Small_Bracket)
		{
			outAnalysisFile << "E: 分析 ( 出错" << endl;
			return false;
		}
		outAnalysisFile << "1> 分析出 (" << endl;
		it_AnalysisCur++;//更新当前分析Tokenen串的位置
						 //分析PR
		if (analysis_express_using_LL1)
		{
			//分析PR
			list<Token> tmpList;
			while (it_AnalysisCur != listToken.end())
			{
				if ((*it_AnalysisCur).type == Delimiter_Right_Small_Bracket)
				{
					break;
				}
				tmpList.push_back(*it_AnalysisCur);
				it_AnalysisCur++; //更新当前分析Tokenen串的位置
			}
			if ((*grammar_for_expression).runGrammarAnalysis(tmpList))
			{
				//cout << endl << "分析PR成功" << endl;
				(*grammar_for_expression).saveAnalysisResultToFile(outAnalysisFile);
			}
			else
			{
				//cout << endl << "分析PR，存在语法错误" << endl;
				return false;
			}
		}
		else
		{
			if (!grammarAnalysis_eexpr(it_AnalysisCur, listToken))
			{
				outAnalysisFile << "E: 分析 eexpr 出错" << endl;
				return false;
			}
		}
		//分析右括号
		if (it_AnalysisCur == listToken.end())
		{
			outAnalysisFile << "E: 已经分析到Tokenen串的末尾" << endl;
		}
		if ((*it_AnalysisCur).type != Delimiter_Right_Small_Bracket) //不为右小括号
		{
			outAnalysisFile << "E: 分析 ) 出错" << endl;
		}
		outAnalysisFile << "1> 分析出 )" << endl;
		it_AnalysisCur++;//更新当前分析Tokenen串的位置
						 //分析SB
		if (!grammarAnalysisSB(it_AnalysisCur, listToken))
		{
			outAnalysisFile << "E: 分析 SB 出错" << endl;
			return false;
		}
		//分析RS1
		if (!grammarAnalysisRS1(it_AnalysisCur, listToken))
		{
			outAnalysisFile << "E: 分析 RS1 出错" << endl;
			return false;
		}
	}
	//分析 while
	//RS -> while (PR) SB
	else if ((*it_AnalysisCur).type == Keyword_while)
	{
		outAnalysisFile << "G: RS -> while (PR) SB" << endl;
		outAnalysisFile << "1> 分析出 while" << endl;
		it_AnalysisCur++;//更新当前分析Tokenen串的位置
						 //分析左小括号
		if (it_AnalysisCur == listToken.end())
		{
			outAnalysisFile << "E: 已经分析到Tokenen串的末尾" << endl;
			return false;
		}
		if ((*it_AnalysisCur).type != Delimiter_Left_Small_Bracket)
		{
			outAnalysisFile << "E: 分析 ( 出错" << endl;
			return false;
		}
		outAnalysisFile << "1> 分析出 (" << endl;
		it_AnalysisCur++;//更新当前分析Tokenen串的位置
						 //分析PR
		if (analysis_express_using_LL1)
		{
			list<Token> tmpList;
			while (it_AnalysisCur != listToken.end())
			{
				if ((*it_AnalysisCur).type == Delimiter_Right_Small_Bracket)
				{
					break;
				}
				tmpList.push_back(*it_AnalysisCur);
				it_AnalysisCur++; //更新当前分析Tokenen串的位置
			}
			if ((*grammar_for_expression).runGrammarAnalysis(tmpList))
			{
				//cout << endl << "分析PR成功" << endl;
				(*grammar_for_expression).saveAnalysisResultToFile(outAnalysisFile);
			}
			else
			{
				//cout << endl << "分析PR，存在语法错误" << endl;
				return false;
			}
		}
		else
		{
			if (!grammarAnalysis_eexpr(it_AnalysisCur, listToken))
			{
				outAnalysisFile << "E: 分析 eexpr 出错" << endl;
				return false;
			}
		}
		//分析右小括号
		if (it_AnalysisCur == listToken.end())
		{
			outAnalysisFile << "E: 已经分析到Tokenen串的末尾" << endl;
			return false;
		}
		if ((*it_AnalysisCur).type != Delimiter_Right_Small_Bracket) //不为右小括号
		{
			outAnalysisFile << "E: 分析 ) 出错" << endl;
			return false;
		}
		outAnalysisFile << "1> 分析出 )" << endl;
		it_AnalysisCur++;//更新当前分析Tokenen串的位置
						 //分析SB
		if (!grammarAnalysisSB(it_AnalysisCur, listToken))
		{
			outAnalysisFile << "E: 分析 SB 出错" << endl;
			return false;
		}
	}
	//分析 do
	//RS -> do SB while ( PR ) ;
	else if ((*it_AnalysisCur).type == Keyword_do)
	{
		outAnalysisFile << "G: RS -> do SB while ( PR ) ;" << endl;
		outAnalysisFile << "1> 分析出 do" << endl;
		it_AnalysisCur++;//更新当前分析Tokenen串的位置
						 //分析SB
		if (!grammarAnalysisSB(it_AnalysisCur, listToken))
		{
			outAnalysisFile << "E: 分析 SB 出错" << endl;
			return false;
		}
		//分析while
		if (it_AnalysisCur == listToken.end())
		{
			outAnalysisFile << "E: 已经分析到Tokenen串的末尾" << endl;
			return false;
		}
		if ((*it_AnalysisCur).type != Keyword_while)
		{
			outAnalysisFile << "E: 分析 while 出错" << endl;
			return false;
		}
		outAnalysisFile << "1> 分析出 while" << endl;
		it_AnalysisCur++;//更新当前分析Tokenen串的位置
						 //分析左小括号
		if (it_AnalysisCur == listToken.end())
		{
			outAnalysisFile << "E: 已经分析到Tokenen串的末尾" << endl;
			return false;
		}
		if ((*it_AnalysisCur).type != Delimiter_Left_Small_Bracket)
		{
			outAnalysisFile << "E: 分析 ( 出错" << endl;
			return false;
		}
		outAnalysisFile << "1> 分析出 (" << endl;
		it_AnalysisCur++;//更新当前分析Tokenen串的位置
		if (analysis_express_using_LL1)
		{
			//分析PR
			list<Token> tmpList;
			while (it_AnalysisCur != listToken.end())
			{
				if ((*it_AnalysisCur).type == Delimiter_Right_Small_Bracket)
				{
					break;
				}
				tmpList.push_back(*it_AnalysisCur);
				it_AnalysisCur++; //更新当前分析Tokenen串的位置
			}
			if ((*grammar_for_expression).runGrammarAnalysis(tmpList))
			{
				//cout << endl << "分析PR成功" << endl;
				(*grammar_for_expression).saveAnalysisResultToFile(outAnalysisFile);
			}
			else
			{
				//cout << endl << "分析PR，存在语法错误" << endl;
				return false;
			}
		}
		else
		{
			if (!grammarAnalysis_eexpr(it_AnalysisCur, listToken))
			{
				outAnalysisFile << "E: 分析 eexpr 出错" << endl;
				return false;
			}
		}
		//分析右小括号
		if (it_AnalysisCur == listToken.end())
		{
			outAnalysisFile << "E: 已经分析到Tokenen串的末尾" << endl;
			return false;
		}
		if ((*it_AnalysisCur).type != Delimiter_Right_Small_Bracket) //不为右小括号
		{
			outAnalysisFile << "E: 分析 ) 出错" << endl;
			return false;
		}
		outAnalysisFile << "1> 分析出 )" << endl;
		it_AnalysisCur++;//更新当前分析Tokenen串的位置
						 //分析分号 ;
		if (it_AnalysisCur == listToken.end())
		{
			outAnalysisFile << "E: 已经分析到Tokenen串的末尾" << endl;
			return false;
		}
		if ((*it_AnalysisCur).type != Delimiter_Semicolon)
		{
			outAnalysisFile << "E: 分析 ; 出错" << endl;
			return false;
		}
		outAnalysisFile << "1> 分析出 ;" << endl;
		it_AnalysisCur++;//更新当前分析Tokenen串的位置
	}
	//分析 for
	//RS -> for ( PR ; PR ; PR ) SB
	else if ((*it_AnalysisCur).type == Keyword_for)
	{
		outAnalysisFile << "G: RS -> for ( PR ; PR ; PR ) SB" << endl;
		outAnalysisFile << "1> 分析出 for" << endl;
		it_AnalysisCur++;//更新当前分析Tokenen串的位置
						 //分析左小括号
		if (it_AnalysisCur == listToken.end())
		{
			outAnalysisFile << "E: 已经分析到Tokenen串的末尾" << endl;
			return false;
		}
		if ((*it_AnalysisCur).type != Delimiter_Left_Small_Bracket)
		{
			outAnalysisFile << "E: 分析 ( 出错" << endl;
			return false;
		}
		outAnalysisFile << "1> 分析出 (" << endl;
		it_AnalysisCur++;//更新当前分析Tokenen串的位置
		for (int i = 0; i < 2; i++)
		{
			//分析PR
			if (analysis_express_using_LL1)
			{
				list<Token> tmpList;
				while (it_AnalysisCur != listToken.end())
				{
					if ((*it_AnalysisCur).type == Delimiter_Comma) //到逗号结束
					{
						break;
					}
					tmpList.push_back(*it_AnalysisCur);
					it_AnalysisCur++; //更新当前分析Tokenen串的位置
				}
				if ((*grammar_for_expression).runGrammarAnalysis(tmpList))
				{
					//cout << endl << "分析PR成功" << endl;
					(*grammar_for_expression).saveAnalysisResultToFile(outAnalysisFile);
				}
				else
				{
					//cout << endl << "分析PR，存在语法错误" << endl;
					return false;
				}
			}
			else
			{
				if (!grammarAnalysis_eexpr(it_AnalysisCur, listToken))
				{
					outAnalysisFile << "E: 分析 eexpr 出错" << endl;
					return false;
				}
			}
			//分析分号
			if (it_AnalysisCur == listToken.end())
			{
				outAnalysisFile << "E: 已经分析到Tokenen串的末尾" << endl;
				return false;
			}
			if ((*it_AnalysisCur).type != Delimiter_Semicolon)	// ; 分号
			{
				outAnalysisFile << "E: 分析 ; 出错" << endl;
				return false;
			}
			outAnalysisFile << "1> 分析出 ;" << endl;
			it_AnalysisCur++;//更新当前分析Tokenen串的位置
		}
		//分析PR
		if (analysis_express_using_LL1)
		{
			list<Token> tmpList;
			while (it_AnalysisCur != listToken.end())
			{
				if ((*it_AnalysisCur).type == Delimiter_Right_Small_Bracket) //到右小括号结束
				{
					break;
				}
				tmpList.push_back(*it_AnalysisCur);
				it_AnalysisCur++; //更新当前分析Tokenen串的位置
			}
			if ((*grammar_for_expression).runGrammarAnalysis(tmpList))
			{
				//cout << endl << "分析PR成功" << endl;
				(*grammar_for_expression).saveAnalysisResultToFile(outAnalysisFile);
			}
			else
			{
				//cout << endl << "分析PR，存在语法错误" << endl;
				return false;
			}
		}
		else
		{
			if (!grammarAnalysis_eexpr(it_AnalysisCur, listToken))
			{
				outAnalysisFile << "E: 分析 eexpr 出错" << endl;
				return false;
			}
		}
		//分析右小括号
		if (it_AnalysisCur == listToken.end())
		{
			outAnalysisFile << "E: 已经分析到Tokenen串的末尾" << endl;
			return false;
		}
		if ((*it_AnalysisCur).type != Delimiter_Right_Small_Bracket) //不为右小括号
		{
			outAnalysisFile << "E: 当前位置缺少右小括号" << endl;
			return false;
		}
		outAnalysisFile << "1> 分析出 )" << endl;
		it_AnalysisCur++;//更新当前分析Tokenen串的位置
						 //分析SB
		if (!grammarAnalysisSB(it_AnalysisCur, listToken))
		{
			outAnalysisFile << "E: 分析 SB 出错" << endl;
			return false;
		}
	}
	//分析 break
	//RS -> break ;
	else if ((*it_AnalysisCur).type == Keyword_break)
	{
		outAnalysisFile << "G: RS -> break ;" << endl;
		outAnalysisFile << "1> 分析出 break" << endl;
		it_AnalysisCur++;//更新当前分析Tokenen串的位置
						 //分析分号
		if (it_AnalysisCur == listToken.end())
		{
			outAnalysisFile << "E: 已经分析到Tokenen串的末尾" << endl;
			return false;
		}
		if ((*it_AnalysisCur).type != Delimiter_Semicolon) //不为分号
		{
			outAnalysisFile << "E: 分析 ; 出错" << endl;
			return false;
		}
		outAnalysisFile << "1> 分析出 ;" << endl;
		it_AnalysisCur++;//更新当前分析Tokenen串的位置
	}
	//分析 continue
	// RS -> continue;
	else if ((*it_AnalysisCur).type == Keyword_continue)
	{
		outAnalysisFile << "G: RS -> continue;" << endl;
		outAnalysisFile << "1> 分析出 continue" << endl;
		it_AnalysisCur++;//更新当前分析Tokenen串的位置
						 //分析分号
		if (it_AnalysisCur == listToken.end())
		{
			outAnalysisFile << "E: 已经分析到Tokenen串的末尾" << endl;
			return false;
		}
		if ((*it_AnalysisCur).type != Delimiter_Semicolon) //不为分号
		{
			outAnalysisFile << "E: 分析 ; 出错" << endl;
			return false;
		}
		outAnalysisFile << "1> 分析出 ;" << endl;
		it_AnalysisCur++;//更新当前分析Tokenen串的位置
	}
	//分析 return
	//RS -> return PR ;
	else if ((*it_AnalysisCur).type == Keyword_return)
	{
		outAnalysisFile << "G: return PR ;" << endl;
		outAnalysisFile << "1> 分析出 ;" << endl;
		it_AnalysisCur++;//更新当前分析Tokenen串的位置
		if (analysis_express_using_LL1)
		{
			//分析PR
			list<Token> tmpList;
			while (it_AnalysisCur != listToken.end())
			{
				if ((*it_AnalysisCur).type == Delimiter_Semicolon) //到分号结束
				{
					break;
				}
				tmpList.push_back(*it_AnalysisCur);
				it_AnalysisCur++; //更新当前分析Tokenen串的位置
			}
			if ((*grammar_for_expression).runGrammarAnalysis(tmpList))
			{
				//cout << endl << "分析PR成功" << endl;
				(*grammar_for_expression).saveAnalysisResultToFile(outAnalysisFile);
			}
			else
			{
				//cout << endl << "分析PR，存在语法错误" << endl;
				return false;
			}
		}
		else
		{
			if (!grammarAnalysis_eexpr(it_AnalysisCur, listToken))
			{
				outAnalysisFile << "E: 分析 eexpr 出错" << endl;
				return false;
			}
		}
		//分析分号
		if (it_AnalysisCur == listToken.end())
		{
			outAnalysisFile << "E: 已经分析到Tokenen串的末尾" << endl;
			return false;
		}
		if ((*it_AnalysisCur).type != Delimiter_Semicolon) //不为分号
		{
			outAnalysisFile << "E: 分析 ; 出错" << endl;
			return false;
		}
		outAnalysisFile << "1> 分析出 ;" << endl;
		it_AnalysisCur++;//更新当前分析Tokenen串的位置
	}
	//分析 goto
	//RS -> goto positionName ;
	else if ((*it_AnalysisCur).type == Keyword_goto)
	{
		outAnalysisFile << "G: RS -> goto positionName ;" << endl;
		outAnalysisFile << "1> 分析出 goto" << endl;
		it_AnalysisCur++;//更新当前分析Tokenen串的位置
						 //分析Id
		if (it_AnalysisCur == listToken.end())
		{
			outAnalysisFile << "E: 已经分析到Tokenen串的末尾" << endl;
			return false;
		}
		if ((*it_AnalysisCur).type != Identifier) //不为Id
		{
			outAnalysisFile << "E: 分析 positionName 出错" << endl;
			return false;
		}
		outAnalysisFile << "1> 分析出 positionName " << (*it_AnalysisCur).data << endl;
		it_AnalysisCur++;//更新当前分析Tokenen串的位置
						 //分析 分号
		if (it_AnalysisCur == listToken.end()) //没有分析到末尾
		{
			outAnalysisFile << "E: 已经分析到Tokenen串的末尾" << endl;
			return false;
		}
		if ((*it_AnalysisCur).type != Delimiter_Semicolon)	//是否为分号
		{
			outAnalysisFile << "E: 分析 ; 出错" << endl;
			return false;
		}
		outAnalysisFile << "1> 分析出 ;" << endl;
		it_AnalysisCur++;//更新当前分析Tokenen串的位置
	}
	//分析 print
	//RS -> print ( Print
	else if ((*it_AnalysisCur).type == Keyword_print)
	{
		outAnalysisFile << "G: RS -> print ( Print" << endl;
		outAnalysisFile << "1> 分析出 print" << endl;
		it_AnalysisCur++;//更新当前分析Tokenen串的位置
						 //分析 左小括号
		if (it_AnalysisCur == listToken.end())
		{
			outAnalysisFile << "E: 已经分析到Tokenen串的末尾" << endl;
			return false;
		}
		if ((*it_AnalysisCur).type != Delimiter_Left_Small_Bracket)	//是否为左小括号
		{
			outAnalysisFile << "E: 分析 ( 出错" << endl;
			return false;
		}
		outAnalysisFile << "1> 分析出 (" << endl;
		it_AnalysisCur++;//更新当前分析Tokenen串的位置
		if (!grammarAnalysisPrint(it_AnalysisCur, listToken))
		{
			outAnalysisFile << "E: 分析 Print 出错" << endl;
			return false;
		}
	}
	//分析 scan
	//RS -> scan ( id ) ;
	else if ((*it_AnalysisCur).type == Keyword_scan)
	{
		outAnalysisFile << "G: RS -> scan ( id ) ;" << endl;
		outAnalysisFile << "1> 分析出 scan" << endl;
		it_AnalysisCur++;//更新当前分析Tokenen串的位置
						 //1.分析 左小括号
		if (it_AnalysisCur == listToken.end())
		{
			outAnalysisFile << "E: 已经分析到Tokenen串的末尾" << endl;
			return false;
		}
		if ((*it_AnalysisCur).type != Delimiter_Left_Small_Bracket)	//是否为左小括号
		{
			outAnalysisFile << "E: 分析 ( 出错" << endl;
			return false;
		}
		outAnalysisFile << "1> 分析出 (" << endl;
		it_AnalysisCur++;//更新当前分析Tokenen串的位置
						 //2.分析 id
		if (it_AnalysisCur == listToken.end())
		{
			outAnalysisFile << "E: 已经分析到Tokenen串的末尾" << endl;
			return false;
		}
		if ((*it_AnalysisCur).type != Identifier)	//是否为id
		{
			outAnalysisFile << "E: 分析 id 出错" << endl;
			return false;
		}
		outAnalysisFile << "1> 分析出 id" << endl;
		it_AnalysisCur++;//更新当前分析Tokenen串的位置
						 //3.分析 右小括号
		if (it_AnalysisCur == listToken.end()) //没有分析到末尾
		{
			outAnalysisFile << "E: 已经分析到Tokenen串的末尾" << endl;
			return false;
		}
		if ((*it_AnalysisCur).type != Delimiter_Right_Small_Bracket)	//是否为右小括号
		{
			outAnalysisFile << "E: 分析 ) 出错" << endl;
			return false;
		}
		outAnalysisFile << "1> 分析出 )" << endl;
		it_AnalysisCur++;//更新当前分析Tokenen串的位置
						 //4.分析 分号
		if (it_AnalysisCur == listToken.end()) //没有分析到末尾
		{
			outAnalysisFile << "E: 已经分析到Tokenen串的末尾" << endl;
			return false;
		}
		if ((*it_AnalysisCur).type != Delimiter_Semicolon)	//是否为分号
		{
			outAnalysisFile << "E: 分析 ; 出错" << endl;
			return false;
		}
		outAnalysisFile << "1> 分析出 ;" << endl;
		it_AnalysisCur++;//更新当前分析Tokenen串的位置
	}
	//RS -> MT DT VL ;
	else if ((*it_AnalysisCur).type == Keyword_auto || (*it_AnalysisCur).type == Keyword_register ||
		(*it_AnalysisCur).type == Keyword_extern || (*it_AnalysisCur).type == Keyword_static ||
		(*it_AnalysisCur).type == Keyword_int || (*it_AnalysisCur).type == Keyword_char ||
		(*it_AnalysisCur).type == Keyword_float || (*it_AnalysisCur).type == Keyword_double)
	{
		outAnalysisFile << "G: RS -> MT DT VL ;" << endl;
		//分析MT
		int memoryType = Keyword_extern;
		if (!grammarAnalysisMT(it_AnalysisCur, listToken, memoryType))
		{
			outAnalysisFile << "E: 分析 MT 出错" << endl;
			return false;
		}
		//分析DT
		int dataType = Error;
		if (!grammarAnalysisDT(it_AnalysisCur, listToken, dataType))
		{
			outAnalysisFile << "E: 分析 DT 出错" << endl;
			return false;
		}
		//分析VL
		list<VariableList> variableList;
		if (!grammarAnalysisVL(it_AnalysisCur, listToken, variableList))
		{
			outAnalysisFile << "E: 分析 VL 出错" << endl;
			return false;
		}
		//分析分号
		if (it_AnalysisCur == listToken.end())
		{
			outAnalysisFile << "E:已经分析到Tokenen串的末尾" << endl;
			return false;
		}
		if ((*it_AnalysisCur).type != Delimiter_Semicolon) //不为分号
		{
			outAnalysisFile << "E: 分析 ; 出错" << endl;
			return false;
		}
		outAnalysisFile << "1> 分析出 ;" << endl;
		it_AnalysisCur++;//更新当前分析Tokenen串的位置
	}
	//PR ;
	else if (expressPreAnalysis((*it_AnalysisCur).type))
	{
		outAnalysisFile << "G: RS -> PR ;" << endl;
		if (analysis_express_using_LL1)
		{
			//分析PR
			list<Token> tmpList;
			while (it_AnalysisCur != listToken.end())
			{
				if ((*it_AnalysisCur).type == Delimiter_Semicolon) //到分号结束
				{
					break;
				}
				tmpList.push_back(*it_AnalysisCur);
				it_AnalysisCur++; //更新当前分析Tokenen串的位置
			}
			if ((*grammar_for_expression).runGrammarAnalysis(tmpList))
			{
				//cout << endl << "分析PR成功" << endl;
			}
			else
			{
				//cout << endl << "分析PR，存在语法错误" << endl;
				return false;
			}
		}
		else
		{
			if (!grammarAnalysis_eexpr(it_AnalysisCur, listToken))
			{
				outAnalysisFile << "E: 分析 eexpr 出错" << endl;
				return false;
			}
			outAnalysisFile << "G: RS -> PR ;" << endl;
		}
		//分析分号
		if (it_AnalysisCur == listToken.end())
		{
			outAnalysisFile << "E: 已经分析到Tokenen串的末尾" << endl;
			return false;
		}
		if ((*it_AnalysisCur).type != Delimiter_Semicolon) //不为分号
		{
			outAnalysisFile << "E: 分析 ; 出错" << endl;
			return false;
		}
		outAnalysisFile << "1> 分析出 ;" << endl;
		it_AnalysisCur++;//更新当前分析Tokenen串的位置
	}
	//判断是否为右大括号
	else if ((*it_AnalysisCur).type != Delimiter_Right_Large_Bracket)
	{
		return true;
	}
	else
	{
		return false;
	}
	return true;
}
/*
	RS1 -> $
	RS1 -> else SB
*/
bool GrammarAnalysis::grammarAnalysisRS1(list<Token>::iterator & it_AnalysisCur, list<Token>& listToken)
{
	//是否分析到末尾
	if (it_AnalysisCur == listToken.end()) //没有分析到末尾
	{
		outAnalysisFile << "E: 已经分析到Tokenen串的末尾" << endl;
		return false;
	}
	// else
	if (Keyword_else == (*it_AnalysisCur).type)
	{
		outAnalysisFile << "G: RS1 -> else SB" << endl;
		outAnalysisFile << "1> 分析出 else" << endl;
		it_AnalysisCur++;
		// 分析SB
		if (!grammarAnalysisSB(it_AnalysisCur, listToken))
		{
			outAnalysisFile << "E: 分析 SB 出错" << endl;
			return false;
		}
	}
	return true;
}
/*
	SB -> RS
	SB -> { SB1 }
*/
bool GrammarAnalysis::grammarAnalysisSB(list<Token>::iterator & it_AnalysisCur, list<Token>& listToken)
{
	if (it_AnalysisCur == listToken.end()) //没有分析到末尾
	{
		outAnalysisFile << "E: 已经分析到Tokenen串的末尾" << endl;
		return false;
	}
	//分析左大括号
	if ((*it_AnalysisCur).type == Delimiter_Left_Large_Bracket)
	{
		outAnalysisFile << "G: SB -> { SB1 }" << endl;
		outAnalysisFile << "1> 分析出 {" << endl;
		it_AnalysisCur++;//更新当前分析Tokenen串的位置
						 //分析SB1
		grammarAnalysisSB1(it_AnalysisCur, listToken);	//分析SB1返回值在这个位置永远为true
														//分析右大括号
		if (it_AnalysisCur == listToken.end()) //没有分析到末尾
		{
			outAnalysisFile << "E: 已经分析到Tokenen串的末尾" << endl;
			return false;
		}
		if ((*it_AnalysisCur).type != Delimiter_Right_Large_Bracket)
		{
			outAnalysisFile << "E: 分析 } 出错" << endl;
			return false;
		}
		outAnalysisFile << "1> 分析出 }" << endl;
		it_AnalysisCur++;//更新当前分析Tokenen串的位置
	}
	else
	{
		//分析RS
		if (!grammarAnalysisRS(it_AnalysisCur, listToken))
		{
			outAnalysisFile << "E: 分析 RS 出错" << endl;
			return false;
		}
	}
	return true;
}
/*
	SB1 -> $
	SB1 -> RS SB1
*/
bool GrammarAnalysis::grammarAnalysisSB1(list<Token>::iterator & it_AnalysisCur, list<Token>& listToken)
{
	list<Token>::iterator it_tmp = it_AnalysisCur;
	if (grammarAnalysisRS(it_AnalysisCur, listToken))
	{
		outAnalysisFile << "G: SB1 -> RS SB1" << endl;
		grammarAnalysisSB1(it_AnalysisCur, listToken);
	}
	else
	{
		outAnalysisFile << "G: SB1 -> $" << endl;
		it_AnalysisCur = it_tmp;
		return true;
	}
	return true;
}
/*
	Print -> string ) ;
	Print -> PR ) ;
*/
bool GrammarAnalysis::grammarAnalysisPrint(list<Token>::iterator & it_AnalysisCur, list<Token>& listToken)
{
	if (it_AnalysisCur == listToken.end()) //没有分析到末尾
	{
		outAnalysisFile << "E: 已经分析到Tokenen串的末尾" << endl;
		return false;
	}
	//分析 string ) ;
	if ((*it_AnalysisCur).type == String)	//是否为字符串
	{
		outAnalysisFile << "G: Print -> string ) ;" << endl;
		outAnalysisFile << "1> 分析出 string " << (*it_AnalysisCur).data << endl;
		it_AnalysisCur++;//更新当前分析Tokenen串的位置
						 // 分析 右小括号
		if (it_AnalysisCur == listToken.end()) //没有分析到末尾
		{
			outAnalysisFile << "E: 已经分析到Tokenen串的末尾" << endl;
			return false;
		}
		if ((*it_AnalysisCur).type != Delimiter_Right_Small_Bracket)	//是否为右小括号
		{
			outAnalysisFile << "E: 分析 ) 出错" << endl;
			return false;
		}
		outAnalysisFile << "1> 分析出 )" << endl;
		it_AnalysisCur++;//更新当前分析Tokenen串的位置
						 // 分析 分号
		if (it_AnalysisCur == listToken.end()) //没有分析到末尾
		{
			outAnalysisFile << "E: 已经分析到Tokenen串的末尾" << endl;
			return false;
		}
		if ((*it_AnalysisCur).type != Delimiter_Semicolon)	//是否为分号
		{
			outAnalysisFile << "E: 分析 ; 出错" << endl;
			return false;
		}
		outAnalysisFile << "1> 分析出 ;" << endl;
		it_AnalysisCur++;//更新当前分析Tokenen串的位置
	}
	else
	{
		//分析 PR ) ;
		//分析PR
		if (analysis_express_using_LL1)
		{
			list<Token> tmpList;
			while (it_AnalysisCur != listToken.end())
			{
				if ((*it_AnalysisCur).type == Delimiter_Right_Small_Bracket) //到右小括号结束
				{
					break;
				}
				tmpList.push_back(*it_AnalysisCur);
				it_AnalysisCur++; //更新当前分析Tokenen串的位置
			}
			if ((*grammar_for_expression).runGrammarAnalysis(tmpList))
			{
				//cout << endl << "分析PR成功" << endl;
				(*grammar_for_expression).saveAnalysisResultToFile(outAnalysisFile);
			}
			else
			{
				(*grammar_for_expression).saveAnalysisResultToFile(outAnalysisFile);
				//cout << endl << "Print 分析PR，存在语法错误" << endl;
				return false;
			}
		}
		else
		{
			if (!grammarAnalysis_eexpr(it_AnalysisCur, listToken))
			{
				outAnalysisFile << "E: 分析 eexpr 出错" << endl;
				return false;
			}
		}
		// 分析 右小括号
		if (it_AnalysisCur == listToken.end()) //没有分析到末尾
		{
			outAnalysisFile << "E: 已经分析到Tokenen串的末尾" << endl;
			return false;
		}
		if ((*it_AnalysisCur).type != Delimiter_Right_Small_Bracket)	//是否为右小括号
		{
			outAnalysisFile << "E: 分析 ) 出错" << endl;
			return false;
		}
		outAnalysisFile << "1> 分析出 )" << endl;
		it_AnalysisCur++;//更新当前分析Tokenen串的位置
						 // 分析 分号
		if (it_AnalysisCur == listToken.end()) //没有分析到末尾
		{
			outAnalysisFile << "E: 已经分析到Tokenen串的末尾" << endl;
			return false;
		}
		if ((*it_AnalysisCur).type != Delimiter_Semicolon)	//是否为分号
		{
			outAnalysisFile << "E: 分析 ; 出错" << endl;
			return false;
		}
		outAnalysisFile << "1> 分析出 ;" << endl;
		it_AnalysisCur++;//更新当前分析Tokenen串的位置
	}
	return true;
}
//---------------------------------------------------------------------------------------------------
// 表达式分析
//---------------------------------------------------------------------------------------------------
/*
	eexpr -> bexpr eexpr1
*/
bool GrammarAnalysis::grammarAnalysis_eexpr(list<Token>::iterator & itAnalysisCur, list<Token>& TokenenList)
{
	outAnalysisFile << "G: eexpr -> bexpr eexpr1" << endl;
	if (!grammarAnalysis_bexpr(itAnalysisCur, TokenenList))	//bexpr
	{
		return false;
	}
	if (!grammarAnalysis_eexpr1(itAnalysisCur, TokenenList))	//eexpr1
	{
		return false;
	}
	return true;
}
/*
	eexpr1 -> ao bexpr eexpr1
	eexpr1 -> $
*/
bool GrammarAnalysis::grammarAnalysis_eexpr1(list<Token>::iterator & itAnalysisCur, list<Token>& TokenenList)
{
	if (grammarAnalysis_ao(itAnalysisCur, TokenenList))
	{
		//outAnalysisFile << "G: eexpr1 -> ao bexpr eexpr1" << endl;
		//bexpr
		if (!grammarAnalysis_bexpr(itAnalysisCur, TokenenList))
		{
			outAnalysisFile << "E: 分析 bexpr 出错" << endl;
			return false;
		}
		//bexpr
		if (!grammarAnalysis_eexpr1(itAnalysisCur, TokenenList))
		{
			outAnalysisFile << "E: 分析 eexpr1 出错" << endl;
			return false;
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
bool GrammarAnalysis::grammarAnalysis_ao(list<Token>::iterator & itAnalysisCur, list<Token>& TokenenList)
{
	if (itAnalysisCur == TokenenList.end())	//判断是否分析到Tokenen串的末尾
	{
		outAnalysisFile << "E: 已经分析到Tokenen串的末尾" << endl;
		itAnalysisCur--;
		cout << "语法错误：在第" << (*itAnalysisCur).lineNo << "行，程序不完整，缺少必要内容" << endl;
		itAnalysisCur++;
		return false;
	}
	if ((*itAnalysisCur).type == Operator_Equal)	// =
	{
		outAnalysisFile << "G: eexpr1 -> ao bexpr eexpr1" << endl;
		outAnalysisFile << "1> 分析出 ao " << (*itAnalysisCur).data << endl;
		itAnalysisCur++;
	}
	else if ((*itAnalysisCur).type == Operator_Plus_Equal)	// +=
	{
		outAnalysisFile << "G: eexpr1 -> ao bexpr eexpr1" << endl;
		outAnalysisFile << "1> 分析出 ao " << (*itAnalysisCur).data << endl;
		itAnalysisCur++;
	}
	else if ((*itAnalysisCur).type == Operator_Minus_Equal)	// -=
	{
		outAnalysisFile << "G: eexpr1 -> ao bexpr eexpr1" << endl;
		outAnalysisFile << "1> 分析出 ao " << (*itAnalysisCur).data << endl;
		itAnalysisCur++;
	}
	else if ((*itAnalysisCur).type == Operator_Multiply_Equal)	// *=
	{
		outAnalysisFile << "G: eexpr1 -> ao bexpr eexpr1" << endl;
		outAnalysisFile << "1> 分析出 ao " << (*itAnalysisCur).data << endl;
		itAnalysisCur++;
	}
	else if ((*itAnalysisCur).type == Operator_Divide_Equal)	// /=
	{
		outAnalysisFile << "G: eexpr1 -> ao bexpr eexpr1" << endl;
		outAnalysisFile << "1> 分析出 ao " << (*itAnalysisCur).data << endl;
		itAnalysisCur++;
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
bool GrammarAnalysis::grammarAnalysis_bexpr(list<Token>::iterator & itAnalysisCur, list<Token>& TokenenList)
{
	outAnalysisFile << "G: bexpr -> bterm bexpr1" << endl;
	//bterm
	if (!grammarAnalysis_bterm(itAnalysisCur, TokenenList))
	{
		outAnalysisFile << "E: 分析 bterm 出错" << endl;
		return false;
	}
	//bexpr1
	if (!grammarAnalysis_bexpr1(itAnalysisCur, TokenenList))
	{
		outAnalysisFile << "E: 分析 bexpr1 出错" << endl;
		return false;
	}
	return true;
}
/*
	bexpr1 -> || bterm bexpr1
	bexpr1 -> $
*/
bool GrammarAnalysis::grammarAnalysis_bexpr1(list<Token>::iterator & itAnalysisCur, list<Token>& TokenenList)
{
	if (itAnalysisCur == TokenenList.end())	//判断是否分析到Tokenen串的末尾
	{
		outAnalysisFile << "E: 已经分析到Tokenen串的末尾" << endl;
		itAnalysisCur--;
		cout << "语法错误：在第" << (*itAnalysisCur).lineNo << "行，程序不完整，缺少必要内容" << endl;
		itAnalysisCur++;
		return false;
	}
	if ((*itAnalysisCur).type == Operator_Or)	// ||
	{
		outAnalysisFile << "G: bexpr1 -> || bterm bexpr1" << endl;
		outAnalysisFile << "1> 分析出 ||" << endl;
		itAnalysisCur++;
		if (!grammarAnalysis_bterm(itAnalysisCur, TokenenList))	//bterm
		{
			outAnalysisFile << "E: 分析 bterm 出错" << endl;
			return false;
		}
		if (!grammarAnalysis_bexpr1(itAnalysisCur, TokenenList))	//bexpr1
		{
			outAnalysisFile << "E: 分析 bexpr1 出错" << endl;
			return false;
		}
		return true;
	}
	outAnalysisFile << "G: bexpr1 -> $" << endl;
	return true;
}
/*
bterm -> rterm bterm1
*/
bool GrammarAnalysis::grammarAnalysis_bterm(list<Token>::iterator & itAnalysisCur, list<Token>& TokenenList)
{
	outAnalysisFile << "G: bterm -> rterm bterm1" << endl;
	//rterm
	if (!grammarAnalysis_rexpr(itAnalysisCur, TokenenList))
	{
		outAnalysisFile << "E: 分析 rterm 出错" << endl;
		return false;
	}
	//bterm1
	if (!grammarAnalysis_bterm1(itAnalysisCur, TokenenList))
	{
		outAnalysisFile << "E: 分析 bterm1 出错" << endl;
		return false;
	}
	return true;
}
/*
	bterm1 -> && rterm bterm1
	bterm1 -> $
*/
bool GrammarAnalysis::grammarAnalysis_bterm1(list<Token>::iterator & itAnalysisCur, list<Token>& TokenenList)
{
	if (itAnalysisCur == TokenenList.end())	//判断是否分析到Tokenen串的末尾
	{
		outAnalysisFile << "E: 已经分析到Tokenen串的末尾" << endl;
		itAnalysisCur--;
		cout << "语法错误：在第" << (*itAnalysisCur).lineNo << "行，程序不完整，缺少必要内容" << endl;
		itAnalysisCur++;
		return false;
	}
	if ((*itAnalysisCur).type == Operator_And)	// &&
	{
		outAnalysisFile << "G: bterm1 -> && rterm bterm1" << endl;
		outAnalysisFile << "1> 分析出 &&" << endl;
		itAnalysisCur++;
		//rterm
		if (!grammarAnalysis_rexpr(itAnalysisCur, TokenenList))
		{
			outAnalysisFile << "E: 分析 rterm 出错" << endl;
			return false;
		}
		//bterm1
		if (!grammarAnalysis_bterm1(itAnalysisCur, TokenenList))
		{
			outAnalysisFile << "E: 分析 bterm1 出错" << endl;
			return false;
		}
		return true;
	}
	outAnalysisFile << "G: bterm1 -> $" << endl;
	return true;
}
/*
	rexpr -> aexpr rexpr1
*/
bool GrammarAnalysis::grammarAnalysis_rexpr(list<Token>::iterator & itAnalysisCur, list<Token>& TokenenList)
{
	outAnalysisFile << "G: rterm -> aexpr rterm1" << endl;
	//aexpr
	if (!grammarAnalysis_aexpr(itAnalysisCur, TokenenList))
	{
		outAnalysisFile << "E: 分析 aexpr 出错" << endl;
		return false;
	}
	//rterm1
	if (!grammarAnalysis_rexpr1(itAnalysisCur, TokenenList))
	{
		outAnalysisFile << "E: 分析 rterm1 出错" << endl;
		return false;
	}
	return true;
}
/*
	rterm1 -> < aexpr
	rterm1 -> > aexpr
	rterm1 -> <= aexpr
	rterm1 -> <= aexpr
	rterm1 -> != aexpr
	rterm1 -> == aexpr
	rterm1 -> $
*/
bool GrammarAnalysis::grammarAnalysis_rexpr1(list<Token>::iterator & itAnalysisCur, list<Token>& TokenenList)
{
	if (itAnalysisCur == TokenenList.end())	//判断是否分析到Tokenen串的末尾
	{
		outAnalysisFile << "E: 已经分析到Tokenen串的末尾" << endl;
		itAnalysisCur--;
		cout << "语法错误：在第" << (*itAnalysisCur).lineNo << "行，程序不完整，缺少必要内容" << endl;
		itAnalysisCur++;
		return false;
	}
	if ((*itAnalysisCur).type == Operator_Less_Than)	// <
	{
		outAnalysisFile << "G: rterm1 -> < aexpr" << endl;
		outAnalysisFile << "1> 分析出 <" << endl;
		itAnalysisCur++;
		//aexpr
		if (!grammarAnalysis_aexpr(itAnalysisCur, TokenenList))
		{
			outAnalysisFile << "E: 分析 aexpr 出错" << endl;
			return false;
		}
	}
	else if ((*itAnalysisCur).type == Operator_More_Than) // >
	{
		outAnalysisFile << "G: rterm1 -> > aexpr" << endl;
		outAnalysisFile << "1> 分析出 >" << endl;
		itAnalysisCur++;
		//aexpr
		if (!grammarAnalysis_aexpr(itAnalysisCur, TokenenList))
		{
			outAnalysisFile << "E: 分析 aexpr 出错" << endl;
			return false;
		}
	}
	else if ((*itAnalysisCur).type == Operator_Less_Than_Equal)	// <=
	{
		outAnalysisFile << "G: rterm1 -> <= aexpr" << endl;
		outAnalysisFile << "1> 分析出 <=" << endl;
		itAnalysisCur++;
		//aexpr
		if (!grammarAnalysis_aexpr(itAnalysisCur, TokenenList))
		{
			outAnalysisFile << "E: 分析 aexpr 出错" << endl;
			return false;
		}
	}
	else if ((*itAnalysisCur).type == Operator_More_Than_Equal)	// >=
	{
		outAnalysisFile << "G: rterm1 -> >= aexpr" << endl;
		outAnalysisFile << "1> 分析出 >=" << endl;
		itAnalysisCur++;
		//aexpr
		if (!grammarAnalysis_aexpr(itAnalysisCur, TokenenList))
		{
			outAnalysisFile << "E: 分析 aexpr 出错" << endl;
			return false;
		}
	}
	else if ((*itAnalysisCur).type == Operator_Not_Equal_To)	// !=
	{
		outAnalysisFile << "G: rterm1 -> != aexpr" << endl;
		outAnalysisFile << "1> 分析出 !=" << endl;
		itAnalysisCur++;
		//aexpr
		if (!grammarAnalysis_aexpr(itAnalysisCur, TokenenList))
		{
			outAnalysisFile << "E: 分析 aexpr 出错" << endl;
			return false;
		}
	}
	else if ((*itAnalysisCur).type == Operator_Is_Equal) // ==
	{
		outAnalysisFile << "G: rterm1 -> == aexpr" << endl;
		outAnalysisFile << "1> 分析出 ==" << endl;
		itAnalysisCur++;
		//aexpr
		if (!grammarAnalysis_aexpr(itAnalysisCur, TokenenList))
		{
			outAnalysisFile << "E: 分析 aexpr 出错" << endl;
			return false;
		}
	}
	return true;
}
/*
aexpr -> term aexpr1
*/
bool GrammarAnalysis::grammarAnalysis_aexpr(list<Token>::iterator & itAnalysisCur, list<Token>& TokenenList)
{
	outAnalysisFile << "G: aexpr -> term aexpr1" << endl;
	//term
	if (!grammarAnalysis_term(itAnalysisCur, TokenenList))
	{
		outAnalysisFile << "E: 分析 term 出错" << endl;
		return false;
	}
	//aexpr1
	if (!grammarAnalysis_aexpr1(itAnalysisCur, TokenenList))
	{
		outAnalysisFile << "E: 分析 aexpr1 出错" << endl;
		return false;
	}
	return true;
}
/*
aexpr1 -> + term aexpr1
aexpr1 -> - term aexpr1
aexpr1 -> $
*/
bool GrammarAnalysis::grammarAnalysis_aexpr1(list<Token>::iterator & itAnalysisCur, list<Token>& TokenenList)
{
	if (itAnalysisCur == TokenenList.end())	//判断是否分析到Tokenen串的末尾
	{
		outAnalysisFile << "已经分析到Tokenen串的末尾" << endl;
		itAnalysisCur--;
		cout << "语法错误：在第" << (*itAnalysisCur).lineNo << "行，程序不完整，缺少必要内容" << endl;
		itAnalysisCur++;
		return false;
	}
	if ((*itAnalysisCur).type == Operator_Plus) // +
	{
		outAnalysisFile << "G: aexpr1 -> + term aexpr1" << endl;
		outAnalysisFile << "1> 分析出 +" << endl;
		itAnalysisCur++;
		//term
		if (!grammarAnalysis_term(itAnalysisCur, TokenenList))
		{
			outAnalysisFile << "E: 分析 term 出错" << endl;
			return false;
		}
		//aexpr1
		if (!grammarAnalysis_aexpr1(itAnalysisCur, TokenenList))
		{
			outAnalysisFile << "E: 分析 aexpr1 出错" << endl;
			return false;
		}
	}
	else if ((*itAnalysisCur).type == Operator_Minus) // -
	{
		outAnalysisFile << "G: aexpr1 -> - term aexpr1" << endl;
		outAnalysisFile << "1> 分析出 -" << endl;
		itAnalysisCur++;
		//term
		if (!grammarAnalysis_term(itAnalysisCur, TokenenList))
		{
			outAnalysisFile << "E: 分析 term 出错" << endl;
			return false;
		}
		//aexpr1
		if (!grammarAnalysis_aexpr1(itAnalysisCur, TokenenList))
		{
			outAnalysisFile << "E: 分析 aexpr1 出错" << endl;
			return false;
		}
	}
	return true;
}
/*
term -> factor term1
*/
bool GrammarAnalysis::grammarAnalysis_term(list<Token>::iterator & itAnalysisCur, list<Token>& TokenenList)
{
	outAnalysisFile << "G: term -> factor term1" << endl;
	//分析factor
	if (!grammarAnalysis_factor(itAnalysisCur, TokenenList))
	{
		outAnalysisFile << "E: 分析 factor 出错" << endl;
		return false;
	}
	//分析term1
	if (!grammarAnalysis_term1(itAnalysisCur, TokenenList))
	{
		outAnalysisFile << "E: 分析 term1 出错" << endl;
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
bool GrammarAnalysis::grammarAnalysis_term1(list<Token>::iterator & itAnalysisCur, list<Token>& TokenenList)
{
	if (itAnalysisCur == TokenenList.end())	//判断是否分析到Tokenen串的末尾
	{
		outAnalysisFile << "已经分析到Tokenen串的末尾" << endl;
		itAnalysisCur--;
		cout << "语法错误：在第" << (*itAnalysisCur).lineNo << "行，程序不完整，缺少必要内容" << endl;
		itAnalysisCur++;
		return false;
	}
	//分析 * / %
	if ((*itAnalysisCur).type == Operator_Multiply)
	{
		outAnalysisFile << "G: term1 -> * factor term1" << endl;
		outAnalysisFile << "1> 分析出 *" << endl;
		itAnalysisCur++;
		//分析factor
		if (!grammarAnalysis_factor(itAnalysisCur, TokenenList))
		{
			outAnalysisFile << "E: 分析 factor 出错" << endl;
			return false;
		}
		//分析term1
		if (!grammarAnalysis_term1(itAnalysisCur, TokenenList))
		{
			outAnalysisFile << "E: 分析 term1 出错" << endl;
			return false;
		}
	}
	if ((*itAnalysisCur).type == Operator_Divide)
	{
		outAnalysisFile << "G: term1 -> / factor term1" << endl;
		outAnalysisFile << "1> 分析出 /" << endl;
		itAnalysisCur++;
		//分析factor
		if (!grammarAnalysis_factor(itAnalysisCur, TokenenList))
		{
			outAnalysisFile << "E: 分析 factor 出错" << endl;
			return false;
		}
		//分析term1
		if (!grammarAnalysis_term1(itAnalysisCur, TokenenList))
		{
			outAnalysisFile << "E: 分析 term1 出错" << endl;
			return false;
		}
	}
	if ((*itAnalysisCur).type == Operator_Mod)
	{
		outAnalysisFile << "G: term1 -> % factor term1" << endl;
		outAnalysisFile << "1> 分析出 %" << endl;
		itAnalysisCur++;
		//分析factor
		if (!grammarAnalysis_factor(itAnalysisCur, TokenenList))
		{
			outAnalysisFile << "E: 分析 factor 出错" << endl;
			return false;
		}
		//分析term1
		if (!grammarAnalysis_term1(itAnalysisCur, TokenenList))
		{
			outAnalysisFile << "E: 分析 term1 出错" << endl;
			return false;
		}
	}
	return true;
}
/*
factor -> ! ael
factor -> ael
*/
bool GrammarAnalysis::grammarAnalysis_factor(list<Token>::iterator & itAnalysisCur, list<Token>& TokenenList)
{
	if (itAnalysisCur == TokenenList.end())	//判断是否分析到Tokenen串的末尾
	{
		outAnalysisFile << "E: 已经分析到Tokenen串的末尾" << endl;
		itAnalysisCur--;
		cout << "语法错误：在第" << (*itAnalysisCur).lineNo << "行，程序不完整，缺少必要内容" << endl;
		itAnalysisCur++;
		return false;
	}
	if ((*itAnalysisCur).type == Operator_Not)	// !
	{
		outAnalysisFile << "G: factor -> ! ael" << endl;
		outAnalysisFile << "1> 分析出 !" << endl;
		itAnalysisCur++;
		//分析ael
		if (!grammarAnalysis_ael(itAnalysisCur, TokenenList))
		{
			outAnalysisFile << "E: 分析 ael 出错" << endl;
			return false;
		}
		return true;
	}
	else
	{
		outAnalysisFile << "G: factor -> ael" << endl;
		//分析ael
		if (!grammarAnalysis_ael(itAnalysisCur, TokenenList))
		{
			outAnalysisFile << "E: 分析 ael 出错" << endl;
			return false;
		}
		return true;
	}
}
/*
	ael -> ( bexpr )
	ael -> root
*/
bool GrammarAnalysis::grammarAnalysis_ael(list<Token>::iterator & itAnalysisCur, list<Token>& TokenenList)
{
	if (itAnalysisCur == TokenenList.end())	//判断是否分析到Tokenen串的末尾
	{
		outAnalysisFile << "E:已经分析到Tokenen串的末尾" << endl;
		itAnalysisCur--;
		cout << "语法错误：在第" << (*itAnalysisCur).lineNo << "行，程序不完整，缺少必要内容" << endl;
		itAnalysisCur++;
		return false;
	}
	if ((*itAnalysisCur).type == Delimiter_Left_Small_Bracket)	//左小括号
	{
		outAnalysisFile << "G: ael -> ( bexpr )" << endl;
		outAnalysisFile << "1> 分析出 (" << endl;
		itAnalysisCur++;
		// 分析bexpr
		if (itAnalysisCur == TokenenList.end())	//判断是否分析到Tokenen串的末尾
		{
			outAnalysisFile << "E: 已经分析到Tokenen串的末尾" << endl;
			return false;
		}
		if ((*itAnalysisCur).type != Delimiter_Right_Small_Bracket)	//右小括号
		{
			outAnalysisFile << "E: 分析 ) 出错" << endl;
			return false;
		}
		outAnalysisFile << "1> 分析出 )" << endl;
		itAnalysisCur++;
	}
	else
	{
		outAnalysisFile << "G: ael -> root" << endl;
		if (!grammarAnalysis_root(itAnalysisCur, TokenenList))
		{
			outAnalysisFile << "E: 分析 root 出错" << endl;
			return false;
		}
	}
	return true;
}
/*
	root -> id(变量)
	root -> 整型(八进制、十进制、十六进制)
	root -> 浮点型( 小数、指数 )
	root -> 布尔型 BOOL
	root -> 字符型
*/
bool GrammarAnalysis::grammarAnalysis_root(list<Token>::iterator & itAnalysisCur, list<Token>& TokenenList)
{
	if (itAnalysisCur == TokenenList.end())	//判断是否分析到Tokenen串的末尾
	{
		outAnalysisFile << "E: 已经分析到Tokenen串的末尾" << endl;
		//提示错误
		itAnalysisCur--;
		cout << "语法错误：在第" << (*itAnalysisCur).lineNo << "行，程序不完整，缺少必要内容" << endl;
		itAnalysisCur++;
		return false;
	}
	if ((*itAnalysisCur).type == Identifier)	//id
	{
		outAnalysisFile << "G: root -> id(变量)" << endl;
		outAnalysisFile << "1> 分析出 id " << (*itAnalysisCur).data << endl;
		itAnalysisCur++;
	}
	else if ((*itAnalysisCur).type == Character)	//字符
	{
		outAnalysisFile << "G: root -> 字符型" << endl;
		outAnalysisFile << "1> 分析出 char " << (*itAnalysisCur).data << endl;
		itAnalysisCur++;
	}
	else if ((*itAnalysisCur).type == Number_Octonary)	//整型 八进制
	{
		outAnalysisFile << "G: root -> 整型(八进制)" << endl;
		outAnalysisFile << "1> 分析出 整型(八进制) " << (*itAnalysisCur).data << endl;
		itAnalysisCur++;
	}
	else if ((*itAnalysisCur).type == Number_Decimalism)	//整型 十进制
	{
		outAnalysisFile << "G: root -> 整型(十进制)" << endl;
		outAnalysisFile << "1> 分析出 整型(十进制) " << (*itAnalysisCur).data << endl;
		itAnalysisCur++;
	}
	else if ((*itAnalysisCur).type == Number_Hexadecimal)	//整型 十六进制
	{
		outAnalysisFile << "G: root -> 整型(十六进制)" << endl;
		outAnalysisFile << "1> 分析出 整型(十六进制) " << (*itAnalysisCur).data << endl;
		itAnalysisCur++;
	}
	else if ((*itAnalysisCur).type == Number_Decimals)	//浮点型 小数
	{
		outAnalysisFile << "G: root -> 浮点型( 小数 )" << endl;
		outAnalysisFile << "1> 分析出 浮点型( 小数 ) " << (*itAnalysisCur).data << endl;
		itAnalysisCur++;
	}
	else if ((*itAnalysisCur).type == Number_Exponent)	//浮点型 指数
	{
		outAnalysisFile << "G: root -> 浮点型( 指数 )" << endl;
		outAnalysisFile << "1> 分析出 浮点型( 指数 ) " << (*itAnalysisCur).data << endl;
		itAnalysisCur++;
	}
	else if (grammarAnalysisBOOL(itAnalysisCur, TokenenList))
	{
		//分析BOOL
	}
	else
	{
		return false;
	}
	return true;
}
/*
BOOL -> true
BOOL -> false
*/
bool GrammarAnalysis::grammarAnalysisBOOL(list<Token>::iterator & itAnalysisCur, list<Token>& TokenenList)
{
	if (itAnalysisCur == TokenenList.end())	//判断是否分析到Tokenen串的末尾
	{
		outAnalysisFile << "E: 已经分析到Tokenen串的末尾" << endl;
		return false;
	}
	if ((*itAnalysisCur).type == Keyword_true)
	{
		outAnalysisFile << "G: BOOL -> true" << endl;
		outAnalysisFile << "1> 分析出 true" << endl;
		itAnalysisCur++;	//更新当前分析Tokenen串的位置
	}
	else if ((*itAnalysisCur).type == Keyword_false)
	{
		outAnalysisFile << "G: BOOL -> false" << endl;
		outAnalysisFile << "1> 分析出 false " << endl;
		itAnalysisCur++;	//更新当前分析Tokenen串的位置
	}
	else
	{
		return false;//表明当前分析的Tokenen串不是一个布尔量，返回
	}
	return true;
}

bool GrammarAnalysis::expressPreAnalysis(int type)
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
//识别语法错误
int GrammarAnalysis::recogniseGrammarError(list<Token>::iterator& itAnalysisCur, int curType, int nextType)
{
	//Token丢失
	if ((*itAnalysisCur).type == nextType)
	{
		return TokenLose;
	}
	//Token多余
	if ((*(++itAnalysisCur)).type == curType)
	{
		--itAnalysisCur;
		return TokenExcess;
	}
	--itAnalysisCur;
	//Token不匹配
	if ((*(++itAnalysisCur)).type == curType)
	{
		--itAnalysisCur;
		return TokenExcess;
	}
	--itAnalysisCur;
	return TokenMismatch;
}
