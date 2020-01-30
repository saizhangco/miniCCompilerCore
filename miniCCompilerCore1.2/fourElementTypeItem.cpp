#include "fourElementTypeItem.h"


FourElementTypeItem::FourElementTypeItem()
{
	this->mType = 0;
	mPrintString = "";
	mCacheBuffer = "";
}


FourElementTypeItem::~FourElementTypeItem()
{
}

void FourElementTypeItem::printFourElementTypeItem()
{
	switch (mType)
	{
	case 0:
		cout << "未初始化" << endl;
		break;
	case 1:
		switch (mConstantType)
		{
		case 1:
			cout << "常量 整型 " << mConstantInteger << endl;
			break;
		case 2:
			cout << "常量 浮点型 " << mConstantFloat << endl;
			break;
		case 3:
			cout << "常量 字符型 " << mConstantChar << endl;
			break;
		default:
			break;
		}
		break;
	case 2:
		cout << "用户定义的变量 " << mUserIdentifierName << endl;
		break;
	case 3:
		cout << "临时变量 " << mTempIdentifierName << endl;
		break;
	case 4:
		break;
	case 5:
		cout << "->" << mNumber << endl;
		break;
	default:
		break;
	}
}

string FourElementTypeItem::getContent()
{
	string result = "";
	switch (mType)
	{
	case 0:
		result = "_";
		break;
	case 1:
		switch (mConstantType)
		{
		case 1:
			result = to_string(mConstantInteger);
			break;
		case 2:
			result = to_string(mConstantFloat);
			break;
		case 3:
			result = to_string(mConstantChar);
			break;
		case 4:
			result = mPrintString;
			break;
		default:
			break;
		}
		break;
	case 2:
		result = mUserIdentifierName;
		break;
	case 3:
		result = mTempIdentifierName;
		break;
	case 4:
		result = "bool";
		break;
	case 5:
		result = "->" + to_string(mNumber);
	default:
		break;
	}
	return result;
}