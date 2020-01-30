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
//��ʹ��LL1Ԥ�����������miniC���ԣ����ܰ���ȫ�ֱ�����
bool GrammarAnalysis::grammarAnalysisUsingLL1WithoutGlobalVariable(list<Token>& listToken)
{
	ofstream fout("analysis\\grammarAnalysisUsingLL1.txt");
	grammar_for_miniC = new LL_1_Analysis("grammar\\grammar_for_miniC.txt");
	fout << "********************************************" << endl;
	fout << "*        LL1Ԥ�����,������ȫ�ֱ���        *" << endl;
	fout << "********************************************" << endl;
	if ((*grammar_for_miniC).runGrammarAnalysis(listToken))
	{
		//cout << endl << "�����ɹ�" << endl << endl;
		//(*grammar_for_miniC).printAnalysisResult();
		(*grammar_for_miniC).saveAnalysisResultToFile(fout);	//��LL1Ԥ���������������ļ���
		//return true;
	}
	else
	{
		//cout << endl << "�﷨��������" << endl << endl;
		delete grammar_for_miniC;
		return false;
	}
	delete grammar_for_miniC;
	fout.close();
	return true;
}
//2.
//ʹ�õݹ��½���LL1Ԥ�����������miniC���ԣ�LL1���� ������
bool GrammarAnalysis::grammarAnalysisUsingRecursiveDescentAndLL1_1(list<Token>& listToken)
{
	outAnalysisFile.open("analysis\\grammarAnalysisUsingRecursiveDescentAndLL1_1.txt");
	grammar_for_function_body = new LL_1_Analysis("grammar\\grammar_for_function_body.txt");
	analysis_function_body_using_LL1 = true;
	outAnalysisFile << "********************************************" << endl;
	outAnalysisFile << "*  LL1Ԥ������������塢ʵ�֣�ȫ�ֱ������� *" << endl;
	outAnalysisFile << "*            �ݹ��½�����������            *" << endl;
	outAnalysisFile << "********************************************" << endl;
	list<Token>::iterator it_AnalysisCur = listToken.begin();
	grammarTree->root->data = "�﷨������";	//�﷨��������ʼ��
	if (grammarAnalysisS(it_AnalysisCur, listToken, grammarTree->root))
	{
		//cout << endl << "�����ɹ�" << endl << endl;
		//return true;
	}
	else
	{
		//cout << endl << "�﷨��������" << endl << endl;
		delete grammar_for_function_body;
		return false;
	}
	delete grammar_for_function_body;
	outAnalysisFile.close();
	return true;
}
//3.
//ʹ�õݹ��½���LL1Ԥ�����������miniC���ԣ�LL1������ ���ʽ
bool GrammarAnalysis::grammarAnalysisUsingRecursiveDescentAndLL1_2(list<Token>& listToken)
{
	outAnalysisFile.open("analysis\\grammarAnalysisUsingRecursiveDescentAndLL1_2.txt");
	grammar_for_expression = new LL_1_Analysis("grammar\\grammar_for_expression.txt");
	analysis_express_using_LL1 = true;
	outAnalysisFile << "********************************************" << endl;
	outAnalysisFile << "*             LL1Ԥ��������ʽ            *" << endl;
	outAnalysisFile << "*            �ݹ��½����������﷨          *" << endl;
	outAnalysisFile << "********************************************" << endl;
	list<Token>::iterator it_AnalysisCur = listToken.begin();
	grammarTree->root->data = "�﷨������";	//�﷨��������ʼ��
	if (grammarAnalysisS(it_AnalysisCur, listToken, grammarTree->root))
	{
		//cout << endl << "�����ɹ�" << endl << endl;
		//return true;
	}
	else
	{
		//cout << endl << "�﷨��������" << endl << endl;
		delete grammar_for_expression;
		return false;
	}
	delete grammar_for_expression;
	outAnalysisFile.close();
	return true;
}
//4.
//��ʹ�õݹ��½�����miniC����
bool GrammarAnalysis::grammarAnalysisUsingRecursiveDescent(list<Token>& TokenenList)
{
	outAnalysisFile.open("analysis\\grammarAnalysisUsingRecursiveDescent.txt");
	outAnalysisFile << "********************************************" << endl;
	outAnalysisFile << "*             �ݹ��½��﷨����             *" << endl;
	outAnalysisFile << "********************************************" << endl;

	list<Token>::iterator it_AnalysisCur = TokenenList.begin();
	grammarTree->root->data = "�﷨������";	//�﷨��������ʼ��
	if (grammarAnalysisS(it_AnalysisCur, TokenenList, grammarTree->root))
	{
		//cout << endl << "�����ɹ�" << endl << endl;
		//ll1.printAnalysisResult();
		//grammar_for_function_body.printAnalysisResult();
		//return true;
	}
	else
	{
		//cout << endl << "�﷨��������" << endl << endl;
		return false;
	}
	outAnalysisFile.close();
	return true;
}
//5.
//ʹ��LL1Ԥ����������ո��º���ķ�����
bool GrammarAnalysis::grammarAnalysisUsingLL1_2(list<Token>& listToken)
{
	//analysis\\grammarAnalysisUsingLL1_2.txt
	grammar_for_miniC_2 = new LL_1_Analysis("grammar\\grammar_for_miniC_2.txt");
	ofstream fout("analysis\\grammarAnalysisUsingLL1_2.txt");
	fout << "********************************************" << endl;
	fout << "*         LL1Ԥ�����,���º���ķ�         *" << endl;
	fout << "********************************************" << endl;
	if ((*grammar_for_miniC_2).runGrammarAnalysis(listToken))
	{
		//cout << endl << "LL1Ԥ�����ʹ�ø��º���ķ��������ɹ�" << endl << endl;
		//(*grammar_for_miniC_2).printAnalysisResult();
		(*grammar_for_miniC_2).saveAnalysisResultToFile(fout);
	}
	else
	{
		//cout << endl << "�﷨��������" << endl << endl;
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
// ȫ�ֱ������塢��������������ʵ��
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
			outAnalysisFile << "E: ���� F ����" << endl;
			return false;
		}
		if (!grammarAnalysisS(it_AnalysisCur, listToken, node))
		{
			outAnalysisFile << "E: ���� S ����" << endl;
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
	// ���� MT1
	int memoryType = Keyword_extern;
	if (grammarAnalysisMT1(it_AnalysisCur, listToken, memoryType))
	{
		//cout << "����MT1�ɹ�" << endl;
	}
	// ���� DT
	int dataType = Error;
	if (grammarAnalysisDT(it_AnalysisCur, listToken, dataType))
	{
		//cout << "����DT�ɹ�" << endl;
	}
	grammarTreeTmp.dataType = dataType;
	// ���� F1
	if (!grammarAnalysisF1(it_AnalysisCur, listToken, grammarTreeTmp))
	{
		outAnalysisFile << "E: ���� F1 ����" << endl;
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
	case 2:	//��������
	{
		FunctionDefinition *fd = new FunctionDefinition(grammarTreeTmp);
		(*fd).isComeTrue = false;
		node->addChildToRoot(fd);
		break;
	}
	case 3:	//����ʵ��
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
	// ���� ID �� ��С����
	if ((*it_AnalysisCur).type == Identifier && (++it_AnalysisCur) != listToken.end() &&
		(*it_AnalysisCur).type == Delimiter_Left_Small_Bracket)	// id ( ��С����
	{
		outAnalysisFile << "G: F1 -> functionName ( PL ) F2" << endl;
		//cout << "��������" << functionName << endl;
		outAnalysisFile << "1> ������ functionName " << functionName << endl;
		outAnalysisFile << "1> ������ (" << endl;
		tmp.functionName = functionName;	//�����������ص�tmp��ȥ
		it_AnalysisCur++;	//���µ�ǰ����Tokenen����λ��
							//���� PL
		if (!grammarAnalysisPL(it_AnalysisCur, listToken, tmp.parameterList))	//����PL������
		{
			outAnalysisFile << "E: ���� PL ����" << endl;
			return false;
		}
		//���� ��С����
		if (it_AnalysisCur == listToken.end())
		{
			outAnalysisFile << "E: �Ѿ�������Tokenen����ĩβ" << endl;
			return false;
		}
		if ((*it_AnalysisCur).type != Delimiter_Right_Small_Bracket)	// ) ��С����
		{
			outAnalysisFile << "E: ���� ) ����" << endl;
			return false;
		}
		outAnalysisFile << "1> ������ )" << endl;
		it_AnalysisCur++;	//���µ�ǰ����Tokenen����λ��
		if (!grammarAnalysisF2(it_AnalysisCur, listToken, tmp))	//����������
		{
			outAnalysisFile << "E: ���� F2 ����" << endl;
			return false;
		}
	}
	else // F1 -> VL ;
	{
		outAnalysisFile << "G: F1 -> VL ;" << endl;
		--it_AnalysisCur;	//����֮ǰ����Tokenen����λ��
							//����VL
		tmp.tmpType = 1;	//�ⲿ���ݶ���
		if (!grammarAnalysisVL(it_AnalysisCur, listToken, tmp.variableList))
		{
			outAnalysisFile << "E: ���� VL ����" << endl;
			return false;
		}
		if (it_AnalysisCur == listToken.end())	//����������ĩβ
		{
			outAnalysisFile << "E: �Ѿ�������Tokenen����ĩβ" << endl;
			return false;
		}
		//�����ֺ� ;
		if (Delimiter_Semicolon != (*it_AnalysisCur).type)
		{
			outAnalysisFile << "E: ���� ; ����" << endl;
			return false;
		}
		outAnalysisFile << "1> ������ ;" << endl;
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
	if (it_AnalysisCur == listToken.end())//��ǰ����λ���Ƿ����
	{
		outAnalysisFile << "E: �Ѿ�������Tokenen����ĩβ" << endl;
		return false;
	}
	if ((*it_AnalysisCur).type == Delimiter_Semicolon)	//�Ƿ�Ϊ�ֺ�
	{
		outAnalysisFile << "G: F2 -> ;" << endl;
		tmp.tmpType = 2;	//��������
							//cout << "����������������" << endl;
		it_AnalysisCur++;	//���µ�ǰ����Tokenen����λ��
	}
	else if ((*it_AnalysisCur).type == Delimiter_Left_Large_Bracket)	//�Ƿ�Ϊ�������
	{
		outAnalysisFile << "G: F2 -> { FB }" << endl;
		it_AnalysisCur++;	//���µ�ǰ����Tokenen����λ��
		tmp.tmpType = 3;	//����ʵ��
		if (analysis_function_body_using_LL1)
		{
			list<Token> tempList;
			int countFindRightLargeBracket = 0;	//�ҵ��Ҵ����ŵĸ���
			while (it_AnalysisCur != listToken.end())
			{
				if ((*it_AnalysisCur).type == Delimiter_Right_Large_Bracket)	//�Ƿ�Ϊ�Ҵ�����
				{	//����whileѭ�������µ�ǰ����Tokenen����λ��
					countFindRightLargeBracket++;	//�ҵ��Ҵ�����
					if (countFindRightLargeBracket == 1)
					{
						it_AnalysisCur++;	//���µ�ǰ����Tokenen����λ��
						break;
					}
					else
					{
						tempList.push_back(*it_AnalysisCur);	//��Tokenen����ӵ�List������
						it_AnalysisCur++;	//���µ�ǰ����Tokenen����λ��
					}
				}
				else if ((*it_AnalysisCur).type == Delimiter_Left_Large_Bracket)	//�Ƿ�Ϊ�������
				{
					tempList.push_back(*it_AnalysisCur);	//��Tokenen����ӵ�List������
					it_AnalysisCur++;	//���µ�ǰ����Tokenen����λ��
					countFindRightLargeBracket--;
				}
				else
				{
					tempList.push_back(*it_AnalysisCur);	//��Tokenen����ӵ�List������
					it_AnalysisCur++;	//���µ�ǰ����Tokenen����λ��
				}
			}
			if (!(*grammar_for_function_body).runGrammarAnalysis(tempList))
			{
				//cout << "��������ڴ���" << endl;
				(*grammar_for_function_body).printAnalysisResult();
				return false;
			}
			(*grammar_for_function_body).saveAnalysisResultToFile(outAnalysisFile);
			if (countFindRightLargeBracket != 1)
			{
				//cout << "ȱ���Ҵ�����" << endl;
			}
		}
		else
		{
			// FB
			if (!grammarAnalysisFB(it_AnalysisCur, listToken))
			{
				outAnalysisFile << "E: ���� FB ����" << endl;
				return false;
			}
			// } �Ҵ�����
			if (it_AnalysisCur == listToken.end())	//����������ĩβ
			{
				outAnalysisFile << "E: �Ѿ�������Tokenen����ĩβ" << endl;
				return false;
			}
			if ((*it_AnalysisCur).type != Delimiter_Right_Large_Bracket)	//�Ƿ�Ϊ�Ҵ�����
			{
				outAnalysisFile << "E: ���� } ����" << endl;
				return false;
			}
			it_AnalysisCur++;//���µ�ǰ����Tokenen����λ��
			outAnalysisFile << "1> ������ }" << endl;
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
	if (it_AnalysisCur == listToken.end())	//��ǰ����λ���Ƿ����
	{
		outAnalysisFile << "E: �Ѿ�������Tokenen����ĩβ" << endl;
		return false;
	}
	if ((*it_AnalysisCur).type == Keyword_auto)	//auto
	{
		outAnalysisFile << "G: MT -> auto" << endl;
		outAnalysisFile << "1> ������ auto" << endl;
		memoryType = Keyword_auto;
		it_AnalysisCur++;	//���µ�ǰ����Tokenen����λ��
		return true;
	}
	else if ((*it_AnalysisCur).type == Keyword_register)
	{
		outAnalysisFile << "G: MT -> register" << endl;
		outAnalysisFile << "1> ������ register" << endl;
		memoryType = Keyword_register;
		it_AnalysisCur++;	//���µ�ǰ����Tokenen����λ��
		return true;
	}
	else if (grammarAnalysisMT1(it_AnalysisCur, listToken, memoryType))
	{
		return true;
	}
	else
	{
		outAnalysisFile << "E: ���� MT1 ����" << endl;
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
	if (it_AnalysisCur == listToken.end())	//��ǰ����λ���Ƿ����
	{
		outAnalysisFile << "E: �Ѿ�������Tokenen����ĩβ" << endl;
		return false;
	}
	if ((*it_AnalysisCur).type == Keyword_extern)
	{
		outAnalysisFile << "G: MT1 -> extern" << endl;
		outAnalysisFile << "1> ������ extern" << endl;
		memoryType = Keyword_extern;
		it_AnalysisCur++;	//���µ�ǰ����Tokenen����λ��
		return true;
	}
	else if ((*it_AnalysisCur).type == Keyword_static)
	{
		outAnalysisFile << "G: MT1 -> static" << endl;
		outAnalysisFile << "1> ������ static" << endl;
		memoryType = Keyword_static;
		it_AnalysisCur++;	//���µ�ǰ����Tokenen����λ��
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
	if (it_AnalysisCur == listToken.end())//��ǰ����λ���Ƿ����
	{
		outAnalysisFile << "�Ѿ�������Tokenen����ĩβ" << endl;
		return false;
	}
	if ((*it_AnalysisCur).type == Keyword_void)
	{
		outAnalysisFile << "G: DT -> void" << endl;
		outAnalysisFile << "1> ������ void" << endl;
		dataType = Keyword_void;
		it_AnalysisCur++;	//���µ�ǰ����Tokenen����λ��
		return true;
	}
	else if ((*it_AnalysisCur).type == Keyword_int)
	{
		outAnalysisFile << "G: DT -> int" << endl;
		outAnalysisFile << "1> ������ int" << endl;
		dataType = Keyword_int;
		it_AnalysisCur++;	//���µ�ǰ����Tokenen����λ��
		return true;
	}
	else if ((*it_AnalysisCur).type == Keyword_char)
	{
		outAnalysisFile << "G: DT -> char" << endl;
		outAnalysisFile << "1> ������ char" << endl;
		dataType = Keyword_char;
		it_AnalysisCur++;	//���µ�ǰ����Tokenen����λ��
		return true;
	}
	else if ((*it_AnalysisCur).type == Keyword_float)
	{
		outAnalysisFile << "G: DT -> float" << endl;
		outAnalysisFile << "1> ������ float" << endl;
		dataType = Keyword_float;
		it_AnalysisCur++;	//���µ�ǰ����Tokenen����λ��
		return true;
	}
	else if ((*it_AnalysisCur).type == Keyword_double)
	{
		outAnalysisFile << "G: DT -> double" << endl;
		outAnalysisFile << "1> ������ double" << endl;
		dataType = Keyword_double;
		it_AnalysisCur++;	//���µ�ǰ����Tokenen����λ��
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
	//����VD
	VariableList variable;
	if (!grammarAnalysisVD(it_AnalysisCur, listToken, variable))
	{
		outAnalysisFile << "E: ���� VD ����" << endl;
		return false;
	}
	variableList.push_back(variable);
	//����VL1
	if (!grammarAnalysisVL1(it_AnalysisCur, listToken, variableList))
	{
		outAnalysisFile << "E: ���� VL1 ����" << endl;
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
	//�ж��Ƿ������ĩβ
	if (it_AnalysisCur == listToken.end())
	{
		outAnalysisFile << "E: �Ѿ�������Tokenen����ĩβ" << endl;
		return false;
	}
	// VL1 -> , VD VL1
	//�����Ƿ�Ϊ���� ,
	if (Delimiter_Comma == (*it_AnalysisCur).type)
	{
		outAnalysisFile << "G: VL1 -> , VD VL1" << endl;
		it_AnalysisCur++;//���µ�ǰ����Tokenen����λ��
						 //����VL1
		VariableList variable;
		if (!grammarAnalysisVD(it_AnalysisCur, listToken, variable))
		{
			outAnalysisFile << "E: ���� VD ����" << endl;
			return false;
		}
		variableList.push_back(variable);
		if (!grammarAnalysisVL1(it_AnalysisCur, listToken, variableList))
		{
			outAnalysisFile << "E: ���� VL1 ����" << endl;
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
	//�Ƿ������Tokenen����ĩβ
	if (it_AnalysisCur == listToken.end())	//û�з�����ĩβ
	{
		outAnalysisFile << "E; �Ѿ�������Tokenen����ĩβ" << endl;
		return false;
	}
	//�ж��Ƿ�ΪID
	if (Identifier == (*it_AnalysisCur).type)
	{
		outAnalysisFile << "1> ������ variableName " << (*it_AnalysisCur).data << endl;
		variable.varName = (*it_AnalysisCur).data;
		it_AnalysisCur++;//���µ�ǰ����Tokenen����λ��
						 //����VD1
		if (!grammarAnalysisVD1(it_AnalysisCur, listToken, variable.initValue))
		{
			outAnalysisFile << "E: ���� VD1 ����" << endl;
			return false;
		}
	}
	return true;
}

/*
	VD1 -> = PR (����ͨ������ ���� �� �ֺ� ������)
	VD1 -> $
*/
bool GrammarAnalysis::grammarAnalysisVD1(list<Token>::iterator & it_AnalysisCur, list<Token>& listToken, list<Token>& initValue)
{
	//�ж��Ƿ������Tokenen����ĩβ
	if (it_AnalysisCur == listToken.end())	//û�з�����ĩβ
	{
		outAnalysisFile << "E: �Ѿ�������Tokenen����ĩβ" << endl;
		return false;
	}
	// VD1 -> = PR
	//�����Ƿ�Ϊ�Ⱥ� =
	if (Operator_Equal == (*it_AnalysisCur).type)	//Ϊ�Ⱥ�
	{
		outAnalysisFile << "G: VD1 -> = PR" << endl;
		outAnalysisFile << "1> ������ =" << endl;
		//ʹ��LL(1)Ԥ��������������ʽ
		if (analysis_express_using_LL1)
		{
			list<Token> tmpList;
			tmpList.push_back(*(--it_AnalysisCur));  //��Id��ӵ�List��
			++it_AnalysisCur;
			tmpList.push_back(*it_AnalysisCur); //����ֵ������ӵ�List��
			it_AnalysisCur++;//���µ�ǰ����Tokenen����λ��
							 //����PR
			while (it_AnalysisCur != listToken.end())
			{
				if ((*it_AnalysisCur).type == Delimiter_Semicolon || (*it_AnalysisCur).type == Delimiter_Comma)	//���� �� �ֺ�
				{
					break;
				}
				tmpList.push_back(*it_AnalysisCur); //���Ƶ�List��
				initValue.push_back(*it_AnalysisCur);
				it_AnalysisCur++; //���µ�ǰ����Tokenen����λ��
			}
			if ((*grammar_for_expression).runGrammarAnalysis(tmpList))
			{
				//cout << endl << "����PR�ɹ�" << endl;
				(*grammar_for_expression).saveAnalysisResultToFile(outAnalysisFile);
			}
			else
			{
				//cout << endl << "����PR�������﷨����" << endl;
				return false;
			}
		}
		//ʹ�õݹ��½��ķ����������ʽ
		else
		{
			it_AnalysisCur++; //���µ�ǰ����Tokenen����λ��
			if (!grammarAnalysis_bexpr(it_AnalysisCur, listToken))
			{
				outAnalysisFile << "E: ���� PR ����" << endl;
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
		//cout << "����PL1�ɹ�" << endl;
		return true;
	}
	//cout << "����PL1ʧ�ܣ�����ԭ������λ��" << endl;
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
	//����PD
	ParameterList parameter;
	if (!grammarAnalysisPD(it_AnalysisCur, listToken, parameter))	//����PD������
	{
		outAnalysisFile << "E: ���� PD ����" << endl;
		return false;
	}
	parameterList.push_back(parameter);
	//����PL2
	if (!grammarAnalysisPL2(it_AnalysisCur, listToken, parameterList))	//����PL2������
	{
		outAnalysisFile << "E: ���� PL2 ����" << endl;
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
	//�ж��Ƿ������Tokenen����ĩβ
	if (it_AnalysisCur == listToken.end())
	{
		outAnalysisFile << "�Ѿ�������Tokenen����ĩβ" << endl;
		return false;
	}
	//�ж��Ƿ�Ϊ ���� ,
	if (Delimiter_Comma == (*it_AnalysisCur).type) // PL2 -> , PD PL2
	{
		outAnalysisFile << "G: PL2 -> , PD PL2" << endl;
		outAnalysisFile << "1> ������ ," << endl;
		it_AnalysisCur++;
		ParameterList parameter;
		if (!grammarAnalysisPD(it_AnalysisCur, listToken, parameter))
		{
			outAnalysisFile << "E: ���� PD ����" << endl;
			return false;
		}
		parameterList.push_back(parameter);	//��ӵ�List
											//����ѭ��PL2
		if (!grammarAnalysisPL2(it_AnalysisCur, listToken, parameterList))
		{
			outAnalysisFile << "E: ���� PL2 ����" << endl;
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
		outAnalysisFile << "E: ���� DT ����" << endl;
		return false;
	}
	parameter.parameterType = dataType;
	string parameterName = "";	//��ʼ��Ϊ���ַ���
	if (!grammarAnalysisPD1(it_AnalysisCur, listToken, parameterName))
	{
		outAnalysisFile << "E: ���� PD1 ����" << endl;
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
		outAnalysisFile << "1> ������ parameterName " << (*it_AnalysisCur).data << endl;
		parameterName = (*it_AnalysisCur).data;
		it_AnalysisCur++;	//���µ�ǰ����Tokenen����λ��
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
		//cout << "����RS����" << endl;
		grammarAnalysisFB(it_AnalysisCur, listToken);
		return true;
	}
	it_AnalysisCur = tempCur;	//�޷�������RS����ָ�֮ǰ��λ��
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
	// �Ƿ������ĩβ
	if (it_AnalysisCur == listToken.end()) //û�з�����ĩβ
	{
		outAnalysisFile << "E: �Ѿ�������Tokenen����ĩβ" << endl;
		return false;
	}
	//���� if
	// RS -> if ( PR ) SB RS1
	if ((*it_AnalysisCur).type == Keyword_if)
	{
		outAnalysisFile << "G: RS -> if ( PR ) SB RS1" << endl;
		outAnalysisFile << "1> ������ if" << endl;
		it_AnalysisCur++;//���µ�ǰ����Tokenen����λ��
						 //����������
		if (it_AnalysisCur == listToken.end())
		{
			outAnalysisFile << "E: �Ѿ�������Tokenen����ĩβ" << endl;
			return false;
		}
		if ((*it_AnalysisCur).type != Delimiter_Left_Small_Bracket)
		{
			outAnalysisFile << "E: ���� ( ����" << endl;
			return false;
		}
		outAnalysisFile << "1> ������ (" << endl;
		it_AnalysisCur++;//���µ�ǰ����Tokenen����λ��
						 //����PR
		if (analysis_express_using_LL1)
		{
			//����PR
			list<Token> tmpList;
			while (it_AnalysisCur != listToken.end())
			{
				if ((*it_AnalysisCur).type == Delimiter_Right_Small_Bracket)
				{
					break;
				}
				tmpList.push_back(*it_AnalysisCur);
				it_AnalysisCur++; //���µ�ǰ����Tokenen����λ��
			}
			if ((*grammar_for_expression).runGrammarAnalysis(tmpList))
			{
				//cout << endl << "����PR�ɹ�" << endl;
				(*grammar_for_expression).saveAnalysisResultToFile(outAnalysisFile);
			}
			else
			{
				//cout << endl << "����PR�������﷨����" << endl;
				return false;
			}
		}
		else
		{
			if (!grammarAnalysis_eexpr(it_AnalysisCur, listToken))
			{
				outAnalysisFile << "E: ���� eexpr ����" << endl;
				return false;
			}
		}
		//����������
		if (it_AnalysisCur == listToken.end())
		{
			outAnalysisFile << "E: �Ѿ�������Tokenen����ĩβ" << endl;
		}
		if ((*it_AnalysisCur).type != Delimiter_Right_Small_Bracket) //��Ϊ��С����
		{
			outAnalysisFile << "E: ���� ) ����" << endl;
		}
		outAnalysisFile << "1> ������ )" << endl;
		it_AnalysisCur++;//���µ�ǰ����Tokenen����λ��
						 //����SB
		if (!grammarAnalysisSB(it_AnalysisCur, listToken))
		{
			outAnalysisFile << "E: ���� SB ����" << endl;
			return false;
		}
		//����RS1
		if (!grammarAnalysisRS1(it_AnalysisCur, listToken))
		{
			outAnalysisFile << "E: ���� RS1 ����" << endl;
			return false;
		}
	}
	//���� while
	//RS -> while (PR) SB
	else if ((*it_AnalysisCur).type == Keyword_while)
	{
		outAnalysisFile << "G: RS -> while (PR) SB" << endl;
		outAnalysisFile << "1> ������ while" << endl;
		it_AnalysisCur++;//���µ�ǰ����Tokenen����λ��
						 //������С����
		if (it_AnalysisCur == listToken.end())
		{
			outAnalysisFile << "E: �Ѿ�������Tokenen����ĩβ" << endl;
			return false;
		}
		if ((*it_AnalysisCur).type != Delimiter_Left_Small_Bracket)
		{
			outAnalysisFile << "E: ���� ( ����" << endl;
			return false;
		}
		outAnalysisFile << "1> ������ (" << endl;
		it_AnalysisCur++;//���µ�ǰ����Tokenen����λ��
						 //����PR
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
				it_AnalysisCur++; //���µ�ǰ����Tokenen����λ��
			}
			if ((*grammar_for_expression).runGrammarAnalysis(tmpList))
			{
				//cout << endl << "����PR�ɹ�" << endl;
				(*grammar_for_expression).saveAnalysisResultToFile(outAnalysisFile);
			}
			else
			{
				//cout << endl << "����PR�������﷨����" << endl;
				return false;
			}
		}
		else
		{
			if (!grammarAnalysis_eexpr(it_AnalysisCur, listToken))
			{
				outAnalysisFile << "E: ���� eexpr ����" << endl;
				return false;
			}
		}
		//������С����
		if (it_AnalysisCur == listToken.end())
		{
			outAnalysisFile << "E: �Ѿ�������Tokenen����ĩβ" << endl;
			return false;
		}
		if ((*it_AnalysisCur).type != Delimiter_Right_Small_Bracket) //��Ϊ��С����
		{
			outAnalysisFile << "E: ���� ) ����" << endl;
			return false;
		}
		outAnalysisFile << "1> ������ )" << endl;
		it_AnalysisCur++;//���µ�ǰ����Tokenen����λ��
						 //����SB
		if (!grammarAnalysisSB(it_AnalysisCur, listToken))
		{
			outAnalysisFile << "E: ���� SB ����" << endl;
			return false;
		}
	}
	//���� do
	//RS -> do SB while ( PR ) ;
	else if ((*it_AnalysisCur).type == Keyword_do)
	{
		outAnalysisFile << "G: RS -> do SB while ( PR ) ;" << endl;
		outAnalysisFile << "1> ������ do" << endl;
		it_AnalysisCur++;//���µ�ǰ����Tokenen����λ��
						 //����SB
		if (!grammarAnalysisSB(it_AnalysisCur, listToken))
		{
			outAnalysisFile << "E: ���� SB ����" << endl;
			return false;
		}
		//����while
		if (it_AnalysisCur == listToken.end())
		{
			outAnalysisFile << "E: �Ѿ�������Tokenen����ĩβ" << endl;
			return false;
		}
		if ((*it_AnalysisCur).type != Keyword_while)
		{
			outAnalysisFile << "E: ���� while ����" << endl;
			return false;
		}
		outAnalysisFile << "1> ������ while" << endl;
		it_AnalysisCur++;//���µ�ǰ����Tokenen����λ��
						 //������С����
		if (it_AnalysisCur == listToken.end())
		{
			outAnalysisFile << "E: �Ѿ�������Tokenen����ĩβ" << endl;
			return false;
		}
		if ((*it_AnalysisCur).type != Delimiter_Left_Small_Bracket)
		{
			outAnalysisFile << "E: ���� ( ����" << endl;
			return false;
		}
		outAnalysisFile << "1> ������ (" << endl;
		it_AnalysisCur++;//���µ�ǰ����Tokenen����λ��
		if (analysis_express_using_LL1)
		{
			//����PR
			list<Token> tmpList;
			while (it_AnalysisCur != listToken.end())
			{
				if ((*it_AnalysisCur).type == Delimiter_Right_Small_Bracket)
				{
					break;
				}
				tmpList.push_back(*it_AnalysisCur);
				it_AnalysisCur++; //���µ�ǰ����Tokenen����λ��
			}
			if ((*grammar_for_expression).runGrammarAnalysis(tmpList))
			{
				//cout << endl << "����PR�ɹ�" << endl;
				(*grammar_for_expression).saveAnalysisResultToFile(outAnalysisFile);
			}
			else
			{
				//cout << endl << "����PR�������﷨����" << endl;
				return false;
			}
		}
		else
		{
			if (!grammarAnalysis_eexpr(it_AnalysisCur, listToken))
			{
				outAnalysisFile << "E: ���� eexpr ����" << endl;
				return false;
			}
		}
		//������С����
		if (it_AnalysisCur == listToken.end())
		{
			outAnalysisFile << "E: �Ѿ�������Tokenen����ĩβ" << endl;
			return false;
		}
		if ((*it_AnalysisCur).type != Delimiter_Right_Small_Bracket) //��Ϊ��С����
		{
			outAnalysisFile << "E: ���� ) ����" << endl;
			return false;
		}
		outAnalysisFile << "1> ������ )" << endl;
		it_AnalysisCur++;//���µ�ǰ����Tokenen����λ��
						 //�����ֺ� ;
		if (it_AnalysisCur == listToken.end())
		{
			outAnalysisFile << "E: �Ѿ�������Tokenen����ĩβ" << endl;
			return false;
		}
		if ((*it_AnalysisCur).type != Delimiter_Semicolon)
		{
			outAnalysisFile << "E: ���� ; ����" << endl;
			return false;
		}
		outAnalysisFile << "1> ������ ;" << endl;
		it_AnalysisCur++;//���µ�ǰ����Tokenen����λ��
	}
	//���� for
	//RS -> for ( PR ; PR ; PR ) SB
	else if ((*it_AnalysisCur).type == Keyword_for)
	{
		outAnalysisFile << "G: RS -> for ( PR ; PR ; PR ) SB" << endl;
		outAnalysisFile << "1> ������ for" << endl;
		it_AnalysisCur++;//���µ�ǰ����Tokenen����λ��
						 //������С����
		if (it_AnalysisCur == listToken.end())
		{
			outAnalysisFile << "E: �Ѿ�������Tokenen����ĩβ" << endl;
			return false;
		}
		if ((*it_AnalysisCur).type != Delimiter_Left_Small_Bracket)
		{
			outAnalysisFile << "E: ���� ( ����" << endl;
			return false;
		}
		outAnalysisFile << "1> ������ (" << endl;
		it_AnalysisCur++;//���µ�ǰ����Tokenen����λ��
		for (int i = 0; i < 2; i++)
		{
			//����PR
			if (analysis_express_using_LL1)
			{
				list<Token> tmpList;
				while (it_AnalysisCur != listToken.end())
				{
					if ((*it_AnalysisCur).type == Delimiter_Comma) //�����Ž���
					{
						break;
					}
					tmpList.push_back(*it_AnalysisCur);
					it_AnalysisCur++; //���µ�ǰ����Tokenen����λ��
				}
				if ((*grammar_for_expression).runGrammarAnalysis(tmpList))
				{
					//cout << endl << "����PR�ɹ�" << endl;
					(*grammar_for_expression).saveAnalysisResultToFile(outAnalysisFile);
				}
				else
				{
					//cout << endl << "����PR�������﷨����" << endl;
					return false;
				}
			}
			else
			{
				if (!grammarAnalysis_eexpr(it_AnalysisCur, listToken))
				{
					outAnalysisFile << "E: ���� eexpr ����" << endl;
					return false;
				}
			}
			//�����ֺ�
			if (it_AnalysisCur == listToken.end())
			{
				outAnalysisFile << "E: �Ѿ�������Tokenen����ĩβ" << endl;
				return false;
			}
			if ((*it_AnalysisCur).type != Delimiter_Semicolon)	// ; �ֺ�
			{
				outAnalysisFile << "E: ���� ; ����" << endl;
				return false;
			}
			outAnalysisFile << "1> ������ ;" << endl;
			it_AnalysisCur++;//���µ�ǰ����Tokenen����λ��
		}
		//����PR
		if (analysis_express_using_LL1)
		{
			list<Token> tmpList;
			while (it_AnalysisCur != listToken.end())
			{
				if ((*it_AnalysisCur).type == Delimiter_Right_Small_Bracket) //����С���Ž���
				{
					break;
				}
				tmpList.push_back(*it_AnalysisCur);
				it_AnalysisCur++; //���µ�ǰ����Tokenen����λ��
			}
			if ((*grammar_for_expression).runGrammarAnalysis(tmpList))
			{
				//cout << endl << "����PR�ɹ�" << endl;
				(*grammar_for_expression).saveAnalysisResultToFile(outAnalysisFile);
			}
			else
			{
				//cout << endl << "����PR�������﷨����" << endl;
				return false;
			}
		}
		else
		{
			if (!grammarAnalysis_eexpr(it_AnalysisCur, listToken))
			{
				outAnalysisFile << "E: ���� eexpr ����" << endl;
				return false;
			}
		}
		//������С����
		if (it_AnalysisCur == listToken.end())
		{
			outAnalysisFile << "E: �Ѿ�������Tokenen����ĩβ" << endl;
			return false;
		}
		if ((*it_AnalysisCur).type != Delimiter_Right_Small_Bracket) //��Ϊ��С����
		{
			outAnalysisFile << "E: ��ǰλ��ȱ����С����" << endl;
			return false;
		}
		outAnalysisFile << "1> ������ )" << endl;
		it_AnalysisCur++;//���µ�ǰ����Tokenen����λ��
						 //����SB
		if (!grammarAnalysisSB(it_AnalysisCur, listToken))
		{
			outAnalysisFile << "E: ���� SB ����" << endl;
			return false;
		}
	}
	//���� break
	//RS -> break ;
	else if ((*it_AnalysisCur).type == Keyword_break)
	{
		outAnalysisFile << "G: RS -> break ;" << endl;
		outAnalysisFile << "1> ������ break" << endl;
		it_AnalysisCur++;//���µ�ǰ����Tokenen����λ��
						 //�����ֺ�
		if (it_AnalysisCur == listToken.end())
		{
			outAnalysisFile << "E: �Ѿ�������Tokenen����ĩβ" << endl;
			return false;
		}
		if ((*it_AnalysisCur).type != Delimiter_Semicolon) //��Ϊ�ֺ�
		{
			outAnalysisFile << "E: ���� ; ����" << endl;
			return false;
		}
		outAnalysisFile << "1> ������ ;" << endl;
		it_AnalysisCur++;//���µ�ǰ����Tokenen����λ��
	}
	//���� continue
	// RS -> continue;
	else if ((*it_AnalysisCur).type == Keyword_continue)
	{
		outAnalysisFile << "G: RS -> continue;" << endl;
		outAnalysisFile << "1> ������ continue" << endl;
		it_AnalysisCur++;//���µ�ǰ����Tokenen����λ��
						 //�����ֺ�
		if (it_AnalysisCur == listToken.end())
		{
			outAnalysisFile << "E: �Ѿ�������Tokenen����ĩβ" << endl;
			return false;
		}
		if ((*it_AnalysisCur).type != Delimiter_Semicolon) //��Ϊ�ֺ�
		{
			outAnalysisFile << "E: ���� ; ����" << endl;
			return false;
		}
		outAnalysisFile << "1> ������ ;" << endl;
		it_AnalysisCur++;//���µ�ǰ����Tokenen����λ��
	}
	//���� return
	//RS -> return PR ;
	else if ((*it_AnalysisCur).type == Keyword_return)
	{
		outAnalysisFile << "G: return PR ;" << endl;
		outAnalysisFile << "1> ������ ;" << endl;
		it_AnalysisCur++;//���µ�ǰ����Tokenen����λ��
		if (analysis_express_using_LL1)
		{
			//����PR
			list<Token> tmpList;
			while (it_AnalysisCur != listToken.end())
			{
				if ((*it_AnalysisCur).type == Delimiter_Semicolon) //���ֺŽ���
				{
					break;
				}
				tmpList.push_back(*it_AnalysisCur);
				it_AnalysisCur++; //���µ�ǰ����Tokenen����λ��
			}
			if ((*grammar_for_expression).runGrammarAnalysis(tmpList))
			{
				//cout << endl << "����PR�ɹ�" << endl;
				(*grammar_for_expression).saveAnalysisResultToFile(outAnalysisFile);
			}
			else
			{
				//cout << endl << "����PR�������﷨����" << endl;
				return false;
			}
		}
		else
		{
			if (!grammarAnalysis_eexpr(it_AnalysisCur, listToken))
			{
				outAnalysisFile << "E: ���� eexpr ����" << endl;
				return false;
			}
		}
		//�����ֺ�
		if (it_AnalysisCur == listToken.end())
		{
			outAnalysisFile << "E: �Ѿ�������Tokenen����ĩβ" << endl;
			return false;
		}
		if ((*it_AnalysisCur).type != Delimiter_Semicolon) //��Ϊ�ֺ�
		{
			outAnalysisFile << "E: ���� ; ����" << endl;
			return false;
		}
		outAnalysisFile << "1> ������ ;" << endl;
		it_AnalysisCur++;//���µ�ǰ����Tokenen����λ��
	}
	//���� goto
	//RS -> goto positionName ;
	else if ((*it_AnalysisCur).type == Keyword_goto)
	{
		outAnalysisFile << "G: RS -> goto positionName ;" << endl;
		outAnalysisFile << "1> ������ goto" << endl;
		it_AnalysisCur++;//���µ�ǰ����Tokenen����λ��
						 //����Id
		if (it_AnalysisCur == listToken.end())
		{
			outAnalysisFile << "E: �Ѿ�������Tokenen����ĩβ" << endl;
			return false;
		}
		if ((*it_AnalysisCur).type != Identifier) //��ΪId
		{
			outAnalysisFile << "E: ���� positionName ����" << endl;
			return false;
		}
		outAnalysisFile << "1> ������ positionName " << (*it_AnalysisCur).data << endl;
		it_AnalysisCur++;//���µ�ǰ����Tokenen����λ��
						 //���� �ֺ�
		if (it_AnalysisCur == listToken.end()) //û�з�����ĩβ
		{
			outAnalysisFile << "E: �Ѿ�������Tokenen����ĩβ" << endl;
			return false;
		}
		if ((*it_AnalysisCur).type != Delimiter_Semicolon)	//�Ƿ�Ϊ�ֺ�
		{
			outAnalysisFile << "E: ���� ; ����" << endl;
			return false;
		}
		outAnalysisFile << "1> ������ ;" << endl;
		it_AnalysisCur++;//���µ�ǰ����Tokenen����λ��
	}
	//���� print
	//RS -> print ( Print
	else if ((*it_AnalysisCur).type == Keyword_print)
	{
		outAnalysisFile << "G: RS -> print ( Print" << endl;
		outAnalysisFile << "1> ������ print" << endl;
		it_AnalysisCur++;//���µ�ǰ����Tokenen����λ��
						 //���� ��С����
		if (it_AnalysisCur == listToken.end())
		{
			outAnalysisFile << "E: �Ѿ�������Tokenen����ĩβ" << endl;
			return false;
		}
		if ((*it_AnalysisCur).type != Delimiter_Left_Small_Bracket)	//�Ƿ�Ϊ��С����
		{
			outAnalysisFile << "E: ���� ( ����" << endl;
			return false;
		}
		outAnalysisFile << "1> ������ (" << endl;
		it_AnalysisCur++;//���µ�ǰ����Tokenen����λ��
		if (!grammarAnalysisPrint(it_AnalysisCur, listToken))
		{
			outAnalysisFile << "E: ���� Print ����" << endl;
			return false;
		}
	}
	//���� scan
	//RS -> scan ( id ) ;
	else if ((*it_AnalysisCur).type == Keyword_scan)
	{
		outAnalysisFile << "G: RS -> scan ( id ) ;" << endl;
		outAnalysisFile << "1> ������ scan" << endl;
		it_AnalysisCur++;//���µ�ǰ����Tokenen����λ��
						 //1.���� ��С����
		if (it_AnalysisCur == listToken.end())
		{
			outAnalysisFile << "E: �Ѿ�������Tokenen����ĩβ" << endl;
			return false;
		}
		if ((*it_AnalysisCur).type != Delimiter_Left_Small_Bracket)	//�Ƿ�Ϊ��С����
		{
			outAnalysisFile << "E: ���� ( ����" << endl;
			return false;
		}
		outAnalysisFile << "1> ������ (" << endl;
		it_AnalysisCur++;//���µ�ǰ����Tokenen����λ��
						 //2.���� id
		if (it_AnalysisCur == listToken.end())
		{
			outAnalysisFile << "E: �Ѿ�������Tokenen����ĩβ" << endl;
			return false;
		}
		if ((*it_AnalysisCur).type != Identifier)	//�Ƿ�Ϊid
		{
			outAnalysisFile << "E: ���� id ����" << endl;
			return false;
		}
		outAnalysisFile << "1> ������ id" << endl;
		it_AnalysisCur++;//���µ�ǰ����Tokenen����λ��
						 //3.���� ��С����
		if (it_AnalysisCur == listToken.end()) //û�з�����ĩβ
		{
			outAnalysisFile << "E: �Ѿ�������Tokenen����ĩβ" << endl;
			return false;
		}
		if ((*it_AnalysisCur).type != Delimiter_Right_Small_Bracket)	//�Ƿ�Ϊ��С����
		{
			outAnalysisFile << "E: ���� ) ����" << endl;
			return false;
		}
		outAnalysisFile << "1> ������ )" << endl;
		it_AnalysisCur++;//���µ�ǰ����Tokenen����λ��
						 //4.���� �ֺ�
		if (it_AnalysisCur == listToken.end()) //û�з�����ĩβ
		{
			outAnalysisFile << "E: �Ѿ�������Tokenen����ĩβ" << endl;
			return false;
		}
		if ((*it_AnalysisCur).type != Delimiter_Semicolon)	//�Ƿ�Ϊ�ֺ�
		{
			outAnalysisFile << "E: ���� ; ����" << endl;
			return false;
		}
		outAnalysisFile << "1> ������ ;" << endl;
		it_AnalysisCur++;//���µ�ǰ����Tokenen����λ��
	}
	//RS -> MT DT VL ;
	else if ((*it_AnalysisCur).type == Keyword_auto || (*it_AnalysisCur).type == Keyword_register ||
		(*it_AnalysisCur).type == Keyword_extern || (*it_AnalysisCur).type == Keyword_static ||
		(*it_AnalysisCur).type == Keyword_int || (*it_AnalysisCur).type == Keyword_char ||
		(*it_AnalysisCur).type == Keyword_float || (*it_AnalysisCur).type == Keyword_double)
	{
		outAnalysisFile << "G: RS -> MT DT VL ;" << endl;
		//����MT
		int memoryType = Keyword_extern;
		if (!grammarAnalysisMT(it_AnalysisCur, listToken, memoryType))
		{
			outAnalysisFile << "E: ���� MT ����" << endl;
			return false;
		}
		//����DT
		int dataType = Error;
		if (!grammarAnalysisDT(it_AnalysisCur, listToken, dataType))
		{
			outAnalysisFile << "E: ���� DT ����" << endl;
			return false;
		}
		//����VL
		list<VariableList> variableList;
		if (!grammarAnalysisVL(it_AnalysisCur, listToken, variableList))
		{
			outAnalysisFile << "E: ���� VL ����" << endl;
			return false;
		}
		//�����ֺ�
		if (it_AnalysisCur == listToken.end())
		{
			outAnalysisFile << "E:�Ѿ�������Tokenen����ĩβ" << endl;
			return false;
		}
		if ((*it_AnalysisCur).type != Delimiter_Semicolon) //��Ϊ�ֺ�
		{
			outAnalysisFile << "E: ���� ; ����" << endl;
			return false;
		}
		outAnalysisFile << "1> ������ ;" << endl;
		it_AnalysisCur++;//���µ�ǰ����Tokenen����λ��
	}
	//PR ;
	else if (expressPreAnalysis((*it_AnalysisCur).type))
	{
		outAnalysisFile << "G: RS -> PR ;" << endl;
		if (analysis_express_using_LL1)
		{
			//����PR
			list<Token> tmpList;
			while (it_AnalysisCur != listToken.end())
			{
				if ((*it_AnalysisCur).type == Delimiter_Semicolon) //���ֺŽ���
				{
					break;
				}
				tmpList.push_back(*it_AnalysisCur);
				it_AnalysisCur++; //���µ�ǰ����Tokenen����λ��
			}
			if ((*grammar_for_expression).runGrammarAnalysis(tmpList))
			{
				//cout << endl << "����PR�ɹ�" << endl;
			}
			else
			{
				//cout << endl << "����PR�������﷨����" << endl;
				return false;
			}
		}
		else
		{
			if (!grammarAnalysis_eexpr(it_AnalysisCur, listToken))
			{
				outAnalysisFile << "E: ���� eexpr ����" << endl;
				return false;
			}
			outAnalysisFile << "G: RS -> PR ;" << endl;
		}
		//�����ֺ�
		if (it_AnalysisCur == listToken.end())
		{
			outAnalysisFile << "E: �Ѿ�������Tokenen����ĩβ" << endl;
			return false;
		}
		if ((*it_AnalysisCur).type != Delimiter_Semicolon) //��Ϊ�ֺ�
		{
			outAnalysisFile << "E: ���� ; ����" << endl;
			return false;
		}
		outAnalysisFile << "1> ������ ;" << endl;
		it_AnalysisCur++;//���µ�ǰ����Tokenen����λ��
	}
	//�ж��Ƿ�Ϊ�Ҵ�����
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
	//�Ƿ������ĩβ
	if (it_AnalysisCur == listToken.end()) //û�з�����ĩβ
	{
		outAnalysisFile << "E: �Ѿ�������Tokenen����ĩβ" << endl;
		return false;
	}
	// else
	if (Keyword_else == (*it_AnalysisCur).type)
	{
		outAnalysisFile << "G: RS1 -> else SB" << endl;
		outAnalysisFile << "1> ������ else" << endl;
		it_AnalysisCur++;
		// ����SB
		if (!grammarAnalysisSB(it_AnalysisCur, listToken))
		{
			outAnalysisFile << "E: ���� SB ����" << endl;
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
	if (it_AnalysisCur == listToken.end()) //û�з�����ĩβ
	{
		outAnalysisFile << "E: �Ѿ�������Tokenen����ĩβ" << endl;
		return false;
	}
	//�����������
	if ((*it_AnalysisCur).type == Delimiter_Left_Large_Bracket)
	{
		outAnalysisFile << "G: SB -> { SB1 }" << endl;
		outAnalysisFile << "1> ������ {" << endl;
		it_AnalysisCur++;//���µ�ǰ����Tokenen����λ��
						 //����SB1
		grammarAnalysisSB1(it_AnalysisCur, listToken);	//����SB1����ֵ�����λ����ԶΪtrue
														//�����Ҵ�����
		if (it_AnalysisCur == listToken.end()) //û�з�����ĩβ
		{
			outAnalysisFile << "E: �Ѿ�������Tokenen����ĩβ" << endl;
			return false;
		}
		if ((*it_AnalysisCur).type != Delimiter_Right_Large_Bracket)
		{
			outAnalysisFile << "E: ���� } ����" << endl;
			return false;
		}
		outAnalysisFile << "1> ������ }" << endl;
		it_AnalysisCur++;//���µ�ǰ����Tokenen����λ��
	}
	else
	{
		//����RS
		if (!grammarAnalysisRS(it_AnalysisCur, listToken))
		{
			outAnalysisFile << "E: ���� RS ����" << endl;
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
	if (it_AnalysisCur == listToken.end()) //û�з�����ĩβ
	{
		outAnalysisFile << "E: �Ѿ�������Tokenen����ĩβ" << endl;
		return false;
	}
	//���� string ) ;
	if ((*it_AnalysisCur).type == String)	//�Ƿ�Ϊ�ַ���
	{
		outAnalysisFile << "G: Print -> string ) ;" << endl;
		outAnalysisFile << "1> ������ string " << (*it_AnalysisCur).data << endl;
		it_AnalysisCur++;//���µ�ǰ����Tokenen����λ��
						 // ���� ��С����
		if (it_AnalysisCur == listToken.end()) //û�з�����ĩβ
		{
			outAnalysisFile << "E: �Ѿ�������Tokenen����ĩβ" << endl;
			return false;
		}
		if ((*it_AnalysisCur).type != Delimiter_Right_Small_Bracket)	//�Ƿ�Ϊ��С����
		{
			outAnalysisFile << "E: ���� ) ����" << endl;
			return false;
		}
		outAnalysisFile << "1> ������ )" << endl;
		it_AnalysisCur++;//���µ�ǰ����Tokenen����λ��
						 // ���� �ֺ�
		if (it_AnalysisCur == listToken.end()) //û�з�����ĩβ
		{
			outAnalysisFile << "E: �Ѿ�������Tokenen����ĩβ" << endl;
			return false;
		}
		if ((*it_AnalysisCur).type != Delimiter_Semicolon)	//�Ƿ�Ϊ�ֺ�
		{
			outAnalysisFile << "E: ���� ; ����" << endl;
			return false;
		}
		outAnalysisFile << "1> ������ ;" << endl;
		it_AnalysisCur++;//���µ�ǰ����Tokenen����λ��
	}
	else
	{
		//���� PR ) ;
		//����PR
		if (analysis_express_using_LL1)
		{
			list<Token> tmpList;
			while (it_AnalysisCur != listToken.end())
			{
				if ((*it_AnalysisCur).type == Delimiter_Right_Small_Bracket) //����С���Ž���
				{
					break;
				}
				tmpList.push_back(*it_AnalysisCur);
				it_AnalysisCur++; //���µ�ǰ����Tokenen����λ��
			}
			if ((*grammar_for_expression).runGrammarAnalysis(tmpList))
			{
				//cout << endl << "����PR�ɹ�" << endl;
				(*grammar_for_expression).saveAnalysisResultToFile(outAnalysisFile);
			}
			else
			{
				(*grammar_for_expression).saveAnalysisResultToFile(outAnalysisFile);
				//cout << endl << "Print ����PR�������﷨����" << endl;
				return false;
			}
		}
		else
		{
			if (!grammarAnalysis_eexpr(it_AnalysisCur, listToken))
			{
				outAnalysisFile << "E: ���� eexpr ����" << endl;
				return false;
			}
		}
		// ���� ��С����
		if (it_AnalysisCur == listToken.end()) //û�з�����ĩβ
		{
			outAnalysisFile << "E: �Ѿ�������Tokenen����ĩβ" << endl;
			return false;
		}
		if ((*it_AnalysisCur).type != Delimiter_Right_Small_Bracket)	//�Ƿ�Ϊ��С����
		{
			outAnalysisFile << "E: ���� ) ����" << endl;
			return false;
		}
		outAnalysisFile << "1> ������ )" << endl;
		it_AnalysisCur++;//���µ�ǰ����Tokenen����λ��
						 // ���� �ֺ�
		if (it_AnalysisCur == listToken.end()) //û�з�����ĩβ
		{
			outAnalysisFile << "E: �Ѿ�������Tokenen����ĩβ" << endl;
			return false;
		}
		if ((*it_AnalysisCur).type != Delimiter_Semicolon)	//�Ƿ�Ϊ�ֺ�
		{
			outAnalysisFile << "E: ���� ; ����" << endl;
			return false;
		}
		outAnalysisFile << "1> ������ ;" << endl;
		it_AnalysisCur++;//���µ�ǰ����Tokenen����λ��
	}
	return true;
}
//---------------------------------------------------------------------------------------------------
// ���ʽ����
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
			outAnalysisFile << "E: ���� bexpr ����" << endl;
			return false;
		}
		//bexpr
		if (!grammarAnalysis_eexpr1(itAnalysisCur, TokenenList))
		{
			outAnalysisFile << "E: ���� eexpr1 ����" << endl;
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
	if (itAnalysisCur == TokenenList.end())	//�ж��Ƿ������Tokenen����ĩβ
	{
		outAnalysisFile << "E: �Ѿ�������Tokenen����ĩβ" << endl;
		itAnalysisCur--;
		cout << "�﷨�����ڵ�" << (*itAnalysisCur).lineNo << "�У�����������ȱ�ٱ�Ҫ����" << endl;
		itAnalysisCur++;
		return false;
	}
	if ((*itAnalysisCur).type == Operator_Equal)	// =
	{
		outAnalysisFile << "G: eexpr1 -> ao bexpr eexpr1" << endl;
		outAnalysisFile << "1> ������ ao " << (*itAnalysisCur).data << endl;
		itAnalysisCur++;
	}
	else if ((*itAnalysisCur).type == Operator_Plus_Equal)	// +=
	{
		outAnalysisFile << "G: eexpr1 -> ao bexpr eexpr1" << endl;
		outAnalysisFile << "1> ������ ao " << (*itAnalysisCur).data << endl;
		itAnalysisCur++;
	}
	else if ((*itAnalysisCur).type == Operator_Minus_Equal)	// -=
	{
		outAnalysisFile << "G: eexpr1 -> ao bexpr eexpr1" << endl;
		outAnalysisFile << "1> ������ ao " << (*itAnalysisCur).data << endl;
		itAnalysisCur++;
	}
	else if ((*itAnalysisCur).type == Operator_Multiply_Equal)	// *=
	{
		outAnalysisFile << "G: eexpr1 -> ao bexpr eexpr1" << endl;
		outAnalysisFile << "1> ������ ao " << (*itAnalysisCur).data << endl;
		itAnalysisCur++;
	}
	else if ((*itAnalysisCur).type == Operator_Divide_Equal)	// /=
	{
		outAnalysisFile << "G: eexpr1 -> ao bexpr eexpr1" << endl;
		outAnalysisFile << "1> ������ ao " << (*itAnalysisCur).data << endl;
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
		outAnalysisFile << "E: ���� bterm ����" << endl;
		return false;
	}
	//bexpr1
	if (!grammarAnalysis_bexpr1(itAnalysisCur, TokenenList))
	{
		outAnalysisFile << "E: ���� bexpr1 ����" << endl;
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
	if (itAnalysisCur == TokenenList.end())	//�ж��Ƿ������Tokenen����ĩβ
	{
		outAnalysisFile << "E: �Ѿ�������Tokenen����ĩβ" << endl;
		itAnalysisCur--;
		cout << "�﷨�����ڵ�" << (*itAnalysisCur).lineNo << "�У�����������ȱ�ٱ�Ҫ����" << endl;
		itAnalysisCur++;
		return false;
	}
	if ((*itAnalysisCur).type == Operator_Or)	// ||
	{
		outAnalysisFile << "G: bexpr1 -> || bterm bexpr1" << endl;
		outAnalysisFile << "1> ������ ||" << endl;
		itAnalysisCur++;
		if (!grammarAnalysis_bterm(itAnalysisCur, TokenenList))	//bterm
		{
			outAnalysisFile << "E: ���� bterm ����" << endl;
			return false;
		}
		if (!grammarAnalysis_bexpr1(itAnalysisCur, TokenenList))	//bexpr1
		{
			outAnalysisFile << "E: ���� bexpr1 ����" << endl;
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
		outAnalysisFile << "E: ���� rterm ����" << endl;
		return false;
	}
	//bterm1
	if (!grammarAnalysis_bterm1(itAnalysisCur, TokenenList))
	{
		outAnalysisFile << "E: ���� bterm1 ����" << endl;
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
	if (itAnalysisCur == TokenenList.end())	//�ж��Ƿ������Tokenen����ĩβ
	{
		outAnalysisFile << "E: �Ѿ�������Tokenen����ĩβ" << endl;
		itAnalysisCur--;
		cout << "�﷨�����ڵ�" << (*itAnalysisCur).lineNo << "�У�����������ȱ�ٱ�Ҫ����" << endl;
		itAnalysisCur++;
		return false;
	}
	if ((*itAnalysisCur).type == Operator_And)	// &&
	{
		outAnalysisFile << "G: bterm1 -> && rterm bterm1" << endl;
		outAnalysisFile << "1> ������ &&" << endl;
		itAnalysisCur++;
		//rterm
		if (!grammarAnalysis_rexpr(itAnalysisCur, TokenenList))
		{
			outAnalysisFile << "E: ���� rterm ����" << endl;
			return false;
		}
		//bterm1
		if (!grammarAnalysis_bterm1(itAnalysisCur, TokenenList))
		{
			outAnalysisFile << "E: ���� bterm1 ����" << endl;
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
		outAnalysisFile << "E: ���� aexpr ����" << endl;
		return false;
	}
	//rterm1
	if (!grammarAnalysis_rexpr1(itAnalysisCur, TokenenList))
	{
		outAnalysisFile << "E: ���� rterm1 ����" << endl;
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
	if (itAnalysisCur == TokenenList.end())	//�ж��Ƿ������Tokenen����ĩβ
	{
		outAnalysisFile << "E: �Ѿ�������Tokenen����ĩβ" << endl;
		itAnalysisCur--;
		cout << "�﷨�����ڵ�" << (*itAnalysisCur).lineNo << "�У�����������ȱ�ٱ�Ҫ����" << endl;
		itAnalysisCur++;
		return false;
	}
	if ((*itAnalysisCur).type == Operator_Less_Than)	// <
	{
		outAnalysisFile << "G: rterm1 -> < aexpr" << endl;
		outAnalysisFile << "1> ������ <" << endl;
		itAnalysisCur++;
		//aexpr
		if (!grammarAnalysis_aexpr(itAnalysisCur, TokenenList))
		{
			outAnalysisFile << "E: ���� aexpr ����" << endl;
			return false;
		}
	}
	else if ((*itAnalysisCur).type == Operator_More_Than) // >
	{
		outAnalysisFile << "G: rterm1 -> > aexpr" << endl;
		outAnalysisFile << "1> ������ >" << endl;
		itAnalysisCur++;
		//aexpr
		if (!grammarAnalysis_aexpr(itAnalysisCur, TokenenList))
		{
			outAnalysisFile << "E: ���� aexpr ����" << endl;
			return false;
		}
	}
	else if ((*itAnalysisCur).type == Operator_Less_Than_Equal)	// <=
	{
		outAnalysisFile << "G: rterm1 -> <= aexpr" << endl;
		outAnalysisFile << "1> ������ <=" << endl;
		itAnalysisCur++;
		//aexpr
		if (!grammarAnalysis_aexpr(itAnalysisCur, TokenenList))
		{
			outAnalysisFile << "E: ���� aexpr ����" << endl;
			return false;
		}
	}
	else if ((*itAnalysisCur).type == Operator_More_Than_Equal)	// >=
	{
		outAnalysisFile << "G: rterm1 -> >= aexpr" << endl;
		outAnalysisFile << "1> ������ >=" << endl;
		itAnalysisCur++;
		//aexpr
		if (!grammarAnalysis_aexpr(itAnalysisCur, TokenenList))
		{
			outAnalysisFile << "E: ���� aexpr ����" << endl;
			return false;
		}
	}
	else if ((*itAnalysisCur).type == Operator_Not_Equal_To)	// !=
	{
		outAnalysisFile << "G: rterm1 -> != aexpr" << endl;
		outAnalysisFile << "1> ������ !=" << endl;
		itAnalysisCur++;
		//aexpr
		if (!grammarAnalysis_aexpr(itAnalysisCur, TokenenList))
		{
			outAnalysisFile << "E: ���� aexpr ����" << endl;
			return false;
		}
	}
	else if ((*itAnalysisCur).type == Operator_Is_Equal) // ==
	{
		outAnalysisFile << "G: rterm1 -> == aexpr" << endl;
		outAnalysisFile << "1> ������ ==" << endl;
		itAnalysisCur++;
		//aexpr
		if (!grammarAnalysis_aexpr(itAnalysisCur, TokenenList))
		{
			outAnalysisFile << "E: ���� aexpr ����" << endl;
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
		outAnalysisFile << "E: ���� term ����" << endl;
		return false;
	}
	//aexpr1
	if (!grammarAnalysis_aexpr1(itAnalysisCur, TokenenList))
	{
		outAnalysisFile << "E: ���� aexpr1 ����" << endl;
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
	if (itAnalysisCur == TokenenList.end())	//�ж��Ƿ������Tokenen����ĩβ
	{
		outAnalysisFile << "�Ѿ�������Tokenen����ĩβ" << endl;
		itAnalysisCur--;
		cout << "�﷨�����ڵ�" << (*itAnalysisCur).lineNo << "�У�����������ȱ�ٱ�Ҫ����" << endl;
		itAnalysisCur++;
		return false;
	}
	if ((*itAnalysisCur).type == Operator_Plus) // +
	{
		outAnalysisFile << "G: aexpr1 -> + term aexpr1" << endl;
		outAnalysisFile << "1> ������ +" << endl;
		itAnalysisCur++;
		//term
		if (!grammarAnalysis_term(itAnalysisCur, TokenenList))
		{
			outAnalysisFile << "E: ���� term ����" << endl;
			return false;
		}
		//aexpr1
		if (!grammarAnalysis_aexpr1(itAnalysisCur, TokenenList))
		{
			outAnalysisFile << "E: ���� aexpr1 ����" << endl;
			return false;
		}
	}
	else if ((*itAnalysisCur).type == Operator_Minus) // -
	{
		outAnalysisFile << "G: aexpr1 -> - term aexpr1" << endl;
		outAnalysisFile << "1> ������ -" << endl;
		itAnalysisCur++;
		//term
		if (!grammarAnalysis_term(itAnalysisCur, TokenenList))
		{
			outAnalysisFile << "E: ���� term ����" << endl;
			return false;
		}
		//aexpr1
		if (!grammarAnalysis_aexpr1(itAnalysisCur, TokenenList))
		{
			outAnalysisFile << "E: ���� aexpr1 ����" << endl;
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
	//����factor
	if (!grammarAnalysis_factor(itAnalysisCur, TokenenList))
	{
		outAnalysisFile << "E: ���� factor ����" << endl;
		return false;
	}
	//����term1
	if (!grammarAnalysis_term1(itAnalysisCur, TokenenList))
	{
		outAnalysisFile << "E: ���� term1 ����" << endl;
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
	if (itAnalysisCur == TokenenList.end())	//�ж��Ƿ������Tokenen����ĩβ
	{
		outAnalysisFile << "�Ѿ�������Tokenen����ĩβ" << endl;
		itAnalysisCur--;
		cout << "�﷨�����ڵ�" << (*itAnalysisCur).lineNo << "�У�����������ȱ�ٱ�Ҫ����" << endl;
		itAnalysisCur++;
		return false;
	}
	//���� * / %
	if ((*itAnalysisCur).type == Operator_Multiply)
	{
		outAnalysisFile << "G: term1 -> * factor term1" << endl;
		outAnalysisFile << "1> ������ *" << endl;
		itAnalysisCur++;
		//����factor
		if (!grammarAnalysis_factor(itAnalysisCur, TokenenList))
		{
			outAnalysisFile << "E: ���� factor ����" << endl;
			return false;
		}
		//����term1
		if (!grammarAnalysis_term1(itAnalysisCur, TokenenList))
		{
			outAnalysisFile << "E: ���� term1 ����" << endl;
			return false;
		}
	}
	if ((*itAnalysisCur).type == Operator_Divide)
	{
		outAnalysisFile << "G: term1 -> / factor term1" << endl;
		outAnalysisFile << "1> ������ /" << endl;
		itAnalysisCur++;
		//����factor
		if (!grammarAnalysis_factor(itAnalysisCur, TokenenList))
		{
			outAnalysisFile << "E: ���� factor ����" << endl;
			return false;
		}
		//����term1
		if (!grammarAnalysis_term1(itAnalysisCur, TokenenList))
		{
			outAnalysisFile << "E: ���� term1 ����" << endl;
			return false;
		}
	}
	if ((*itAnalysisCur).type == Operator_Mod)
	{
		outAnalysisFile << "G: term1 -> % factor term1" << endl;
		outAnalysisFile << "1> ������ %" << endl;
		itAnalysisCur++;
		//����factor
		if (!grammarAnalysis_factor(itAnalysisCur, TokenenList))
		{
			outAnalysisFile << "E: ���� factor ����" << endl;
			return false;
		}
		//����term1
		if (!grammarAnalysis_term1(itAnalysisCur, TokenenList))
		{
			outAnalysisFile << "E: ���� term1 ����" << endl;
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
	if (itAnalysisCur == TokenenList.end())	//�ж��Ƿ������Tokenen����ĩβ
	{
		outAnalysisFile << "E: �Ѿ�������Tokenen����ĩβ" << endl;
		itAnalysisCur--;
		cout << "�﷨�����ڵ�" << (*itAnalysisCur).lineNo << "�У�����������ȱ�ٱ�Ҫ����" << endl;
		itAnalysisCur++;
		return false;
	}
	if ((*itAnalysisCur).type == Operator_Not)	// !
	{
		outAnalysisFile << "G: factor -> ! ael" << endl;
		outAnalysisFile << "1> ������ !" << endl;
		itAnalysisCur++;
		//����ael
		if (!grammarAnalysis_ael(itAnalysisCur, TokenenList))
		{
			outAnalysisFile << "E: ���� ael ����" << endl;
			return false;
		}
		return true;
	}
	else
	{
		outAnalysisFile << "G: factor -> ael" << endl;
		//����ael
		if (!grammarAnalysis_ael(itAnalysisCur, TokenenList))
		{
			outAnalysisFile << "E: ���� ael ����" << endl;
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
	if (itAnalysisCur == TokenenList.end())	//�ж��Ƿ������Tokenen����ĩβ
	{
		outAnalysisFile << "E:�Ѿ�������Tokenen����ĩβ" << endl;
		itAnalysisCur--;
		cout << "�﷨�����ڵ�" << (*itAnalysisCur).lineNo << "�У�����������ȱ�ٱ�Ҫ����" << endl;
		itAnalysisCur++;
		return false;
	}
	if ((*itAnalysisCur).type == Delimiter_Left_Small_Bracket)	//��С����
	{
		outAnalysisFile << "G: ael -> ( bexpr )" << endl;
		outAnalysisFile << "1> ������ (" << endl;
		itAnalysisCur++;
		// ����bexpr
		if (itAnalysisCur == TokenenList.end())	//�ж��Ƿ������Tokenen����ĩβ
		{
			outAnalysisFile << "E: �Ѿ�������Tokenen����ĩβ" << endl;
			return false;
		}
		if ((*itAnalysisCur).type != Delimiter_Right_Small_Bracket)	//��С����
		{
			outAnalysisFile << "E: ���� ) ����" << endl;
			return false;
		}
		outAnalysisFile << "1> ������ )" << endl;
		itAnalysisCur++;
	}
	else
	{
		outAnalysisFile << "G: ael -> root" << endl;
		if (!grammarAnalysis_root(itAnalysisCur, TokenenList))
		{
			outAnalysisFile << "E: ���� root ����" << endl;
			return false;
		}
	}
	return true;
}
/*
	root -> id(����)
	root -> ����(�˽��ơ�ʮ���ơ�ʮ������)
	root -> ������( С����ָ�� )
	root -> ������ BOOL
	root -> �ַ���
*/
bool GrammarAnalysis::grammarAnalysis_root(list<Token>::iterator & itAnalysisCur, list<Token>& TokenenList)
{
	if (itAnalysisCur == TokenenList.end())	//�ж��Ƿ������Tokenen����ĩβ
	{
		outAnalysisFile << "E: �Ѿ�������Tokenen����ĩβ" << endl;
		//��ʾ����
		itAnalysisCur--;
		cout << "�﷨�����ڵ�" << (*itAnalysisCur).lineNo << "�У�����������ȱ�ٱ�Ҫ����" << endl;
		itAnalysisCur++;
		return false;
	}
	if ((*itAnalysisCur).type == Identifier)	//id
	{
		outAnalysisFile << "G: root -> id(����)" << endl;
		outAnalysisFile << "1> ������ id " << (*itAnalysisCur).data << endl;
		itAnalysisCur++;
	}
	else if ((*itAnalysisCur).type == Character)	//�ַ�
	{
		outAnalysisFile << "G: root -> �ַ���" << endl;
		outAnalysisFile << "1> ������ char " << (*itAnalysisCur).data << endl;
		itAnalysisCur++;
	}
	else if ((*itAnalysisCur).type == Number_Octonary)	//���� �˽���
	{
		outAnalysisFile << "G: root -> ����(�˽���)" << endl;
		outAnalysisFile << "1> ������ ����(�˽���) " << (*itAnalysisCur).data << endl;
		itAnalysisCur++;
	}
	else if ((*itAnalysisCur).type == Number_Decimalism)	//���� ʮ����
	{
		outAnalysisFile << "G: root -> ����(ʮ����)" << endl;
		outAnalysisFile << "1> ������ ����(ʮ����) " << (*itAnalysisCur).data << endl;
		itAnalysisCur++;
	}
	else if ((*itAnalysisCur).type == Number_Hexadecimal)	//���� ʮ������
	{
		outAnalysisFile << "G: root -> ����(ʮ������)" << endl;
		outAnalysisFile << "1> ������ ����(ʮ������) " << (*itAnalysisCur).data << endl;
		itAnalysisCur++;
	}
	else if ((*itAnalysisCur).type == Number_Decimals)	//������ С��
	{
		outAnalysisFile << "G: root -> ������( С�� )" << endl;
		outAnalysisFile << "1> ������ ������( С�� ) " << (*itAnalysisCur).data << endl;
		itAnalysisCur++;
	}
	else if ((*itAnalysisCur).type == Number_Exponent)	//������ ָ��
	{
		outAnalysisFile << "G: root -> ������( ָ�� )" << endl;
		outAnalysisFile << "1> ������ ������( ָ�� ) " << (*itAnalysisCur).data << endl;
		itAnalysisCur++;
	}
	else if (grammarAnalysisBOOL(itAnalysisCur, TokenenList))
	{
		//����BOOL
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
	if (itAnalysisCur == TokenenList.end())	//�ж��Ƿ������Tokenen����ĩβ
	{
		outAnalysisFile << "E: �Ѿ�������Tokenen����ĩβ" << endl;
		return false;
	}
	if ((*itAnalysisCur).type == Keyword_true)
	{
		outAnalysisFile << "G: BOOL -> true" << endl;
		outAnalysisFile << "1> ������ true" << endl;
		itAnalysisCur++;	//���µ�ǰ����Tokenen����λ��
	}
	else if ((*itAnalysisCur).type == Keyword_false)
	{
		outAnalysisFile << "G: BOOL -> false" << endl;
		outAnalysisFile << "1> ������ false " << endl;
		itAnalysisCur++;	//���µ�ǰ����Tokenen����λ��
	}
	else
	{
		return false;//������ǰ������Tokenen������һ��������������
	}
	return true;
}

bool GrammarAnalysis::expressPreAnalysis(int type)
{
	// ! ( id ����(�ˣ�ʮ��ʮ��) ����(С��ָ) true false char
	if (type == Operator_Not || type == Identifier || type == Number_Octonary
		|| type == Number_Decimalism || type == Number_Hexadecimal || type == Number_Decimals
		|| type == Number_Exponent || type == Keyword_true || type == Keyword_false || type == Character)
	{
		return true;
	}
	return false;
}
//ʶ���﷨����
int GrammarAnalysis::recogniseGrammarError(list<Token>::iterator& itAnalysisCur, int curType, int nextType)
{
	//Token��ʧ
	if ((*itAnalysisCur).type == nextType)
	{
		return TokenLose;
	}
	//Token����
	if ((*(++itAnalysisCur)).type == curType)
	{
		--itAnalysisCur;
		return TokenExcess;
	}
	--itAnalysisCur;
	//Token��ƥ��
	if ((*(++itAnalysisCur)).type == curType)
	{
		--itAnalysisCur;
		return TokenExcess;
	}
	--itAnalysisCur;
	return TokenMismatch;
}
