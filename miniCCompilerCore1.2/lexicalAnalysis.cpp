#include "lexicalAnalysis.h"
LexicalAnalysis::LexicalAnalysis()
{
	analysisGrammar = false;
}

LexicalAnalysis::~LexicalAnalysis()
{
}

int LexicalAnalysis::runLexicalAnalysis(CodeList& codeList)
{
	mCurrentLine = 0;//初始化行号
	int lexicalErrorCount = 0;	//词法错误个数
	//codeList.printCodeList();
	bool isBlockAnnotation = false;	//是否为块注释
	list<Code>::iterator it_code;
	for (it_code = codeList.codeList.begin(); it_code != codeList.codeList.end();it_code++ )
	{
		mCurrentLine++;
		lexical_core(*it_code , isBlockAnnotation ,true);
	}
	//保存词法分析动画信息
	saveLexicalAnalysisAnimationListToFile("analysis\\lexicalAnalysisAnimation.txt");	
	saveTokenListToFile("analysis\\token.txt");	//保存Token串
	//判断TokenList内容是否存在错误
	list<Token>::iterator it_TokenList = mTokenList.begin();
	for (; it_TokenList != mTokenList.end(); it_TokenList++)
	{
		if ( (*it_TokenList).isLexical == false)
		{
			lexicalErrorCount++;	//TokenList存在错误
		}
	}
	return lexicalErrorCount;	//返回词法分析错误个数
}

void LexicalAnalysis::printTokenList()
{
	list<Token>::iterator it_token = mTokenList.begin();
	for (; it_token != mTokenList.end(); it_token++) {
		(*it_token).printToken();
	}
}

void LexicalAnalysis::printLexicalAnalysisAnimationList()
{
	list<LexicalAnalysisAnimation>::iterator it_info = mLexicalAnalysisAnimation.begin();
	for (; it_info != mLexicalAnalysisAnimation.end(); it_info++)
	{
		(*it_info).printLexicalAnalysisAnimation();
	}
}

