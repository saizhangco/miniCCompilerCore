#include "lexicalAnalysisAnimation.h"

LexicalAnalysisAnimation::LexicalAnalysisAnimation()
{
}

LexicalAnalysisAnimation::LexicalAnalysisAnimation(int lineNo, int start, int end, int type, bool isLexical)
{
	m_nLineNo = lineNo;
	m_nStart = start;
	m_nEnd = end;
	m_nType = type;
	m_bIsLexical = isLexical;
}

LexicalAnalysisAnimation::~LexicalAnalysisAnimation()
{
}

void LexicalAnalysisAnimation::printLexicalAnalysisAnimation()
{
	cout << m_nLineNo << "\t" << m_nStart << "\t" << m_nEnd << "\t" 
		<< m_nType << "\t" << (m_bIsLexical ? "true" : "false") << endl;
}
