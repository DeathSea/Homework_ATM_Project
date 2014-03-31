#include "control.h"
#include "Views.h"
void Start::start()
{
	OutputText OutputText;
	InputText  InputText;
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
		std::cout<< err.what() << std::endl << "³ÌÐò¼´½«ÍË³ö" << std::endl;
		exit(1538);
	}
    switch(Choice)
	{
	case (0):

		Menu_length = OutputText.Menu(ATMMenu);
		break;
	case(1):
		OutputText.Menu(AdminMenu);
		break;
	}

}
bool ATM::Login()
{
	
}