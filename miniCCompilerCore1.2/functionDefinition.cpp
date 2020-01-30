#include "functionDefinition.h"
#include "symbol.h"
#include <algorithm>


FunctionDefinition::FunctionDefinition()
{
	funcEnter = 0;
}

FunctionDefinition::FunctionDefinition(int t, string n)
{
	if (t == Error)
		cout << "返回值类型错误" << endl;
	returnType = t;
	functionName = n;
}

FunctionDefinition::FunctionDefinition(GrammarTreeTmp tmp)
{
	if (tmp.dataType == Error)
		cout << "返回值类型错误" << endl;
	memoryType = tmp.memoryType;
	returnType = tmp.dataType;
	functionName = tmp.functionName;
	list<ParameterList>::iterator it_list;
	for (it_list = tmp.parameterList.begin(); it_list != tmp.parameterList.end(); it_list++)
	{
		parameterList.push_back(*it_list);
	}
	funcEnter = 0;
}

FunctionDefinition::~FunctionDefinition()
{
}

void FunctionDefinition::printContent()
{
	if (isComeTrue)
	{
		cout << "  函数实现  ";
	}
	else
	{
		cout << "  函数声明  ";
	}
	switch (memoryType)
	{
	case Keyword_extern:
		cout << "extern";
		break;
	case Keyword_static:
		cout << "static";
		break;
	default:
		break;
	}
	cout << "  ";
	switch (returnType)
	{
	case Keyword_int:
		cout << "int";
		break;
	case Keyword_char:
		cout << "char";
		break;
	case Keyword_float:
		cout << "float";
		break;
	case Keyword_double:
		cout << "double";
		break;
	default:
		break;
	}
	cout << "  " << functionName << "  " << funcEnter << endl;//endl;
	for_each(parameterList.begin(), parameterList.end(),
		[](const ParameterList& p) { cout << "\t" << p.parameterType << "\t" << p.parameterName << endl; });
}

string FunctionDefinition::getContent()
{
	string str = "";
	if (isComeTrue)
	{
		str += "  函数实现  ";
	}
	else
	{
		str += "  函数声明  ";
	}
	switch (memoryType)
	{
	case Keyword_extern:
		str += "extern";
		break;
	case Keyword_static:
		str += "static";
		break;
	default:
		break;
	}
	str += "  ";
	switch (returnType)
	{
	case Keyword_int:
		str += "int";
		break;
	case Keyword_char:
		str += "char";
		break;
	case Keyword_float:
		str += "float";
		break;
	case Keyword_double:
		str += "double";
		break;
	default:
		break;
	}
	str += "  " + functionName + "  " + to_string(funcEnter) + "\n";//endl;
	for_each(parameterList.begin(), parameterList.end(),
		[&str](const ParameterList& p) { str += "\t" + to_string(p.parameterType) + "\t" + p.parameterName + "\n"; });
	return str;
}