void LexicalAnalysis::lexical_core(Code code ,bool & isBlockAnnotation , bool isAnalysisAnimation)
{
	int flag = 0;//1 正在识别关键词和常量
				 //2 正在识别数字常量
				 //-3 正在识别字符常量
				 //-4 正在识别字符串常量
	int numberChange = 0;//处理数字常量时候使用
	bool isLexical = true; //单词识别是否存在错误
	bool isBlockAnnotationTemp = isBlockAnnotation;
	char tp[128];//处理缓冲区
	int tpi = 0;
	tp[0] = '\0';//将处理缓冲区置空
	char* line = (char*)malloc(sizeof(char)* (strlen(code.line.c_str()) + 1));
	strcpy(line, code.line.c_str());
	//line[strlen(pCode->line)] = '\0';//复制字符串到缓冲区
	int lineNo = code.no;
	int lastI = 0;
	for (unsigned int i = 0; i < (strlen(line) + 1); i++)
	{
		//0.是否为块注释处理状态 寻找"*/"结束
		if (isBlockAnnotationTemp)
		{
			while (i++ < (strlen(line) + 1))
			{
				if (line[i] == '\0')
					break;
				else if ((i - 1) >= 0 && line[i - 1] == '*' && line[i] == '/')
				{
					isBlockAnnotationTemp = false;
					break;
				}
			}
		}
		//1。空界符 空格、Tab、回车
		else if (line[i] == ' ' || line[i] == '\t' || line[i] == '\0')
		{
			//判断处理缓冲区是否为空
			if (strcmp(tp, "")) //缓冲区不为空
			{
				int res = getLexicalType(numberChange, flag, tp, isLexical);
				//rToken = newToken(0, tp, res, isLexical);
				//addTokenToLinks(pToken, rToken);
				string str_tmp(tp);
				Token token(lineNo, str_tmp.data(), res, isLexical);
				mTokenList.push_back(token);
				if (isAnalysisAnimation)	//加载词法分析数据
					loadLexicalAnalysisAnimationInfo(lineNo, i  - strlen(tp), i , res, isLexical); //特殊处理
				tpi = 0; tp[0] = '\0';	//重置变量
				flag = 0;
				numberChange = 0;
				isLexical = true;
			}
		}
		//2。实界符 ( ) ; [ ] { } . , ~ 共10个字符 前后分开 自己也保存在Token中
		// # 是异常字符 $ 在文法中分析时会用到
		// || line[i] == '#' || line[i] == '$'
		else if (line[i] == '(' || line[i] == ')' || line[i] == ';' ||
			line[i] == '[' || line[i] == ']' || line[i] == '{' ||
			line[i] == '}' || line[i] == '.' || line[i] == ',' ||
			line[i] == '~')
		{
			if (flag == 2 && (numberChange == 1 || numberChange == 10) && line[i] == '.')	//将'.'添加到缓冲区中，状态发生变化
			{//这是识别数字常量中的一部分
				tp[tpi++] = line[i];
				numberChange = 2;
			}
			else
			{
				//判断处理缓冲区是否为空
				if (strcmp(tp, "")) //缓冲区不为空 不为0
				{
					int res = getLexicalType(numberChange, flag, tp, isLexical);
					//rToken = newToken(0, tp, res, isLexical);
					//addTokenToLinks(pToken, rToken);
					string str_tmp(tp);
					Token token(lineNo, str_tmp.data(), res, isLexical);
					mTokenList.push_back(token);
					if (isAnalysisAnimation)	//加载词法分析数据
						loadLexicalAnalysisAnimationInfo(lineNo, i - strlen(tp), i, res, isLexical);//特殊处理
					tpi = 0;  tp[0] = '\0';	//重置变量
					flag = 0;
					numberChange = 0;
					isLexical = true;
				}
				tp[0] = line[i]; tp[1] = '\0';
				//rToken = newToken(0, tp, getDelimiterType(line[i]), isLexical);
				//addTokenToLinks(pToken, rToken);
				string str_tmp(tp);
				Token token(lineNo, str_tmp.data(), getDelimiterType(line[i]), isLexical);
				mTokenList.push_back(token);
				if (isAnalysisAnimation)	//加载词法分析数据
					loadLexicalAnalysisAnimationInfo(lineNo, i + 1 - strlen(tp), i + 1, getDelimiterType(line[i]), isLexical);
				tpi = 0;  tp[0] = '\0';	//重置变量
				flag = 0;
				numberChange = 0;
				isLexical = true;
			}
		}
		// 文法分析时对'$'符号的识别
		else if (line[i] == '$')
		{
			//判断处理缓冲区是否为空
			if (strcmp(tp, "")) //缓冲区不为空 不为0
			{
				int res = getLexicalType(numberChange, flag, tp, isLexical);
				string str_tmp(tp);
				Token token(lineNo, str_tmp.data(), res, isLexical);
				mTokenList.push_back(token);
				if (isAnalysisAnimation)	//加载词法分析数据
					loadLexicalAnalysisAnimationInfo(lineNo, i - strlen(tp), i, res, isLexical);//特殊处理
				tpi = 0;  tp[0] = '\0';	//重置变量
				flag = 0;
				numberChange = 0;
				isLexical = true;
			}
			tp[0] = line[i]; tp[1] = '\0';
			string str_tmp(tp);
			if (!analysisGrammar)
			{
				isLexical = false;
				cout << "E> Lexical : 在(" << mCurrentLine << ", " << (i + 1) << ")中，\"" << str_tmp << "\"为非法字符" << endl;
			}
			Token token(lineNo, str_tmp.data(), getDelimiterType(line[i]), isLexical);
			mTokenList.push_back(token);
			if (isAnalysisAnimation)	//加载词法分析数据
				loadLexicalAnalysisAnimationInfo(lineNo, i + 1 - strlen(tp), i + 1, getDelimiterType(line[i]), isLexical);
			tpi = 0;  tp[0] = '\0';	//重置变量
			flag = 0;
			numberChange = 0;
			isLexical = true;
		}
		//3.识别出关键词和常量 只包含字母、数字、_，数字不开头
		//[A,Z]、[a,z]、_
		else if ((line[i] >= 'A'&&line[i] <= 'Z') || (line[i] >= 'a'&&line[i] <= 'z') || line[i] == '_')
		{
			if (flag == 0)
			{
				flag = 1;
				tpi = 0; tp[tpi] = '\0';
				tp[tpi++] = line[i];//将处理字符添加到处理缓冲区
				tp[tpi] = '\0';
			}
			else if (flag == 1)
			{
				tp[tpi++] = line[i];//将处理字符添加到处理缓冲区
				tp[tpi] = '\0';
			}
			else if (flag == 2)
			{
				tp[tpi++] = line[i];//将处理字符添加到处理缓冲区
				tp[tpi] = '\0';
				if (numberChange == 3 && (line[i] == 'E' || line[i] == 'e'))
				{
					numberChange = 4;
				}
				else if (numberChange == 10 && (line[i] == 'X' || line[i] == 'x'))
				{
					numberChange = 13;
				}
				else if (numberChange == 13 && ((line[i] >= 'A' && line[i] <= 'F') || (line[i] >= 'a' && line[i] <= 'f')))
				{
					numberChange = 13;
				}
				else
				{
					isLexical = false;//不符合条件，需要报错
				}
			}
			else
			{
				tp[tpi++] = line[i];//将处理字符添加到处理缓冲区
				tp[tpi] = '\0';
				isLexical = false;
			}
		}
		//4.识别运算符 叹号! 取余% 等号= 取余^ 星号*
		else if (line[i] == '!' || line[i] == '%' || line[i] == '=' || line[i] == '^' ||
			line[i] == '*')
		{
			//判断处理缓冲区是否为空
			if (strcmp(tp, ""))//处理缓冲区不为空 不为0
			{
				int res = getLexicalType(numberChange, flag, tp, isLexical);
				//添加到Token串中
				//rToken = newToken(0, tp, res, isLexical);
				//addTokenToLinks(pToken, rToken);
				string str_tmp(tp);
				Token token(lineNo, str_tmp.data(), res, isLexical);
				mTokenList.push_back(token);
				if (isAnalysisAnimation)	//加载词法分析数据
					loadLexicalAnalysisAnimationInfo(lineNo, i - strlen(tp), i, res, isLexical);	//特殊处理
				tp[0] = '\0'; tpi = 0;	//重置变量
				flag = 0;
				numberChange = 0;
				isLexical = 0;
			}
			tpi = 0; tp[tpi] = '\0';
			tp[tpi++] = line[i]; tp[tpi] = '\0';
			if (line[i + 1] == '=')
			{
				i++;
				tp[tpi++] = line[i]; tp[tpi] = '\0';
			}
			//添加到Token串中
			int res = getOperatorType(tp);
			//rToken = newToken(0, tp, res, isLexical);
			//addTokenToLinks(pToken, rToken);
			string str_tmp(tp);
			Token token(lineNo, str_tmp.data(), res, isLexical);
			mTokenList.push_back(token);
			if (isAnalysisAnimation)	//加载词法分析数据
				loadLexicalAnalysisAnimationInfo(lineNo, i + 1 - strlen(tp), i + 1, res, isLexical);
			tp[0] = '\0'; tpi = 0;	//重置变量
			flag = 0;
			numberChange = 0;
			isLexical = true;
		}
		//5.识别运算符 与& 或| 加+ 减- 大于> 小于<
		else if (line[i] == '&' || line[i] == '|' || line[i] == '+' || line[i] == '-' ||
			line[i] == '>' || line[i] == '<')
		{
			if (flag == 2 && numberChange == 4 && (line[i] == '+' || line[i] == '-'))
			{
				tp[tpi++] = line[i]; tp[tpi] = '\0';//添加到缓冲区
				numberChange = 5;
			}
			else
			{
				//判断处理缓冲区是否为空
				if (strcmp(tp, ""))//处理缓冲区不为空 不为0
				{
					int res = getLexicalType(numberChange, flag, tp, isLexical);
					//添加到Token串中
					//rToken = newToken(0, tp, res, isLexical);
					//addTokenToLinks(pToken, rToken);
					string str_tmp(tp);
					Token token(lineNo, str_tmp.data(), res, isLexical);
					mTokenList.push_back(token);
					if (isAnalysisAnimation)	//加载词法分析数据
						loadLexicalAnalysisAnimationInfo(lineNo, i - strlen(tp), i, res, isLexical);	//特殊处理
					tp[0] = '\0'; tpi = 0;	//重置变量
					flag = 0;
					numberChange = 0;
					isLexical = true;
				}
				tpi = 0; tp[tpi] = '\0';
				tp[tpi++] = line[i]; tp[tpi] = '\0';
				if (line[i + 1] == '=' || line[i + 1] == line[i])
				{
					i++;
					tp[tpi++] = line[i]; tp[tpi] = '\0';
				}
				else if (line[i] == '-' && line[i + 1] == '>')//在进行文法分析时会用到
				{
					i++;
					tp[tpi++] = line[i]; tp[tpi] = '\0';
				}
				//添加到Token串中
				int res = getOperatorType(tp);
				//rToken = newToken(0, tp, res, isLexical);
				//addTokenToLinks(pToken, rToken);
				string str_tmp(tp);
				Token token(lineNo, str_tmp.data(), res, isLexical);
				mTokenList.push_back(token);
				if (isAnalysisAnimation)	//加载词法分析数据
					loadLexicalAnalysisAnimationInfo(lineNo, i + 1 - strlen(tp), i + 1, res, isLexical);
				tp[0] = '\0'; tpi = 0;	//重置变量
				flag = 0;
				numberChange = 0;
				isLexical = true;
			}
		}
		//7。识别运算符 斜杠/
		else if (line[i] == '/')
		{
			//判断处理缓冲区是否为空
			if (strcmp(tp, ""))//处理缓冲区不为空 不为0
			{
				int res = getLexicalType(numberChange, flag, tp, isLexical);
				//添加到Token串中
				//rToken = newToken(0, tp, res, isLexical);
				//addTokenToLinks(pToken, rToken);
				string str_tmp(tp);
				Token token(lineNo, str_tmp.data(), res, isLexical);
				mTokenList.push_back(token);
				if (isAnalysisAnimation)	//加载词法分析数据
					loadLexicalAnalysisAnimationInfo(lineNo, i - strlen(tp), i, res, isLexical);	//特殊处理
				tp[0] = '\0'; tpi = 0;	//重置变量
				flag = 0;
				numberChange = 0;
				isLexical = true;
			}
			//判断下一个字符是否为 '*'
			if (line[i + 1] == '*')
			{//接下来的操作为寻找 "*/" 来终结块注释
				cout << "BlockAnnetation" << endl;
				i++;
				isBlockAnnotationTemp = true;
			}
			//判断下一个字符是否为 '/'
			else if (line[i + 1] == '/')
			{//行注释
				while (i++ < (strlen(line) + 1))
				{
					if (line[i] == '\0')
					{
						cout << "行注释" << endl;
						break;
					}
				}
			}
			else
			{
				// 1./ 2./=
				tpi = 0; tp[tpi] = '\0';	//? 这个地方有问题啊
				tp[tpi++] = line[i]; tp[tpi] = '\0';
				if (line[i + 1] == '=')
				{
					i++;
					tp[tpi++] = line[i]; tp[tpi] = '\0';
				}
				//添加到Token串中
				int res = getOperatorType(tp);
				//rToken = newToken(0, tp, res, isLexical);
				//addTokenToLinks(pToken, rToken);
				string str_tmp(tp);
				Token token(lineNo, str_tmp.data(), res, isLexical);
				mTokenList.push_back(token);
				if (isAnalysisAnimation)	//加载词法分析数据
					loadLexicalAnalysisAnimationInfo(lineNo, i + 1 - strlen(tp), i + 1, res, isLexical);
				tp[0] = '\0'; tpi = 0;	//重置变量
				flag = 0;
				numberChange = 0;
				isLexical = true;
			}
		}
		//8.识别运算符 冒号:
		else if (line[i] == ':')
		{
			//判断处理缓冲区是否为空
			if (strcmp(tp, ""))//处理缓冲区不为空 不为0
			{
				int res = getLexicalType(numberChange, flag, tp, isLexical);
				//添加到Token串中
				//rToken = newToken(0, tp, res, isLexical);
				//addTokenToLinks(pToken, rToken);
				string str_tmp(tp);
				Token token(lineNo, str_tmp.data(), res, isLexical);
				mTokenList.push_back(token);
				if (isAnalysisAnimation)	//加载词法分析数据
					loadLexicalAnalysisAnimationInfo(lineNo, i - strlen(tp), i , res, isLexical);	//特殊处理
				tp[0] = '\0'; tpi = 0;	//重置变量
				flag = 0;
				numberChange = 0;
				isLexical = true;
			}
			tpi = 0; tp[tpi] = '\0';
			tp[tpi++] = line[i]; tp[tpi] = '\0';
			if (line[i + 1] == line[i])//line[i + 1] == '=' || 不需要在判断后面是否为=号
			{
				i++;
				tp[tpi++] = line[i]; tp[tpi] = '\0';
			}
			//添加到Token串中
			int res = getOperatorType(tp);
			//rToken = newToken(0, tp, res, isLexical);
			//addTokenToLinks(pToken, rToken);
			string str_tmp(tp);
			Token token(lineNo, str_tmp.data(), res, isLexical);
			mTokenList.push_back(token);
			if (isAnalysisAnimation)	//加载词法分析数据
				loadLexicalAnalysisAnimationInfo(lineNo, i + 1 - strlen(tp), i + 1, res, isLexical);
			tp[0] = '\0'; tpi = 0;	//重置变量
			flag = 0;
			numberChange = 0;
			isLexical = true;
		}
		//9.识别字符常量 'AAAAAAAAA'
		else if (line[i] == '\'')
		{
			//判断处理缓冲区是否为空
			if (strcmp(tp, ""))//处理缓冲区不为空 不为0
			{
				int res = getLexicalType(numberChange, flag, tp, isLexical);
				//添加到Token串中
				//rToken = newToken(0, tp, res, isLexical);
				//addTokenToLinks(pToken, rToken);
				string str_tmp(tp);
				Token token(lineNo, str_tmp.data(), res, isLexical);
				mTokenList.push_back(token);
				if (isAnalysisAnimation)	//加载词法分析数据
					loadLexicalAnalysisAnimationInfo(lineNo, i - strlen(tp), i , res, isLexical);	//特殊处理
				tp[0] = '\0'; tpi = 0;	//重置变量
				flag = 0;
				numberChange = 0;
				isLexical = true;
			}
			tpi = 0; tp[tpi] = '\0';
			tp[tpi++] = line[i]; tp[tpi] = '\0';
			bool complete = false;
			while (i++ < strlen(line)) //i++ < (strlen(line) + ) 不再这里面分析'\0'
			{
				tp[tpi++] = line[i]; tp[tpi] = '\0';
				if (line[i - 1] != '\\' && line[i] == '\'')
				{
					complete = true;
					break;
				}
			}
			//添加到Token串中 根据complete处理错误
			if (complete)//字符识别不存在错误
			{
				if (strlen(tp) > 6)//''中的字符个数不得超过4个
					complete = false;
			}
			//rToken = newToken(0, tp, complete ? Character : 0, isLexical);
			//addTokenToLinks(pToken, rToken);
			string str_tmp(tp);
			Token token(lineNo, str_tmp.data(), complete ? Character : Error, complete);
			mTokenList.push_back(token);
			if (isAnalysisAnimation)	//加载词法分析数据
				loadLexicalAnalysisAnimationInfo(lineNo, i + 1 - strlen(tp), i + 1, Character, isLexical);
			tp[0] = '\0'; tpi = 0;	//重置变量
			flag = 0;
			numberChange = 0;
			isLexical = true;
		}
		//10.识别字符串常量 "AAAAAAAAAAA"
		else if (line[i] == '\"')
		{
			//判断处理缓冲区是否为空
			if (strcmp(tp, ""))//处理缓冲区不为空 不为0
			{
				int res = getLexicalType(numberChange, flag, tp, isLexical);
				//添加到Token串中
				//rToken = newToken(0, tp, res, isLexical);
				//addTokenToLinks(pToken, rToken);
				string str_tmp(tp);
				Token token(lineNo, str_tmp.data(), res, isLexical);
				mTokenList.push_back(token);
				if (isAnalysisAnimation)	//加载词法分析数据
					loadLexicalAnalysisAnimationInfo(lineNo, i - strlen(tp), i, res, isLexical);	//特殊处理
				tp[0] = '\0'; tpi = 0;	//重置变量
				flag = 0;
				numberChange = 0;
				isLexical = true;
			}
			tpi = 0; tp[tpi] = '\0';
			tp[tpi++] = line[i]; tp[tpi] = '\0';
			bool complete = false;
			while (i++ < strlen(line))//i++ < (strlen(line) + ) 不再这里面分析'\0'
			{
				tp[tpi++] = line[i]; tp[tpi] = '\0';
				if (line[i - 1] != '\\' && line[i] == '\"')
				{
					complete = true;
					break;
				}
			}
			//添加到Token串中 根据complete处理错误
			//rToken = newToken(0, tp, complete ? String : 0, isLexical);
			//addTokenToLinks(pToken, rToken);
			string str_tmp(tp);
			Token token(lineNo, str_tmp.data(), complete ? String : Error, complete);
			mTokenList.push_back(token);
			if (isAnalysisAnimation)	//加载词法分析数据
				loadLexicalAnalysisAnimationInfo(lineNo, i + 1 - strlen(tp), i + 1, String, isLexical);
			tp[0] = '\0'; tpi = 0;	//重置变量
			flag = 0;
			numberChange = 0;
			isLexical = true;
		}
		//11.识别数字常量 包括(指数、小数、十进制数、八进制数、十六进制数)
		else if (line[i] >= '0' && line[i] <= '9')
		{
			if (flag == 0)//处理缓冲区应该为空，首先判断是否为空，不为空做相应的处理
			{
				//判断处理缓冲区是否为空 [谨慎操作]
				if (strcmp(tp, ""))//处理缓冲区不为空 不为0
				{
					int res = getLexicalType(numberChange, flag, tp, isLexical);
					//添加到Token串中
					//rToken = newToken(0, tp, res, isLexical);
					//addTokenToLinks(pToken, rToken);
					string str_tmp(tp);
					Token token(lineNo, str_tmp.data(), res, isLexical);
					mTokenList.push_back(token);
					if (isAnalysisAnimation)	//加载词法分析数据
						loadLexicalAnalysisAnimationInfo(lineNo, i - strlen(tp), i, res, isLexical);	//特殊处理
					tp[0] = '\0'; tpi = 0;	//重置变量
					flag = 0;
					numberChange = 0;
					isLexical = true;
				}
				flag = 2; //标明正在识别数字常量
				tpi = 0; tp[tpi] = '\0';
				tp[tpi++] = line[i]; tp[tpi] = '\0';
				//判断是否为 0
				if (line[i] == '0')
				{
					numberChange = 10;
				}
				else
				{
					numberChange = 1;
				}
			}
			else if (flag == 1)//正在识别关键词或标识符 直接添加到缓冲区后面
			{
				tp[tpi++] = line[i]; tp[tpi] = '\0';
			}
			else if (flag == 2)//正在识别数字常量 flag==2时numberChange>0
			{
				if (numberChange == 1 || numberChange == 3 || numberChange == 6 || numberChange == 13)//直接添加到缓冲区
				{
					tp[tpi++] = line[i]; tp[tpi] = '\0';
				}
				else if (numberChange == 2)//添加到缓冲区，状态发生变化
				{
					tp[tpi++] = line[i]; tp[tpi] = '\0';
					numberChange = 3;
				}
				else if (numberChange == 4 || numberChange == 5)//添加到缓冲区，状态发生变化
				{
					tp[tpi++] = line[i]; tp[tpi] = '\0';
					numberChange = 6;
				}
				else if (numberChange == 10 || numberChange == 11)//添加到缓冲区，状态有可能需要发生变化
				{
					tp[tpi++] = line[i]; tp[tpi] = '\0';
					if (!(line[i] >= '0' && line[i] < '8'))//不符合[0,8)
					{//需要提示错误 
						isLexical = false;
					}
					numberChange = 11;
				}
			}
			else//预留的错误处理
			{
				isLexical = false;
			}
		}
		//12.非法字符错
		else
		{
			//判断处理缓冲区是否为空
			if (strcmp(tp, ""))//处理缓冲区不为空 不为0
			{
				int res = getLexicalType(numberChange, flag, tp, isLexical);
				//添加到Token串中
				//rToken = newToken(0, tp, res, isLexical);
				//addTokenToLinks(pToken, rToken);
				string str_tmp(tp);
				Token token(lineNo, str_tmp.data(), res, isLexical);
				mTokenList.push_back(token);
				if (isAnalysisAnimation)	//加载词法分析数据
					loadLexicalAnalysisAnimationInfo(lineNo, i - strlen(tp), i , res, isLexical);	//特殊处理
				tp[0] = '\0'; tpi = 0;	//重置变量
				flag = 0;
				numberChange = 0;
				isLexical = true;
			}
			//处理非法字符
			//在(行,列)出，""为非法字符
			tpi = 0; tp[tpi] = '\0';
			tp[tpi++] = line[i];//将处理字符添加到处理缓冲区
			tp[tpi] = '\0';
			isLexical = false;
			flag = 1;
			string tp_str(tp);
			//异常字符添加到Token串中
			Token token(lineNo, tp_str.data(), Error, isLexical);
			mTokenList.push_back(token);
			cout << "E> Lexical : 在(" << mCurrentLine << ", " << (i+1) << ")中，\"" << tp_str << "\"为非法字符" << endl;
			tpi = 0; tp[tpi] = '\0';	//重置缓冲区
			isLexical = true;
			flag = 0;
			numberChange = 0;
		}
	}
	isBlockAnnotation = isBlockAnnotationTemp;
}

