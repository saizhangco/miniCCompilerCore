#include "objectCodeGeneration_x86.h"
#include "code.h"
#include "variableDefinition.h"

ObjectCodeGeneration_x86::ObjectCodeGeneration_x86()
{
	mObjectCode.codeList.clear();
	mPrintStringCount = 0;
	//object_schemaDefinition();	//模式定义
}

ObjectCodeGeneration_x86::~ObjectCodeGeneration_x86()
{
}

void ObjectCodeGeneration_x86::object_analysisFourElementType(FourElementType& fourElementType)
{
	string markNumberStirng = "@line_" + to_string(fourElementType.mNumber);//标号
	markNumberStirng += ":";
	m_code.push_back(Code(0, markNumberStirng));
	switch (fourElementType.mOperation)
	{
	case IsNot:	// ! (!,a,_,result)	//未测试
	{
		//     mov eax, a
		//     cmp eax, 0
		//     jne EQUAL_ZERO
		//     mov eax, 1
		//     jmp IS_NOT_END
		// EQUAL_ZERO :
		//     mov eax, 0
		// IS_NOT_END :
		//     mov result, eax
		string code = "";
		code = "\tmov eax," + fourElementType.mArg1.getContent();
		m_code.push_back(Code(0, code));
		code = "\tcmp eax,0";
		m_code.push_back(Code(0, code));
		code = "\tjne EQUAL_ZRRO";
		m_code.push_back(Code(0, code));
		code = "\tmov eax,1";
		m_code.push_back(Code(0, code));
		code = "\tjmp IS_NOT_END";
		m_code.push_back(Code(0, code));
		code = "EQUAL_ZERO:";
		m_code.push_back(Code(0, code));
		code = "\tmov eax,0";
		m_code.push_back(Code(0, code));
		code = "IS_NOT_END:";
		m_code.push_back(Code(0, code));
		code = "\tmov " + fourElementType.mResult.getContent() + ",eax";
		m_code.push_back(Code(0, code));
		break;
	}
	case Multiply:	// ( * , a , b , result )	//未测试
	{	//修改 2016-04-29
		string code = "";
		// mov eax,a
		// imul eax,b
		// mov result,eax
		code = "\tmov eax," + fourElementType.mArg1.getContent();
		m_code.push_back(Code(0, code));
		code = "\timul eax," + fourElementType.mArg2.getContent();
		m_code.push_back(Code(0, code));
		code = "\tmov " + fourElementType.mResult.getContent() + ",eax";
		m_code.push_back(Code(0, code));
		break;
	}
	case Divide:	// ( / , a , b , result )	//未测试
	{
		// mov edx, 0
		// mov eax, a
		// mov ebx, b
		// idiv ebx
		// mov result,eax
		string code = "";
		code = "\tmov edx,0";
		m_code.push_back(Code(0, code));
		code = "\tmov eax," + fourElementType.mArg1.getContent();
		m_code.push_back(Code(0, code));
		code = "\tmov ebx," + fourElementType.mArg2.getContent();
		m_code.push_back(Code(0, code));
		code = "\tidiv ebx";
		m_code.push_back(Code(0, code));
		code = "\tmov " + fourElementType.mResult.getContent() + ",eax";
		m_code.push_back(Code(0, code));
		break;
	}
	case Mod:		// ( % , a , b , result )	//未测试
	{
		string code = "";
		//     mov eax, a
		//     mov ebx, a
		// MOD_LOOP :
		//     cmp eax, ebx
		//	   jl MOD_END
		//	   sub eax, ebx
		//	   jmp MOD_LOOP
		// MOD_END :
		//     mov result, eax
		code = "\tmov eax," + fourElementType.mArg1.getContent();
		m_code.push_back(Code(0, code));
		code = "\tmov ebx," + fourElementType.mArg2.getContent();
		m_code.push_back(Code(0, code));
		code = "MOD_LOOP:";
		m_code.push_back(Code(0, code));
		code = "\tcmp eax,ebx";
		m_code.push_back(Code(0, code));
		code = "\tjl MOD_END";
		m_code.push_back(Code(0, code));
		code = "\tsub eax,ebx";
		m_code.push_back(Code(0, code));
		code = "\tjmp MOD_LOOP";
		m_code.push_back(Code(0, code));
		code = "MOD_END";
		m_code.push_back(Code(0, code));
		code = "\tmov " + fourElementType.mResult.getContent() + ",eax";
		m_code.push_back(Code(0, code));
		break;
	}
	case Plus:		// ( + , a , b , result )
	{
		string code = "";
		// mov eax,a
		// add eax,b
		// mov result,eax
		code = "\tmov eax," + fourElementType.mArg1.getContent();
		m_code.push_back(Code(0, code));
		code = "\tadd eax," + fourElementType.mArg2.getContent();
		m_code.push_back(Code(0, code));
		code = "\tmov " + fourElementType.mResult.getContent() + ",eax";
		m_code.push_back(Code(0, code));
		break;
	}
	case Minus:		// ( - , a , b , result )
	{
		string code = "";
		// mov eax,a
		// sub eax,b
		// mov result,eax
		code = "\tmov eax," + fourElementType.mArg1.getContent();
		m_code.push_back(Code(0, code));
		code = "\tsub eax," + fourElementType.mArg2.getContent();
		m_code.push_back(Code(0, code));
		code = "\tmov " + fourElementType.mResult.getContent() + ",eax";
		m_code.push_back(Code(0, code));
		break;
	}
	case Jump:	// ( j , _ , _ , line_no )
	{
		// jmp @line_[line_no]
		string code = "\tjmp @line_" + to_string(fourElementType.mResult.mNumber);
		m_code.push_back(Code(0, code));
		break;
	}
	case Jump_Less_Than:	// ( j< , a , b , line_no )
	{
		string code = "";
		// mov eax,a
		// mov ebx,b
		// cmp eax,ebx
		// jl @line_[line_no]
		code = "\tmov eax," + fourElementType.mArg1.getContent();
		m_code.push_back(Code(0, code));
		code = "\tmov ebx," + fourElementType.mArg2.getContent();
		m_code.push_back(Code(0, code));
		code = "\tcmp eax,ebx";
		m_code.push_back(Code(0, code));
		code = "\tjl @line_" + to_string(fourElementType.mResult.mNumber);
		m_code.push_back(Code(0, code));
		break;
	}
	case Jump_More_Than:	// ( j> , a , b ,line_no )
	{
		string code = "";
		// mov eax,a
		// mov ebx,b
		// cmp eax,ebx
		// jg @line_[line_no]
		code = "\tmov eax," + fourElementType.mArg1.getContent();
		m_code.push_back(Code(0, code));
		code = "\tmov ebx," + fourElementType.mArg2.getContent();
		m_code.push_back(Code(0, code));
		code = "\tcmp eax,ebx";
		m_code.push_back(Code(0, code));
		code = "\tjg @line_" + to_string(fourElementType.mResult.mNumber);
		m_code.push_back(Code(0, code));
		break;
	}
	case Jump_Less_Than_Equal:	// ( j<= , a , b ,line_no )
	{
		string code = "";
		// mov eax,a
		// mov ebx,b
		// cmp eax,ebx
		// jle @line_[line_no]
		code = "\tmov eax," + fourElementType.mArg1.getContent();
		m_code.push_back(Code(0, code));
		code = "\tmov ebx," + fourElementType.mArg2.getContent();
		m_code.push_back(Code(0, code));
		code = "\tcmp eax,ebx";
		m_code.push_back(Code(0, code));
		code = "\tjle @line_" + to_string(fourElementType.mResult.mNumber);
		m_code.push_back(Code(0, code));
		break;
	}
	case Jump_More_Than_Equal:	// ( j>= , a , b ,line_no )
	{
		string code = "";
		// mov eax,a
		// mov ebx,b
		// cmp eax,ebx
		// jge @line_[line_no]
		code = "\tmov eax," + fourElementType.mArg1.getContent();
		m_code.push_back(Code(0, code));
		code = "\tmov ebx," + fourElementType.mArg2.getContent();
		m_code.push_back(Code(0, code));
		code = "\tcmp eax,ebx";
		m_code.push_back(Code(0, code));
		code = "\tjge @line_" + to_string(fourElementType.mResult.mNumber);
		m_code.push_back(Code(0, code));
		break;
	}
	case Jump_Not_Equal_To:		// ( j!= , a , b ,line_no )
	{
		string code = "";
		// mov eax,a
		// mov ebx,b
		// cmp eax,ebx
		// jne @line_[line_no]
		code = "\tmov eax," + fourElementType.mArg1.getContent();
		m_code.push_back(Code(0, code));
		code = "\tmov ebx," + fourElementType.mArg2.getContent();
		m_code.push_back(Code(0, code));
		code = "\tcmp eax,ebx";
		m_code.push_back(Code(0, code));
		code = "\tjne @line_" + to_string(fourElementType.mResult.mNumber);
		m_code.push_back(Code(0, code));
		break;
	}
	case Jump_Is_Equal:		//	( j= , a , b ,line_no )
	{
		string code = "";
		// mov eax,a
		// mov ebx,b
		// cmp eax,ebx
		// je @line_[line_no]
		code = "\tmov eax," + fourElementType.mArg1.getContent();
		m_code.push_back(Code(0, code));
		code = "\tmov ebx," + fourElementType.mArg2.getContent();
		m_code.push_back(Code(0, code));
		code = "\tcmp eax,ebx";
		m_code.push_back(Code(0, code));
		code = "\tje @line_" + to_string(fourElementType.mResult.mNumber);
		m_code.push_back(Code(0, code));
		break;
	}
	case Jump_Not_Zero:	//( jnz , a , _ , line_no )
	{
		string code = "";
		// mov eax,a
		// cmp eax,0
		// jne @line_[line_no]
		code = "\tmov eax," + fourElementType.mArg1.getContent();
		m_code.push_back(Code(0, code));
		code = "\tcmp eax,0";
		m_code.push_back(Code(0, code));
		code = "\tjne @line_" + to_string(fourElementType.mResult.mNumber);
		m_code.push_back(Code(0, code));
		break;
	}
	case Equal:		//	( = , a , _ ,result )
	{
		string code = "";
		// mov eax,a
		// mov result,eax
		code = "\tmov eax," + fourElementType.mArg1.getContent();
		m_code.push_back(Code(0, code));
		code = "\tmov " + fourElementType.mResult.getContent() + ",eax";
		m_code.push_back(Code(0, code));
		break;
	}
	case Sys:	//	( sys , _ , _ ,_ )
	{
		m_code.push_back(Code(0, "\tinvoke ExitProcess,NULL"));
		break;
	}
	case Print:	// ( print , string , _ , _ )
	{
		//String 用户定义变量 临时变量
		if (fourElementType.mArg1.mType == 2)	//用户定义变量
		{
			/*string data = "@String_" + to_string(mPrintStringCount++);
			string code = "\t" + data + " db \'" + fourElementType.mArg1.mPrintString + "\',10,0";
			m_data.push_back(Code1(0, code));*/
			string code = "\tmov eax," + fourElementType.mArg1.mUserIdentifierName + "";
			m_code.push_back(Code(0, code));
			code = "\tinvoke crt_printf,addr @Fmt,eax";
			m_code.push_back(Code(0, code));
		}
		else if (fourElementType.mArg1.mType == 3)	//临时变量
		{
			string code = "\tmov eax," + fourElementType.mArg1.mTempIdentifierName + "";
			m_code.push_back(Code(0, code));
			code = "\tinvoke crt_printf,addr @Fmt,eax";
			m_code.push_back(Code(0, code));
		}
		else
		{
			//@Hello db 'Hello,world', 10, 0
			string data = "@String_" + to_string(mPrintStringCount++);
			string code = "\t" + data + " db \'" + fourElementType.mArg1.mPrintString + "\',10,0";
			m_data.push_back(Code(0, code));
			code = "\tinvoke StdOut,addr " + data;
			m_code.push_back(Code(0, code));
		}
		break;
	}
	default:
		break;
	}
}

