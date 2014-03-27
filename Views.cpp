#include "Views.h"
using namespace std;
OutputText::OutputText()
{
	//主菜单初始化
	MainMenu[0]  = "ATM";
	MainMenu[1]  = "前台";
	//ATM菜单初始化
	ATMMenu[0]   = "查询余额";
	ATMMenu[1]   = "取款";
	ATMMenu[2]   = "存款";
	ATMMenu[3]   = "转账";
	ATMMenu[4]   = "修改密码";
	//前台菜单初始化
	AdminMenu[0] = "增加用户";
	AdminMenu[1] = "导出用户";
	AdminMenu[2] = "导入用户";
	AdminMenu[3] = "查询所有用户";
	AdminMenu[4] = "查询指定用户";
	AdminMenu[5] = "用户取款";
	AdminMenu[6] = "用户存款";
	AdminMenu[7] = "用户修改密码";
}
unsigned int OutputText::Menu(int Menu_Option)
{
	cout << "********************************" << endl;
	string * Menu = NULL;
	unsigned int array_length = 0;
	switch(Menu_Option)
	{
	case(0):
		Menu = MainMenu;
		break;
	case(1):
		Menu = ATMMenu;
		break;
	case(2):
		Menu = AdminMenu;
		break;
	default:
		break;
	}
	if(Menu != NULL){array_length = end(*Menu) - begin(*Menu)-1;}
	else{cout << "程序运行发生了一个问题位于Views.cpp" << endl;return 0;}
	for(int index=0;index != array_length;index++)
	{
		string cmend(19-((*(Menu+index)).size()),' ');
		cout << "*         " << index+1 << ".";
		cout << *(Menu+index) << cmend << "*";
		cout << endl;
	}
	cout << "********************************" << endl;
	cout << "请输入你的选择(1至" << array_length << "):";
	cout.clear();
	return array_length;
}
int InputText::Choice(int Menu_length)
{
	int Choice = 0 ;
	cin >> Choice;
	if(Choice <= Menu_length){return Choice;}
	else{;}
}