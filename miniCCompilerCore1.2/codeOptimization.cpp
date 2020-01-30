#include "codeOptimization.h"

CodeOptimization::CodeOptimization()
{
}

CodeOptimization::~CodeOptimization()
{
}

//���д����Ż�
//ɾ������ת
bool CodeOptimization::runCodeOptimization(SemanticAnalysis & semantic)
{
	//ɾ������ת
	list<FourElementType>::iterator it_FourElementTypeList = semantic.mFourElementTypeList.begin();
	//����List
	for (; it_FourElementTypeList != semantic.mFourElementTypeList.end(); it_FourElementTypeList++)
	{
		//�ж���Ԫʽ�Ƿ�Ϊδ�Ż���Ԫʽ
		if ((*it_FourElementTypeList).mOptimizationType == 0 && (*it_FourElementTypeList).mOperation == Jump
			&& (*it_FourElementTypeList).mResult.mType == 5)//��Ԫʽָ��
		{
			//
			int m_nResult = (*it_FourElementTypeList).mResult.mNumber;//��һ����Ԫʽ
			int m_nResultBack = m_nResult;
			while (true)
			{
				//ͨ��m_nResult�ҵ�ָ����Ԫʽ
				list<FourElementType>::iterator it_find = findItFourElementTypeItem(m_nResult, semantic);
				if (it_find != semantic.mFourElementTypeList.begin())
				{
					//�ж��ҵ���Ԫʽ
					if ((*it_find).mOperation == Jump && (*it_find).mResult.mType == 5)
					{
						m_nResultBack = m_nResult;
						m_nResult = (*it_find).mResult.mNumber;//��һ����Ԫʽ
					}
					else
					{
						break;
					}
				}
				else
				{
					m_nResult = m_nResultBack;
					break;
				}
			}
			//��ʼ�����Ż�
			if (m_nResult != (*it_FourElementTypeList).mResult.mNumber)
			{
				//�������� chain
				int chain_begin = (*it_FourElementTypeList).mResult.mNumber;
				int chain_end = m_nResult;
				//�޸�
				(*it_FourElementTypeList).mOptimizationType = 2;
				(*it_FourElementTypeList).mResultBack.mType = 5;
				(*it_FourElementTypeList).mResultBack.mNumber = chain_begin;
				(*it_FourElementTypeList).mResult.mNumber = chain_end;
				//ɾ��
				while (chain_begin != chain_end && chain_begin !=0)
				{
					//list<FourElementType>::iterator it_find = findItFourElementTypeItem(chain_begin, semantic);
					//ɾ��
					//(*it_find).mOptimizationType = 1;
					//chain_begin = (*it_find).mResult.mNumber;
					chain_begin = findItFourElementTypeRemove(chain_begin, semantic);
				}
			}
		}
	}

	//ɾ��������ת
	for (; it_FourElementTypeList != semantic.mFourElementTypeList.end(); it_FourElementTypeList++)
	{
		//�ж���Ԫʽ�Ƿ�Ϊδ�Ż���Ԫʽ����ת���
		if ((*it_FourElementTypeList).mOptimizationType == 0 && (*it_FourElementTypeList).mOperation == Jump
			&& (*it_FourElementTypeList).mResult.mType == 5)//��Ԫʽָ��
		{
			if ((*it_FourElementTypeList).mNumber == ((*it_FourElementTypeList).mResult.mNumber - 1))
			{
				//����Ԫʽ����������Ԫʽ������
				(*it_FourElementTypeList).mOptimizationType = 1;//ɾ��
			}
		}
	}
	//�����ļ�
	saveCodeOptimizationToFile(semantic, "analysis//codeOptimization.txt");
	return true;
}

list<FourElementType>::iterator CodeOptimization::findItFourElementTypeItem(int m_nResult, SemanticAnalysis& semantic)
{
	list<FourElementType>::iterator it_FourElementTypeList = semantic.mFourElementTypeList.begin();
	//����List
	for (; it_FourElementTypeList != semantic.mFourElementTypeList.end(); it_FourElementTypeList++)
	{
		//�ж�mNumber==m_nResult
		if (m_nResult == (*it_FourElementTypeList).mNumber)
		{
			return it_FourElementTypeList;//���ص�ǰָ��
		}
	}
	return semantic.mFourElementTypeList.end();
}

int CodeOptimization::findItFourElementTypeRemove(int m_nResult, SemanticAnalysis & semantic)
{
	list<FourElementType>::iterator it_FourElementTypeList = semantic.mFourElementTypeList.begin();
	//����List
	for (; it_FourElementTypeList != semantic.mFourElementTypeList.end(); it_FourElementTypeList++)
	{
		//�ж�mNumber==m_nResult
		if (m_nResult == (*it_FourElementTypeList).mNumber)
		{
			(*it_FourElementTypeList).mOptimizationType = 1;
			return (*it_FourElementTypeList).mResult.mNumber;
			//return it_FourElementTypeList;//���ص�ǰָ��
		}
	}
	return 0;
}

bool CodeOptimization::saveCodeOptimizationToFile(SemanticAnalysis & semantic, const string & fileName)
{
	//"analysis//codeOptimization.txt"
	ofstream outFile(fileName);
	outFile << "********************************************" << endl;
	outFile << "*                 �����Ż�                 *" << endl;
	outFile << "********************************************" << endl;
	list<FourElementType>::iterator it_FourElementTypeList = semantic.mFourElementTypeList.begin();
	//����List
	for (; it_FourElementTypeList != semantic.mFourElementTypeList.end(); it_FourElementTypeList++)
	{
		string content = (*it_FourElementTypeList).getFourElementType();
		string optimization = "";
		if ((*it_FourElementTypeList).mOptimizationType == 0)
		{
			optimization = "\n";
		}
		else if((*it_FourElementTypeList).mOptimizationType == 1)	//ɾ��
		{
			optimization = "\tRemove\n";
		}
		else if ((*it_FourElementTypeList).mOptimizationType == 2)	//�޸�
		{
			optimization = "\tModify " + to_string((*it_FourElementTypeList).mResultBack.mNumber) + "->" 
				+ to_string((*it_FourElementTypeList).mResult.mNumber) + "\n";
		}
		outFile << content << optimization;
	}
	outFile.close();
	return true;
}

