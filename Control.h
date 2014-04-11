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
class Start
{
private:
	OutputText OutputText;
	InputText  InputText;
public:
	void start();
	unsigned make_choice(unsigned Menu_option);
	void ATM_choice(long &);
};
class ATM
{
private:
	OutputText OutputText;
	InputText  InputText;
	OperaData  OperaData;
	Start Start;
public:
	bool Login(long &card_id);
	void UserBalance(long &id);//查询余额
	void Withdrawal(long &id);//#取款
	void Deposit(long &id);//#存款
	void Transfer();//#转账
	void ChangeCode(); 
};
class Admin
{        
private:
	OutputText OutputText;
	InputText  InputText;
	OperaData  OperaData;
public:
	bool Login();
	void AddUser();
	void EXportUser();
	void ImportUser();
	void InquiryAllUserInfo();
	void InquiryNominatedUserInfo();
	void UserWithdrawal();
	void UserDeposit();
	void UserTransfer();
	void UserChangCode();
};
#endif