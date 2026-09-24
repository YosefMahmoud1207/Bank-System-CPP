#ifndef SAVINGACCOUNT_H
#define SAVINGACCOUNT_H
#pragma once



class SavingAccount : public Account
{
private:

 double invest_balance_;
 const double transferFee = 1 ; 

public:

SavingAccount(const std::string& holder_name, const std::string& national_id, double balance, 
                  const std::string& password, double invest_balance, 
                  int account_number = -1, bool isAlreadyHashed = false);


                  
BalanceDetails GetBalanceDetails()const override;   

bool Withdraw(double amount_withdraw , std::string account_target)override ; 
bool TransferSend(double amount_transfer , std::string account_number_reciever)override;
    


    
    ~SavingAccount();
};

#endif