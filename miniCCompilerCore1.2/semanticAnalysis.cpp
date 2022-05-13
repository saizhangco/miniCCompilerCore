#include "semanticAnalysis.h"
#include "symbol.h"
#include "fourElementType.h"
#include "functionDefinition.h"
#include <fstream>
#include "linuxStrings.h"


SemanticAnalysis::SemanticAnalysis()
{
	//cout << "��ʼ�����������:" << endl;
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
	�������ִ�к���
*/
bool SemanticAnalysis::runSemanticAnalysis(list<Token>& TokenenList)
{
	/*cout << "��������Tokenen��:" << endl;
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
		//cout << "����������" << endl;
		return false;
	}
	/* ��ӡ�����������
	printFourElementTypeList();	//��ӡ�м���루��Ԫʽ��ʾ��
	cout << "--------------------" << endl;
	cout << "������Ϣ" << endl;
	printErrorInfo();	//��ӡ������Ϣ
	cout << "--------------------" << endl;
	cout << "�û��������" << endl;
	list<VariableDefinition>::iterator it = mVariableDefinitionList.begin();
	for (; it != mVariableDefinitionList.end(); it++)
	{
		(*it).printContent();
	}
	cout << "--------------------" << endl;
	cout << "����������ʵ��" << endl;
	list<FunctionDefinition>::iterator it1 = mFunctionDefinitionList.begin();
	for (; it1 != mFunctionDefinitionList.end(); it1++)
	{
		(*it1).printContent();
	}
	*/
	//�жϳ����Ƿ�ȱ�ٺ������
	bool isExistProgramEnter = false;	//�Ƿ���ں������
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
		mErrorInfo.push_back("����ȱ�ٺ������");
	}
	//����Ԫʽ�������ļ���
	saveSemanticInfoToFile();
	//���������Ϣ
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
	cout << "�����������������" << mErrorInfo.size() << "����" << endl;
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
//���м���뱣�����ļ���
void SemanticAnalysis::saveSemanticInfoToFile()
{
	ofstream outFile("analysis\\semanticAnalysis.txt");
	//����������
	outFile << "********************************************" << endl;
	outFile << "*            ����������м����            *" << endl;
	outFile << "********************************************" << endl;

	//���������Ϣ
	outFile << endl;
	outFile << "--------------------------------------------" << endl;
	outFile << "������Ϣ" << endl;
	outFile << "�����������������" << mErrorInfo.size() << "����" << endl;
	list<string>::iterator it = mErrorInfo.begin();
	for (; it != mErrorInfo.end(); it++)
	{
		outFile << "error: " << (*it) << endl;
	}
	outFile << "--------------------------------------------" << endl;

	//��������
	outFile << endl;
	outFile << "--------------------------------------------" << endl;
	outFile << "��������" << endl;
	list<VariableDefinition>::iterator it1 = mVariableDefinitionList.begin();
	for (; it1 != mVariableDefinitionList.end(); it1++)
	{
		outFile << (*it1).getContent();
	}
	outFile << "--------------------------------------------" << endl;

	//����������ʵ��
	outFile << endl;
	outFile << "--------------------------------------------" << endl;
	outFile << "����������ʵ��" << endl;
	list<FunctionDefinition>::iterator it2 = mFunctionDefinitionList.begin();
	for (; it2 != mFunctionDefinitionList.end(); it2++)
	{
		outFile << (*it2).getContent();
	}
	outFile << "--------------------------------------------" << endl;

	//�м����
	outFile << endl;
	outFile << "--------------------------------------------" << endl;
	outFile << "�м����[��Ԫʽ��ʽ]" << endl;
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
	//������ָ���޸�Ϊc
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
// ȫ�ֱ������塢��������������ʵ��
//---------------------------------------------------------------------------------------------------
/*
	S -> $
	S -> F S
*/
bool SemanticAnalysis::semanticAnalysisS(list<Token>::iterator & itAnalysisCur, list<Token>& TokenenList)
{
	if (itAnalysisCur == TokenenList.end())
	{
		//�������
		FourElementTypeItem nullId;
		FourElementType four(mFourElementTypeList.size() + 1, Sys, nullId, nullId, nullId);
		mFourElementTypeList.push_back(four);
		return true;
	}
	else
	{
		//���� F
		if (!semanticAnalysisF(itAnalysisCur, TokenenList))
		{
			return false;
		}
		//���� S
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
	// ���� MT1
	grammarTreeTmp.memoryType = Keyword_extern;
	if (!semanticAnalysisMT1(itAnalysisCur, TokenenList, grammarTreeTmp.memoryType))
	{
		//����ʧ��
		return false;
	}
	// ���� DT
	grammarTreeTmp.dataType = Error;
	if (!semanticAnalysisDT(itAnalysisCur, TokenenList, grammarTreeTmp.dataType))
	{
		return false;
	}
	//grammarTreeTmp.dataType = dataType;
	// ���� F1
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
	case 2:	//��������
	{
		//FunctionDefinition *fd = new FunctionDefinition(grammarTreeTmp);
		//node->addChildToRoot(fd);
		FunctionDefinition fd(grammarTreeTmp);
		fd.isComeTrue = false;
		if (!isMatchFunctionComeTrueAndDefine(fd))
		{
			//������
			mFunctionDefinitionList.push_back(fd);
		}
		break;
	}
	case 3:	//����ʵ��
	{
		//FunctionDeclaration *fd = new FunctionDeclaration(grammarTreeTmp);
		//node->addChildToRoot(fd);
		FunctionDefinition fd(grammarTreeTmp);
		fd.isComeTrue = true;
		fd.funcEnter = funcEnter;
		if (!isMatchFunctionComeTrueAndDefine(fd))
		{
			//������
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
	// ���� ID �� ��С����
	if ((*itAnalysisCur).type == Identifier && (++itAnalysisCur) != TokenenList.end() &&
		(*itAnalysisCur).type == Delimiter_Left_Small_Bracket)	// id ( ��С����
	{
		curFunctionName = functionName;		//��ǰ�����ĺ�����
		tmp.functionName = functionName;	//�����������ص�tmp��ȥ
		itAnalysisCur++;	//���µ�ǰ����Tokenen����λ��
							//���� PL
		if (!semanticAnalysisPL(itAnalysisCur, TokenenList, tmp.parameterList))	//����PL������
		{
			return false;
		}
		//���� ��С����
		if (itAnalysisCur == TokenenList.end())
		{
			return false;
		}
		if ((*itAnalysisCur).type != Delimiter_Right_Small_Bracket)	// ) ��С����
		{
			return false;
		}
		itAnalysisCur++;	//���µ�ǰ����Tokenen����λ��
		if (!semanticAnalysisF2(itAnalysisCur, TokenenList, tmp))	//����������
		{
			return false;
		}
	}
	else // F1 -> VL ;
	{
		--itAnalysisCur;	//����֮ǰ����Tokenen����λ��
		//����VL
		tmp.tmpType = 1;	//�ⲿ���ݶ���
		// tmp.variableList;
		if (!semanticAnalysisVL(itAnalysisCur, TokenenList, tmp.variableList, true))
		{
			return false;
		}
		if (itAnalysisCur == TokenenList.end())	//����������ĩβ
		{
			return false;
		}
		//�����ֺ� ;
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
	if (itAnalysisCur == TokenenList.end())//��ǰ����λ���Ƿ����
	{
		return false;
	}
	//�ֺ�
	if ((*itAnalysisCur).type == Delimiter_Semicolon)	//�Ƿ�Ϊ�ֺ�
	{
		tmp.tmpType = 2;	//��������
		itAnalysisCur++;	//���µ�ǰ����Tokenen����λ��
	}
	//�������
	else if ((*itAnalysisCur).type == Delimiter_Left_Large_Bracket)	//�Ƿ�Ϊ�������
	{
		itAnalysisCur++;	//���µ�ǰ����Tokenen����λ��
		tmp.tmpType = 3;	//����ʵ��
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
		// } �Ҵ�����
		if (itAnalysisCur == TokenenList.end())	//����������ĩβ
		{
			return false;
		}
		if ((*itAnalysisCur).type != Delimiter_Right_Large_Bracket)	//�Ƿ�Ϊ�Ҵ�����
		{
			return false;
		}
		itAnalysisCur++;//���µ�ǰ����Tokenen����λ��

		int tmpReturn = mFourElementTypeList.size() + 1;	//tmpReturn = NXQ
		//����returnPosi����Ϣ
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
	curFunctionName = "";;	//��յ�ǰ�����ĺ�����
	return true;
}
/*
	MT -> auto
	MT -> register
	MT -> MT1
*/
bool SemanticAnalysis::semanticAnalysisMT(list<Token>::iterator & itAnalysisCur, list<Token>& TokenenList, int& memoryType)
{
	if (itAnalysisCur == TokenenList.end())	//��ǰ����λ���Ƿ����
	{
		return false;
	}
	if ((*itAnalysisCur).type == Keyword_auto)	//auto
	{
		memoryType = Keyword_auto;
		itAnalysisCur++;	//���µ�ǰ����Tokenen����λ��
		return true;
	}
	else if ((*itAnalysisCur).type == Keyword_register)
	{
		memoryType = Keyword_register;
		itAnalysisCur++;	//���µ�ǰ����Tokenen����λ��
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
	if (itAnalysisCur == TokenenList.end())	//��ǰ����λ���Ƿ����
	{
		return false;
	}
	if ((*itAnalysisCur).type == Keyword_extern)
	{
		memoryType = Keyword_extern;
		itAnalysisCur++;	//���µ�ǰ����Tokenen����λ��
		return true;
	}
	else if ((*itAnalysisCur).type == Keyword_static)
	{
		memoryType = Keyword_static;
		itAnalysisCur++;	//���µ�ǰ����Tokenen����λ��
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
	if (itAnalysisCur == TokenenList.end())//��ǰ����λ���Ƿ����
	{
		return false;
	}
	if ((*itAnalysisCur).type == Keyword_void)
	{
		dataType = Keyword_void;
		itAnalysisCur++;	//���µ�ǰ����Token����λ��
		return true;
	}
	else if ((*itAnalysisCur).type == Keyword_int)
	{
		dataType = Keyword_int;
		itAnalysisCur++;	//���µ�ǰ����Token����λ��
		return true;
	}
	else if ((*itAnalysisCur).type == Keyword_char)
	{
		//dataType = Keyword_char;
		itAnalysisCur++;	//���µ�ǰ����Tokenen����λ��
		return true;
	}
	else if ((*itAnalysisCur).type == Keyword_float)
	{
		//dataType = Keyword_float;
		itAnalysisCur++;	//���µ�ǰ����Tokenen����λ��
		return true;
	}
	else if ((*itAnalysisCur).type == Keyword_double)
	{
		//dataType = Keyword_double;
		itAnalysisCur++;	//���µ�ǰ����Tokenen����λ��
		return true;
	}
	return false;
}
/*
	VL -> VD VL1
*/
bool SemanticAnalysis::semanticAnalysisVL(list<Token>::iterator & itAnalysisCur, list<Token>& TokenenList, list<VariableList>& variableList, bool isGlobal)
{
	//����VD
	VariableList variable;
	if (!semanticAnalysisVD(itAnalysisCur, TokenenList, variable, isGlobal))
	{
		return false;
	}
	variableList.push_back(variable);
	//����VL1
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
	//�ж��Ƿ������ĩβ
	if (itAnalysisCur == TokenenList.end())
	{
		return false;
	}
	// VL1 -> , VD VL1
	//�����Ƿ�Ϊ���� ,
	if (Delimiter_Comma == (*itAnalysisCur).type)
	{
		itAnalysisCur++;//���µ�ǰ����Tokenen����λ��
		//����VL1
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
	//�Ƿ������Tokenen����ĩβ
	if (itAnalysisCur == TokenenList.end())	//û�з�����ĩβ
	{
		return false;
	}
	//�ж��Ƿ�ΪID
	if (Identifier == (*itAnalysisCur).type)
	{
		variable.varName = (*itAnalysisCur).data;
		if (isRepetDefineVariable((*itAnalysisCur).data, isGlobal))
		{
			mErrorInfo.push_back("���� " + (*itAnalysisCur).data + " �ظ�����");
		}
		variableCache.push_back((*itAnalysisCur).data);
		itAnalysisCur++;//���µ�ǰ����Tokenen����λ��
		//����VD1
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
	//�ж��Ƿ������Tokenen����ĩβ
	if (itAnalysisCur == TokenenList.end())	//û�з�����ĩβ
	{
		return false;
	}
	// VD1 -> = PR
	//�����Ƿ�Ϊ�Ⱥ� =
	if (Operator_Equal == (*itAnalysisCur).type)	//Ϊ�Ⱥ�
	{
		itAnalysisCur++; //���µ�ǰ����Tokenen����λ��
		list<Token>::iterator it = itAnalysisCur;
		FourElementTypeItem bexpr;
		if (!semanticAnalysis_bexpr(itAnalysisCur, TokenenList, bexpr))
		{
			//outAnalysisFile << "E: ���� PR ����" << endl;
			return false;
		}

		if (bexpr.mType == 4)	//���bexprΪBOOL������Ҫ��ת��Ϊ��BOOL��
		{
			FourElementTypeItem nullId;
			FourElementTypeItem tempId = newTempIdentifier();
			FourElementTypeItem constant;
			constant.mType = 1;
			constant.mConstantType = 1;
			//�����
			constant.mConstantInteger = 1;
			int mTC = mFourElementTypeList.size() + 1;
			FourElementType four(mFourElementTypeList.size() + 1, Equal, constant, nullId, tempId);
			mFourElementTypeList.push_back(four);
			//��ת���
			FourElementTypeItem pFour;
			pFour.mType = 5;
			pFour.mNumber = mTC + 3;
			FourElementType four1(mFourElementTypeList.size() + 1, Jump, nullId, nullId, pFour);
			mFourElementTypeList.push_back(four1);
			//�ٳ���
			constant.mConstantInteger = 0;
			int mFC = mFourElementTypeList.size() + 1;
			FourElementType four2(mFourElementTypeList.size() + 1, Equal, constant, nullId, tempId);
			mFourElementTypeList.push_back(four2);
			//�޸���Ԫʽ�б�
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
		initValue.clear();	//���initValue
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
	//����PD
	ParameterList parameter;
	if (!semanticAnalysisPD(itAnalysisCur, TokenenList, parameter))	//����PD������
	{
		return false;
	}
	parameterList.push_back(parameter);
	//����PL2
	if (!semanticAnalysisPL2(itAnalysisCur, TokenenList, parameterList))	//����PL2������
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
	//�ж��Ƿ������Tokenen����ĩβ
	if (itAnalysisCur == TokenenList.end())
	{
		return false;
	}
	//�ж��Ƿ�Ϊ ���� ,
	if (Delimiter_Comma == (*itAnalysisCur).type) // PL2 -> , PD PL2
	{
		itAnalysisCur++;
		ParameterList parameter;
		if (!semanticAnalysisPD(itAnalysisCur, TokenenList, parameter))
		{
			return false;
		}
		parameterList.push_back(parameter);	//��ӵ�List
		//����ѭ��PL2
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
	string parameterName = "";	//��ʼ��Ϊ���ַ���
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
		itAnalysisCur++;	//���µ�ǰ����Tokenen����λ��
		return true;
	}
	return true;
}
//-------------------------------------------�������-----------------------------------------------
/*
	FB -> $
	FB -> RS FB
*/
bool SemanticAnalysis::semanticAnalysis_FB(list<Token>::iterator & itAnalysisCur, list<Token>& TokenenList, int& FB_CHAIN)
{
	list<Token>::iterator tempCur = itAnalysisCur;
	//�����ֳ�
	list<FourElementType> tempFourElementTypeList = mFourElementTypeList;	//��ԪʽList
	list<FourElementTypeItem> tempTempIdentifierList = mTempIdentifierList;	//��ʱ����List
	list<string> tempErrorInfo = mErrorInfo;	//�������
	//int chain = FB_CHAIN;
	if (semanticAnalysis_RS(itAnalysisCur, TokenenList, FB_CHAIN))
	{
		semanticAnalysis_FB(itAnalysisCur, TokenenList, FB_CHAIN);
		return true;
	}
	itAnalysisCur = tempCur;	//�޷�������RS����ָ�֮ǰ��λ��
	//�ָ��ֳ�
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
	// �Ƿ������ĩβ
	if (itAnalysisCur == TokenenList.end()) //û�з�����ĩβ
	{
		return false;
	}
	//RS CHAIN
	if (RS_CHAIN != 0)
	{
		int NXQ = mFourElementTypeList.size() + 1;//������һ��ģ���chain
		modify_end_c(RS_CHAIN, NXQ);

	}
	//------------------------------
	//���� if
	// RS -> if ( PR ) SB RS1
	if ((*itAnalysisCur).type == Keyword_if)
	{
		itAnalysisCur++;//���µ�ǰ����Tokenen����λ��
		//1.����������
		if (itAnalysisCur == TokenenList.end())
		{
			return false;
		}
		if ((*itAnalysisCur).type != Delimiter_Left_Small_Bracket)
		{
			return false;
		}
		itAnalysisCur++;//���µ�ǰ����Tokenen����λ��
		//2.����PR
		FourElementTypeItem express;
		if (!semanticAnalysis_eexpr(itAnalysisCur, TokenenList, express))
		{
			//cout << (*itAnalysisCur).data << endl;
			return false;
		}
		//����eexpr BOOL�� ��BOOL��->��ΪBOOL��
		if (express.mType <= 0 || express.mType > 4)
		{
			return false;
		}
		if (express.mType != 4)	//���eexpr��ΪBOOL��������Ҫ��ת��ΪBOOL��
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
		//3.����������
		if (itAnalysisCur == TokenenList.end())
		{
			return false;
		}
		if ((*itAnalysisCur).type != Delimiter_Right_Small_Bracket) //��Ϊ��С����
		{
			return false;
		}
		itAnalysisCur++;//���µ�ǰ����Tokenen����λ��
		//4.����SB
		int SB_CHAIN = 0;
		if (!semanticAnalysis_SB(itAnalysisCur, TokenenList, SB_CHAIN))
		{
			//cout << "����SB����" << endl;
			return false;
		}
		//���� SB chain
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

		//5.����RS1
		// int RS1_CHAIN = 0;
		if (!semanticAnalysis_RS1(itAnalysisCur, TokenenList, RS_CHAIN, mFC))
		{
			//cout << "����RS1����" << endl;
			return false;
		}
		//���� SB chain
		/*int NXQ = mFourElementTypeList.size() + 1;
		if (RS1_CHAIN != 0)
		{
		modify_end_c(RS1_CHAIN, NXQ);

		}*/
		return true;
	}
	//------------------------------
	//���� while
	//RS -> while (PR) SB
	else if ((*itAnalysisCur).type == Keyword_while)
	{
		itAnalysisCur++;//���µ�ǰ����Tokenen����λ��
		//1.������С����
		if (itAnalysisCur == TokenenList.end())
		{
			cout << "�Ѿ�������Tokenen����ĩβ" << endl;
			return false;
		}
		if ((*itAnalysisCur).type != Delimiter_Left_Small_Bracket)
		{
			cout << "��ǰλ��ȱ����С����" << endl;
			return false;
		}
		itAnalysisCur++;//���µ�ǰ����Tokenen����λ��
		//2.����PR
		int RETURN = mFourElementTypeList.size() + 1;	//RETURN = NXQ
		int tmpContinue = RETURN;	//continue�������ص�λ�� tmpContinue = RETURN
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
		if (express.mType != 4)	//���express��ΪBOOL��������Ҫ��ת��ΪBOOL��
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
		//3.������С����
		if (itAnalysisCur == TokenenList.end())
		{
			//cout << "�Ѿ�������Tokenen����ĩβ" << endl;
			return false;
		}
		if ((*itAnalysisCur).type != Delimiter_Right_Small_Bracket) //��Ϊ��С����
		{
			//cout << "��ǰλ��ȱ����С����" << endl;
			return false;
		}
		itAnalysisCur++;//���µ�ǰ����Tokenen����λ��
		//4.����SB
		int HEAD = mFourElementTypeList.size() + 1;	// HEAD = NXQ
		backpatch(express.mTC, HEAD);	// backpatch(E.TC,HEAD)
		RS_CHAIN = express.mFC;	// RS.CHAIN = E.FC
		int tmpBreak = RS_CHAIN;	//break����������λ�� tmpBreak = E.FC
		//cout << "tmpBreak " << tmpBreak << endl;
		int SB_CHAIN = 0;	// SB_CHAIN
		if (!semanticAnalysis_SB(itAnalysisCur, TokenenList, SB_CHAIN))
		{
			return false;
		}
		//���� SB chain
		if (SB_CHAIN != 0)
		{
			int NXQ = mFourElementTypeList.size() + 1;
			modify_end_c(SB_CHAIN, NXQ);

		}
		//����continue_posi��break_posiλ����Ϣ
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
		//��Ԫʽ (Jump,_,_,RETUREN)
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
	//���� do
	//RS -> do SB while ( PR ) ;
	else if ((*itAnalysisCur).type == Keyword_do)
	{
		int HEAD = mFourElementTypeList.size() + 1;	//HEAD = NXQ
		itAnalysisCur++;//���µ�ǰ����Tokenen����λ��
		//1.����SB
		int SB_CHAIN = 0;
		if (!semanticAnalysis_SB(itAnalysisCur, TokenenList, SB_CHAIN))
		{
			//cout << "����SB����" << endl;
			return false;
		}
		//���� SB chain
		if (SB_CHAIN != 0)
		{
			int NXQ = mFourElementTypeList.size() + 1;
			modify_end_c(SB_CHAIN, NXQ);
		}
		//2.����while
		if (itAnalysisCur == TokenenList.end())
		{
			return false;
		}
		if ((*itAnalysisCur).type != Keyword_while)
		{
			return false;
		}
		itAnalysisCur++;//���µ�ǰ����Tokenen����λ��
		//3.������С����
		if (itAnalysisCur == TokenenList.end())
		{
			return false;
		}
		if ((*itAnalysisCur).type != Delimiter_Left_Small_Bracket)
		{
			return false;
		}
		itAnalysisCur++;//���µ�ǰ����Tokenen����λ��
		//4.����PR
		int tmpContinue = mFourElementTypeList.size() + 1;	//continue��ת��λ��
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
		if (express.mType != 4)	//���express��ΪBOOL��������Ҫ��ת��ΪBOOL��
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
		int tmpBreak = express.mFC;	//break��ת��λ��
		//���� continue_posi �� break_posi λ����Ϣ
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
		//5.������С����
		if (itAnalysisCur == TokenenList.end())
		{
			return false;
		}
		if ((*itAnalysisCur).type != Delimiter_Right_Small_Bracket) //��Ϊ��С����
		{
			return false;
		}
		itAnalysisCur++;//���µ�ǰ����Tokenen����λ��
		//6.�����ֺ� ;
		if (itAnalysisCur == TokenenList.end())
		{
			return false;
		}
		if ((*itAnalysisCur).type != Delimiter_Semicolon)
		{
			return false;
		}
		itAnalysisCur++;//���µ�ǰ����Tokenen����λ��
		return true;
	}
	//------------------------------
	//���� for
	//RS -> for ( PR ; PR ; PR ) SB
	else if ((*itAnalysisCur).type == Keyword_for)
	{
		itAnalysisCur++;//���µ�ǰ����Tokenen����λ��
		//1.������С����
		if (itAnalysisCur == TokenenList.end())
		{
			return false;
		}
		if ((*itAnalysisCur).type != Delimiter_Left_Small_Bracket)
		{
			return false;
		}
		itAnalysisCur++;//���µ�ǰ����Tokenen����λ��
		//2.����PR ��һ�����ʽ ��ʼ�����
		FourElementTypeItem express_1;
		if (!semanticAnalysis_eexpr(itAnalysisCur, TokenenList, express_1))
		{
			//cout << (*itAnalysisCur).data << endl;
			return false;
		}
		//����express_1 BOOL�� ��BOOL��->��ΪBOOL��
		if (express_1.mType <= 0 || express_1.mType > 4)
		{
			return false;
		}
		if (express_1.mType == 4)	//���express_1ΪBOOL��������Ҫ��ת��Ϊ->��BOOL��
		{
			FourElementTypeItem nullId;
			FourElementTypeItem tempId = newTempIdentifier();
			FourElementTypeItem constant;
			constant.mType = 1;
			constant.mConstantType = 1;
			//�����
			constant.mConstantInteger = 1;
			int mTC = mFourElementTypeList.size() + 1;
			FourElementType four(mFourElementTypeList.size() + 1, Equal, constant, nullId, tempId);
			mFourElementTypeList.push_back(four);
			//��ת���
			FourElementTypeItem pFour;
			pFour.mType = 5;
			pFour.mNumber = mTC + 3;
			FourElementType four1(mFourElementTypeList.size() + 1, Jump, nullId, nullId, pFour);
			mFourElementTypeList.push_back(four1);
			//�ٳ���
			constant.mConstantInteger = 0;
			int mFC = mFourElementTypeList.size() + 1;
			FourElementType four2(mFourElementTypeList.size() + 1, Equal, constant, nullId, tempId);
			mFourElementTypeList.push_back(four2);
			//�޸���Ԫʽ�б�
			//cout << "mFC " << express_1.mFC << endl;
			modify_end_c(express_1.mTC, mTC);
			modify_end_c(express_1.mFC, mFC);
			express_1 = tempId;
		}
		//3.�����ֺ� 
		if (itAnalysisCur == TokenenList.end())
		{
			return false;
		}
		if ((*itAnalysisCur).type != Delimiter_Semicolon)	// ;
		{
			return false;
		}
		itAnalysisCur++;//���µ�ǰ����Tokenen����λ��
		//4.����PR �ڶ������ʽ �ж�����
		//judge
		int JUDGE = mFourElementTypeList.size() + 1;	//JUDGE = NXQ
		//int tmpContinue = JUDGE;	//continue��ת��λ�� �޸�ΪAGAIN
		FourElementTypeItem express_2;
		if (!semanticAnalysis_eexpr(itAnalysisCur, TokenenList, express_2))
		{
			cout << (*itAnalysisCur).data << endl;
			return false;
		}
		//����express_2 BOOL�� ��BOOL��->��ΪBOOL��
		if (express_2.mType <= 0 || express_2.mType > 4)
		{
			return false;
		}
		if (express_2.mType != 4)	//���express_2��ΪBOOL��������Ҫ��ת��ΪBOOL��
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
		int tmpBreak = chain;	//break��ת��λ�� tmpBreak = E2.FC
		int mTC = express_2.mTC;	//mTC = PR(2).TC
		//5.�����ֺ�
		if (itAnalysisCur == TokenenList.end())
		{
			return false;
		}
		if ((*itAnalysisCur).type != Delimiter_Semicolon)	// ;
		{
			return false;
		}
		itAnalysisCur++;//���µ�ǰ����Tokenen����λ��

		//6.����PR ���������ʽ ѭ��ִ�б��ʽ
		int AGAIN = mFourElementTypeList.size() + 1;	// AGAIN = NXQ
		int tmpContinue = AGAIN;	//continue��ת��λ�� tmpContinue = AGAIN
		FourElementTypeItem express_3;
		if (!semanticAnalysis_eexpr(itAnalysisCur, TokenenList, express_3))
		{
			//cout << (*itAnalysisCur).data << endl;
			return false;
		}
		//����express_3 BOOL�� ��BOOL��->��ΪBOOL��
		if (express_3.mType <= 0 || express_3.mType > 4)
		{
			return false;
		}
		if (express_3.mType == 4)	//���express_3ΪBOOL��������Ҫ��ת��Ϊ->��BOOL��
		{
			FourElementTypeItem nullId;
			FourElementTypeItem tempId = newTempIdentifier();
			FourElementTypeItem constant;
			constant.mType = 1;
			constant.mConstantType = 1;
			//�����
			constant.mConstantInteger = 1;
			int mTC = mFourElementTypeList.size() + 1;
			FourElementType four(mFourElementTypeList.size() + 1, Equal, constant, nullId, tempId);
			mFourElementTypeList.push_back(four);
			//��ת���
			FourElementTypeItem pFour;
			pFour.mType = 5;
			pFour.mNumber = mTC + 3;
			FourElementType four1(mFourElementTypeList.size() + 1, Jump, nullId, nullId, pFour);
			mFourElementTypeList.push_back(four1);
			//�ٳ���
			constant.mConstantInteger = 0;
			int mFC = mFourElementTypeList.size() + 1;
			FourElementType four2(mFourElementTypeList.size() + 1, Equal, constant, nullId, tempId);
			mFourElementTypeList.push_back(four2);
			//�޸���Ԫʽ�б�
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
		//7.������С����
		if (itAnalysisCur == TokenenList.end())
		{
			return false;
		}
		if ((*itAnalysisCur).type != Delimiter_Right_Small_Bracket) //��Ϊ��С����
		{
			return false;
		}
		itAnalysisCur++;//���µ�ǰ����Tokenen����λ��
		int SB_start = mFourElementTypeList.size() + 1;	//SB_start = NXQ
		modify_end_c(mTC, SB_start);					//modify_end_c(mTC ,SB_start )
		//����SB
		int SB_CHAIN = 0;
		if (!semanticAnalysis_SB(itAnalysisCur, TokenenList, SB_CHAIN))
		{
			return false;
		}
		//���� SB chain
		if (SB_CHAIN != 0)
		{
			int NXQ = mFourElementTypeList.size() + 1;
			modify_end_c(SB_CHAIN, NXQ);

		}
		//���� continue_posi �� break_posi λ����Ϣ
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
	//���� break
	//RS -> break ;
	else if ((*itAnalysisCur).type == Keyword_break)
	{
		//cout << "break" << endl;
		itAnalysisCur++;//���µ�ǰ����Tokenen����λ��
		//�����ֺ�
		if (itAnalysisCur == TokenenList.end())
		{
			return false;
		}
		if ((*itAnalysisCur).type != Delimiter_Semicolon) //��Ϊ�ֺ�
		{
			return false;
		}
		itAnalysisCur++;//���µ�ǰ����Tokenen����λ��
		//��Ҫ����
		//�������λ�� breakPosiList.Add( NXQ )
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
	//���� continue
	// RS -> continue;
	else if ((*itAnalysisCur).type == Keyword_continue)
	{
		itAnalysisCur++;//���µ�ǰ����Tokenen����λ��
		//�����ֺ�
		if (itAnalysisCur == TokenenList.end())
		{
			return false;
		}
		if ((*itAnalysisCur).type != Delimiter_Semicolon) //��Ϊ�ֺ�
		{
			return false;
		}
		itAnalysisCur++;//���µ�ǰ����Tokenen����λ��
		//��Ҫ����
		//�������λ��continuePosiList.Add( NXQ )
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
	//���� return
	//RS -> return PR ;
	else if ((*itAnalysisCur).type == Keyword_return)
	{
		itAnalysisCur++;//���µ�ǰ����Tokenen����λ��
		//1.����PR
		list<Token> tmpList;
		while (itAnalysisCur != TokenenList.end())
		{
			if ((*itAnalysisCur).type == Delimiter_Semicolon) //���ֺŽ���
			{
				break;
			}
			tmpList.push_back(*itAnalysisCur);
			itAnalysisCur++; //���µ�ǰ����Tokenen����λ��
		}
		FourElementTypeItem eexpr;
		if (!semanticAnalysis_aexpr(itAnalysisCur, TokenenList, eexpr))
		{
			//���ʽ��������
			return false;
		}
		//���eexprΪBOOL������Ҫ��ת��Ϊ��BOOL��
		if (eexpr.mType == 4)	//���bexprΪBOOL������Ҫ��ת��Ϊ��BOOL��
		{
			FourElementTypeItem nullId;
			FourElementTypeItem tempId = newTempIdentifier();
			FourElementTypeItem constant;
			constant.mType = 1;
			constant.mConstantType = 1;
			//�����
			constant.mConstantInteger = 1;
			int mTC = mFourElementTypeList.size() + 1;
			FourElementType four(mFourElementTypeList.size() + 1, Equal, constant, nullId, tempId);
			mFourElementTypeList.push_back(four);
			//��ת���
			FourElementTypeItem pFour;
			pFour.mType = 5;
			pFour.mNumber = mTC + 3;
			FourElementType four1(mFourElementTypeList.size() + 1, Jump, nullId, nullId, pFour);
			mFourElementTypeList.push_back(four1);
			//�ٳ���
			constant.mConstantInteger = 0;
			int mFC = mFourElementTypeList.size() + 1;
			FourElementType four2(mFourElementTypeList.size() + 1, Equal, constant, nullId, tempId);
			mFourElementTypeList.push_back(four2);
			//�޸���Ԫʽ�б�
			//cout << "mFC " << eexpr.mFC << endl;
			modify_end_c(eexpr.mTC, mTC);
			modify_end_c(eexpr.mFC, mFC);
			eexpr = tempId;
		}
		
		//2.�����ֺ�
		if (itAnalysisCur == TokenenList.end())
		{
			//cout << "�Ѿ�������Tokenen����ĩβ" << endl;
			return false;
		}
		if ((*itAnalysisCur).type != Delimiter_Semicolon) //��Ϊ�ֺ�
		{
			//cout << "��ǰλ��ȱ�ٷֺ�" << endl;
			return false;
		}
		itAnalysisCur++;//���µ�ǰ����Tokenen����λ��

		//��Ҫ����
		//�������λ��returnPosiList.Add( NXQ )
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
	//���� goto
	else if ((*it_AnalysisCur).type == Keyword_goto)
	{
	it_AnalysisCur++;//���µ�ǰ����Tokenen����λ��
	//����Id
	if (it_AnalysisCur == listToken.end())
	{
	cout << "�Ѿ�������Tokenen����ĩβ" << endl;
	return false;
	}
	if ((*it_AnalysisCur).type != Identifier) //��ΪId
	{
	cout << "��ǰλ��ȱ�ٱ�ʶ��" << endl;
	return false;
	}
	it_AnalysisCur++;//���µ�ǰ����Tokenen����λ��
	}
	*/
	//���� print
	//RS -> print ( Print
	else if ((*itAnalysisCur).type == Keyword_print)
	{
		//outAnalysisFile << "G: RS -> print ( Print" << endl;
		//outAnalysisFile << "1> ������ print" << endl;
		itAnalysisCur++;//���µ�ǰ����Tokenen����λ��
						//���� ��С����
		if (itAnalysisCur == TokenenList.end())
		{
			//outAnalysisFile << "E: �Ѿ�������Tokenen����ĩβ" << endl;
			return false;
		}
		if ((*itAnalysisCur).type != Delimiter_Left_Small_Bracket)	//�Ƿ�Ϊ��С����
		{
			//outAnalysisFile << "E: ���� ( ����" << endl;
			return false;
		}
		//outAnalysisFile << "1> ������ (" << endl;
		itAnalysisCur++;//���µ�ǰ����Tokenen����λ��
		if (!semanticAnalysisPrint(itAnalysisCur, TokenenList, RS_CHAIN))
		{
			//outAnalysisFile << "E: ���� Print ����" << endl;
			return false;
		}
		return true;
	}
	//���� scan
	//RS -> scan ( id ) ;
	else if ((*itAnalysisCur).type == Keyword_scan)
	{
		//outAnalysisFile << "G: RS -> scan ( id ) ;" << endl;
		//outAnalysisFile << "1> ������ scan" << endl;
		itAnalysisCur++;//���µ�ǰ����Tokenen����λ��
						//1.���� ��С����
		if (itAnalysisCur == TokenenList.end())
		{
			//outAnalysisFile << "E: �Ѿ�������Tokenen����ĩβ" << endl;
			return false;
		}
		if ((*itAnalysisCur).type != Delimiter_Left_Small_Bracket)	//�Ƿ�Ϊ��С����
		{
			//outAnalysisFile << "E: ���� ( ����" << endl;
			return false;
		}
		//outAnalysisFile << "1> ������ (" << endl;
		itAnalysisCur++;//���µ�ǰ����Tokenen����λ��
						//2.���� id
		if (itAnalysisCur == TokenenList.end())
		{
			//outAnalysisFile << "E: �Ѿ�������Tokenen����ĩβ" << endl;
			return false;
		}
		if ((*itAnalysisCur).type != Identifier)	//�Ƿ�Ϊid
		{
			//outAnalysisFile << "E: ���� id ����" << endl;
			return false;
		}
		//outAnalysisFile << "1> ������ id" << endl;
		itAnalysisCur++;//���µ�ǰ����Tokenen����λ��
						//3.���� ��С����
		if (itAnalysisCur == TokenenList.end()) //û�з�����ĩβ
		{
			//outAnalysisFile << "E: �Ѿ�������Tokenen����ĩβ" << endl;
			return false;
		}
		if ((*itAnalysisCur).type != Delimiter_Right_Small_Bracket)	//�Ƿ�Ϊ��С����
		{
			//outAnalysisFile << "E: ���� ) ����" << endl;
			return false;
		}
		//outAnalysisFile << "1> ������ )" << endl;
		itAnalysisCur++;//���µ�ǰ����Tokenen����λ��
						//4.���� �ֺ�
		if (itAnalysisCur == TokenenList.end()) //û�з�����ĩβ
		{
			//outAnalysisFile << "E: �Ѿ�������Tokenen����ĩβ" << endl;
			return false;
		}
		if ((*itAnalysisCur).type != Delimiter_Semicolon)	//�Ƿ�Ϊ�ֺ�
		{
			//outAnalysisFile << "E: ���� ; ����" << endl;
			return false;
		}
		//outAnalysisFile << "1> ������ ;" << endl;
		//it_AnalysisCur++;//���µ�ǰ����Tokenen����λ��
		return true;
	}
	//RS -> MT DT VL ;
	else if ((*itAnalysisCur).type == Keyword_auto || (*itAnalysisCur).type == Keyword_register ||
		(*itAnalysisCur).type == Keyword_extern || (*itAnalysisCur).type == Keyword_static ||
		(*itAnalysisCur).type == Keyword_int || (*itAnalysisCur).type == Keyword_char ||
		(*itAnalysisCur).type == Keyword_float || (*itAnalysisCur).type == Keyword_double)
	{
		VariableDefinition variableDefinition;
		//����MT
		variableDefinition.memoryType = Keyword_extern;
		if (semanticAnalysisMT(itAnalysisCur, TokenenList, variableDefinition.memoryType))
		{
			//cout << "����MT1����" << endl;
			//return false;
		}
		//����DT
		variableDefinition.dataType = Error;
		if (!semanticAnalysisDT(itAnalysisCur, TokenenList, variableDefinition.dataType))
		{
			//cout << "����DT����" << endl;
			return false;
		}
		//����VL
		if (!semanticAnalysisVL(itAnalysisCur, TokenenList, variableDefinition.variableList, false))
		{
			//cout << "����VL����" << endl;
			return false;
		}
		mVariableDefinitionList.push_back(variableDefinition);
		//�����ֺ�
		if (itAnalysisCur == TokenenList.end())
		{
			//cout << "�Ѿ�������Tokenen����ĩβ" << endl;
			return false;
		}
		if ((*itAnalysisCur).type != Delimiter_Semicolon) //��Ϊ�ֺ�
		{
			//cout << "��ǰλ��ȱ�ٷֺ�" << endl;
			return false;
		}
		itAnalysisCur++;//���µ�ǰ����Tokenen����λ��
		return true;
	}
	//PR ;
	else if (expressPreAnalysis((*itAnalysisCur).type))
	{
		//����PR ��ֵ���ʽ �������ʽ �߼����ʽ
		FourElementTypeItem express;
		if (!semanticAnalysis_eexpr(itAnalysisCur, TokenenList, express))
		{
			cout << (*itAnalysisCur).data << endl;
			return false;
		}
		//����express ��ΪBOOL�� BOOL��->��Ϊ��BOOL��
		if (express.mType <= 0 || express.mType > 4)
		{
			return false;
		}
		if (express.mType == 4)	//���expressΪBOOL��������Ҫ��ת��Ϊ��BOOL��
		{
			FourElementTypeItem nullId;
			FourElementTypeItem tempId = newTempIdentifier();
			FourElementTypeItem constant;
			constant.mType = 1;
			constant.mConstantType = 1;
			//�����
			constant.mConstantInteger = 1;
			int mTC = mFourElementTypeList.size() + 1;
			FourElementType four(mFourElementTypeList.size() + 1, Equal, constant, nullId, tempId);
			mFourElementTypeList.push_back(four);
			//��ת���
			FourElementTypeItem pFour;
			pFour.mType = 5;
			pFour.mNumber = mTC + 3;
			FourElementType four1(mFourElementTypeList.size() + 1, Jump, nullId, nullId, pFour);
			mFourElementTypeList.push_back(four1);
			//�ٳ���
			constant.mConstantInteger = 0;
			int mFC = mFourElementTypeList.size() + 1;
			FourElementType four2(mFourElementTypeList.size() + 1, Equal, constant, nullId, tempId);
			mFourElementTypeList.push_back(four2);
			//�޸���Ԫʽ�б�
			modify_end_c(express.mTC, mTC);
			modify_end_c(express.mFC, mFC);
			express = tempId;
			//cout << "express" << "eexpr> TC:" << mTC << " FC:" << mFC << endl;
		}
		//��������
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
		//�����ֺ�
		if (itAnalysisCur == TokenenList.end())
		{
			cout << "�Ѿ�������Tokenen����ĩβ" << endl;
			return false;
		}
		if ((*itAnalysisCur).type != Delimiter_Semicolon) //��Ϊ�ֺ�
		{
			cout << "��ǰλ��ȱ�ٷֺ�" << endl;
			return false;
		}
		itAnalysisCur++;//���µ�ǰ����Tokenen����λ��
		return true;
	}
	//�ж��Ƿ�Ϊ�Ҵ�����
	else if ((*itAnalysisCur).type != Delimiter_Right_Large_Bracket)
	{
		return true;
	}
	else
	{
		//cout << (*itAnalysisCur).data << " �޷�ʶ��" << endl;
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
	//�Ƿ������ĩβ
	if (itAnalysisCur == TokenenList.end()) //û�з�����ĩβ
	{
		return false;
	}
	// else
	if (Keyword_else != (*itAnalysisCur).type)
	{
		// TC �� FC �ϲ�
		modify_end_c(FC, chain);
		return true;	//��ΪelseҲ�ǶԵ�
	}
	itAnalysisCur++;	//���µ�ǰ����Tokenen����λ��
	//����SB ������
	//int NXQ = mFourElementTypeList.size() + 1;
	// FC = NXQ
	//modify_end_c(FC, NXQ);

	//����SB
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
	if (itAnalysisCur == TokenenList.end()) //û�з�����ĩβ
	{
		return false;
	}
	//1.�����������
	if ((*itAnalysisCur).type == Delimiter_Left_Large_Bracket)
	{
		itAnalysisCur++;//���µ�ǰ����Tokenen����λ��
		//2.����SB1��������chain
		semanticAnalysis_SB1(itAnalysisCur, TokenenList, SB_CHAIN);	//����SB1����ֵ�����λ����ԶΪtrue
		//3.�����Ҵ�����
		if (itAnalysisCur == TokenenList.end()) //û�з�����ĩβ
		{
			return false;
		}
		if ((*itAnalysisCur).type != Delimiter_Right_Large_Bracket)
		{
			return false;
		}
		itAnalysisCur++;//���µ�ǰ����Tokenen����λ��
	}
	else
	{
		//1.����RS��������chain
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
bool SemanticAnalysis::semanticAnalysis_SB1(list<Token>::iterator & itAnalysisCur, list<Token>& TokenenList, int& SB1_CHAIN)	//�����������᷵��true
{
	list<Token>::iterator it_tmp = itAnalysisCur;
	//����RS
	//int chain = 0;
	if (semanticAnalysis_RS(itAnalysisCur, TokenenList, SB1_CHAIN))
	{
		//����SB1
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
	if (itAnalysisCur == TokenenList.end()) //û�з�����ĩβ
	{
		return false;
	}
	//���� string ) ;
	if ((*itAnalysisCur).type == String)	//�Ƿ�Ϊ�ַ���
	{
		FourElementTypeItem nullId;
		FourElementTypeItem  printString;
		printString.mType = 1;	//����Ϊ����
		printString.mConstantType = 4;	//��������Ϊ�ַ���
		printString.mPrintString = clearUpString((*itAnalysisCur).data);
		FourElementType four(mFourElementTypeList.size() + 1, Print, printString, nullId, nullId);
		mFourElementTypeList.push_back(four);

		FourElementTypeItem  pFour;
		pFour.mType = 5;
		pFour.mNumber = 0;
		FourElementType four1(mFourElementTypeList.size() + 1, Jump, nullId, nullId, pFour);
		mFourElementTypeList.push_back(four1);

		chain = mFourElementTypeList.size();

		itAnalysisCur++;//���µ�ǰ����Tokenen����λ��
						// ���� ��С����
		if (itAnalysisCur == TokenenList.end()) //û�з�����ĩβ
		{
			return false;
		}
		if ((*itAnalysisCur).type != Delimiter_Right_Small_Bracket)	//�Ƿ�Ϊ��С����
		{
			return false;
		}
		itAnalysisCur++;//���µ�ǰ����Tokenen����λ��
						// ���� �ֺ�
		if (itAnalysisCur == TokenenList.end()) //û�з�����ĩβ
		{
			return false;
		}
		if ((*itAnalysisCur).type != Delimiter_Semicolon)	//�Ƿ�Ϊ�ֺ�
		{
			return false;
		}
		itAnalysisCur++;//���µ�ǰ����Tokenen����λ��
	}
	else
	{
		FourElementTypeItem fourElementTypeItem;
		if (!semanticAnalysis_eexpr(itAnalysisCur, TokenenList, fourElementTypeItem))
		{
			//outAnalysisFile << "E: ���� eexpr ����" << endl;
			return false;
		}
		//����four ����������
		switch (fourElementTypeItem.mType)
		{
		case 1:	//����
		{
			FourElementTypeItem nullId;
			FourElementTypeItem  printString;
			printString.mType = 1;	//����Ϊ����
			printString.mConstantType = 4;	//��������Ϊ�ַ���
			printString.mPrintString = fourElementTypeItem.mCacheBuffer;
			FourElementType four(mFourElementTypeList.size() + 1, Print, printString, nullId, nullId);
			mFourElementTypeList.push_back(four);
			break;
		}
		case 2:	//�û��������
		{
			FourElementTypeItem nullId;
			FourElementType four(mFourElementTypeList.size() + 1, Print, fourElementTypeItem, nullId, nullId);	//four�Ǳ���
			mFourElementTypeList.push_back(four);
			break;
		}
		case 3:	//��ʱ����
		{
			FourElementTypeItem nullId;
			FourElementType four(mFourElementTypeList.size() + 1, Print, fourElementTypeItem, nullId, nullId);	//four�Ǳ���
			mFourElementTypeList.push_back(four);
			break;
		}
		case 4:	//�������ʽ
		{
			//���bexprΪBOOL������Ҫ��ת��Ϊ��BOOL��
			FourElementTypeItem nullId;
			FourElementTypeItem tempId = newTempIdentifier();
			FourElementTypeItem constant;
			constant.mType = 1;	//��Ϊ����
			constant.mConstantType = 4;	//��Ϊ�ַ���
										//�����
			constant.mPrintString = "true";
			int mTC = mFourElementTypeList.size() + 1;
			FourElementType four(mFourElementTypeList.size() + 1, Print, constant, nullId, tempId);
			mFourElementTypeList.push_back(four);
			//��ת���
			FourElementTypeItem pFour;
			pFour.mType = 5;
			pFour.mNumber = mTC + 3;
			FourElementType four1(mFourElementTypeList.size() + 1, Jump, nullId, nullId, pFour);
			mFourElementTypeList.push_back(four1);
			//�ٳ���
			constant.mPrintString = "false";
			int mFC = mFourElementTypeList.size() + 1;
			FourElementType four2(mFourElementTypeList.size() + 1, Print, constant, nullId, tempId);
			mFourElementTypeList.push_back(four2);
			//�޸���Ԫʽ�б�
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

		// ���� ��С����
		if (itAnalysisCur == TokenenList.end()) //û�з�����ĩβ
		{
			return false;
		}
		if ((*itAnalysisCur).type != Delimiter_Right_Small_Bracket)	//�Ƿ�Ϊ��С����
		{
			return false;
		}
		itAnalysisCur++;//���µ�ǰ����Tokenen����λ��
		// ���� �ֺ�
		if (itAnalysisCur == TokenenList.end()) //û�з�����ĩβ
		{
			return false;
		}
		if ((*itAnalysisCur).type != Delimiter_Semicolon)	//�Ƿ�Ϊ�ֺ�
		{
			return false;
		}
		itAnalysisCur++;//���µ�ǰ����Tokenen����λ��
	}
	return true;
}
//------------------------------------------���ʽ----------------------------------------------------------------------------
/*
	���ȹؼ������㣺
	1������������ȼ�������ԡ�
	2��һ����ֵ���ʽ����ֵ�ģ�ֵ���Ǳ�����ֵ������a=3 �������ֵ���ʽ��ֵ����3������b=��a=3������b��ֵΪ3.
	���磺
	a=b=c��ֻ��һ����������Ⱥţ��������ȼ���һ���ģ����ȺŵĽ�����Ǵ��������(Ҳ���ǵ�ʽ�����������)������a=b=c ��ͬ�� a=(b=c),��a=4,b=4;
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
	//1.Ԥ�ȷ�����һ��Tokenen���Ƿ�Ϊ��ֵ�����
	list<Token>::iterator tmp = itAnalysisCur;
	if (semanticAnalysis_ao(itAnalysisCur, TokenenList, ao))	//��һ��Tokenen��Ϊ��ֵ�������bexprӦ��Ϊ����
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
		//1.1����bexpr�Ƿ�Ϊ�����������Ϊ�����򱨴�
		if (!(eexpr.mType == 2 || eexpr.mType == 3))	//�Ƿ�Ϊ�û��Զ����������ʱ����
		{
			mErrorInfo.push_back("��n�У������" + ao_str + "���Ӧ��Ϊһ������");
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

		//1.Ԥ�ȷ�����һ��Tokenen���Ƿ�Ϊ��ֵ�����
		list<Token>::iterator tmp = itAnalysisCur;
		int ao_tmp = 0;
		string ao_str_tmp = "";
		if (semanticAnalysis_ao(itAnalysisCur, TokenenList, ao_tmp))	//bexprӦ��Ϊ����
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
			//2.1����eexpr1�Ƿ�Ϊ�����������Ϊ�����򱨴�
			if (!(bexpr.mType == 2 || bexpr.mType == 3))	//�Ƿ�Ϊ�û��Զ����������ʱ����
			{
				mErrorInfo.push_back("��n�У������" + ao_str_tmp + "���Ӧ��Ϊһ������");
				return false;	//
			}
		}// end if bexprӦ��Ϊ����
		itAnalysisCur = tmp;

		if (!semanticAnalysis_eexpr1(itAnalysisCur, TokenenList, bexpr))	//bexpr
		{
			return false;
		}
		//��ֵ�������������󣬽�bexpr������ֵ��eexpr1
		if (bexpr.mType >= 1 && bexpr.mType <= 4)
		{
			if (bexpr.mType == 4)	//���bexprΪBOOL������Ҫ��ת��Ϊ��BOOL��
			{
				FourElementTypeItem nullId;
				FourElementTypeItem tempId = newTempIdentifier();
				FourElementTypeItem constant;
				constant.mType = 1;
				constant.mConstantType = 1;
				//�����
				constant.mConstantInteger = 1;
				int mTC = mFourElementTypeList.size() + 1;
				FourElementType four(mFourElementTypeList.size() + 1, Equal, constant, nullId, tempId);
				mFourElementTypeList.push_back(four);
				//��ת���
				FourElementTypeItem pFour;
				pFour.mType = 5;
				pFour.mNumber = mTC + 3;
				FourElementType four1(mFourElementTypeList.size() + 1, Jump, nullId, nullId, pFour);
				mFourElementTypeList.push_back(four1);
				//�ٳ���
				constant.mConstantInteger = 0;
				int mFC = mFourElementTypeList.size() + 1;
				FourElementType four2(mFourElementTypeList.size() + 1, Equal, constant, nullId, tempId);
				mFourElementTypeList.push_back(four2);
				//�޸���Ԫʽ�б�
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
		//1.�ж�bexpr1�Ƿ�ΪBOOL��
		if (bexpr1.mType != 4)	//�����ΪBOOL��������Ҫ��ת��ΪBOOL��
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
		//1.�ж�bterm�Ƿ�ΪBOOL��
		if (bterm.mType != 4)	//�����ΪBOOL��������Ҫ��ת��ΪBOOL��
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
		//1.�ж�bterm1�Ƿ�ΪBOOL��
		if (bterm1.mType != 4)	//�����ΪBOOL��������Ҫ��ת��ΪBOOL��
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
		//2.�ж�term�Ƿ�ΪBOOL��
		if (rterm.mType != 4)	//���rterm��ΪBOOL��������Ҫ��ת��ΪBOOL��
		{
			//2.1��rtermת��ΪBOOL��
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
			//ת������
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
	//ǰ4��������ͺ���2������������ȼ�ȷʵ�ǲ�һ���ģ�������6����������������ӣ����д��һ���ǿ��Եģ�֮ǰ������Ǵ���
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

		//ǰ������
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

		//ǰ������
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

		//ǰ������
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

		//ǰ������
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
	//�޸��ķ�����ӵ�����
	else if ((*itAnalysisCur).type == Operator_Not_Equal_To)	// !=
	{
		itAnalysisCur++;
		FourElementTypeItem aexpr;
		if (!semanticAnalysis_aexpr(itAnalysisCur, TokenenList, aexpr))	//aexpr
		{
			return false;
		}

		//ǰ������
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

		//ǰ������
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
	// �ж�term1��factor�Ƿ�Ϊ���������Ϊ�������������ǵ�ֵ
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
		//��������������%�����Ҳ��������붼Ϊint��
		if (factor.mType == 1 && term1.mType == 1)	//ֱ�Ӽ��㣬���õ��Ľ����ֵ��term1
		{
			if (term1.mConstantType == 1)	//�Ƿ�Ϊint����
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
					//�����%�ұ�Ӧ��Ϊint����
					switch (factor.mConstantType)
					{
					case 1:	//int
						term1.mConstantInteger %= factor.mConstantInteger;
						break;
					case 2:	//float
					{
						//�����%�ұ�Ӧ��Ϊint����
						mErrorInfo.push_back("�����%�ұ߲���������Ϊint��");
						return false;	//����
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
			else if (term1.mConstantType == 2) //�Ƿ�Ϊfloat����
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
					//�����%���Ӧ��Ϊint����
					mErrorInfo.push_back("�����%��߲���������Ϊint��");
					return false;	//����
					break;
				}
				default:
					break;
				}
			}
			else    //Ϊchar����
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
						//�����%�ұ�Ӧ��Ϊint����
						mErrorInfo.push_back("�����%�ұ߲���������Ϊint��");
						return false;	//����
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
			//���λ��Ҫ��� term1 �� factor�������ͣ������������%
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
		case 1://����
		{
			switch (ael.mConstantType)
			{
			case 1://����
				ael.mConstantInteger == 0 ? ael.mConstantInteger = 1 : ael.mConstantInteger = 0;
				break;
			case 2://������
				ael.mConstantFloat == 0.0 ? ael.mConstantFloat = 1.0 : ael.mConstantFloat == 0.0;
				break;
			case 3://�ַ���
				ael.mConstantChar == 0 ? ael.mConstantChar = 1 : ael.mConstantChar = 0;
				break;
			default:
				break;
			}
			factor = ael;
			break;
		}
		case 2:	//�û�����ı���
		{
			FourElementTypeItem tempId = newTempIdentifier();
			FourElementTypeItem nullId;
			FourElementType four(mFourElementTypeList.size() + 1, IsNot, ael, nullId, tempId);
			mFourElementTypeList.push_back(four);
			factor = tempId;
			break;
		}
		case 3:	//��ʱ����
		{
			FourElementTypeItem tempId = newTempIdentifier();
			FourElementTypeItem nullId;
			FourElementType four(mFourElementTypeList.size() + 1, IsNot, ael, nullId, tempId);
			mFourElementTypeList.push_back(four);
			factor = tempId;
			break;
		}
		case 4:	//BOOL����
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
	if ((*itAnalysisCur).type == Delimiter_Left_Small_Bracket)	//��С����
	{
		itAnalysisCur++;
		// bexpr
		semanticAnalysis_bexpr(itAnalysisCur, TokenenList, ael);	//bexpr
		if (itAnalysisCur == TokenenList.end())
			return false;
		if ((*itAnalysisCur).type == Delimiter_Right_Small_Bracket)	//��С����
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
	root -> ����(�˽��ơ�ʮ���ơ�ʮ������)
	root -> ������( С����ָ�� )
	root -> BOOL ������
	root -> �ַ���
	//root -> �ַ����� ����printλ���õ�
*/
bool SemanticAnalysis::semanticAnalysis_root(list<Token>::iterator& itAnalysisCur, list<Token>& TokenenList, FourElementTypeItem& root)
{
	if (itAnalysisCur == TokenenList.end())
		return false;
	if ((*itAnalysisCur).type == Identifier)	//id
	{
		if (!isUserVariableDefinition((*itAnalysisCur).data))
		{
			mErrorInfo.push_back("���� \"" + (*itAnalysisCur).data + "\" δ����");
		}
		root.mType = 2;	//�û�����ı���
		root.mUserIdentifierName = (*itAnalysisCur).data;
		itAnalysisCur++;
	}
	else if ((*itAnalysisCur).type == Character)	//�ַ�
	{
		root.mType = 1;	//����
		root.mConstantType = 3;	//�ַ���
		root.mConstantChar = stringConvertCharacter((*itAnalysisCur).data);
		itAnalysisCur++;
	}
	else if ((*itAnalysisCur).type == String)	//�ַ���
	{
		//����������ط����ַ�������N���ַ������
		itAnalysisCur++;
	}
	else if ((*itAnalysisCur).type == Number_Octonary)	//���� �˽���
	{
		root.mCacheBuffer = (*itAnalysisCur).data;	//���͵��ַ�����ʽ��ӵ�������
		root.mType = 1;//����
		root.mConstantType = 1;	//����
		root.mConstantInteger = stringConvertNumberOctonary((*itAnalysisCur).data);
		itAnalysisCur++;
	}
	else if ((*itAnalysisCur).type == Number_Decimalism)	//���� ʮ����
	{
		root.mCacheBuffer = (*itAnalysisCur).data;	//���͵��ַ�����ʽ��ӵ�������
		root.mType = 1;//����
		root.mConstantType = 1;	//����
		root.mConstantInteger = stringConvertNumberDecimalism((*itAnalysisCur).data);
		itAnalysisCur++;
	}
	else if ((*itAnalysisCur).type == Number_Hexadecimal)	//���� ʮ������
	{
		root.mCacheBuffer = (*itAnalysisCur).data;	//���͵��ַ�����ʽ��ӵ�������
		root.mType = 1;//����
		root.mConstantType = 1;	//����
		root.mConstantInteger = stringConvertNumberHexadecimal((*itAnalysisCur).data);
		itAnalysisCur++;
	}
	else if ((*itAnalysisCur).type == Number_Decimals)	//������ С��
	{
		itAnalysisCur++;
	}
	else if ((*itAnalysisCur).type == Number_Exponent)	//������ ָ��
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
		BOOL.mType = 1;	//����
		BOOL.mConstantType = 1;	//����
		BOOL.mConstantInteger = 1;
	}
	else if ((*itAnalysisCur).type == Keyword_false)
	{
		itAnalysisCur++;
		BOOL.mType = 1;	//����
		BOOL.mConstantType = 1;	//����
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
	// ! ( id ����(�ˣ�ʮ��ʮ��) ����(С��ָ) true false char
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
// true-�ظ� false-���ظ�
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
//�жϺ��������ͺ���ʵ���Ƿ�ƥ��
// true-ƥ�� false-��ƥ��
bool SemanticAnalysis::isMatchFunctionComeTrueAndDefine(FunctionDefinition fd)
{
	//��������ͬ ����ֵ������ͬ ����������ͬ ÿ������������ͬ
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
				//�ظ�����Ĵ���
				mErrorInfo.push_back("���� " + fd.functionName + " �ظ�����");
			}
			if (fd.isComeTrue)	//�Ǻ���ʵ��
				(*it).funcEnter = fd.funcEnter;
			return true;	//����[�п������ظ����壬����ӵ�list��]
		}
	}
	return false;
}
