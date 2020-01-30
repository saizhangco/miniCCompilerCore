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
	mCurrentLine = 0;//��ʼ���к�
	int lexicalErrorCount = 0;	//�ʷ��������
	//codeList.printCodeList();
	bool isBlockAnnotation = false;	//�Ƿ�Ϊ��ע��
	list<Code>::iterator it_code;
	for (it_code = codeList.codeList.begin(); it_code != codeList.codeList.end();it_code++ )
	{
		mCurrentLine++;
		lexical_core(*it_code , isBlockAnnotation ,true);
	}
	//����ʷ�����������Ϣ
	saveLexicalAnalysisAnimationListToFile("analysis\\lexicalAnalysisAnimation.txt");	
	saveTokenListToFile("analysis\\token.txt");	//����Token��
	//�ж�TokenList�����Ƿ���ڴ���
	list<Token>::iterator it_TokenList = mTokenList.begin();
	for (; it_TokenList != mTokenList.end(); it_TokenList++)
	{
		if ( (*it_TokenList).isLexical == false)
		{
			lexicalErrorCount++;	//TokenList���ڴ���
		}
	}
	return lexicalErrorCount;	//���شʷ������������
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
	int flag = 0;//1 ����ʶ��ؼ��ʺͳ���
				 //2 ����ʶ�����ֳ���
				 //-3 ����ʶ���ַ�����
				 //-4 ����ʶ���ַ�������
	int numberChange = 0;//�������ֳ���ʱ��ʹ��
	bool isLexical = true; //����ʶ���Ƿ���ڴ���
	bool isBlockAnnotationTemp = isBlockAnnotation;
	char tp[128];//��������
	int tpi = 0;
	tp[0] = '\0';//�����������ÿ�
	char* line = (char*)malloc(sizeof(char)* (strlen(code.line.c_str()) + 1));
	strcpy(line, code.line.c_str());
	//line[strlen(pCode->line)] = '\0';//�����ַ�����������
	int lineNo = code.no;
	int lastI = 0;
	for (unsigned int i = 0; i < (strlen(line) + 1); i++)
	{
		//0.�Ƿ�Ϊ��ע�ʹ���״̬ Ѱ��"*/"����
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
		//1���ս�� �ո�Tab���س�
		else if (line[i] == ' ' || line[i] == '\t' || line[i] == '\0')
		{
			//�жϴ��������Ƿ�Ϊ��
			if (strcmp(tp, "")) //��������Ϊ��
			{
				int res = getLexicalType(numberChange, flag, tp, isLexical);
				//rToken = newToken(0, tp, res, isLexical);
				//addTokenToLinks(pToken, rToken);
				string str_tmp(tp);
				Token token(lineNo, str_tmp.data(), res, isLexical);
				mTokenList.push_back(token);
				if (isAnalysisAnimation)	//���شʷ���������
					loadLexicalAnalysisAnimationInfo(lineNo, i  - strlen(tp), i , res, isLexical); //���⴦��
				tpi = 0; tp[0] = '\0';	//���ñ���
				flag = 0;
				numberChange = 0;
				isLexical = true;
			}
		}
		//2��ʵ��� ( ) ; [ ] { } . , ~ ��10���ַ� ǰ��ֿ� �Լ�Ҳ������Token��
		// # ���쳣�ַ� $ ���ķ��з���ʱ���õ�
		// || line[i] == '#' || line[i] == '$'
		else if (line[i] == '(' || line[i] == ')' || line[i] == ';' ||
			line[i] == '[' || line[i] == ']' || line[i] == '{' ||
			line[i] == '}' || line[i] == '.' || line[i] == ',' ||
			line[i] == '~')
		{
			if (flag == 2 && (numberChange == 1 || numberChange == 10) && line[i] == '.')	//��'.'��ӵ��������У�״̬�����仯
			{//����ʶ�����ֳ����е�һ����
				tp[tpi++] = line[i];
				numberChange = 2;
			}
			else
			{
				//�жϴ��������Ƿ�Ϊ��
				if (strcmp(tp, "")) //��������Ϊ�� ��Ϊ0
				{
					int res = getLexicalType(numberChange, flag, tp, isLexical);
					//rToken = newToken(0, tp, res, isLexical);
					//addTokenToLinks(pToken, rToken);
					string str_tmp(tp);
					Token token(lineNo, str_tmp.data(), res, isLexical);
					mTokenList.push_back(token);
					if (isAnalysisAnimation)	//���شʷ���������
						loadLexicalAnalysisAnimationInfo(lineNo, i - strlen(tp), i, res, isLexical);//���⴦��
					tpi = 0;  tp[0] = '\0';	//���ñ���
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
				if (isAnalysisAnimation)	//���شʷ���������
					loadLexicalAnalysisAnimationInfo(lineNo, i + 1 - strlen(tp), i + 1, getDelimiterType(line[i]), isLexical);
				tpi = 0;  tp[0] = '\0';	//���ñ���
				flag = 0;
				numberChange = 0;
				isLexical = true;
			}
		}
		// �ķ�����ʱ��'$'���ŵ�ʶ��
		else if (line[i] == '$')
		{
			//�жϴ��������Ƿ�Ϊ��
			if (strcmp(tp, "")) //��������Ϊ�� ��Ϊ0
			{
				int res = getLexicalType(numberChange, flag, tp, isLexical);
				string str_tmp(tp);
				Token token(lineNo, str_tmp.data(), res, isLexical);
				mTokenList.push_back(token);
				if (isAnalysisAnimation)	//���شʷ���������
					loadLexicalAnalysisAnimationInfo(lineNo, i - strlen(tp), i, res, isLexical);//���⴦��
				tpi = 0;  tp[0] = '\0';	//���ñ���
				flag = 0;
				numberChange = 0;
				isLexical = true;
			}
			tp[0] = line[i]; tp[1] = '\0';
			string str_tmp(tp);
			if (!analysisGrammar)
			{
				isLexical = false;
				cout << "E> Lexical : ��(" << mCurrentLine << ", " << (i + 1) << ")�У�\"" << str_tmp << "\"Ϊ�Ƿ��ַ�" << endl;
			}
			Token token(lineNo, str_tmp.data(), getDelimiterType(line[i]), isLexical);
			mTokenList.push_back(token);
			if (isAnalysisAnimation)	//���شʷ���������
				loadLexicalAnalysisAnimationInfo(lineNo, i + 1 - strlen(tp), i + 1, getDelimiterType(line[i]), isLexical);
			tpi = 0;  tp[0] = '\0';	//���ñ���
			flag = 0;
			numberChange = 0;
			isLexical = true;
		}
		//3.ʶ����ؼ��ʺͳ��� ֻ������ĸ�����֡�_�����ֲ���ͷ
		//[A,Z]��[a,z]��_
		else if ((line[i] >= 'A'&&line[i] <= 'Z') || (line[i] >= 'a'&&line[i] <= 'z') || line[i] == '_')
		{
			if (flag == 0)
			{
				flag = 1;
				tpi = 0; tp[tpi] = '\0';
				tp[tpi++] = line[i];//�������ַ���ӵ���������
				tp[tpi] = '\0';
			}
			else if (flag == 1)
			{
				tp[tpi++] = line[i];//�������ַ���ӵ���������
				tp[tpi] = '\0';
			}
			else if (flag == 2)
			{
				tp[tpi++] = line[i];//�������ַ���ӵ���������
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
					isLexical = false;//��������������Ҫ����
				}
			}
			else
			{
				tp[tpi++] = line[i];//�������ַ���ӵ���������
				tp[tpi] = '\0';
				isLexical = false;
			}
		}
		//4.ʶ������� ̾��! ȡ��% �Ⱥ�= ȡ��^ �Ǻ�*
		else if (line[i] == '!' || line[i] == '%' || line[i] == '=' || line[i] == '^' ||
			line[i] == '*')
		{
			//�жϴ��������Ƿ�Ϊ��
			if (strcmp(tp, ""))//����������Ϊ�� ��Ϊ0
			{
				int res = getLexicalType(numberChange, flag, tp, isLexical);
				//��ӵ�Token����
				//rToken = newToken(0, tp, res, isLexical);
				//addTokenToLinks(pToken, rToken);
				string str_tmp(tp);
				Token token(lineNo, str_tmp.data(), res, isLexical);
				mTokenList.push_back(token);
				if (isAnalysisAnimation)	//���شʷ���������
					loadLexicalAnalysisAnimationInfo(lineNo, i - strlen(tp), i, res, isLexical);	//���⴦��
				tp[0] = '\0'; tpi = 0;	//���ñ���
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
			//��ӵ�Token����
			int res = getOperatorType(tp);
			//rToken = newToken(0, tp, res, isLexical);
			//addTokenToLinks(pToken, rToken);
			string str_tmp(tp);
			Token token(lineNo, str_tmp.data(), res, isLexical);
			mTokenList.push_back(token);
			if (isAnalysisAnimation)	//���شʷ���������
				loadLexicalAnalysisAnimationInfo(lineNo, i + 1 - strlen(tp), i + 1, res, isLexical);
			tp[0] = '\0'; tpi = 0;	//���ñ���
			flag = 0;
			numberChange = 0;
			isLexical = true;
		}
		//5.ʶ������� ��& ��| ��+ ��- ����> С��<
		else if (line[i] == '&' || line[i] == '|' || line[i] == '+' || line[i] == '-' ||
			line[i] == '>' || line[i] == '<')
		{
			if (flag == 2 && numberChange == 4 && (line[i] == '+' || line[i] == '-'))
			{
				tp[tpi++] = line[i]; tp[tpi] = '\0';//��ӵ�������
				numberChange = 5;
			}
			else
			{
				//�жϴ��������Ƿ�Ϊ��
				if (strcmp(tp, ""))//����������Ϊ�� ��Ϊ0
				{
					int res = getLexicalType(numberChange, flag, tp, isLexical);
					//��ӵ�Token����
					//rToken = newToken(0, tp, res, isLexical);
					//addTokenToLinks(pToken, rToken);
					string str_tmp(tp);
					Token token(lineNo, str_tmp.data(), res, isLexical);
					mTokenList.push_back(token);
					if (isAnalysisAnimation)	//���شʷ���������
						loadLexicalAnalysisAnimationInfo(lineNo, i - strlen(tp), i, res, isLexical);	//���⴦��
					tp[0] = '\0'; tpi = 0;	//���ñ���
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
				else if (line[i] == '-' && line[i + 1] == '>')//�ڽ����ķ�����ʱ���õ�
				{
					i++;
					tp[tpi++] = line[i]; tp[tpi] = '\0';
				}
				//��ӵ�Token����
				int res = getOperatorType(tp);
				//rToken = newToken(0, tp, res, isLexical);
				//addTokenToLinks(pToken, rToken);
				string str_tmp(tp);
				Token token(lineNo, str_tmp.data(), res, isLexical);
				mTokenList.push_back(token);
				if (isAnalysisAnimation)	//���شʷ���������
					loadLexicalAnalysisAnimationInfo(lineNo, i + 1 - strlen(tp), i + 1, res, isLexical);
				tp[0] = '\0'; tpi = 0;	//���ñ���
				flag = 0;
				numberChange = 0;
				isLexical = true;
			}
		}
		//7��ʶ������� б��/
		else if (line[i] == '/')
		{
			//�жϴ��������Ƿ�Ϊ��
			if (strcmp(tp, ""))//����������Ϊ�� ��Ϊ0
			{
				int res = getLexicalType(numberChange, flag, tp, isLexical);
				//��ӵ�Token����
				//rToken = newToken(0, tp, res, isLexical);
				//addTokenToLinks(pToken, rToken);
				string str_tmp(tp);
				Token token(lineNo, str_tmp.data(), res, isLexical);
				mTokenList.push_back(token);
				if (isAnalysisAnimation)	//���شʷ���������
					loadLexicalAnalysisAnimationInfo(lineNo, i - strlen(tp), i, res, isLexical);	//���⴦��
				tp[0] = '\0'; tpi = 0;	//���ñ���
				flag = 0;
				numberChange = 0;
				isLexical = true;
			}
			//�ж���һ���ַ��Ƿ�Ϊ '*'
			if (line[i + 1] == '*')
			{//�������Ĳ���ΪѰ�� "*/" ���ս��ע��
				cout << "BlockAnnetation" << endl;
				i++;
				isBlockAnnotationTemp = true;
			}
			//�ж���һ���ַ��Ƿ�Ϊ '/'
			else if (line[i + 1] == '/')
			{//��ע��
				while (i++ < (strlen(line) + 1))
				{
					if (line[i] == '\0')
					{
						cout << "��ע��" << endl;
						break;
					}
				}
			}
			else
			{
				// 1./ 2./=
				tpi = 0; tp[tpi] = '\0';	//? ����ط������Ⱑ
				tp[tpi++] = line[i]; tp[tpi] = '\0';
				if (line[i + 1] == '=')
				{
					i++;
					tp[tpi++] = line[i]; tp[tpi] = '\0';
				}
				//��ӵ�Token����
				int res = getOperatorType(tp);
				//rToken = newToken(0, tp, res, isLexical);
				//addTokenToLinks(pToken, rToken);
				string str_tmp(tp);
				Token token(lineNo, str_tmp.data(), res, isLexical);
				mTokenList.push_back(token);
				if (isAnalysisAnimation)	//���شʷ���������
					loadLexicalAnalysisAnimationInfo(lineNo, i + 1 - strlen(tp), i + 1, res, isLexical);
				tp[0] = '\0'; tpi = 0;	//���ñ���
				flag = 0;
				numberChange = 0;
				isLexical = true;
			}
		}
		//8.ʶ������� ð��:
		else if (line[i] == ':')
		{
			//�жϴ��������Ƿ�Ϊ��
			if (strcmp(tp, ""))//����������Ϊ�� ��Ϊ0
			{
				int res = getLexicalType(numberChange, flag, tp, isLexical);
				//��ӵ�Token����
				//rToken = newToken(0, tp, res, isLexical);
				//addTokenToLinks(pToken, rToken);
				string str_tmp(tp);
				Token token(lineNo, str_tmp.data(), res, isLexical);
				mTokenList.push_back(token);
				if (isAnalysisAnimation)	//���شʷ���������
					loadLexicalAnalysisAnimationInfo(lineNo, i - strlen(tp), i , res, isLexical);	//���⴦��
				tp[0] = '\0'; tpi = 0;	//���ñ���
				flag = 0;
				numberChange = 0;
				isLexical = true;
			}
			tpi = 0; tp[tpi] = '\0';
			tp[tpi++] = line[i]; tp[tpi] = '\0';
			if (line[i + 1] == line[i])//line[i + 1] == '=' || ����Ҫ���жϺ����Ƿ�Ϊ=��
			{
				i++;
				tp[tpi++] = line[i]; tp[tpi] = '\0';
			}
			//��ӵ�Token����
			int res = getOperatorType(tp);
			//rToken = newToken(0, tp, res, isLexical);
			//addTokenToLinks(pToken, rToken);
			string str_tmp(tp);
			Token token(lineNo, str_tmp.data(), res, isLexical);
			mTokenList.push_back(token);
			if (isAnalysisAnimation)	//���شʷ���������
				loadLexicalAnalysisAnimationInfo(lineNo, i + 1 - strlen(tp), i + 1, res, isLexical);
			tp[0] = '\0'; tpi = 0;	//���ñ���
			flag = 0;
			numberChange = 0;
			isLexical = true;
		}
		//9.ʶ���ַ����� 'AAAAAAAAA'
		else if (line[i] == '\'')
		{
			//�жϴ��������Ƿ�Ϊ��
			if (strcmp(tp, ""))//����������Ϊ�� ��Ϊ0
			{
				int res = getLexicalType(numberChange, flag, tp, isLexical);
				//��ӵ�Token����
				//rToken = newToken(0, tp, res, isLexical);
				//addTokenToLinks(pToken, rToken);
				string str_tmp(tp);
				Token token(lineNo, str_tmp.data(), res, isLexical);
				mTokenList.push_back(token);
				if (isAnalysisAnimation)	//���شʷ���������
					loadLexicalAnalysisAnimationInfo(lineNo, i - strlen(tp), i , res, isLexical);	//���⴦��
				tp[0] = '\0'; tpi = 0;	//���ñ���
				flag = 0;
				numberChange = 0;
				isLexical = true;
			}
			tpi = 0; tp[tpi] = '\0';
			tp[tpi++] = line[i]; tp[tpi] = '\0';
			bool complete = false;
			while (i++ < strlen(line)) //i++ < (strlen(line) + ) �������������'\0'
			{
				tp[tpi++] = line[i]; tp[tpi] = '\0';
				if (line[i - 1] != '\\' && line[i] == '\'')
				{
					complete = true;
					break;
				}
			}
			//��ӵ�Token���� ����complete�������
			if (complete)//�ַ�ʶ�𲻴��ڴ���
			{
				if (strlen(tp) > 6)//''�е��ַ��������ó���4��
					complete = false;
			}
			//rToken = newToken(0, tp, complete ? Character : 0, isLexical);
			//addTokenToLinks(pToken, rToken);
			string str_tmp(tp);
			Token token(lineNo, str_tmp.data(), complete ? Character : Error, complete);
			mTokenList.push_back(token);
			if (isAnalysisAnimation)	//���شʷ���������
				loadLexicalAnalysisAnimationInfo(lineNo, i + 1 - strlen(tp), i + 1, Character, isLexical);
			tp[0] = '\0'; tpi = 0;	//���ñ���
			flag = 0;
			numberChange = 0;
			isLexical = true;
		}
		//10.ʶ���ַ������� "AAAAAAAAAAA"
		else if (line[i] == '\"')
		{
			//�жϴ��������Ƿ�Ϊ��
			if (strcmp(tp, ""))//����������Ϊ�� ��Ϊ0
			{
				int res = getLexicalType(numberChange, flag, tp, isLexical);
				//��ӵ�Token����
				//rToken = newToken(0, tp, res, isLexical);
				//addTokenToLinks(pToken, rToken);
				string str_tmp(tp);
				Token token(lineNo, str_tmp.data(), res, isLexical);
				mTokenList.push_back(token);
				if (isAnalysisAnimation)	//���شʷ���������
					loadLexicalAnalysisAnimationInfo(lineNo, i - strlen(tp), i, res, isLexical);	//���⴦��
				tp[0] = '\0'; tpi = 0;	//���ñ���
				flag = 0;
				numberChange = 0;
				isLexical = true;
			}
			tpi = 0; tp[tpi] = '\0';
			tp[tpi++] = line[i]; tp[tpi] = '\0';
			bool complete = false;
			while (i++ < strlen(line))//i++ < (strlen(line) + ) �������������'\0'
			{
				tp[tpi++] = line[i]; tp[tpi] = '\0';
				if (line[i - 1] != '\\' && line[i] == '\"')
				{
					complete = true;
					break;
				}
			}
			//��ӵ�Token���� ����complete�������
			//rToken = newToken(0, tp, complete ? String : 0, isLexical);
			//addTokenToLinks(pToken, rToken);
			string str_tmp(tp);
			Token token(lineNo, str_tmp.data(), complete ? String : Error, complete);
			mTokenList.push_back(token);
			if (isAnalysisAnimation)	//���شʷ���������
				loadLexicalAnalysisAnimationInfo(lineNo, i + 1 - strlen(tp), i + 1, String, isLexical);
			tp[0] = '\0'; tpi = 0;	//���ñ���
			flag = 0;
			numberChange = 0;
			isLexical = true;
		}
		//11.ʶ�����ֳ��� ����(ָ����С����ʮ���������˽�������ʮ��������)
		else if (line[i] >= '0' && line[i] <= '9')
		{
			if (flag == 0)//��������Ӧ��Ϊ�գ������ж��Ƿ�Ϊ�գ���Ϊ������Ӧ�Ĵ���
			{
				//�жϴ��������Ƿ�Ϊ�� [��������]
				if (strcmp(tp, ""))//����������Ϊ�� ��Ϊ0
				{
					int res = getLexicalType(numberChange, flag, tp, isLexical);
					//��ӵ�Token����
					//rToken = newToken(0, tp, res, isLexical);
					//addTokenToLinks(pToken, rToken);
					string str_tmp(tp);
					Token token(lineNo, str_tmp.data(), res, isLexical);
					mTokenList.push_back(token);
					if (isAnalysisAnimation)	//���شʷ���������
						loadLexicalAnalysisAnimationInfo(lineNo, i - strlen(tp), i, res, isLexical);	//���⴦��
					tp[0] = '\0'; tpi = 0;	//���ñ���
					flag = 0;
					numberChange = 0;
					isLexical = true;
				}
				flag = 2; //��������ʶ�����ֳ���
				tpi = 0; tp[tpi] = '\0';
				tp[tpi++] = line[i]; tp[tpi] = '\0';
				//�ж��Ƿ�Ϊ 0
				if (line[i] == '0')
				{
					numberChange = 10;
				}
				else
				{
					numberChange = 1;
				}
			}
			else if (flag == 1)//����ʶ��ؼ��ʻ��ʶ�� ֱ����ӵ�����������
			{
				tp[tpi++] = line[i]; tp[tpi] = '\0';
			}
			else if (flag == 2)//����ʶ�����ֳ��� flag==2ʱnumberChange>0
			{
				if (numberChange == 1 || numberChange == 3 || numberChange == 6 || numberChange == 13)//ֱ����ӵ�������
				{
					tp[tpi++] = line[i]; tp[tpi] = '\0';
				}
				else if (numberChange == 2)//��ӵ���������״̬�����仯
				{
					tp[tpi++] = line[i]; tp[tpi] = '\0';
					numberChange = 3;
				}
				else if (numberChange == 4 || numberChange == 5)//��ӵ���������״̬�����仯
				{
					tp[tpi++] = line[i]; tp[tpi] = '\0';
					numberChange = 6;
				}
				else if (numberChange == 10 || numberChange == 11)//��ӵ���������״̬�п�����Ҫ�����仯
				{
					tp[tpi++] = line[i]; tp[tpi] = '\0';
					if (!(line[i] >= '0' && line[i] < '8'))//������[0,8)
					{//��Ҫ��ʾ���� 
						isLexical = false;
					}
					numberChange = 11;
				}
			}
			else//Ԥ���Ĵ�����
			{
				isLexical = false;
			}
		}
		//12.�Ƿ��ַ���
		else
		{
			//�жϴ��������Ƿ�Ϊ��
			if (strcmp(tp, ""))//����������Ϊ�� ��Ϊ0
			{
				int res = getLexicalType(numberChange, flag, tp, isLexical);
				//��ӵ�Token����
				//rToken = newToken(0, tp, res, isLexical);
				//addTokenToLinks(pToken, rToken);
				string str_tmp(tp);
				Token token(lineNo, str_tmp.data(), res, isLexical);
				mTokenList.push_back(token);
				if (isAnalysisAnimation)	//���شʷ���������
					loadLexicalAnalysisAnimationInfo(lineNo, i - strlen(tp), i , res, isLexical);	//���⴦��
				tp[0] = '\0'; tpi = 0;	//���ñ���
				flag = 0;
				numberChange = 0;
				isLexical = true;
			}
			//����Ƿ��ַ�
			//��(��,��)����""Ϊ�Ƿ��ַ�
			tpi = 0; tp[tpi] = '\0';
			tp[tpi++] = line[i];//�������ַ���ӵ���������
			tp[tpi] = '\0';
			isLexical = false;
			flag = 1;
			string tp_str(tp);
			//�쳣�ַ���ӵ�Token����
			Token token(lineNo, tp_str.data(), Error, isLexical);
			mTokenList.push_back(token);
			cout << "E> Lexical : ��(" << mCurrentLine << ", " << (i+1) << ")�У�\"" << tp_str << "\"Ϊ�Ƿ��ַ�" << endl;
			tpi = 0; tp[tpi] = '\0';	//���û�����
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
	case '$':return Delimiter_Dollar;	// $ ��Ԫ����
	default:return 0;
	}
}

int LexicalAnalysis::getLexicalType(int numberChange, int flag, char * tp, bool & isLexical)
{
	int res = flag;
	if (flag == 1) //�ؼ��� or ��ʶ��
	{
		res = getIdentifierType(tp);
	}
	else if (flag == 2)
	{
		if (numberChange == 1 || numberChange == 10) //���� [ʮ����]
		{
			res = Number_Decimalism;
		}
		else if (numberChange == 3) //С��
		{
			res = Number_Decimals;
		}
		else if (numberChange == 6) //ָ��
		{
			res = Number_Exponent;
		}
		else if (numberChange == 11) //���� [�˽���]
		{
			res = Number_Octonary;
		}
		else if (numberChange == 13) //���� [ʮ������]
		{
			res = Number_Hexadecimal;
		}
		else //����
		{
			isLexical = false;
			res = 0;
		}
	}
	return res;
}

int LexicalAnalysis::getIdentifierType(const char * tp)
{
	//C�����еĹؼ���
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
	//��������������ǹؼ���,�п����Ǳ�־��
	else
	{//�ж��Ƿ�Ϊ��ʶ��
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
	if (!strcmp(tp, "!"))//#define Operator_Not// ! ��
	{
		return Operator_Not;
	}
	else if (!strcmp(tp, "!="))//#define Operator_Not_Equal_To// != ������
	{
		return Operator_Not_Equal_To;
	}
	else if (!strcmp(tp, "%"))//#define Operator_Mod// % ȡ��
	{
		return Operator_Mod;
	}
	else if (!strcmp(tp, "%="))//#define Operator_Mod_Equal// %= ȡ�����
	{
		return Operator_Mod_Equal;
	}
	else if (!strcmp(tp, "="))//#define Operator_Equal// = ����
	{
		return Operator_Equal;
	}
	else if (!strcmp(tp, "=="))//#define Operator_Is_Equal// == �Ƿ����
	{
		return Operator_Is_Equal;
	}
	else if (!strcmp(tp, "^"))//#define Operator_Xor// ^ ���
	{
		return Operator_Xor;
	}
	else if (!strcmp(tp, "^="))//#define Operator_Xor_Equal// ^= ������
	{
		return Operator_Xor_Equal;
	}
	else if (!strcmp(tp, "&"))//#define Operator_Bit_And// & λ��
	{
		return Operator_Bit_And;
	}
	else if (!strcmp(tp, "&="))//#define Operator_Bit_And_Equal// &= λ�ڵ���
	{
		return Operator_Bit_And_Equal;
	}
	else if (!strcmp(tp, "&&"))//#define Operator_And// && �߼���
	{
		return Operator_And;
	}
	else if (!strcmp(tp, "+"))//#define Operator_Plus// + ��
	{
		return Operator_Plus;
	}
	else if (!strcmp(tp, "+="))//#define Operator_Plus_Equal// += �ӵ���
	{
		return Operator_Plus_Equal;
	}
	else if (!strcmp(tp, "++"))//#define Operator_Plus_Plus// ++ ����
	{
		return Operator_Plus_Plus;
	}
	else if (!strcmp(tp, "-"))//#define Operator_Minus// - ��
	{
		return Operator_Minus;
	}
	else if (!strcmp(tp, "-="))//#define Operator_Minus_Equal// -= ������
	{
		return Operator_Minus_Equal;
	}
	else if (!strcmp(tp, "--"))//#define Operator_Minus_Minus// -- �Լ�
	{
		return Operator_Minus_Minus;
	}
	else if (!strcmp(tp, "|"))//#define Operator_Bit_Or// | λ��
	{
		return Operator_Bit_Or;
	}
	else if (!strcmp(tp, "|="))//#define Operator_Bit_Or_Equal// |= λ�����
	{
		return Operator_Bit_Or_Equal;
	}
	else if (!strcmp(tp, "||"))//#define Operator_Or// || �߼���
	{
		return Operator_Or;
	}
	else if (!strcmp(tp, "<"))//#define Operator_Less_Than// < С��
	{
		return Operator_Less_Than;
	}
	else if (!strcmp(tp, "<="))//#define Operator_Less_Than_Equal// <= С�ڵ���
	{
		return Operator_Less_Than_Equal;
	}
	else if (!strcmp(tp, "<<"))//#define Operator_Left_Shift// << ����
	{
		return Operator_Left_Shift;
	}
	else if (!strcmp(tp, ">"))//#define Operator_More_Than// > ����
	{
		return Operator_More_Than;
	}
	else if (!strcmp(tp, ">="))//#define Operator_More_Than_Equal// >= ���ڵ���
	{
		return Operator_More_Than_Equal;
	}
	else if (!strcmp(tp, ">>"))//#define Operator_Right_Shift// >> ����
	{
		return Operator_Right_Shift;
	}
	else if (!strcmp(tp, "*"))//#define Operator_Multiply// * �� ��
	{
		return Operator_Multiply;
	}
	else if (!strcmp(tp, "*="))//#define Operator_Multiply_Equal// *= �˵���
	{
		return Operator_Multiply_Equal;
	}
	else if (!strcmp(tp, "/"))//#define Operator_Divide// / ��
	{
		return Operator_Divide;
	}
	else if (!strcmp(tp, "/="))//#define Operator_Divide_Equal// /= ������
	{
		return Operator_Divide_Equal;
	}
	else if (!strcmp(tp, ":"))//#define Operator_Colon// : ð��[��ʹ��]
	{
		return Operator_Colon;
	}
	else if (!strcmp(tp, "::"))//#define Operator_Member// :: ��Ա�����
	{
		return Operator_Member;
	}
	else if (!strcmp(tp, "->"))//#define Operator_Arrows 0x40// -> ��ͷ
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
	//�����ʽ
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
