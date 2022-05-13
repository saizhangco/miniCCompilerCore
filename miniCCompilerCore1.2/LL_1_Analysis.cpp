#include "LL_1_Analysis.h"
#include "symbol.h"
#include <algorithm>

LL_1_Analysis::LL_1_Analysis()
{
	Grammar gram;
	g = gram;
	isReady = true;
	if (!initFirstSet(gram))
	{
		cout << "初始化FirstSet失败!" << endl;
		isReady = false;
		return;
	}
	//printFirstSetFormat_1();	//打印 FirstSet集
	//cout << endl;
	if (!initFollowSet(gram))
	{
		cout << "初始化FollowSet失败!" << endl;
		isReady = false;
		return;
	}
	//printFollowSetFormat_1();	//打印 Follow集
	if (!initAnalysisTable(gram))
	{
		cout << "初始化预测分析表失败!" << endl;
		isReady = false;
		return;
	}
	//printAnalysisTable();		//打印 预测分析表
	analysisResult.clear();
}

LL_1_Analysis::LL_1_Analysis(const string & fileName)
{
	Grammar gram(fileName);
	g = gram;
	isReady = true;
	if (!initFirstSet(gram))
	{
		cout << "初始化FirstSet失败!" << endl;
		isReady = false;
		return;
	}
	//printFirstSetFormat_1();	//打印 FirstSet集
	cout << endl;
	if (!initFollowSet(gram))
	{
		cout << "初始化FollowSet失败!" << endl;
		isReady = false;
		return;
	}
	//printFollowSetFormat_1();	//打印 Follow集
	if (!initAnalysisTable(gram))
	{
		cout << "初始化预测分析表失败!" << endl;
		isReady = false;
		return;
	}
	//printAnalysisTable();		//打印 预测分析表
	analysisResult.clear();
}

LL_1_Analysis::~LL_1_Analysis()
{
}

