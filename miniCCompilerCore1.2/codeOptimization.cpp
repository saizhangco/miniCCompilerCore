#include "codeOptimization.h"

CodeOptimization::CodeOptimization()
{
}

CodeOptimization::~CodeOptimization()
{
}

//进行代码优化
//删除空跳转
bool CodeOptimization::runCodeOptimization(SemanticAnalysis & semantic)
{
	//删除空跳转
	list<FourElementType>::iterator it_FourElementTypeList = semantic.mFourElementTypeList.begin();
	//遍历List
	for (; it_FourElementTypeList != semantic.mFourElementTypeList.end(); it_FourElementTypeList++)
	{
		//判断四元式是否为未优化四元式
		if ((*it_FourElementTypeList).mOptimizationType == 0 && (*it_FourElementTypeList).mOperation == Jump
			&& (*it_FourElementTypeList).mResult.mType == 5)//四元式指针
		{
			//
			int m_nResult = (*it_FourElementTypeList).mResult.mNumber;//下一个四元式
			int m_nResultBack = m_nResult;
			while (true)
			{
				//通过m_nResult找到指定四元式
				list<FourElementType>::iterator it_find = findItFourElementTypeItem(m_nResult, semantic);
				if (it_find != semantic.mFourElementTypeList.begin())
				{
					//判断找到四元式
					if ((*it_find).mOperation == Jump && (*it_find).mResult.mType == 5)
					{
						m_nResultBack = m_nResult;
						m_nResult = (*it_find).mResult.mNumber;//下一个四元式
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
			//开始进行优化
			if (m_nResult != (*it_FourElementTypeList).mResult.mNumber)
			{
				//保存链条 chain
				int chain_begin = (*it_FourElementTypeList).mResult.mNumber;
				int chain_end = m_nResult;
				//修改
				(*it_FourElementTypeList).mOptimizationType = 2;
				(*it_FourElementTypeList).mResultBack.mType = 5;
				(*it_FourElementTypeList).mResultBack.mNumber = chain_begin;
				(*it_FourElementTypeList).mResult.mNumber = chain_end;
				//删除
				while (chain_begin != chain_end && chain_begin !=0)
				{
					//list<FourElementType>::iterator it_find = findItFourElementTypeItem(chain_begin, semantic);
					//删除
					//(*it_find).mOptimizationType = 1;
					//chain_begin = (*it_find).mResult.mNumber;
					chain_begin = findItFourElementTypeRemove(chain_begin, semantic);
				}
			}
		}
	}

	//删除相邻跳转
	for (; it_FourElementTypeList != semantic.mFourElementTypeList.end(); it_FourElementTypeList++)
	{
		//判断四元式是否为未优化四元式，跳转语句
		if ((*it_FourElementTypeList).mOptimizationType == 0 && (*it_FourElementTypeList).mOperation == Jump
			&& (*it_FourElementTypeList).mResult.mType == 5)//四元式指针
		{
			if ((*it_FourElementTypeList).mNumber == ((*it_FourElementTypeList).mResult.mNumber - 1))
			{
				//该四元式不被其他四元式所依赖
				(*it_FourElementTypeList).mOptimizationType = 1;//删除
			}
		}
	}
	//保存文件
	saveCodeOptimizationToFile(semantic, "analysis//codeOptimization.txt");
	return true;
}

list<FourElementType>::iterator CodeOptimization::findItFourElementTypeItem(int m_nResult, SemanticAnalysis& semantic)
{
	list<FourElementType>::iterator it_FourElementTypeList = semantic.mFourElementTypeList.begin();
	//遍历List
	for (; it_FourElementTypeList != semantic.mFourElementTypeList.end(); it_FourElementTypeList++)
	{
		//判断mNumber==m_nResult
		if (m_nResult == (*it_FourElementTypeList).mNumber)
		{
			return it_FourElementTypeList;//返回当前指针
		}
	}
	return semantic.mFourElementTypeList.end();
}

int CodeOptimization::findItFourElementTypeRemove(int m_nResult, SemanticAnalysis & semantic)
{
	list<FourElementType>::iterator it_FourElementTypeList = semantic.mFourElementTypeList.begin();
	//遍历List
	for (; it_FourElementTypeList != semantic.mFourElementTypeList.end(); it_FourElementTypeList++)
	{
		//判断mNumber==m_nResult
		if (m_nResult == (*it_FourElementTypeList).mNumber)
		{
			(*it_FourElementTypeList).mOptimizationType = 1;
			return (*it_FourElementTypeList).mResult.mNumber;
			//return it_FourElementTypeList;//返回当前指针
		}
	}
	return 0;
}

bool CodeOptimization::saveCodeOptimizationToFile(SemanticAnalysis & semantic, const string & fileName)
{
	//"analysis//codeOptimization.txt"
	ofstream outFile(fileName);
	outFile << "********************************************" << endl;
	outFile << "*                 代码优化                 *" << endl;
	outFile << "********************************************" << endl;
	list<FourElementType>::iterator it_FourElementTypeList = semantic.mFourElementTypeList.begin();
	//遍历List
	for (; it_FourElementTypeList != semantic.mFourElementTypeList.end(); it_FourElementTypeList++)
	{
		string content = (*it_FourElementTypeList).getFourElementType();
		string optimization = "";
		if ((*it_FourElementTypeList).mOptimizationType == 0)
		{
			optimization = "\n";
		}
		else if((*it_FourElementTypeList).mOptimizationType == 1)	//删除
		{
			optimization = "\tRemove\n";
		}
		else if ((*it_FourElementTypeList).mOptimizationType == 2)	//修改
		{
			optimization = "\tModify " + to_string((*it_FourElementTypeList).mResultBack.mNumber) + "->" 
				+ to_string((*it_FourElementTypeList).mResult.mNumber) + "\n";
		}
		outFile << content << optimization;
	}
	outFile.close();
	return true;
}

