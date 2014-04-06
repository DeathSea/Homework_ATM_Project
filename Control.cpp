#include "control.h"
#include "helper.h"
void Start::start()
{
	InitData DDDDDDATA;//fucking to init the data
	OutputText OutputText;
	InputText  InputText;
	ATM ATM;
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
		OutputText.Menu(AdminMenu);
		break;
	}

}
bool ATM::Login(void)
{
	long card_id;
	char code[255] = {'\0'};
	unsigned database_sha1[5];
	helper helper;
	OutputText.CardID();
	InputText.CardID(&card_id);
	OutputText.Code();
	InputText.Code(code);
    if(!OperaData.ReadDataInfo(card_id,database_sha1))
	{
		std::cout << "Can't find the card id in the database ,Please check again"<<std::endl;
		return true;
	}
	else
	{
	   if(helper.check(code,database_sha1))
	   {
		   return true;
	   }
	   else
	   {
		   std::cout << "code error"<<std::endl;
		   return false;
	   }
	}
}