bool LL_1_Analysis::initFirstSet(Grammar& g)
{
	//1.根据文法中的非终结符初始化FirstSet
	list<Token>::iterator it;
	for (it = g.mNonterminator.begin(); it != g.mNonterminator.end(); it++)
	{
		if (!existInFirstSet((*it).data))//不存在
		{
			First f(*it);
			firstSet.push_back(f);
		}
	}
	//2. 若有产生式A->aα,a属于Vt,则把a加入到First(A)中
	list<Production>::iterator it_p;
	for (it_p = g.mProduction.begin(); it_p != g.mProduction.end(); it_p++)
	{
		//判断产生式右部的第一个符号
		if (g.isTerminator((*(*it_p).right.begin()).data))//如果为终结符，添加
		{
			list<First>::iterator it_f = getFirstAsNonterminator((*it_p).left.data);
			if (it_f == firstSet.end())
			{
				cout << "出错了，在创建First集时，无非终结符" << endl;
			}
			else
			{
				if (!existATItemInATItemList((*it_f).mFirst, (*(*it_p).right.begin()).data))
				{
					//添加到 first集 中
					//Tok tok((*(*it_p).right.begin()).data, (*(*it_p).right.begin()).type);
					AnalysisTableItem item(*(*it_p).right.begin(), *it_p);
					(*it_f).mFirst.push_back(item);
				}
			}
		}
	}
	//3. 若有产生式A->$,则把$加入到First(A)中
	for (it_p = g.mProduction.begin(); it_p != g.mProduction.end(); it_p++)
	{
		if ((*(*it_p).right.begin()).data == "$")//如果为$，添加
		{
			list<First>::iterator it_f = getFirstAsNonterminator((*it_p).left.data);
			if (it_f == firstSet.end())
			{
				cout << "出错了，在创建First集时，无非终结符" << endl;
			}
			else
			{
				if (!existATItemInATItemList((*it_f).mFirst, (*(*it_p).right.begin()).data))
				{
					//添加到 first集 中
					//Tok tok((*(*it_p).right.begin()).data, (*(*it_p).right.begin()).type);
					AnalysisTableItem item(*(*it_p).right.begin(), *it_p);
					(*it_f).mFirst.push_back(item);
				}
			}
		}
	}
	//4. A->Xα
	//5. A->X1 X2 ...Xk α
	list<Production>::reverse_iterator it_rp;
	for (it_rp = g.mProduction.rbegin(); it_rp != g.mProduction.rend(); it_rp++)
	{
		Production prod = *it_rp;
		Token left = prod.left;			//产生式 左部
		list<Token> right = prod.right;	//产生式 右部
		list<Token>::iterator it_r = right.begin();	//产生式 右部 迭代
		list<First>::iterator it_f = getFirstAsNonterminator(left.data);	//产生式左部 First集
		bool loop = true;
		while (loop)
		{
			loop = false;
			if (g.isNonterminator((*it_r).data))//是否为非终结符
			{
				//将非终结符的First集添加到 左部的First集
				list<First>::reverse_iterator it_first = firstSet.rbegin();
				for (it_first = firstSet.rbegin(); it_first != firstSet.rend(); it_first++)	//遍历firstSet
				{
					if ((*it_first).mNonterminator.data == (*it_r).data)	//找到First集
					{
						list<AnalysisTableItem>::iterator terminator;
						for (terminator = (*it_first).mFirst.begin(); terminator != (*it_first).mFirst.end(); terminator++)
						{
							if ((*terminator).mTerminator.data != "$")	//不为$
							{
								if (!existATItemInATItemList((*it_f).mFirst, (*terminator).mTerminator.data))//不存在
								{
									AnalysisTableItem item((*terminator).mTerminator, prod);
									(*it_f).mFirst.push_back(item);
								}
							}
						}
					}
				}
				//if (!existATItemInATItemList((*it_f).other, (*it_r).data) && (*it_r).data != (*it_f).Nonterminator.data)
				//{
				//	//不存在且不为自己，非终结符在other中是否存在
				//	//添加other集中
				//	//Tok tok((*it_r).data, (*it_r).type);
				//	ATItem item((*it_r), *it_p);
				//	(*it_f).other.push_back(item);
				//}
				//判断是否继续循环
				list<First>::iterator it_f_t = getFirstAsNonterminator((*it_r).data);
				if (existATItemInATItemList((*it_f_t).mFirst, "$"))
				{
					if (++it_r != right.end())
						loop = true;
					else
					{
						if (!existATItemInATItemList((*it_f).mFirst, "$"))//不存在
						{
							Token nu("$", Delimiter_Dollar);
							AnalysisTableItem item(nu, prod);
							(*it_f).mFirst.push_back(item);
						}
					}
				}
			}
			else if (g.isTerminator((*it_r).data))//是否为终结符
			{
				if ((*it_r).data != "$")	//不为$
				{
					if (!existATItemInATItemList((*it_f).mFirst, (*it_r).data))//在First集中不存在
					{
						AnalysisTableItem item((*it_r), prod);
						(*it_f).mFirst.push_back(item);
					}
				}
			}
		}
	}
#if false //2016-04-13 根据设计的文法更新的算法
	//4. A->Xα
	bool loop = true;
	for (it_p = g.Production.begin(); it_p != g.Production.end(); it_p++)
	{
		Prod prod = *it_p;
		Tok left = prod.left;
		list<Tok> right = prod.right;
		list<Tok>::iterator it_r = right.begin();
		list<First>::iterator it_f = getFirstAsNonterminator(left.data);
		loop = true;
		while (loop)
		{
			loop = false;
			if (g.isNonterminator((*it_r).data))//是否为非终结符
			{
				if (!existATItemInATItemList((*it_f).other, (*it_r).data) && (*it_r).data != (*it_f).Nonterminator.data)
				{
					//不存在且不为自己，非终结符在other中是否存在
					//添加other集中
					//Tok tok((*it_r).data, (*it_r).type);
					ATItem item((*it_r), *it_p);
					(*it_f).other.push_back(item);
				}
				//判断是否继续循环
				list<First>::iterator it_f_t = getFirstAsNonterminator((*it_r).data);
				if (existATItemInATItemList((*it_f_t).first, "$"))
				{
					if (++it_r != right.end())
						loop = true;
				}
			}
		}
	}

	//5.消除First集中other的内容
	//方法：先找到other为空的First集，去替换other中的非终结符
	loop = true;
	unsigned int count = 0;
	while (loop)
	{
		list<First>::iterator it_f;
		//5.1.找到一个other.size()为0的First集
		for (it_f = firstSet.begin(); it_f != firstSet.end(); it_f++)
		{
			//5.2.判断other.size()是否为0
			if ((*it_f).other.size() == 0)
			{
				First first = *it_f;
				list<First>::iterator it_f1;
				for (it_f1 = firstSet.begin(); it_f1 != firstSet.end(); it_f1++)
				{
					list<ATItem>::iterator it_t;
					for (it_t = (*it_f1).other.begin(); it_t != (*it_f1).other.end();)
					{
						if ((*it_t).Terminator.data == first.Nonterminator.data)
						{
							//cout << "添加" << first.Nonterminator.data << endl;
							list<ATItem>::iterator terminator;
							for (terminator = (*it_f).first.begin(); terminator != (*it_f).first.end(); terminator++)
							{
								if (!existATItemInATItemList((*it_f1).first, (*terminator).Terminator.data))//不存在
								{
									ATItem item((*terminator).Terminator, (*it_t).Production);
									(*it_f1).first.push_back(item);
								}
							}
							//删除
							list<ATItem>::iterator tmp;
							tmp = it_t;
							it_t++;
							(*it_f1).other.erase(tmp);
						}
						else
						{
							it_t++;
						}
					}
				}
			}
		}
		//判断是否还要继续
		loop = false;
		//如果循环次数大于 Nonterminator.size()的平方次，立即结束
		if (++count > (g.Nonterminator.size()*g.Nonterminator.size()))
		{
			return false;
		}
		list<First>::iterator it_ff;
		for (it_ff = firstSet.begin(); it_ff != firstSet.end(); it_ff++)
		{

			if ((*it_ff).getOtherSize() > 0)
			{
				loop = true;
				break;
			}
		}
	}
	//cout << "count: " << count << endl;  
#endif
#if false
	//5.消除First集中other的内容
	loop = true;
	unsigned int count = 0;
	while (loop)
	{
		list<First>::iterator it_f;
		//1.找到other中需要置换的非终结符
		for (it_f = firstSet.begin(); it_f != firstSet.end(); it_f++)
		{
			list<Tok>::iterator it_t;
			for (it_t = (*it_f).other.begin(); it_t != (*it_f).other.end(); )
			{
				string s = (*it_t).data;
				list<First>::iterator f = getFirstAsNonterminator(s);//获得First集
				if (f != firstSet.end())
				{
					if ((*f).other.size() == 0)
					{
						//将f中的first内的除#以外的终结符全部添加到it_f
						/*list<Tok>::iterator tok;
						for (tok = (*f).first.begin(); tok != (*f).first.end(); tok++)
						{
						if ((*tok).data != "#")
						{
						if (!existTokInTokList((*it_f).first, (*tok).data))
						{
						Tok tok((*tok).data, (*tok).type);
						(*it_f).first.push_back(tok);
						}
						}
						}*/
						/*if ((*it_f).other.size() == 1)
						{
						cout << "hhhhhhh" << endl;
						(*it_f).other.clear();
						}*/
						/*else
						{*/
						list<Tok> l_tok = (*it_f).other;
						/*list<Tok>::iterator tmp;
						tmp = it_t;
						it_t++;*/
						l_tok.erase(it_t);
						/*}*/
						break;
					}
					else
						it_t++;
				}
				else
				{
					it_t++;
				}
			}
		}
		//判断是否还要继续
		loop = false;
		if (++count > (g.Nonterminator.size()*g.Nonterminator.size()))
		{
			loop = false;
			break;
		}
		for (it_f = firstSet.begin(); it_f != firstSet.end(); it++)
		{

			if ((*it_f).other.size() > 0)
			{
				loop = true;
				break;
			}
		}
}
	cout << "count: " << count << endl;
#endif
	return true;
}

