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
#include <vector>
using std::string;using std::ifstream;using std::ofstream;using std::vector;

class InitData//初始化数据
{
public:
	//user_info user_HEAD;//以struct 类型数组实现存放
	//admin_user admin_HEAD;
	InitData();
	~InitData();
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
	void AddUser(const long &id,const string &name,unsigned *code_sha1,const float &balance);
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
private:
	WriteData WD;
public:
    bool ReadDataInfo(long card_id,unsigned * sha1);//读取用户密码的sha1值
	bool ReadDataInfo(string admin_name,unsigned * sha1);//读取admin密码的sha1值
	bool ReadDataInfo(long card_id);//读取用户是否锁定
	void ReadDataInfo(const long &id,float &balance);
	void ReadDataInfo(const long &id,string &name);//通过id读用户名
	void ReadDataInfo(vector<long> &id_list);
	bool ReadDataInfo(const string &name,long &id);//通过用户名读id
	//void QueryDatabase();
	void ChangDataInfo(long card_id,bool enable);//使用户账户禁用/可用
	void ChangDataInfo(long &id,float money,bool I_or_O);//1为进（存），0为出（取）
	void ChangDataInfo(long &id,unsigned * sha1);
	//void AlterDataBase();
};
class ImportData
{
private:
	void ReadFile(const string &filename);
};
class ExportData :pulic ReadFile
{
private:
	WriteData WD;
	void ReadFile(const string &filename);
};
#endif