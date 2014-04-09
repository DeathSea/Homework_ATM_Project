#include "control.h"
#include "helper.h"

void Start::start()
{
	ATM ATM;Admin Admin;
	enum Menu {MainMenu,ATMMenu,AdminMenu};
	unsigned int Menu_length = 0;
	unsigned int Choice      = 0;
	bool login=false,ATM_login = false,admin_login = false;
	Choice = Start::make_choice(MainMenu);
	switch(Choice)
	{
	case (0):
		ATM_login = ATM.Login();
		break;
	case(1):
		admin_login = Admin.Login();
		break;
	default:
		OutputText.Prompt("未知选项！");
		exit(1365);
	}
	if(ATM_login){Choice = Start::make_choice(ATMMenu);}
	if(admin_login){Choice = Start::make_choice(AdminMenu);}
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
		if(try_time == 2)
		{
			OutputText.Prompt("尝试次数超过三次！");
			Start.start();
			return false;
			break;
		}
	}
	if(!OperaData.ReadDataInfo(card_id)){OutputText.Prompt("账号已锁定，请联系管理员");return false;}
	try_time = 0;
	OutputText.Code();
	InputText.Code(code);
	while(!helper.check(code,database_sha1))
	{
		OutputText.Prompt("密码错误");
		try_time ++;
		OutputText.Code();
		InputText.Code(code);
		if (try_time==2)
		{
			OutputText.Prompt("尝试次数超过三次，账号已锁定，到后台解决吧少年！");
			OperaData.ChangDataInfo(card_id,false);//账号锁定
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
		if(try_time == 2)
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
		if (try_time==2)
		{
			OutputText.Prompt("密码输入三次错误！，程序即将退出");
			exit(5923);
			return false;
			break;
		}
	}
	return true;
}
unsigned Start::make_choice(unsigned Menu)
{
	unsigned int Menu_length = 0;
	unsigned int Choice      = 0;
	Menu_length = OutputText.Menu(Menu);
	try
	{
		Choice      = InputText.Choice(Menu_length);
	}
	catch(std::out_of_range err)
	{
		std::cout<< err.what() << std::endl << "程序即将退出" << std::endl;
		exit(1538);
	}
	return Choice;
}