bool LL_1_Analysis::initFollowSet(Grammar & g)
{
	//1.根据文法中的非终结符初始化Follow集
	list<Token>::iterator it_t1;
	for (it_t1 = g.mNonterminator.begin(); it_t1 != g.mNonterminator.end(); it_t1++)
	{
		Follow follow((*it_t1));
		followSet.push_back(follow);	//将新建项添加到Follow集中
	}
	//2.如果A是开始符号，#属于Follow(A)
	list<Follow>::iterator it_f2;
	for (it_f2 = followSet.begin(); it_f2 != followSet.end(); it_f2++)
	{
		if ((*it_f2).mNonterminator.data == g.mStarter.data)
		{
			Token tok("#", Delimiter_Pound_Sign);
			(*it_f2).mFollow.push_back(tok);
			break;
		}
	}
	//3.若有产生式  B->--Aa-- ,a属于Vt,把a加入到Follow(A)中
	list<Production>::iterator it_p3;
	for (it_p3 = g.mProduction.begin(); it_p3 != g.mProduction.end(); it_p3++)
	{
		Token tok_left = (*it_p3).left;			//产生式左部
		list<Token>::iterator it_right = (*it_p3).right.begin();	//产生式右部 迭代
		list<Token>::iterator it_pre = it_right;			//产生式右部 迭代
		if (it_right == (*it_p3).right.end())
		{
			continue;
		}
		for (it_right++; it_right != (*it_p3).right.end(); it_right++)
		{
			//满足条件 pre为非终结符 ，right为终结符
			if (g.isNonterminator((*it_pre).data) && g.isTerminator((*it_right).data))
			{
				list<Follow>::iterator it_follow3 = getFollowAsNonterminator((*it_pre).data);
				if (it_follow3 != followSet.end())
				{
					Token tok((*it_right).data, (*it_right).type);
					(*it_follow3).mFollow.push_back(tok);	//添加到指定非终极符的Follow集中
				}
				else
				{
					cout << "加载Follow集第2步出现错误" << endl;
				}
			}
			it_pre = it_right;
		}
	}
	//4.若有产生式 B->--AX--,X属于Vn,把First(X--)中非$元素加入Follow(A)中
	list<Production>::iterator it_p4;
	for (it_p4 = g.mProduction.begin(); it_p4 != g.mProduction.end(); it_p4++)
	{
		list<Token>::iterator it_right = (*it_p4).right.begin();
		list<Token>::iterator it_pre = it_right;
		if (it_right == (*it_p4).right.end())
		{
			continue;
		}
		for (it_right++; it_right != (*it_p4).right.end(); it_right++)
		{
			//满足条件 pre为非终结符 ，right也为非终结符
			if (g.isNonterminator((*it_pre).data) && g.isNonterminator((*it_right).data))
			{
				bool isLoop = true;	//是否循环
				list<Follow>::iterator it_follow4 = getFollowAsNonterminator((*it_pre).data);
				list<Token>::iterator tmp_right = it_right;
				while (isLoop)
				{
					isLoop = false;
					list<First>::iterator it_first4 = getFirstAsNonterminator((*tmp_right).data);
					list<AnalysisTableItem>::iterator it_tok4;
					for (it_tok4 = (*it_first4).mFirst.begin(); it_tok4 != (*it_first4).mFirst.end(); it_tok4++)
					{
						if ((*it_tok4).mTerminator.data == "$")//是否为$
						{
							isLoop = true;
						}
						else
						{
							if (!existTokInTokList((*it_follow4).mFollow, (*it_tok4).mTerminator.data))
							{
								Token tok((*it_tok4).mTerminator.data, (*it_tok4).mTerminator.type);
								(*it_follow4).mFollow.push_back(tok);
							}
						}
					}
					if (isLoop)
					{
						tmp_right++;
						if (tmp_right == (*it_p4).right.end())
						{
							isLoop = false;
						}
						else
						{
							isLoop = false;
							if (g.isTerminator((*tmp_right).data))	//为终结符
							{
								if (!existTokInTokList((*it_follow4).mFollow, (*tmp_right).data))
								{
									Token tok((*tmp_right).data, (*tmp_right).type);
									(*it_follow4).mFollow.push_back(tok);
								}
							}
							else if (g.isNonterminator((*tmp_right).data))	//为非终结符
							{
								isLoop = true;
							}
						}
					}
				}
			}
		}
	}//end for 4
	 //5.若 B->--A,或 B->--AX 且X推导出$，把Follow(B)加到Follow(A)中
	list<Production>::iterator it_p5;
	for (it_p5 = g.mProduction.begin(); it_p5 != g.mProduction.end(); it_p5++)
	{
		Token left = (*it_p5).left;
		list<Token>::reverse_iterator it_right;
		bool isNonterm = true;
		it_right = (*it_p5).right.rbegin();
		while (it_right != (*it_p5).right.rend() && isNonterm)
		{
			isNonterm = false;
			if (g.isNonterminator((*it_right).data))//right为非终结符
			{
				bool isLoop = true;
				list<Token>::reverse_iterator tmp = it_right;
				while (isLoop)
				{
					isLoop = false;
					list<Follow>::iterator follow = getFollowAsNonterminator((*tmp).data);
					if (!existTokInTokList((*follow).mOther, left.data) && left.data != (*follow).mNonterminator.data)
					{//不存在且不为自己，则添加到other中
						Token tok(left.data, left.type);
						(*follow).mOther.push_back(tok);
					}
					list<First>::iterator first = getFirstAsNonterminator((*tmp).data);
					if (existATItemInATItemList((*first).mFirst, (string&)"$"))// 能够推导出$
					{
						tmp++;
						if (tmp != (*it_p5).right.rend() && g.isNonterminator((*tmp).data))
						{//递增有效，并且为非终结符
							isLoop = true;
						}
					}
				}
				isNonterm = true;
			}
			it_right++;
		}
	}
	//6.消除follow中的other
	//循环遍历other，如果other指向的非终结符other为空，则置换
	bool loop = true;
	unsigned int count = 0;
	while (loop)
	{
		list<Follow>::iterator it_f6;
		for (it_f6 = followSet.begin(); it_f6 != followSet.end(); it_f6++)
		{
			list<Token>::iterator tok6;
			for (tok6 = (*it_f6).mOther.begin(); tok6 != (*it_f6).mOther.end();)
			{
				list<Follow>::iterator follow = this->getFollowAsNonterminator((*tok6).data);
				if (0 == (*follow).mOther.size())
				{
					list<Token>::iterator it_t;//循环添加
					for (it_t = (*follow).mFollow.begin(); it_t != (*follow).mFollow.end(); it_t++)
					{
						if (!existTokInTokList((*it_f6).mFollow, (*it_t).data))
						{
							Token tok((*it_t).data, (*it_t).type);
							(*it_f6).mFollow.push_back(tok);
						}
					}
					//输出other元素
					list<Token>::iterator tmp = tok6;
					tok6++;
					(*it_f6).mOther.erase(tmp);
				}
				else
				{
					tok6++;
				}
			}//end for tok6
		}// end for it_f6
		 // ******
		 //如果循环次数大于 Nonterminator.size()的平方次，立即结束
		if (++count > (g.mNonterminator.size()*g.mNonterminator.size()))
		{
			return false;
		}
		//判断是否继续循环消除
		loop = false;
		for (it_f6 = followSet.begin(); it_f6 != followSet.end(); it_f6++)
		{
			if ((*it_f6).mOther.size() > 0)
			{
				loop = true;
				break;
			}
		}
	}
	//cout << "follow count : " << count << endl;
	return true;
}

