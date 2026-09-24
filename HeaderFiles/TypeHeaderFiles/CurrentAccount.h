#ifndef CURRENTACCOUNT_H
#define CURRENTACCOUNT_H
#pragma once



class CurrentAccount : public Account
{
private:

const double withdrawFee = .01 ; 
const double transferFee = 1 ; 
 
public:

     CurrentAccount(const std::string& holder_name, const std::string& national_id, 
                   double balance, const std::string& password, 
                   int account_number = -1, bool isAlreadyHashed = false);


bool Withdraw(double amount_withdraw , std::string account_target)override ; 
bool TransferSend(double amount_transfer_withdraw , std::string account_number_reciever)override;    


    
    ~CurrentAccount();
};

#endif