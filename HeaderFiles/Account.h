#ifndef ACCOUNT_H
#define ACCOUNT_H
#pragma once
#include<string>
#include<vector>



enum class AccountType
{
  Saving , Current
};

struct BalanceDetails
{
  double total_balance;
  double invest_balance;
  double available_balance;
};

struct Transaction
{
  std::string typeTransaction;
  double amountTransaction;
  std::string accountNumberTransfer;
};

class Account
{
protected:
 
  std::string holder_name_;
  std::string national_id_;
  AccountType type_;
  std::string password_; 
  static int next_account_number_;
  std::string account_number_;
  double balance_;
  std::vector<Transaction>TransactionHistory;

public:
   //Constructor
  Account(const std::string& holder_name , const std::string& national_id , AccountType type
     , double balance , const std::string& password , bool isAlreadyHashed = false );


                             //FUNCTIONS IN THE CLASS

/*Getter & Setter*/
  std::string GetHolderName() const;
  std::string GetNationalId() const;
  std::string HideNationalId() const;
  std::string GetAccountType()const;
  virtual BalanceDetails GetBalanceDetails() const;
  std::string GetAccountNumber() const;
  static void SetNextAccountNumber(int nextNum);

/*Password*/
  bool VerifyPassword(const std::string & pass_word)const;
  std::string GetPassword() const;
  bool ChangePassword(const std::string& old_password , const std::string& new_password);
  void ForgotPassword(const std::string& new_password);
  
  

/*Banking Operations*/ 
  bool Deposit(double amount_deposit , std::string account_target);
  bool TransferReceive(double amount_deposit , std::string account_number_sender);//edit
  virtual bool Withdraw(double amount_withdraw , std::string account_target) = 0; 
  virtual bool TransferSend(double amount_transfer_withdraw ,  std::string account_number_reciever) = 0;//edit
  


/*Transactions*/
  void AddTransaction(const std::string& type, double amount , const std::string accountTarget);
  void PrintTransactionHistory() const ; 
  // get transactions to save it
  const std::vector<Transaction>& GetTransactionHistory()const;
  // (Load the previos transactions)
  void AddLoadedTransaction(const std::string& type, double amount, std::string& targetAcc);

  
  
  
   
   
    
    virtual ~Account() = default;
};

 

#endif