bool LL_1_Analysis::initAnalysisTable(Grammar& g)
{
	//1.根据非终结符初始化预测分析表
	list<Token>::iterator it_t1;
	for (it_t1 = g.mNonterminator.begin(); it_t1 != g.mNonterminator.end(); it_t1++)
	{
		AnalysisTable at(*it_t1);
		analysisTable.push_back(at);
	}
	//2.构造预测分析表
	list<First>::iterator it_first;
	//2.1遍历 First集
	for (it_first = firstSet.begin(); it_first != firstSet.end(); it_first++)
	{
		Token nonterm = (*it_first).mNonterminator;	//First集非终极符
		list<AnalysisTable>::iterator it_at = getAnalysisTableAsNonterminator(nonterm.data);
		if (it_at == analysisTable.end())
			return false;
		list<AnalysisTableItem>::iterator it_item;
		//2.2遍历 ATItem
		for (it_item = (*it_first).mFirst.begin(); it_item != (*it_first).mFirst.end(); it_item++)
		{
			//2.3 是终结符，除$外，则添加
			if (g.isTerminator((*it_item).mTerminator.data))
			{
				AnalysisTableItem item((*it_item).mTerminator, (*it_item).mProduction);
				(*it_at).mItemList.push_back(item);
			}
		}
		for (it_item = (*it_first).mFirst.begin(); it_item != (*it_first).mFirst.end(); it_item++)
		{
			//2.4 是$，遍历Follow集添加
			if ("$" == (*it_item).mTerminator.data)
			{
				list<Follow>::iterator it_follow = getFollowAsNonterminator(nonterm.data);
				/*Prod prod;
				prod.left = nonterm;
				Tok tok("$", Delimiter_Dollar);
				prod.right.push_back(tok);*/
				list<Token>::iterator it_f_t;
				for (it_f_t = (*it_follow).mFollow.begin(); it_f_t != (*it_follow).mFollow.end(); it_f_t++)
				{
					if (!existATItemInATItemList((*it_at).mItemList, (*it_f_t).data))
					{
						AnalysisTableItem item((*it_f_t), (*it_item).mProduction);
						(*it_at).mItemList.push_back(item);
					}
				}
			}
		}
	}
	return true;
}

