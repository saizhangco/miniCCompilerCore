#include "variableDefinition.h"
#include "symbol.h"


VariableDefinition::VariableDefinition()
{
	actionScope = "@Local";
}

VariableDefinition::VariableDefinition(GrammarTreeTmp & tmp)
{
	actionScope = "@Global";
	memoryType = tmp.memoryType;
	dataType = tmp.dataType;
	list<VariableList>::iterator it_list;
	for (it_list = tmp.variableList.begin(); it_list != tmp.variableList.end(); it_list++)
	{
		variableList.push_back(*it_list);
	}
}

VariableDefinition::~VariableDefinition()
{

}

void VariableDefinition::printContent()
{
	cout << actionScope << "  " << "  变量定义  ";
	switch (memoryType)
	{
	case Keyword_extern:
		cout << "extern";
		break;
	case Keyword_static:
		cout << "static";
		break;
	case Keyword_auto:
		cout << "auto";
		break;
	case Keyword_register:
		cout << "register";
		break;
	default:
		break;
	}
	cout << "  ";
	switch (dataType)
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
		cout << "Error";
		break;
	}
	cout << endl;
	list<VariableList>::iterator it_list = variableList.begin();
	for (; it_list != variableList.end(); it_list++)
	{
		cout << "\t" << (*it_list).varName << "\t";
		if ((*it_list).initValue.size() <= 0)
		{
			cout << "未初始化";
		}
		else
		{
			list<Token>::iterator it_tok = (*it_list).initValue.begin();
			for (; it_tok != (*it_list).initValue.end(); it_tok++)
			{
				cout << (*it_tok).data << " ";
			}
		}
		cout << endl;
	}
}

string VariableDefinition::getContent()
{
	string str = "";
	str += actionScope + "  " + "  变量定义  ";
	switch (memoryType)
	{
	case Keyword_extern:
		str += "extern";
		break;
	case Keyword_static:
		str += "static";
		break;
	case Keyword_auto:
		str += "auto";
		break;
	case Keyword_register:
		str += "register";
		break;
	default:
		break;
	}
	str += "  ";
	switch (dataType)
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
		str += "Error";
		break;
	}
	str += "\n";
	list<VariableList>::iterator it_list = variableList.begin();
	for (; it_list != variableList.end(); it_list++)
	{
		str += "\t" + (*it_list).varName + "\t";
		if ((*it_list).initValue.size() <= 0)
		{
			str += "未初始化";
		}
		else
		{
			list<Token>::iterator it_tok = (*it_list).initValue.begin();
			for (; it_tok != (*it_list).initValue.end(); it_tok++)
			{
				str += (*it_tok).data + " ";
			}
		}
		str += "\n";
	}
	return str;
}