void ObjectCodeGeneration_x86::object_schemaDefinition()
{
	mSchemaDefinition.push_back(Code(0, ".386"));	//定义了程序使用的指令集
	mSchemaDefinition.push_back(Code(0, ".model flat,stdcall"));	//工作模式
	mSchemaDefinition.push_back(Code(0, "option casemap:none"));	//格式
}

void ObjectCodeGeneration_x86::object_includeLib()
{
	mSchemaDefinition.push_back(Code(0, "include E:\\masm32\\include\\windows.inc"));
	mSchemaDefinition.push_back(Code(0, "include E:\\masm32\\include\\user32.inc"));
	mSchemaDefinition.push_back(Code(0, "includelib E:\\masm32\\lib\\user32.lib"));
	mSchemaDefinition.push_back(Code(0, "include E:\\masm32\\include\\kernel32.inc"));
	mSchemaDefinition.push_back(Code(0, "includelib E:\\masm32\\lib\\kernel32.lib"));
	mSchemaDefinition.push_back(Code(0, "include E:\\masm32\\include\\masm32.inc"));
	mSchemaDefinition.push_back(Code(0, "includelib E:\\masm32\\lib\\masm32.lib"));
	mSchemaDefinition.push_back(Code(0, "include E:\\masm32\\include\\msvcrt.inc"));
	mSchemaDefinition.push_back(Code(0, "includelib E:\\masm32\\lib\\msvcrt.lib"));
}

