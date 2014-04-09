//
/*
界面层（View Layer）
Designed by DeathSea 2014 Jnu
提供文本界面的输入与输出
*/
#ifndef VIEW_HEAD
#define VIEW_HEAD
#include <iostream>
#include <string>
#include <locale>
#include <iterator>
#include <stdexcept>
#include <conio.h>
using std::string;
class OutputText
{
private:
	string MainMenu[2];
	string ATMMenu[5];
	string AdminMenu[8];
public:
	OutputText();
	unsigned int Menu(int Menu_Option);//打印菜单，传入值0,1,2分别为主菜单，ATM菜单,前台菜单
	void CardID(void);//打印输入卡号的提示
	void Code();//打印输入密码的提示
	void Money();//打印输入钱数的提示
	void Prompt(const string pro);//提示
	void Confirm();//确认
	void ChangeCode();//打印修改密码的提示
	void AdminName();//打印输入admin名的信息
	void AddUser();//打印增加用户的信息
	void UserInfo();//打印用户信息
};
class InputText
{
public:
	int Choice(int Menu_length);//截取用户输入//返回用户选择//传入菜单长度
	void CardID(long * card_id);//获得用户用户卡号
	void AdminName(string * in);//获取admin名
	void Code(char * code);//获取密码
	void Money();//获取钱数
	void FileName();//获取文件路径
	void UserName();//获取用户名
};
#endif