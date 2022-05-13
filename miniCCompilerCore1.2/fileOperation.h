#pragma once
/**
* 命名空间: None
*
* 功 能： 文件操作类
* 类 名： FileOperation
*
* Ver  2016-06-10  张赛  定义文件操作类，打开、关闭、读写文件
* ───────────────────────────────────
* V0.02 2016-06-10 张赛 2版
*
* Copyright (c) 2015 Lir Corporation. All rights reserved.
*┌──────────────────────────────────┐
*│　此技术信息为本公司机密信息，未经本公司书面同意禁止向第三方披露．　│
*│　版权所有：*****有限公司 　　　              　　　　　　　　　　　│
*└──────────────────────────────────┘
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

//将数据结构写入文件
template<class T>
void FileOperation<T>::writeToFile(T& t)
{
	// 判断是否正在读取文件内容
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
	// 判断是否正在写入文件内容
	if (writeLock)
	{
		cout << mFileName << " is writing!" << endl;
	}
	readLock = true;
	int count = 0;
	fin.read((char*)&count, sizeof(int));
	fin.read((char*)&t, count);
}

// true 打开文件成功
// false 打开文件失败
template<class T>
bool FileOperation<T>::openFile(const string & fileName)
{
	mFileName = fileName;
	fout.open(mFileName, ios::binary | ios::app);	//追加
	if (!fout.is_open())
	{
		cout << "the output stream of " + mFileName + " open failed!" << endl;
		return false;
	}
	fin.open(mFileName, ios::binary);
	if (!fin.is_open())
	{
		cout << "the input stream of " + mFileName + " open failed!" << endl;
		fout.close();	//关闭上一步打开的文件输出流
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
