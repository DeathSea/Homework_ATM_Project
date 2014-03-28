//#include <iostream>
//#include "Control.h"
//#include "Data.h"
#include "Views.h"
//using namespace std;
int main(void)
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
		std::cout<< err.what() << std::endl << "程序即将退出" << std::endl;
		return 1023;
	}
    switch(Choice)
	{
	case (0):
		OutputText.Menu(ATMMenu);
		break;
	case(1):
		OutputText.Menu(AdminMenu);
		break;
	}
	//cout << Choice ;
    //OutPutText.Menu(ATMMenu);
	//OutPutText.Menu(AdminMenu);
    return 0;
}