bool LL_1_Analysis::runGrammarAnalysis(list<Token>& list_t)
{
	//1.判断是否可以进行语法分析
	if (!isReady)
	{
		cout << "LL_1预测分析缺少前提条件，不能进行语法分析!" << endl;
		return false;
	}
	//2.新建一个list，拷贝list原有的内容，并在list的末尾添加 "#"
	list<Token> list_left;
	for_each(list_t.begin(), list_t.end(), [&list_left](const Token& t) {
		Token tt(t.data, t.type);
		list_left.push_back(tt);
	});
	Token tok("#", Delimiter_Pound_Sign);
	list_left.push_back(tok);
	//打印Token串中的data
	//for_each(list_left.begin(), list_left.end(), [](const Token& t) { cout << t.data << " "; });
	//cout << endl;
	//3.新建一个分析栈，并初始化
	stack<Token> analysisStack;
	analysisStack.push(tok);
	tok = g.mStarter;
	analysisStack.push(tok);
	//list<Tok>::iterator it_t = list_left.begin();
	Token a = list_left.front();
	string analysisStackData;
	while (true)
	{
		if (!analysisStack.empty())	//stack不为空
		{
			analysisStackData = getTokStackData(analysisStack);
			Token X = analysisStack.top();
			analysisStack.pop();
			if (g.isTerminator(X.type))	//是终结符
			{
				if (X.type == a.type)//读入下一个符号到a中
				{
					LL_1_AnalysisItem item(analysisResult.size() + 1, analysisStackData, list_left, a.data.append("match"));
					analysisResult.push_back(item);
					//cout << a.data << "匹配" << endl;
					list_left.pop_front();
					a = list_left.front();
				}
				else
				{	//报错
					return false;
				}
			}
			else
			{
				if (X.type == Delimiter_Pound_Sign)	//是否 "#"
				{
					if (X.type == a.type)
					{	//分析结束
						LL_1_AnalysisItem item(analysisResult.size() + 1, analysisStackData, list_left, string().append("accept"));
						analysisResult.push_back(item);
						//cout << "接受" << endl;
						return true;
					}
					else
					{	//报错
						return false;
					}
				}
				else
				{
					list<AnalysisTable>::iterator it_at = getAnalysisTableAsNonterminator(X.data);
					if (existATItemInATItemList((*it_at).mItemList, a.type))
					{
						list<AnalysisTableItem>::iterator it_item = getATItemAsNonterminator(it_at, a.type);
						list<Token>::reverse_iterator it_tok;
						it_tok = (*it_item).mProduction.right.rbegin();
						if ((*it_tok).data != "$")	//若右部符号为$，则意味着什么也不压入栈
						{
							for (; it_tok != (*it_item).mProduction.right.rend(); it_tok++)
							{
								Token t = *it_tok;
								analysisStack.push(t);
							}
						}
						LL_1_AnalysisItem item(analysisResult.size() + 1, analysisStackData, list_left, string().append((*it_item).mProduction.getProd()));
						analysisResult.push_back(item);
						//(*it_item).mProduction.printProdLine();
					}
					else
					{	//报错
						return false;
					}
				}
			}
		}
		else
		{	//如果没有分析结束，分析栈就空了，则报错
			return false;
		}
	}
	return true;
}

