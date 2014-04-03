#include "Data.h"
#include "sha1.h"
InitData::InitData()
{
	OpenData OpenData;
	ReadData ReadData;
	user_HEAD.next = NULL;
	ifstream UserDataFile = OpenData.OpenUserDataFile();
	ReadData.ReadUserDataFile(UserDataFile,&user_HEAD);
	ifstream AdminDataFile = OpenData.OpenAdminDataFile();
	ReadData.ReadAdminDataFile(AdminDataFile,&admin_HEAD);
}
ifstream OpenData::OpenUserDataFile()
{
	WriteData WriteData;
	ifstream user_database(UserDataFileName);
	if((!user_database.is_open()))
	{
		std::cout << "未找到用户数据库文件，将重新建立"<<std::endl<<"联系前台以建立新账户"<<std::endl;
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
		std::cout << "未找到管理员数据库文件，程序发生严重错误"<<std::endl<< "联系程序员以解决" <<std::endl;
		WriteData.WriteDataFile(AdminDataFileName);
    	ifstream admin_database(AdminDataFileName);
		exit(8210);
	}
	return admin_database;
}

void WriteData::WriteDataFile(const string FileName)
{
	ofstream temp_file(FileName);
	temp_file.close();
}

void ReadData::ReadUserDataFile(ifstream &File,struct user_info * p)
{
	if (File)
	{
		while(!File.eof())
		{
    		File >> p->CardID 
			>> p->user_name 
			>> hex >> p->code_sha1[0] 
			>> p->code_sha1[1] 
			>> p->code_sha1[2] 
			>> p->code_sha1[3] 
			>> p->code_sha1[4] 
			>> p->Balance 
			>> p->Enable;
            p->next = new struct user_info;
			p = p->next;
			p->next = NULL;
		}
		File.close();
	}
}

void ReadData::ReadAdminDataFile(ifstream &File,struct admin_user *p)
{
	if (File)
	{
		if(!File.eof())
		{
    		File >>  p->Admin_name
			>> hex >> p->code_sha1[0] 
			>> p->code_sha1[1] 
			>> p->code_sha1[2] 
			>> p->code_sha1[3] 
			>> p->code_sha1[4] ;
		}
		File.close();
	}
}