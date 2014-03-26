//
/*
界面层（View Layer）
Designed by DeathSea 2014 Jnu
提供文本界面的输入与输出
*/
#include <iostream>
#include <string>
#include <locale>
using std::string;
class OutputText
{
private:
	string MainMenu[2];
	string ATMMenu[5];
	string AdminMenu[8];
public:
	OutputText();
	void Menu(int Menu_Option);
	/*void CardID();
	void Code();
	void Money();
	void Prompt();//提示
	void Confirm();//确认
	void ChangeCode();
	void AdminName();
	void AddUser();
	void UserInfo();*/
};
/*class InputText
{
	void CardID();
	void AdminName();
	void Code();
	void Money();
	void FileName();
	void UserName();
};*/