bool LL_1_Analysis::writeAnalysisTableBinary(const string & at_name)
{
	FileOperation<AnalysisTable> fo;
	if (fo.openFile(at_name))	//打开文件成功
	{
		list<AnalysisTable>::iterator it = analysisTable.begin();
		for (; it != analysisTable.end(); it++)
		{
			fo.writeToFile(*it);
		}
		fo.closeFile();
		return true;
	}
	return false;
}

bool LL_1_Analysis::readAnalysisTableBinary(const string & at_name)
{
	analysisTable.clear();
	FileOperation<AnalysisTable> fo;
	if (fo.openFile(at_name))
	{
		while (!fo.is_eof())
		{
			AnalysisTable *localAT = new AnalysisTable;
			fo.readFromFile(*localAT);
			analysisTable.push_back(*localAT);
		}
		fo.closeFile();
		return true;
	}
	return false;
}

bool LL_1_Analysis::existInListTok(list<Token>& tok, string & s) const
{
	list<Token>::iterator it;
	for (it = tok.begin(); it != tok.end(); it++)
	{
		if ((*it).data == s)
			return true;
	}
	return false;
}

bool LL_1_Analysis::existInFirstSet(string & d)
{
	list<First>::iterator it;
	for (it = firstSet.begin(); it != firstSet.end(); it++)
	{
		if ((*it).mNonterminator.data == d)
			return true;
	}
	return false;
}

bool LL_1_Analysis::existInFollowSet(string & d)
{
	list<Follow>::iterator it;
	for (it = followSet.begin(); it != followSet.end(); it++)
	{
		if ((*it).mNonterminator.data == d)
			return true;
	}
	return false;
}

bool LL_1_Analysis::existTokInTokList(list<Token>& tok, string & s)
{
	list<Token>::iterator it;
	for (it = tok.begin(); it != tok.end(); it++)
	{
		if ((*it).data == s)
			return true;
	}
	return false;
}

bool LL_1_Analysis::existTokInTokVector(vector<Token>& tok, string & s)
{
	vector<Token>::iterator it;
	for (it = tok.begin(); it != tok.end(); it++)
	{
		if ((*it).data == s)
			return true;
	}
	return false;
}

