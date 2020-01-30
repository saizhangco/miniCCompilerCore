#include "codeList.h"

CodeList::CodeList()
{
	this->codeList.clear();	//清空List中的内容
}

CodeList::CodeList(const string & fileName)
{
	readCodeListFromFile(fileName);
}

CodeList::~CodeList()
{
}

void CodeList::printCodeList()
{
	list<Code>::iterator it_code;
	for (it_code = codeList.begin(); it_code != codeList.end(); it_code++)
	{
		cout << (*it_code).no << "\t" << (*it_code).line << endl;
	}
}

bool CodeList::saveCodeListToFile(const string& fileName)
{
	list<Code>::iterator it_code;
	bool result = true;
	ofstream outFile(fileName);//打开输出流 "code.txt"
	//outFile.open(fileName, ios::out, 0); //ios::out 内存数据输出到文件
	for (it_code = codeList.begin(); it_code != codeList.end(); it_code++)
	{
		outFile << (*it_code).no << " " << (*it_code).line << endl;
	}
	outFile.close();
	return result;

}

bool CodeList::readCodeListFromFile(const string& fileName)
{
	bool result = true;
	FILE* pFile;
	pFile = fopen(fileName.data(), "r");//打开文件
	char c, temp[1024];//这个位置的1024需要考虑，当要读取的字符串超过1024时如何处理
	temp[0] = '\0';
	int count = 0;
	int lineNo = 1;
	while ((c = fgetc(pFile)) != EOF)//从文件依次读取字符
	{
		if (c != '\n')
		{
			temp[count++] = c;
		}
		else
		{
			temp[count++] = '\0';
			//addCodeToLinks(head, newCode(lineNo++, (const char*)temp));
			Code code(lineNo++, temp);
			codeList.push_back(code);	//将数据加入到List中
			count = 0;
		}
	}
	temp[count++] = '\0';
	Code code(lineNo++, temp);
	codeList.push_back(code);	//将数据加入到List中
								//将最后一行的数据添加到pCode中
	fclose(pFile);//关闭文件
	return result;
}