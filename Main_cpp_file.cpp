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
	Choice      = InputText.Choice(Menu_length);
	//cout << Choice ;
    //OutPutText.Menu(ATMMenu);
	//OutPutText.Menu(AdminMenu);
    return 0;
}