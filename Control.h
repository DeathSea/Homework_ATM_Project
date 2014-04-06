/*
控制层（Control Layer）
Designed by DeathSea 2014 Jnu
程序主要逻辑
*/

#ifndef CONTROL_HEAD
#define CONTROL_HEAD
#include <stdexcept>
#include "Views.h"
#include "Data.h"
class ATM
{
private:
	OutputText OutputText;
	InputText  InputText;
	OperaData  OperaData;
public:
	bool Login();
//	void UserBalance();
//	void Withdrawal();//#取款
//	void Deposit();//#存款
//	void Transfer();//#转账
//	void ChangeCode(); 
};
class Admin
{        
public:
	bool Login();
//	void AddUser();
//	void EXportUser();
//	void ImportUser();
//	void InquiryAllUserInfo();
//	void InquiryNominatedUserInfo();
//	void UserWithdrawal();
//	void UserDeposit();
//	void UserTransfer();
//	void UserChangCode();
};
class Start
{
public:
	void start();
//	void show_menu();
};
#endif