void ObjectCodeGeneration_x86::runObjectCodeGeneration_x86(SemanticAnalysis semantic)
{
	object_schemaDefinition();	//模式定义
	object_includeLib();		// include lib
	m_data.push_back(Code(0, ".data"));	// data
	m_data.push_back(Code(0, "\tid1 dd 20"));
	m_data.push_back(Code(0, "\t@Fmt db \"%d\",10,0"));
	m_code.push_back(Code(0, ".code"));	// code
	m_code.push_back(Code(0, "start:"));

	////分析 mVariableDefinitionList
	// 所有的变量都使用 dd 数据类型
	// 四字节 doubleword dd
	list<VariableDefinition>::iterator it_mVDL = semantic.mVariableDefinitionList.begin();
	for (; it_mVDL != semantic.mVariableDefinitionList.end(); it_mVDL++)
	{
		list<VariableList>::iterator it_mVLL = (*it_mVDL).variableList.begin();
		for (; it_mVLL != (*it_mVDL).variableList.end(); it_mVLL++)
		{
			string code = "\t" + (*it_mVLL).varName + " dd ?";
			m_data.push_back(Code(0, code));
		}
	}
	//分析 mTempIdentifierList
	list<FourElementTypeItem>::iterator it_mTIL = semantic.mTempIdentifierList.begin();
	for (; it_mTIL != semantic.mTempIdentifierList.end(); it_mTIL++)
	{
		string code = "\t" + (*it_mTIL).mTempIdentifierName + " dd ?";
		m_data.push_back(Code(0, code));
	}
	//分析 mFETL
	list<FourElementType>::iterator it = semantic.mFourElementTypeList.begin();
	for (; it != semantic.mFourElementTypeList.end(); it++)
	{
		if ((*it).mOptimizationType != 1)//没有被删除
		{
			object_analysisFourElementType((*it));
		}
	}
	//m_code.push_back(Code1(0, "\tinvoke StdOut,addr @Hello"));
	//m_code.push_back(Code1(0, "\tinvoke ExitProcess,NULL"));
	m_code.push_back(Code(0, "end start"));
	//汇编代码保存在文件中
	outFile("analysis\\object");
}

void ObjectCodeGeneration_x86::outFile(string fileName)
{
	ofstream outFile(fileName + ".asm");
	list<Code>::iterator it = this->mSchemaDefinition.begin();
	for (; it != this->mSchemaDefinition.end(); it++)	//模式定义
	{
		outFile << (*it).line << endl;
	}
	it = this->mIncludeLib.begin();
	for (; it != this->mIncludeLib.end(); it++)	// include lib
	{
		outFile << (*it).line << endl;
	}
	it = this->m_data.begin();
	for (; it != this->m_data.end(); it++)	// data
	{
		outFile << (*it).line << endl;
	}
	it = this->m_code.begin();
	for (; it != this->m_code.end(); it++)	// code
	{
		outFile << (*it).line << endl;
	}
}

void ObjectCodeGeneration_x86::compiler()
{
	system("script\\compiler_link.bat");
}

void ObjectCodeGeneration_x86::run()
{
	system("script\\run.bat temp\\miniC");
}