bool LL_1_Analysis::existATItemInATItemList(list<AnalysisTableItem>& item, string & s)
{
	list<AnalysisTableItem>::iterator it;
	for (it = item.begin(); it != item.end(); it++)
	{
		if ((*it).mTerminator.data == s)
			return true;
	}
	return false;
}

bool LL_1_Analysis::existATItemInATItemList(list<AnalysisTableItem>& item, const char* s)
{
	list<AnalysisTableItem>::iterator it;
	for (it = item.begin(); it != item.end(); it++)
	{
		if ((*it).mTerminator.data == s)
			return true;
	}
	return false;
}

bool LL_1_Analysis::existATItemInATItemList(list<AnalysisTableItem>& item, int & t)
{
	list<AnalysisTableItem>::iterator it;
	for (it = item.begin(); it != item.end(); it++)
	{
		if ((*it).mTerminator.type == t)
			return true;
	}
	return false;
}

void LL_1_Analysis::printFirstSet()
{
	list<First>::iterator it;
	for (it = firstSet.begin(); it != firstSet.end(); it++)
	{
		cout << "N------>: " << (*it).mNonterminator.data << endl;
		//first
		list<AnalysisTableItem>::iterator it_i;
		cout << "First-->: ";
		for (it_i = (*it).mFirst.begin(); it_i != (*it).mFirst.end(); it_i++)
		{
			cout << (*it_i).mTerminator.data << " ";
		}
		cout << endl;
		//other
		cout << "Other-->: ";
		for (it_i = (*it).mOther.begin(); it_i != (*it).mOther.end(); it_i++)
		{
			cout << (*it_i).mTerminator.data << " ";
		}
		cout << endl;
	}
}


void LL_1_Analysis::printFollowSet()
{
	list<Follow>::iterator it;
	for (it = followSet.begin(); it != followSet.end(); it++)
	{
		cout << "N------>: " << (*it).mNonterminator.data << endl;
		list<Token>::iterator it_t;
		//first
		cout << "Follow-->: ";
		for (it_t = (*it).mFollow.begin(); it_t != (*it).mFollow.end(); it_t++)
		{
			cout << (*it_t).data << " ";
		}
		cout << endl;
		//other
		cout << "Other-->: ";
		for (it_t = (*it).mOther.begin(); it_t != (*it).mOther.end(); it_t++)
		{
			cout << (*it_t).data << " ";
		}
		cout << endl;
	}
}

void LL_1_Analysis::printFirstSetFormat_1()
{
	list<First>::iterator it;
	for (it = firstSet.begin(); it != firstSet.end(); it++)
	{
		cout << "First( " << (*it).mNonterminator.data << " ) = { ";
		//first
		list<AnalysisTableItem>::iterator it_t;
		bool isDouhao = false;
		for (it_t = (*it).mFirst.begin(); it_t != (*it).mFirst.end(); it_t++)
		{
			if (isDouhao)
			{
				cout << ", ";
			}
			cout << (*it_t).mTerminator.data;
			isDouhao = true;
		}
		cout << " }" << endl;
	}
}

void LL_1_Analysis::printFollowSetFormat_1()
{
	list<Follow>::iterator it;
	for (it = followSet.begin(); it != followSet.end(); it++)
	{
		cout << "Follow( " << (*it).mNonterminator.data << " ) = { ";
		//first
		list<Token>::iterator it_t;
		bool isDouhao = false;
		for (it_t = (*it).mFollow.begin(); it_t != (*it).mFollow.end(); it_t++)
		{
			if (isDouhao)
			{
				cout << ", ";
			}
			cout << (*it_t).data;
			isDouhao = true;
		}
		cout << " }" << endl;
	}
}

void LL_1_Analysis::printAnalysisTable()
{
	list<AnalysisTable>::iterator it;
	for (it = analysisTable.begin(); it != analysisTable.end(); it++)
	{
		cout << "--" << (*it).mNonterminator.data << "--" << endl;
		list<AnalysisTableItem>::iterator item;
		for (item = (*it).mItemList.begin(); item != (*it).mItemList.end(); item++)
		{
			cout << "        " << (*item).mTerminator.data << " : ";
			(*item).mProduction.printProdLine();
		}
	}
}

void LL_1_Analysis::printAnalysisResult()
{
	list<LL_1_AnalysisItem>::iterator it;
	for (it = analysisResult.begin(); it != analysisResult.end(); it++)
	{
		/*cout << (*it).analysisStack << "    ";
		cout << (*it).leftString << "    ";
		cout << (*it).deduceProd << endl;*/
		printf("%-5d  %-8s%12s        %-16s\n", (*it).id, (*it).analysisStack.data(), (*it).leftString.data(), (*it).deduceProd.data());
	}
}