int LexicalAnalysis::getDelimiterType(char c)
{
	switch (c)
	{
	case '(':return Delimiter_Left_Small_Bracket;
	case ')':return Delimiter_Right_Small_Bracket;
	case ';':return Delimiter_Semicolon;
	case '[':return Delimiter_Left_Middle_Bracket;
	case ']':return Delimiter_Right_Middle_Bracket;
	case '{':return Delimiter_Left_Large_Bracket;
	case '}':return Delimiter_Right_Large_Bracket;
	case '.':return Delimiter_Period;
	case ',':return Delimiter_Comma;
	case '~':return Delimiter_Tilde;
	case '#':return Delimiter_Pound_Sign;
	case '$':return Delimiter_Dollar;	// $ 美元符号
	default:return 0;
	}
}

int LexicalAnalysis::getLexicalType(int numberChange, int flag, char * tp, bool & isLexical)
{
	int res = flag;
	if (flag == 1) //关键词 or 标识符
	{
		res = getIdentifierType(tp);
	}
	else if (flag == 2)
	{
		if (numberChange == 1 || numberChange == 10) //整数 [十进制]
		{
			res = Number_Decimalism;
		}
		else if (numberChange == 3) //小数
		{
			res = Number_Decimals;
		}
		else if (numberChange == 6) //指数
		{
			res = Number_Exponent;
		}
		else if (numberChange == 11) //整数 [八进制]
		{
			res = Number_Octonary;
		}
		else if (numberChange == 13) //整数 [十六进制]
		{
			res = Number_Hexadecimal;
		}
		else //报错
		{
			isLexical = false;
			res = 0;
		}
	}
	return res;
}

