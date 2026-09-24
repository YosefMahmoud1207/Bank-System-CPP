#include "Account.h"
#include "CurrentAccount.h"



CurrentAccount::~CurrentAccount()
{

}


     CurrentAccount::CurrentAccount(const std::string& holder_name, const std::string& national_id, 
                               double balance, const std::string& password, 
                               int account_number, bool isAlreadyHashed)
     :Account (holder_name ,  national_id , AccountType::Current , balance , password , isAlreadyHashed )
     {
        
     }




bool CurrentAccount::Withdraw(double amount_withdraw , std::string account_target)  
    {
      double Fee = withdrawFee * amount_withdraw; 
      double total_withdraw_amount = (amount_withdraw + Fee);
      if(amount_withdraw > 0 && total_withdraw_amount <= balance_ && amount_withdraw <= 5000 ) 
      {
        balance_ -= total_withdraw_amount; 
        AddTransaction("Withdraw" , amount_withdraw , account_target);

        return true;  
      }
  
      else 
      {
        return false;
      }
    }


bool CurrentAccount::TransferSend(double amount_transfer_withdraw ,  std::string account_number_reciever)
    { 
      double total_withdraw_amount = (amount_transfer_withdraw + transferFee);
      if(amount_transfer_withdraw > 0 && total_withdraw_amount <= balance_ && amount_transfer_withdraw <= 50000 ) 
      {
        balance_ -= total_withdraw_amount; 
        AddTransaction("Send Transfer" , amount_transfer_withdraw , account_number_reciever);

        return true;  
      }
  
      else 
      {
        return false;
      }
    }
