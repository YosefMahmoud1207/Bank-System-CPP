#ifndef BANKSYSTEM_H
#define BANKSYSTEM_H
#pragma once
#include"Account.h"
#include<memory>
#include<vector>



class BankSystem
{

private:

  /*contaner of Accounts*/
std::vector<std::unique_ptr<Account>>accounts ;
   /*the account that we will use*/
Account* currentUser = nullptr; 

void HandleLogin();
void HandleRegister();
void UserMenuLoop();


void SaveDataProfile();
void LoadDataProfile();

void SaveDataTransactions();
void LoadDataTransactions();

public:

void Run();





};

#endif