int LexicalAnalysis::getIdentifierType(const char * tp)
{
	//C语言中的关键词
	if (!strcmp(tp, "auto"))//1.auto
	{
		return Keyword_auto;
	}
	else if (!strcmp(tp, "break"))//2.break
	{
		return Keyword_break;
	}
	else if (!strcmp(tp, "case"))//3.case
	{
		return Keyword_case;
	}
	else if (!strcmp(tp, "char"))//4.char
	{
		return Keyword_char;
	}
	else if (!strcmp(tp, "const"))//5.const
	{
		return Keyword_const;
	}
	else if (!strcmp(tp, "continue"))//6.continue
	{
		return Keyword_continue;
	}
	else if (!strcmp(tp, "default"))//7.default
	{
		return Keyword_default;
	}
	else if (!strcmp(tp, "do"))//8.do
	{
		return Keyword_do;
	}
	else if (!strcmp(tp, "double"))//9.double
	{
		return Keyword_double;
	}
	else if (!strcmp(tp, "else"))//10.else
	{
		return Keyword_else;
	}
	else if (!strcmp(tp, "enum"))//11.enum
	{
		return Keyword_enum;
	}
	else if (!strcmp(tp, "extern"))//12.extern
	{
		return Keyword_extern;
	}
	else if (!strcmp(tp, "float"))//13.float
	{
		return Keyword_float;
	}
	else if (!strcmp(tp, "for"))//14.for
	{
		return Keyword_for;
	}
	else if (!strcmp(tp, "goto"))//15.goto
	{
		return Keyword_goto;
	}
	else if (!strcmp(tp, "if"))//16.if
	{
		return Keyword_if;
	}
	else if (!strcmp(tp, "inline"))//17.inline
	{
		return Keyword_inline;
	}
	else if (!strcmp(tp, "int"))//18.int
	{
		return Keyword_int;
	}
	else if (!strcmp(tp, "long"))//19.long
	{
		return Keyword_long;
	}
	else if (!strcmp(tp, "register"))//20.register
	{
		return Keyword_register;
	}
	else if (!strcmp(tp, "restrict"))//21.restrict
	{
		return Keyword_restrict;
	}
	else if (!strcmp(tp, "return"))//22.return
	{
		return Keyword_return;
	}
	else if (!strcmp(tp, "short"))//23.short
	{
		return Keyword_short;
	}
	else if (!strcmp(tp, "signed"))//24.signed
	{
		return Keyword_signed;
	}
	else if (!strcmp(tp, "sizeof"))//25.sizeof
	{
		return Keyword_sizeof;
	}
	else if (!strcmp(tp, "static"))//26.static
	{
		return Keyword_static;
	}
	else if (!strcmp(tp, "struct"))//27.struct
	{
		return Keyword_struct;
	}
	else if (!strcmp(tp, "switch"))//28.switch
	{
		return Keyword_switch;
	}
	else if (!strcmp(tp, "typedef"))//29.typedef
	{
		return Keyword_typedef;
	}
	else if (!strcmp(tp, "union"))//30.union
	{
		return Keyword_union;
	}
	else if (!strcmp(tp, "unsigned"))//31.unsigned
	{
		return Keyword_unsigned;
	}
	else if (!strcmp(tp, "void"))//32.void
	{
		return Keyword_void;
	}
	else if (!strcmp(tp, "volatile"))//33.volatile
	{
		return Keyword_volatile;
	}
	else if (!strcmp(tp, "while"))//34.while
	{
		return Keyword_while;
	}
	else if (!strcmp(tp, "_bool"))//35._bool
	{
		return Keyword__bool;
	}
	else if (!strcmp(tp, "_Complex"))//36._Complex
	{
		return Keyword__Complex;
	}
	else if (!strcmp(tp, "_Imaginary"))//37._Imaginary
	{
		return Keyword__Imaginary;
	}
	else if (!strcmp(tp, "true"))	//true
	{
		return Keyword_true;
	}
	else if (!strcmp(tp, "false"))	//false
	{
		return Keyword_false;
	}
	else if (!strcmp(tp, "print"))	//true
	{
		return Keyword_print;
	}
	else if (!strcmp(tp, "scan"))	//false
	{
		return Keyword_scan;
	}
	//其他的情况不再是关键词,有可能是标志符
	else
	{//判断是否为标识符
		bool isIdentifier = true;
		if (tp[0] == '_' || (tp[0] >= 'A' && tp[0] <= 'Z') || (tp[0] >= 'a' && tp[0] <= 'z'))
		{
			for (unsigned int i = 1; i < strlen(tp); i++)
			{
				if (!(tp[0] == '_' || (tp[0] >= 'A' && tp[0] <= 'Z') || (tp[0] >= 'a' && tp[0] <= 'z')
					|| (tp[0] >= '0' && tp[0] <= '9')))
				{
					isIdentifier = false;
					break;
				}
			}
		}
		else
		{
			isIdentifier = false;
		}
		if (isIdentifier)
		{
			return Identifier;
		}
		else
		{
			return Error;
		}
	}
}

