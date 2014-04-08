#include "control.h"
#include "helper.h"

void Start::start()
{
	OutputText OutputText;
	InputText  InputText;
	ATM ATM;Admin Admin;
	enum Menu {MainMenu,ATMMenu,AdminMenu};
	unsigned int Menu_length = 0;
	unsigned int Choice      = 0;
	bool login=false;
	Menu_length = OutputText.Menu(MainMenu);
	try
	{
		Choice      = InputText.Choice(Menu_length);
	}
	catch(std::out_of_range err)
	{
		std::cout<< err.what() << std::endl << "程序即将退出" << std::endl;
		exit(1538);
	}
	switch(Choice)
	{
	case (0):
		login = ATM.Login();
		if(login){
			Menu_length = OutputText.Menu(ATMMenu);}
		break;
	case(1):
		login = Admin.Login();
		OutputText.Menu(AdminMenu);
		break;
	}

}
bool ATM::Login(void)
{
	long card_id;
	char code[255] = {'\0'};
	unsigned database_sha1[5],try_time = 0;
	helper helper;
	OutputText.CardID();
	InputText.CardID(&card_id);
	while(!OperaData.ReadDataInfo(card_id,database_sha1))
	{
		OutputText.Prompt("卡号未找到，请检查一遍");
		try_time++;
	    OutputText.CardID();
	    InputText.CardID(&card_id);
		if(try_time == 3)
		{
			OutputText.Prompt("尝试次数超过三次！");
			Start.start();
			return false;
			break;
		}
	}
	try_time = 0;
	OutputText.Code();
	InputText.Code(code);
	while(!helper.check(code,database_sha1))
	{
		OutputText.Prompt("密码错误");
		try_time ++;
		OutputText.Code();
		InputText.Code(code);
		if (try_time==3)
		{
			OutputText.Prompt("尝试次数超过三次，账号已锁定，到后台解决吧少年！");
			//账号锁定
			Start.start();
			return false;
			break;
		}
	}
		return true;
}
bool Admin::Login(void)
{
	string name;
	char code[255] = {'\0'};
	unsigned database_sha1[5],try_time = 0;
	helper helper;
	OutputText.AdminName();
	InputText.AdminName(&name);
	while(!OperaData.ReadDataInfo(name,database_sha1))
	{
		OutputText.Prompt("用户名错误");
		try_time ++;
		OutputText.AdminName();
		InputText.AdminName(&name);
		if(try_time == 3)
		{
			OutputText.Prompt("输入三次错误！程序即将退出");
			exit(5921);
			return false;
			break;
		}
	}
	try_time = 0;
	OutputText.Code();
	InputText.Code(code);
	while(!helper.check(code,database_sha1))
	{
		OutputText.Prompt("密码错误！");
		try_time++;
		OutputText.Code();
		InputText.Code(code);
		if (try_time==3)
		{
			OutputText.Prompt("密码输入三次错误！，程序即将退出");
			exit(5923);
			return false;
			break;
		}
	}
	return true;
}