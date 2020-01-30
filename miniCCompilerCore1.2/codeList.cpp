#include "codeList.h"

CodeList::CodeList()
{
	this->codeList.clear();	//���List�е�����
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
	ofstream outFile(fileName);//������� "code.txt"
	//outFile.open(fileName, ios::out, 0); //ios::out �ڴ�����������ļ�
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
	pFile = fopen(fileName.data(), "r");//���ļ�
	char c, temp[1024];//���λ�õ�1024��Ҫ���ǣ���Ҫ��ȡ���ַ�������1024ʱ��δ���
	temp[0] = '\0';
	int count = 0;
	int lineNo = 1;
	while ((c = fgetc(pFile)) != EOF)//���ļ����ζ�ȡ�ַ�
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
			codeList.push_back(code);	//�����ݼ��뵽List��
			count = 0;
		}
	}
	temp[count++] = '\0';
	Code code(lineNo++, temp);
	codeList.push_back(code);	//�����ݼ��뵽List��
								//�����һ�е�������ӵ�pCode��
	fclose(pFile);//�ر��ļ�
	return result;
}