int LexicalAnalysis::getOperatorType(const char * tp)
{
	if (!strcmp(tp, "!"))//#define Operator_Not// ! 非
	{
		return Operator_Not;
	}
	else if (!strcmp(tp, "!="))//#define Operator_Not_Equal_To// != 不等于
	{
		return Operator_Not_Equal_To;
	}
	else if (!strcmp(tp, "%"))//#define Operator_Mod// % 取余
	{
		return Operator_Mod;
	}
	else if (!strcmp(tp, "%="))//#define Operator_Mod_Equal// %= 取余等于
	{
		return Operator_Mod_Equal;
	}
	else if (!strcmp(tp, "="))//#define Operator_Equal// = 等于
	{
		return Operator_Equal;
	}
	else if (!strcmp(tp, "=="))//#define Operator_Is_Equal// == 是否等于
	{
		return Operator_Is_Equal;
	}
	else if (!strcmp(tp, "^"))//#define Operator_Xor// ^ 异或
	{
		return Operator_Xor;
	}
	else if (!strcmp(tp, "^="))//#define Operator_Xor_Equal// ^= 异或等于
	{
		return Operator_Xor_Equal;
	}
	else if (!strcmp(tp, "&"))//#define Operator_Bit_And// & 位与
	{
		return Operator_Bit_And;
	}
	else if (!strcmp(tp, "&="))//#define Operator_Bit_And_Equal// &= 位于等于
	{
		return Operator_Bit_And_Equal;
	}
	else if (!strcmp(tp, "&&"))//#define Operator_And// && 逻辑与
	{
		return Operator_And;
	}
	else if (!strcmp(tp, "+"))//#define Operator_Plus// + 加
	{
		return Operator_Plus;
	}
	else if (!strcmp(tp, "+="))//#define Operator_Plus_Equal// += 加等于
	{
		return Operator_Plus_Equal;
	}
	else if (!strcmp(tp, "++"))//#define Operator_Plus_Plus// ++ 自增
	{
		return Operator_Plus_Plus;
	}
	else if (!strcmp(tp, "-"))//#define Operator_Minus// - 减
	{
		return Operator_Minus;
	}
	else if (!strcmp(tp, "-="))//#define Operator_Minus_Equal// -= 减等于
	{
		return Operator_Minus_Equal;
	}
	else if (!strcmp(tp, "--"))//#define Operator_Minus_Minus// -- 自减
	{
		return Operator_Minus_Minus;
	}
	else if (!strcmp(tp, "|"))//#define Operator_Bit_Or// | 位或
	{
		return Operator_Bit_Or;
	}
	else if (!strcmp(tp, "|="))//#define Operator_Bit_Or_Equal// |= 位或等于
	{
		return Operator_Bit_Or_Equal;
	}
	else if (!strcmp(tp, "||"))//#define Operator_Or// || 逻辑或
	{
		return Operator_Or;
	}
	else if (!strcmp(tp, "<"))//#define Operator_Less_Than// < 小于
	{
		return Operator_Less_Than;
	}
	else if (!strcmp(tp, "<="))//#define Operator_Less_Than_Equal// <= 小于等于
	{
		return Operator_Less_Than_Equal;
	}
	else if (!strcmp(tp, "<<"))//#define Operator_Left_Shift// << 左移
	{
		return Operator_Left_Shift;
	}
	else if (!strcmp(tp, ">"))//#define Operator_More_Than// > 大于
	{
		return Operator_More_Than;
	}
	else if (!strcmp(tp, ">="))//#define Operator_More_Than_Equal// >= 大于等于
	{
		return Operator_More_Than_Equal;
	}
	else if (!strcmp(tp, ">>"))//#define Operator_Right_Shift// >> 右移
	{
		return Operator_Right_Shift;
	}
	else if (!strcmp(tp, "*"))//#define Operator_Multiply// * 乘 星
	{
		return Operator_Multiply;
	}
	else if (!strcmp(tp, "*="))//#define Operator_Multiply_Equal// *= 乘等于
	{
		return Operator_Multiply_Equal;
	}
	else if (!strcmp(tp, "/"))//#define Operator_Divide// / 除
	{
		return Operator_Divide;
	}
	else if (!strcmp(tp, "/="))//#define Operator_Divide_Equal// /= 除等于
	{
		return Operator_Divide_Equal;
	}
	else if (!strcmp(tp, ":"))//#define Operator_Colon// : 冒号[待使用]
	{
		return Operator_Colon;
	}
	else if (!strcmp(tp, "::"))//#define Operator_Member// :: 成员运算符
	{
		return Operator_Member;
	}
	else if (!strcmp(tp, "->"))//#define Operator_Arrows 0x40// -> 箭头
	{
		return Operator_Arrows;
	}
	return Error;
}

