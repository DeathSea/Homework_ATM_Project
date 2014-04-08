/*
数据层（Data Layer）
Designed by DeathSea 2014 Jnu
提供数据初始化与操作
数据的导入导出
*/
#ifndef DATA_HEAD
#define DATA_HEAD
#include <iostream>
#include <fstream>
#include <string>
using std::string;using std::ifstream;using std::ofstream;

class InitData//初始化数据
{
public:
	//user_info user_HEAD;//以struct 类型数组实现存放
	//admin_user admin_HEAD;
	InitData();
	//~InitData();
};
class OpenData
{
public:
	const string UserDataFileName;
	const string AdminDataFileName;
	ifstream OpenUserDataFile();//打开数据文件，返回文件流
	ifstream OpenAdminDataFile();
	void LinkDataBase();
	OpenData():UserDataFileName("user_database.txt"),AdminDataFileName("admin_database.txt"){}
};
class WriteData
{
public:
	void WriteDataFile(const string);
	void WriteDataFile(struct admin_user *p);
	void WriteDataFile(struct user_info *p);
	void InsertDataBase();
};
class ReadData
{
public:
	void ReadDataFile(ifstream &File,struct user_info * p);
	void ReadDataFile(ifstream &File,struct admin_user * p);
	void ExecuteDataBase();
};
class OperaData
{
public:
    bool ReadDataInfo(long card_id,unsigned * sha1);
	bool ReadDataInfo(string admin_name,unsigned * sha1);
	//void QueryDatabase();
	//void ChangDataInfo(long card_id,const char);
	//void AlterDataBase();
};
//class ImportData
//{
//private:
//	void ReadFile();
//};
//class ExportData
//{
//private:
//	void WirteData();
//};
#endif