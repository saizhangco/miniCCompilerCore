#include "fourElementType.h"
#include <string>


FourElementType::FourElementType()
{
	mOptimizationType = 0;	//无优化
}

FourElementType::FourElementType(int number, int operation, FourElementTypeItem & arg1, FourElementTypeItem & arg2, FourElementTypeItem & result)
{
	mOptimizationType = 0;	//无优化
	mNumber = number;
	mOperation = operation;
	mArg1 = arg1;
	mArg2 = arg2;
	mResult = result;
}

FourElementType::~FourElementType()
{
}

void FourElementType::printFourElementType()
{
	cout << mNumber << ": ( " << getOperationContent() << " , " << mArg1.getContent() << " , " << mArg2.getContent()
		<< " , " << mResult.getContent() << " ) " << endl;
}

string FourElementType::getFourElementType()
{
	string str = to_string(mNumber) + ": ( " + getOperationContent() + " , " + mArg1.getContent() + " , " + mArg2.getContent()
		+ " , " + mResult.getContent() + " ) ";
	return str;
}

string FourElementType::getOperationContent()
{
	string result = "";
	switch (mOperation)
	{
	case IsNot:result = "!"; break;
	case Multiply:result = "*"; break;
	case Divide:result = "/"; break;
	case Mod:result = "%"; break;
	case Plus:result = "+"; break;
	case Minus:result = "-"; break;
	case Jump:result = "j"; break;
	case Jump_Less_Than:result = "j<"; break;
	case Jump_More_Than:result = "j>"; break;
	case Jump_Less_Than_Equal:result = "j<="; break;
	case Jump_More_Than_Equal:result = "j>="; break;
	case Jump_Not_Equal_To:result = "j!="; break;
	case Jump_Is_Equal:result = "j=="; break;
	case Jump_Not_Zero:result = "jnz"; break;
	case Equal:result = "="; break;
	case Sys:result = "sys"; break;
	case FuncEnter: result = "funcEnter"; break;
	case FuncExit:result = "funcExit"; break;
	case Print:result = "print"; break;
	default:
		break;
	}
	return result;
}
