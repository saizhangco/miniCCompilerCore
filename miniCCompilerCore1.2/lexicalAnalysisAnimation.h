#pragma once
#include <iostream>
using namespace std;

class LexicalAnalysisAnimation
{
public :
	int m_nLineNo;
	int m_nStart;
	int m_nEnd;
	int m_nType;
	bool m_bIsLexical;
public:
	LexicalAnalysisAnimation();
	LexicalAnalysisAnimation(int lineNo,int start,int end,int type,bool isLexical);
	~LexicalAnalysisAnimation();
	void printLexicalAnalysisAnimation();
};
