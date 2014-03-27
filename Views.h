//
/*
界面层（View Layer）
Designed by DeathSea 2014 Jnu
提供文本界面的输入与输出
*/
#include <iostream>
#include <string>
#include <locale>
#include <iterator>
using std::string;
class OutputText
{
private:
	string MainMenu[2];
	string ATMMenu[5];
	string AdminMenu[8];
public:
	OutputText();
	unsigned int Menu(int Menu_Option);
	void CardID();
	/*void Code();
	void Money();
	void Prompt();//提示
	void Confirm();//确认
	void ChangeCode();
	void AdminName();
	void AddUser();
	void UserInfo();*/
};
class InputText
{
public:
	int Choice(int Menu_length);
/*	void CardID();
	void AdminName();
	void Code();
	void Money();
	void FileName();
	void UserName();*/
};