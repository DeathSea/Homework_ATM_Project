#include "Views.h"
using namespace std;
OutputText::OutputText()
{
	//主菜单初始化
	MainMenu[0] = "ATM";
	MainMenu[1] = "前台";
	//ATM菜单初始化
	ATMMenu[0]  = "查询余额";
	ATMMenu[1]  = "取款";
	ATMMenu[2]  = "存款";
	ATMMenu[3]  = "转账";
	ATMMenu[4]  = "修改密码";
	//前台菜单初始化
}
void OutputText::Menu(int Menu_Option)
{
	cout << "********************************" << endl;
	string * Menu = NULL;
	int array_length;
	switch(Menu_Option)
	{
	case(0):
		Menu = MainMenu;
		array_length = 2;
		break;
	case(1):
		Menu = ATMMenu;
		array_length = 5;
		break;
	}
	for(int index=0;index != array_length;index++)
	{
		string cmend(19-((*(Menu+index)).size()),' ');
		cout << "*         " << index+1 << ".";
		cout << *(Menu+index) << cmend << "*";
		cout << endl;
	}
	cout << "********************************" << endl;
}