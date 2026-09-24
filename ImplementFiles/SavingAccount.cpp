#include "Account.h"
#include "SavingAccount.h"


SavingAccount::~SavingAccount()
{

}

SavingAccount::SavingAccount(const std::string& holder_name, const std::string& national_id, double balance, 
                             const std::string& password, double invest_balance, 
                             int account_number, bool isAlreadyHashed)
:Account (holder_name ,  national_id , AccountType::Saving , balance , password , isAlreadyHashed )
    ,invest_balance_(invest_balance)
    {

    }




BalanceDetails SavingAccount::GetBalanceDetails()const 
    {
      return{balance_ , invest_balance_ , balance_ - invest_balance_};
    }  


bool SavingAccount::Withdraw(double amount_withdraw , std::string account_target)  
    {   
      double available_balance = (balance_ - invest_balance_) ;
      if(amount_withdraw > 0 && amount_withdraw <= available_balance && amount_withdraw <= 5000) 
      {
        balance_ -= amount_withdraw; 
        AddTransaction("Withdraw" , amount_withdraw , account_target);
        return true;  
      }
  
      else 
      {
        return false;
      }
    }


bool SavingAccount::TransferSend(double amount_transfer_withdraw ,  std::string account_number_reciever)
    {  
      double available_balance = (balance_ - invest_balance_) ;
      if(amount_transfer_withdraw > 0 && amount_transfer_withdraw <= available_balance && amount_transfer_withdraw <= 50000) 
      {
        balance_ -= amount_transfer_withdraw; 
        AddTransaction("Send Transfer" , amount_transfer_withdraw , account_number_reciever);
        return true;  
      }
  
      else 
      {
        return false;
      }

    }