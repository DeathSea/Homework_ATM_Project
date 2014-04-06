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
	unsigned int Menu(int Menu_Option);
	void CardID(void);
	void Code();
	/*void Money();
	void Prompt();//提示
	void Confirm();//确认
	void ChangeCode();*/
	void AdminName();
	/*void AddUser();
	void UserInfo();*/
};
class InputText
{
public:
	int Choice(int Menu_length);
	void CardID(long * card_id);
	void AdminName();
	void Code(char * code);
/*	void Money();
	void FileName();
	void UserName();*/
};
#endif