void LL_1_Analysis::saveAnalysisResultToFile(ofstream& fout)
{
	unsigned int id_len = 0;
	unsigned int analysisStack_len = 0;
	unsigned int leftString_len = 0;
	unsigned int deduceProd_len = 0;
	list<LL_1_AnalysisItem>::iterator it;
	//计算每个属性的最大输出长度
	for (it = analysisResult.begin(); it != analysisResult.end(); it++)
	{
		if (id_len < getIntLength((*it).id))
		{
			id_len = getIntLength((*it).id);
		}
		if (analysisStack_len < (*it).analysisStack.size())
		{
			analysisStack_len = (*it).analysisStack.size();
		}
		if (leftString_len < (*it).leftString.size())
		{
			leftString_len = (*it).leftString.size();
		}
		if (deduceProd_len < (*it).deduceProd.size())
		{
			deduceProd_len = (*it).deduceProd.size();
		}
	}
	for (it = analysisResult.begin(); it != analysisResult.end(); it++)
	{
		unsigned int spaceLen = 0;
		//id
		fout << (*it).id;
		spaceLen = id_len - getIntLength((*it).id) + 4;
		while (spaceLen)
		{
			fout << " ";
			spaceLen--;
		}
		//analysisStack
		fout << (*it).analysisStack.data();
		spaceLen = analysisStack_len - (*it).analysisStack.size() + 4;
		while (spaceLen)
		{
			fout << " ";
			spaceLen--;
		}
		//leftString
		fout << (*it).leftString.data();
		spaceLen = leftString_len - (*it).leftString.size() + 4;
		while (spaceLen)
		{
			fout << " ";
			spaceLen--;
		}
		//deducePro
		fout << (*it).deduceProd.data();
		spaceLen = deduceProd_len - (*it).deduceProd.size() + 4;
		while (spaceLen)
		{
			fout << " ";
			spaceLen--;
		}
		fout << endl;
	}
}

list<First>::iterator LL_1_Analysis::getFirstAsNonterminator(string & s)
{
	list<First>::iterator it;
	for (it = firstSet.begin(); it != firstSet.end(); it++)
	{
		if ((*it).mNonterminator.data == s)
			return it;
	}
	return firstSet.end();
}

list<Follow>::iterator LL_1_Analysis::getFollowAsNonterminator(string & s)
{
	list<Follow>::iterator it;
	for (it = followSet.begin(); it != followSet.end(); it++)
	{
		if (s == (*it).mNonterminator.data)
			return it;
	}
	return followSet.end();
}

list<AnalysisTable>::iterator LL_1_Analysis::getAnalysisTableAsNonterminator(string & s)
{
	list<AnalysisTable>::iterator it;
	for (it = analysisTable.begin(); it != analysisTable.end(); it++)
	{
		if ((*it).mNonterminator.data == s)
			return it;
	}
	return analysisTable.end();
}

list<AnalysisTableItem>::iterator LL_1_Analysis::getATItemAsNonterminator(list<AnalysisTable>::iterator& it_at, string & s)
{
	list<AnalysisTableItem>::iterator it;
	for (it = (*it_at).mItemList.begin(); it != (*it_at).mItemList.end(); it++)
	{
		if ((*it).mTerminator.data == s)
			return it;
	}
	return (*it_at).mItemList.end();
}

list<AnalysisTableItem>::iterator LL_1_Analysis::getATItemAsNonterminator(list<AnalysisTable>::iterator & it_at, int & t)
{
	list<AnalysisTableItem>::iterator it;
	for (it = (*it_at).mItemList.begin(); it != (*it_at).mItemList.end(); it++)
	{
		if ((*it).mTerminator.type == t)
			return it;
	}
	return (*it_at).mItemList.end();
}

string LL_1_Analysis::getTokStackData(stack<Token>& stack_t)
{
	string result;
	result.clear();
	stack<Token> tmp_stack = stack_t;
	list<Token> tmp_list;
	while (tmp_stack.size())
	{
		Token tok = tmp_stack.top();
		tmp_list.push_front(tok);
		tmp_stack.pop();
	}
	for (list<Token>::iterator it = tmp_list.begin(); it != tmp_list.end(); it++)
	{
		result += (*it).data;
	}
	return result;
}

unsigned int LL_1_Analysis::getIntLength(int num)
{
	unsigned int len = 0;
	int number = num;
	while (number)
	{
		len++;
		number /= 10;
	}
	return len;
}
