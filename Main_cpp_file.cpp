//#include <iostream>
//#include "Control.h"
//#include "Data.h"
#include "Views.h"
//using namespace std;
int main(void)
{
	enum Menu {MainMenu,ATMMenu,AdminMenu};
	OutputText OutPutText;
	OutPutText.Menu(MainMenu);
    OutPutText.Menu(ATMMenu);
    return 0;
}