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
		cout << "δ��ʼ��" << endl;
		break;
	case 1:
		switch (mConstantType)
		{
		case 1:
			cout << "���� ���� " << mConstantInteger << endl;
			break;
		case 2:
			cout << "���� ������ " << mConstantFloat << endl;
			break;
		case 3:
			cout << "���� �ַ��� " << mConstantChar << endl;
			break;
		default:
			break;
		}
		break;
	case 2:
		cout << "�û�����ı��� " << mUserIdentifierName << endl;
		break;
	case 3:
		cout << "��ʱ���� " << mTempIdentifierName << endl;
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