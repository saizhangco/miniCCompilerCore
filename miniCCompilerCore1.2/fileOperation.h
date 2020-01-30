#pragma once
/**
* �����ռ�: None
*
* �� �ܣ� �ļ�������
* �� ���� FileOperation
*
* Ver  2016-06-10  ����  �����ļ������࣬�򿪡��رա���д�ļ�
* ����������������������������������������������������������������������
* V0.02 2016-06-10 ���� 2��
*
* Copyright (c) 2015 Lir Corporation. All rights reserved.
*������������������������������������������������������������������������
*�����˼�����ϢΪ����˾������Ϣ��δ������˾����ͬ���ֹ���������¶������
*������Ȩ���У�*****���޹�˾ ������              ������������������������
*������������������������������������������������������������������������
*/
#include <iostream>
#include <fstream>
using namespace std;
template <class T>
class FileOperation
{
private:
	string mFileName;
	ofstream fout;
	ifstream fin;
	bool readLock;
	bool writeLock;
public:
	FileOperation();
	~FileOperation();
	void writeToFile(T& t);
	void readFromFile(T& t);
	bool openFile(const string& fileName);
	void closeFile();
	bool is_eof();
};

template<class T>
FileOperation<T>::FileOperation()
{
	fout.clear();
	fin.clear();
	readLock = false;
	writeLock = false;
}

template <class T>
FileOperation<T>::~FileOperation()
{

}

//�����ݽṹд���ļ�
template<class T>
void FileOperation<T>::writeToFile(T& t)
{
	// �ж��Ƿ����ڶ�ȡ�ļ�����
	if (readLock)
	{
		cout << mFileName << " is reading!" << endl;
	}
	writeLock = true;
	int count = 0;
	count = sizeof(t);
	fout.write((char*)&count, sizeof(int));
	fout.write((char*)&t, count);
}

template<class T>
void FileOperation<T>::readFromFile(T& t)
{
	// �ж��Ƿ�����д���ļ�����
	if (writeLock)
	{
		cout << mFileName << " is writing!" << endl;
	}
	readLock = true;
	int count = 0;
	fin.read((char*)&count, sizeof(int));
	fin.read((char*)&t, count);
}

// true ���ļ��ɹ�
// false ���ļ�ʧ��
template<class T>
bool FileOperation<T>::openFile(const string & fileName)
{
	mFileName = fileName;
	fout.open(mFileName, ios::binary | ios::app);	//׷��
	if (!fout.is_open())
	{
		cout << "the output stream of " + mFileName + " open failed!" << endl;
		return false;
	}
	fin.open(mFileName, ios::binary);
	if (!fin.is_open())
	{
		cout << "the input stream of " + mFileName + " open failed!" << endl;
		fout.close();	//�ر���һ���򿪵��ļ������
		return false;
	}
	return true;
}

template<class T>
void FileOperation<T>::closeFile()
{
	fout.close();
	fin.close();
	readLock = false;
	writeLock = false;
}

template<class T>
bool FileOperation<T>::is_eof()
{
	return fin.eof();
}