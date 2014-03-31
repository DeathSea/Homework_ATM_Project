#include "Data.h"
#include "sha1.h"
InitData::InitData()
{
	OpenData OpenData;
	ReadData ReadData;
	ifstream UserDataFile = OpenData.OpenUserDataFile();
	ReadData.ReadUserDataFile(UserDataFile);
}
ifstream OpenData::OpenUserDataFile()
{
	WriteData WriteData;
	ifstream user_database(UserDataFileName);
	if((!user_database.is_open()))
	{
		WriteData.WriteDataFile(UserDataFileName);
    	ifstream user_database(UserDataFileName);
	}
	return user_database;
}
ifstream OpenData::OpenAdminDataFile()
{
	WriteData WriteData;
	ifstream admin_database(AdminDataFileName);
	if((!admin_database.is_open()))
	{
		WriteData.WriteDataFile(AdminDataFileName);
    	ifstream admin_database(AdminDataFileName);
	}
	return admin_database;
}

void WriteData::WriteDataFile(const string FileName)
{
	ofstream temp_file(FileName);
	temp_file.close();
}

struct user_info * ReadData::ReadUserDataFile(ifstream File)
{
	//File.getline()
}