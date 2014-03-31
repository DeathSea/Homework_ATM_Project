/*
数据层（Data Layer）
Designed by DeathSea 2014 Jnu
提供数据初始化与操作
数据的导入导出
*/
#include <iostream>
#include <fstream>
//#include <stdlib.h>
using std::string;using std::ifstream;using std::ofstream;
struct user_info
{
	long CardID;
	string user_name;
	unsigned code_sha1[5];
	//string salt;//原本想加盐的，算了，太复杂不弄了
	long Balance;
	bool Enable;
	user_info * next;
};
struct admin_user
{
	string Admin_name;
	//string salt; //同上
	unsigned code_sha1[5];
};
class InitData//初始化数据
{
public:
	user_info user_info;//以struct 类型数组实现存放
	admin_user admin_info;
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
	//void WriteDataFile((struct *)user_info);
	void InsertDataBase();
};
class ReadData
{
public:
	struct user_info * ReadUserDataFile(ifstream File);
	void ExecuteDataBase();
};
//class OperaData
//{
//public:
//    void ReadDataInfo();
//	void QueryDatabase();
//	void ChangDataInfo();
//	void AlterDataBase();
//};
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