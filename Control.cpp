#include "control.h"
#include "helper.h"
InitData DDDDDData;
void Start::start()
{
	OutputText OutputText;
	InputText  InputText;
	ATM ATM;
	enum Menu {MainMenu,ATMMenu,AdminMenu};
	unsigned int Menu_length = 0;
	unsigned int Choice      = 0;
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
		ATM.Login();
		Menu_length = OutputText.Menu(ATMMenu);
		break;
	case(1):
		OutputText.Menu(AdminMenu);
		break;
	}

}
bool ATM::Login(void)
{
	long card_id;
	char code[255];
	unsigned database_sha1[5];
	helper helper;
	//bool ;
	OutputText.CardID();
	InputText.CardID(card_id);
	OutputText.Code();
	InputText.Code(code);
    OperaData.ReadDataInfo(card_id,database_sha1);
	helper.check(code,database_sha1);
}