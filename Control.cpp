#include "control.h"

void Start::start()
{
	ATM ATM;Admin Admin;
	enum Menu {MainMenu,ATMMenu,AdminMenu};
	unsigned int Menu_length = 0;
	unsigned int Choice = 0;
	bool login=false,ATM_login = false,admin_login = false;
	long id = -1;
	Choice = Start::make_choice(MainMenu);
	switch(Choice)
	{
	case (0):
		ATM_login = ATM.Login(id);
		break;
	case(1):
		admin_login = Admin.Login();
		break;
	case(2):
		exit(0);
	default:
		OutputText.Prompt("未知选项！");
		exit(1365);
	}
	if(ATM_login)
	{
		Start::ATM_choice(id);
	}
	if(admin_login)
	{
		Start::Admin_choice();
	}
}
void Start::ATM_choice(long &id)
{
	ATM ATM;
	unsigned int Choice      = 0;
	Choice = Start::make_choice(1);
	switch(Choice)
	{
	case(0):
		ATM.UserBalance(id);
		Start::ATM_choice(id);
		break;
	case(1):
		ATM.Withdrawal(id,false);
		Start::ATM_choice(id);
		break;
	case(2):
		ATM.Deposit(id,false);
		Start::ATM_choice(id);
		break;
	case(3):
		ATM.Transfer(id);
		Start::ATM_choice(id);
		break;
	case(4):
		ATM.ChangeCode();
		Start::ATM_choice(id);
		break;
	case(5):
		Start::start();
	default:
		OutputText.Prompt("未知选项！");
		exit(1365);
	}
}
void Start::Admin_choice()
{
	Admin Admin;
	unsigned int Choice      = 0;
	long id = 0;
	Choice = Start::make_choice(2);
	switch(Choice)
	{
	case(0):
		Admin.AddUser();
		Start::Admin_choice();
		break;
	case(1):
		break;
	case(2):
		break;
	case(3):
		Admin.InquiryAllUserInfo();
		Start::Admin_choice();
		break;
	case(4):
		Admin.InquiryNominatedUserInfo();
		Start::Admin_choice();
		break;
	case(5):
		if(Admin.GetID(id))
		{
			Admin.Withdrawal(id,true);
		}
		Start::Admin_choice();
		break;
	case(6):
		if(Admin.GetID(id))
		{
			Admin.Deposit(id,true);
		}
		Start::Admin_choice();
		break;
	case(7):
		if(Admin.GetID(id))
		{
			Admin.ChangeCode(id);
		}
		Start::Admin_choice();
		break;
	case(8):
		Start::start();
	default:
		OutputText.Prompt("未知选项！");
		exit(1365);
	}
}
bool ATM::Login(long &id)
{
	long card_id;
	char code[255] = {'\0'};
	unsigned database_sha1[5],try_time = 0;
	OutputText.CardID();
	InputText.CardID(&card_id);
	while(!OperaData.ReadDataInfo(card_id,database_sha1))
	{
		OutputText.Prompt("卡号未找到，请检查一遍");
		try_time++;
		if(try_time == 3)
		{
			OutputText.Prompt("尝试次数超过三次！");
			Start.start();
			return false;
			break;
		}
	    OutputText.CardID();
	    InputText.CardID(&card_id);
	}
	if(!OperaData.ReadDataInfo(card_id)){OutputText.Prompt("账号已锁定，请联系管理员");return false;}
	id = card_id;
	try_time = 0;
	OutputText.Code();
	InputText.Code(code);
	while(!helper.check(code,database_sha1))
	{
		OutputText.Prompt("密码错误");
		try_time ++;
		if (try_time==3)
		{
			OutputText.Prompt("尝试次数超过三次，账号已锁定，到后台解决吧少年！");
			OperaData.ChangDataInfo(card_id,false);//账号锁定
			Start.start();
			return false;
			break;
		}
		OutputText.Code();
		InputText.Code(code);
	}
		return true;
}
bool Admin::Login(void)
{
	string name;
	char code[255] = {'\0'};
	unsigned database_sha1[5],try_time = 0;
	OutputText.AdminName();
	InputText.AdminName(&name);
	while(!OperaData.ReadDataInfo(name,database_sha1))
	{
		OutputText.Prompt("用户名错误");
		try_time ++;
		if(try_time == 3)
		{
			OutputText.Prompt("输入三次错误！程序即将退出");
			exit(5921);
			return false;
			break;
		}
		OutputText.AdminName();
		InputText.AdminName(&name);
	}
	try_time = 0;
	OutputText.Code();
	InputText.Code(code);
	while(!helper.check(code,database_sha1))
	{
		OutputText.Prompt("密码错误！");
		try_time++;
		if (try_time==3)
		{
			OutputText.Prompt("密码输入三次错误！，程序即将退出");
			exit(5923);
			return false;
			break;
		}
		OutputText.Code();
		InputText.Code(code);
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
void ATM::UserBalance(long &id)
{
	float balance = 0;
	OperaData.ReadDataInfo(id,balance);
	OutputText.Prompt("你的余额为:");
	OutputText.Prompt(balance);
}
void ATM::Withdrawal(long &id,bool Admin_or_not)
{
	if(!OperaData.ReadDataInfo(id)){OutputText.Prompt("账号已被锁定，请联系管理员!");return ;}
	float money=0;
	if(!Admin_or_not){OutputText.Prompt("注意：取款只支持整百取款");}
	OutputText.Confirm("取款");
	bool Yes_or_No = InputText.Confirm();
    float balance = 0;
	if (!Yes_or_No){return ;}
	else
	{
		OutputText.Money();
		try
		{		
			if(!Admin_or_not){int m = (int)money;InputText.Money(m);}
			else{InputText.Money(money);}
			OperaData.ReadDataInfo(id,balance);
		}
		catch(std::runtime_error err)
		{
			std::cout << err.what() << std::endl;
			return;
		}
		if(balance > money)
		{
			OperaData.ChangDataInfo(id,money,0);
			std::cout<<"这是你的"<<money<<"元整，请拿好"<<std::endl;
		}
		else{OutputText.Prompt("余额不足！");}
	}
}
void ATM::Deposit(long &id,bool Admin_or_not)
{
	if(!OperaData.ReadDataInfo(id)){OutputText.Prompt("账号已被锁定，请联系管理员!");return ;}
	float money=0;
	if(!Admin_or_not){OutputText.Prompt("注意：存款只支持整百！");}
	OutputText.Money();
	try
	{
		if(!Admin_or_not){int m = (int)money;InputText.Money(m);}
		else{InputText.Money(money);}
	}
	catch(std::runtime_error err)
	{
		std::cout << err.what() << std::endl;
		return;
	}
	OperaData.ChangDataInfo(id,money,1);
	std::cout<<"已存入"<<money<<"元整"<<std::endl;
}
void ATM::Transfer(long &id)
{
	if(!OperaData.ReadDataInfo(id)){OutputText.Prompt("账号已被锁定，请联系管理员!");return ;}
    float money = 0,balance = 0;
	long target_id = 0;
	unsigned s[5];
	OutputText.Confirm("转账");
	if(!InputText.Confirm()){return;};
	OutputText.Prompt("请输入对方卡号");
	InputText.CardID(&target_id);
	if(!OperaData.ReadDataInfo(target_id,s))
	{
		OutputText.Prompt("卡号不存在");
		return;
	}
	OutputText.Money();
	InputText.Money(money);
	OperaData.ReadDataInfo(id,balance);
	if (money > balance){OutputText.Prompt("你的余额不足");return;}
	else
	{
		OperaData.ChangDataInfo(id,money,0);
		OperaData.ChangDataInfo(target_id,money,1);
		OutputText.Prompt("转账成功！");
	}
}
void ATM::ChangeCode(){OutputText.Prompt("ATM不支持修改密码的说！");}
bool Admin::GetID(long &id)
{
	if(!OperaData.ReadDataInfo(id)){OutputText.Prompt("账号已被锁定，请先办理黑名单移除业务");return false;}
	unsigned database_sha1[5],try_time = 0;char code[255] = {'\0'};
	long id_tmp;
	OutputText.Prompt("请输入要操作的卡号");
	InputText.CardID(&id_tmp);
	if(!OperaData.ReadDataInfo(id_tmp,database_sha1))
	{
		OutputText.Prompt("卡号未找到请重新确认");
		return false;
	}
	OutputText.Code();
	InputText.Code(code);
	while(!helper.check(code,database_sha1))
	{
		OutputText.Prompt("密码错误！");
		try_time++;
		if (try_time==3)
		{
			return false;
			break;
		}
		OutputText.Code();
		InputText.Code(code);
	}
	id = id_tmp;
	return true;
}
void Admin::ChangeCode(long &id)
{   
	char origin_code[256]={'\0'},first_code_input[256]={'\0'},second_code_input[256]={'\0'};
	unsigned sha1[5],trytime = 0,new_sha[5];bool uncorrect = true;
	OutputText.Confirm("修改密码");
	if(!InputText.Confirm()){return ;}
	OperaData.ReadDataInfo(id,sha1);
	OutputText.Prompt("请输入原密码以再次确认：");
	InputText.Code(origin_code);
	OutputText.Prompt("验证中...请稍候");
	if(!helper.check(origin_code,sha1)){OutputText.Prompt("原密码错误！请再次检查！");return;}
	OutputText.Prompt("输入要修改的密码：");
	InputText.Code(first_code_input);
	OutputText.Prompt("请再次输入密码：");
	InputText.Code(second_code_input);
	while(strlen(first_code_input)!=strlen(second_code_input))
	{
		OutputText.Prompt("两次密码不相同！");
		trytime++;
		if(trytime == 3)
		{
			OutputText.Prompt("尝试超过三次，恶意操作，账号已锁定！");
			OperaData.ChangDataInfo(id,false);
		}
		OutputText.Prompt("输入要修改的密码：");
		InputText.Code(first_code_input);
		OutputText.Prompt("请再次输入密码：");
		InputText.Code(second_code_input);
	} 
	trytime = 0;
	for(int i=0;first_code_input[i]!='\0';i++)
	{
		if(first_code_input[i]!=second_code_input[i])
		{
			OutputText.Prompt("两次密码不相同！");
			return;
		}
	}
	OutputText.Prompt("处理中，请稍候");
	helper.calculate(first_code_input,new_sha);
	OperaData.ChangDataInfo(id,new_sha);
	OutputText.Prompt("修改完成");
	return;
}
void Admin::InquiryAllUserInfo()
{
	vector<long> id_list;
	OperaData.ReadDataInfo(id_list);
	auto list_size = id_list.size();
	decltype(list_size) index = 0;
	string name;float balance;bool enable;
	OutputText.UserInfo();
	for(;index!=list_size;index++)
	{
		OperaData.ReadDataInfo(id_list[index],name);
		OperaData.ReadDataInfo(id_list[index],balance);
		enable = OperaData.ReadDataInfo(id_list[index]);
		OutputText.UserInfo(id_list[index],name,balance,enable);
	}
}
void Admin::InquiryNominatedUserInfo()
{
	int Choice = 0,length = OutputText.Menu(3);
	long id = 0;float balance;bool enable;
	string name;
	Choice = InputText.Choice(length);
	if (Choice == 0)//id方法
	{
		unsigned sha1[5];
		OutputText.CardID();
		InputText.CardID(&id);
		if(!OperaData.ReadDataInfo(id,sha1))
		{
			OutputText.Prompt("ID不存在！请确认！");
			return;
		}
	}
	else//用户名方式
	{
		OutputText.UserName();
		InputText.AdminName(&name);
		if(!OperaData.ReadDataInfo(name,id))
		{
			OutputText.Prompt("用户名不存在！请确认！");
			return;
		};
	}
	OperaData.ReadDataInfo(id,name);
	OperaData.ReadDataInfo(id,balance);
	enable = OperaData.ReadDataInfo(id);
	OutputText.UserInfo();
	OutputText.UserInfo(id,name,balance,enable);
	return;
}
void Admin::AddUser()
{
	WriteData WriteData;
	vector<long> id_list;
	OperaData.ReadDataInfo(id_list);
	auto last_id = id_list[id_list.size()-1];
	OutputText.Confirm("添加用户");
	long id;
	string name;
	char first_input_code[255] = {'\0'},second_input_code[255] = {'\0'};
	unsigned code_sha1[5];
	float balance;
	if(InputText.Confirm())
	{
		OutputText.Prompt("提示：最后一位id为：");
		std::cout << last_id << std::endl;
		OutputText.CardID();
		InputText.CardID(&id);
		OutputText.UserName();
		InputText.AdminName(&name);
		OutputText.Code();
		InputText.Code(first_input_code);
		OutputText.Prompt("请再次输入密码以确认");
		InputText.Code(second_input_code);
		for(int i=0;first_input_code[i]!='\0';i++)
		{
			if(first_input_code[i]!=second_input_code[i])
			{
				OutputText.Prompt("两次密码不相同！");
				return;
			}
		}
		helper.calculate(first_input_code,code_sha1);
		OutputText.Prompt("预存款为50确认吗？(Y/N):");
		if(InputText.Confirm()){balance = 50;}
		else{OutputText.Money();try{InputText.Money(balance);}catch(std::runtime_error err){std::cout << err.what() << std::endl;return;}}
		WriteData.AddUser(id,name,code_sha1,balance);
	}
	else{return ;}
}