#include "Account.h"
#include "BankUtils.h"
#include<iostream>
#include<vector>
#include<string>




/*
becase we use (static) the value changes every time when we use (++)
(static) save the last value and ignore the prevois value
*/
int Account::next_account_number_=1001;


//constructor in class Account(Intializer List)
Account::Account(const std::string& holder_name , const std::string& national_id ,AccountType type , double balance , const std::string& password , bool isAlreadyHashed )
  :
    holder_name_ (holder_name),
    national_id_(national_id),
    type_ (type),
    balance_ (balance) ,
    password_ (isAlreadyHashed ? password : BankUtils::HashingStrInput(password)),
    account_number_ (std::to_string(next_account_number_++))
  {

  }  



std::string Account::GetHolderName() const
    {
      return holder_name_;
    }

     
std::string Account::GetNationalId() const
    {
      return national_id_;
    }
     
    
std::string Account::HideNationalId() const
    {
      std::string masked=national_id_;
      for(int i = 2 ; i <= 10 ; i++)
      {
        masked[i] = '*';
      }
      return masked;
    }


std::string Account::GetAccountType() const
    {
      switch (type_)
      {
       case AccountType::Saving:
         return "Saving Account";
      
       case AccountType::Current:
         return "Current Account";

       default:
         return "UnKnown";  
      }
    }


BalanceDetails Account::GetBalanceDetails() const 
    {
      return {balance_ , 0.0 , balance_};
    }


std::string Account::GetAccountNumber() const
    {
      return account_number_;
    }


void Account::SetNextAccountNumber(int nextNum) 
    {
      next_account_number_ = nextNum; 
    }









    

bool Account::VerifyPassword(const std::string & pass_word)const
    {
      return password_ == BankUtils::HashingStrInput(pass_word);
    }  

    
std::string Account::GetPassword() const
    {
      return password_;
    }


bool Account::ChangePassword(const std::string& old_password , const std::string& new_password)
    {
      if(password_ != BankUtils::HashingStrInput(old_password) || old_password == new_password)
      {
        return false;
      } 

      password_=BankUtils::HashingStrInput(new_password);
      return true;
    }
      
    
void Account::ForgotPassword(const std::string& new_password)
    {
      password_ =BankUtils::HashingStrInput(new_password);
    }











bool Account::Deposit(double amount_deposit , std::string account_target)
    {
      if(amount_deposit > 0 && amount_deposit <= 5000 ) 
      {
        balance_ += amount_deposit; 
        AddTransaction("Deposit" , amount_deposit , account_target);  
        return true; 
      }
  
      else 
      {
       return false;
      }

    }


/*fuction transfer deposit*/
bool Account::TransferReceive(double amount_transfer_deposit , std::string account_number_sender)
    {
      if(amount_transfer_deposit > 0 && amount_transfer_deposit <= 50000 ) 
      {
        balance_ += amount_transfer_deposit;
        AddTransaction("Receive Transfer" , amount_transfer_deposit , account_number_sender);   
        return true; 
      }
  
      else 
      {
       return false;
      }

    }




void Account::AddTransaction(const std::string& type, double amount , const std::string accountTarget)
    {
      Transaction T;
      T.typeTransaction = type;
      T.amountTransaction = amount;
      T.accountNumberTransfer = accountTarget;

      TransactionHistory.push_back(T);
    }

 
void Account::PrintTransactionHistory() const 
    {
      std::cout<<"\n--- Transaction History for Account: " << account_number_ << " ---\n";
      if(TransactionHistory.empty())
      {
        std::cout << "No transactions performed yet.\n";
        return;
      }

      for(size_t i=0 ; i<TransactionHistory.size() ; i++)
      {
        std::cout<<i+1<<".Type : "<<TransactionHistory[i].typeTransaction
        <<" |Amount : "<<TransactionHistory[i].amountTransaction;

        if(TransactionHistory[i].accountNumberTransfer != account_number_)
        {
          if(TransactionHistory[i].typeTransaction == "Send Transfer")
          {
            std::cout<<" |To Account Number : "<<TransactionHistory[i].accountNumberTransfer;
          }
          else if(TransactionHistory[i].typeTransaction == "Receive Transfer")
          {
            std::cout<<" |From Account Number : "<<TransactionHistory[i].accountNumberTransfer;
          }
        }

        std::cout<<"\n-------------------------------------------------\n";

      }

    }


// get transactions to save it
const std::vector<Transaction>& Account::GetTransactionHistory() const
    { 
      return TransactionHistory; 
    }

// (Load the previos transactions)
void Account::AddLoadedTransaction(const std::string& type, double amount, std::string& targetAcc)
    {
      TransactionHistory.push_back({type, amount, targetAcc});
    }




   




   
   
    
    









 












