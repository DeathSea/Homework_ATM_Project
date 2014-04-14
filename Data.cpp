#include "Data.h"
#include "sha1.h"
struct user_info
{
	long CardID;
	string user_name;
	unsigned code_sha1[5];
	//string salt;//原本想加盐的，算了，太复杂不弄了
	float Balance;
	bool Enable;
	user_info * next;
} user_HEAD;
struct admin_user
{
	string Admin_name;
	//string salt; //同上
	unsigned code_sha1[5];
} admin_HEAD;
InitData::InitData()
{
	OpenData OpenData;
	ReadData ReadData;
	user_HEAD.next = NULL;
	ifstream UserDataFile = OpenData.OpenUserDataFile();
	ReadData.ReadDataFile(UserDataFile,&user_HEAD);
	ifstream AdminDataFile = OpenData.OpenAdminDataFile();
	ReadData.ReadDataFile(AdminDataFile,&admin_HEAD);
}
InitData::~InitData()
{
	WriteData WriteData;
	WriteData.WriteDataFile(&admin_HEAD);
	WriteData.WriteDataFile(&user_HEAD);
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

void WriteData::WriteDataFile(struct admin_user *p)
{
	ofstream tp_file("admin_database.txt");
	if(tp_file)
	{
		tp_file << p->Admin_name
		<< " " << std::hex << p->code_sha1[0] 
		<< " " << p->code_sha1[1] 
		<< " " << p->code_sha1[2]
		<< " " << p->code_sha1[3] 
		<< " " << p->code_sha1[4]
		<< std::dec
			<< std::endl;
	}
}
void WriteData::WriteDataFile(struct user_info *p)
{
	ofstream tp_file("user_database.txt");
	if(tp_file)
	{
		while (p->next->next !=NULL)
		{
			tp_file << p->CardID
			<< " " << p->user_name 
			<< " " << std::hex << p->code_sha1[0] 
			<< " " << p->code_sha1[1] 
			<< " " << p->code_sha1[2]
			<< " " << p->code_sha1[3] 
			<< " " << p->code_sha1[4]
			<< std::dec
			<< " " << p->Balance
			<< " " << p->Enable
			<< std::endl;
			p = p->next;
		}
	}
}
void ReadData::ReadDataFile(ifstream &File,struct user_info * p)
{
	if (File)
	{
		while(!File.eof())
		{
    		File >> p->CardID 
			>> p->user_name 
			>> std::hex >> p->code_sha1[0] 
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

void ReadData::ReadDataFile(ifstream &File,struct admin_user *p)
{
	if (File)
	{
		if(!File.eof())
		{
    		File >>  p->Admin_name
			>> std::hex >> p->code_sha1[0] 
			>> p->code_sha1[1] 
			>> p->code_sha1[2] 
			>> p->code_sha1[3] 
			>> p->code_sha1[4] ;
		}
		File.close();
	}
}
bool OperaData::ReadDataInfo(long card_id,unsigned * sha1)
{
	struct user_info *p;
	p = &user_HEAD;
	while(p->next != NULL)
	{
		if (p->CardID == card_id)
		{
			sha1[0] = p->code_sha1[0];
			sha1[1] = p->code_sha1[1];
			sha1[2] = p->code_sha1[2];
			sha1[3] = p->code_sha1[3];
			sha1[4] = p->code_sha1[4];
			return true;
		}
		p = p->next;
	}
	return false;
}
bool OperaData::ReadDataInfo(string admin_name,unsigned * sha1)
{
	struct admin_user * p;
	p = &admin_HEAD;
	if(p->Admin_name == admin_name)
	{
		sha1[0] = p->code_sha1[0];
		sha1[1] = p->code_sha1[1];
		sha1[2] = p->code_sha1[2];
		sha1[3] = p->code_sha1[3];
		sha1[4] = p->code_sha1[4];
		return true;
	}
	return false;
}
bool OperaData::ReadDataInfo(long card_id)
{
	struct user_info *p;
	p = &user_HEAD;
	while(p->next != NULL)
	{
		if (p->CardID == card_id)
		{
			return p->Enable;
		}
		p = p->next;
	}
}
void OperaData::ChangDataInfo(long card_id,bool enable)
{
	struct user_info *p;
	p = &user_HEAD;
	while(p->next != NULL)
	{
		if (p->CardID == card_id)
		{
			p->Enable = enable;
		}
		p = p->next;
	}
	WD.WriteDataFile(&user_HEAD);
}
void OperaData::ChangDataInfo(long &id,float money,bool I_or_O)
{
	struct user_info *p;
	p = &user_HEAD;
	if(I_or_O == false)
	{
		while(p->next != NULL)
		{
			if (p->CardID == id)
			{
				p->Balance -= money;
			}
			p = p->next;
		}
	}
	else
	{
		while(p->next != NULL)
		{
			if (p->CardID == id)
			{
				p->Balance += money;
			}
			p = p->next;
		}
	}
	WD.WriteDataFile(&user_HEAD);
}
void OperaData::ReadDataInfo(const long &id,float &balance)
{
	struct user_info *p;
	p = &user_HEAD;
	while(p->next != NULL)
	{
		if (p->CardID == id)
		{
			balance = p->Balance;
		}
		p = p->next;
	}
}
void OperaData::ReadDataInfo(const long &id,string &name)
{
	struct user_info *p;
	p = &user_HEAD;
	while(p->next != NULL)
	{
		if (p->CardID == id)
		{
			name = p->user_name;
		}
		p = p->next;
	}
}
void OperaData::ChangDataInfo(long &id,unsigned * sha1)
{
	struct user_info *p;
	p = &user_HEAD;
	while(p->next != NULL)
	{
		if (p->CardID == id)
		{
			p->code_sha1[0] = sha1[0];
			p->code_sha1[1] = sha1[1];
			p->code_sha1[2] = sha1[2];
			p->code_sha1[3] = sha1[3];
			p->code_sha1[4] = sha1[4];
		}
		p = p->next;
	}
	WD.WriteDataFile(&user_HEAD);
}
void OperaData::ReadDataInfo(vector<long> &id_list)
{
	struct user_info *p = &user_HEAD;
	while(p->next->next != NULL)
	{
		id_list.push_back(p->CardID);
		p = p->next;
	}
}
bool OperaData::ReadDataInfo(const string &name,long &id)
{
	struct user_info *p = &user_HEAD;
	while(p->next->next!=NULL)
	{
		if(p->user_name == name)
		{
			id = p->CardID;
			return true;
		}
	}
	return false;
}
void WriteData::AddUser(const long &id,const string &name,unsigned * code_sha1,const float &balance)
{
	struct user_info *p = &user_HEAD;
	while(p!=NULL){p = p->next;}
	p ->CardID = id;
	p ->user_name = name;
	p->code_sha1[0] = code_sha1[0];
	p->code_sha1[1] = code_sha1[1];
	p->code_sha1[2] = code_sha1[2];
	p->code_sha1[3] = code_sha1[3];
	p->code_sha1[4] = code_sha1[4];
	p->Balance = balance;
	p->Enable = true;
}