void LexicalAnalysis::loadLexicalAnalysisAnimationInfo(int lineNo, int start, int end, int type, bool isLexical)
{
	LexicalAnalysisAnimation animationInfo(lineNo, start, end, type, isLexical);
	mLexicalAnalysisAnimation.push_back(animationInfo);
}

bool LexicalAnalysis::saveLexicalAnalysisAnimationListToFile(const string & fileName)
{
	ofstream outFile(fileName);
	//outFile.open(fileName, ios::out, 0);
	list<LexicalAnalysisAnimation>::iterator it_info = mLexicalAnalysisAnimation.begin();
	for (; it_info != mLexicalAnalysisAnimation.end(); it_info++)
	{
		outFile << (*it_info).m_nLineNo << " " << (*it_info).m_nStart << " " << (*it_info).m_nEnd << " "
			<< (*it_info).m_nType << " " << ((*it_info).m_bIsLexical ? 1 : 0) << endl;
	}
	return true;
}

bool LexicalAnalysis::saveTokenListToFile(const string & fileName)
{
	//保存格式
	// "lineNo data type isLexical" "int string int bool"
	ofstream outFile(fileName);
	list<Token>::iterator it_token = mTokenList.begin();
	for (; it_token != mTokenList.end(); it_token++)
	{
		outFile << (*it_token).lineNo << " " << (*it_token).data << " "
			<< (*it_token).type << " " << ((*it_token).isLexical ? 1 : 0) << endl;
	}
	return true;
}
