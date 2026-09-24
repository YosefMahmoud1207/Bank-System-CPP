#include "BankSystem.h"
#include"BankUtils.h"
#include"Account.h"
#include "SavingAccount.h"
#include "CurrentAccount.h"
#include<iostream>
#include<fstream>
#include<sstream>


void BankSystem::Run()
{
   std::string mainChoice ;
   
   LoadDataProfile();
   LoadDataTransactions();
   while (true)
   {
     currentUser=nullptr; /*to clear pointer every loop . becase pointer save values
     & avoid if(currentUser !=nullptr) when user enter wrong*/
     std::cout << "\n=== BANK SYSTEM GATEWAY ===\n";
     std::cout << "1. Log In\n";
     std::cout << "2. Register (Create Account)\n";
     std::cout << "3. Exit\n";
     std::cout << "Choice: ";
     std::cin >> mainChoice;

     if (mainChoice == "1") //  LOG IN 
     {
       HandleLogin();
     }

     else if (mainChoice == "2") //  REGISTER
     {
        HandleRegister();
     }

     else if(mainChoice == "3") //  EXIT
        break;

     else  //   WRONG CHOICE
       std::cerr<<"Invalid Choice . Enter your choice again ...\n";
   }

}








void BankSystem::HandleLogin()
{
    std::string id, pass;
    std::cout << "Enter National ID: ";
    std::cin >> id;
    std::cout<<"enter your pass word : \n";
    std::cin>>pass;
  

    for(auto &acc : accounts)
     {
       if(acc->GetNationalId()==id)
        {
          currentUser=acc.get();  
          break;
        }
     }

    if(currentUser != nullptr)
    {
      // pass word
      int attempt=1;
      bool access =false;
      while(attempt<3)
       {
         if(currentUser-> VerifyPassword(pass))
         { 
           access = true;
           break;
         }
         else
         { 
           std::cerr<<"Wrong pass word . It remains : "<<(3-attempt)<<". Try to put it again.\n";
           std::cin>>pass;
           attempt++;
           access=false;
         }
       }
      if(!access)
       {
         std::cerr<<"ACCOUNT OUT! . due to 3 wrong attempts password.\n";
         std::cerr<<"If you forgot password : Enter [1] || If NOT : enter anything else ... \n";
         std::string forgot;
         std::cin>>forgot;
         if(forgot == "1")
         {
           bool reset_success=false;
           for(int i=0 ; i<3 ; i++)
           { 
             std::cout<<"Enter your national ID : ";
             std::string ID1;
             std::cin>>ID1;

             if(ID1 == currentUser->GetNationalId())
             { 
               std::cout<<"Enter the password must be ( >= 8 Character) consists of";
               std::cout<<" [Upper case - Lower case - Numbers - Special character] & mustnot spaces : \n";
               std::string input_password;
               std::cin>>input_password;
               while(!BankUtils::CheckPassword(input_password))
               {
                std::cerr<<"Error . Enter your Pass Word again , Pass Word must be ( >= 8 Character) consists of [Upper case - Lower case - Numbers - Special character] & mustnot spaces : \n";
                std::cin>>input_password;
               }

               currentUser-> ForgotPassword(input_password);
               std::cout<<"Password reset successfuly . \n";

               reset_success=true;
               access=true;  //to allow to user to continue the programe;
               UserMenuLoop();
               break; 
             }
          
             else 
             { 
              std::cerr<<"National ID is wrong! || Attempts remaning: "<<(2-i) <<"\n";
             } 
            }


            if(!reset_success)
            {
              std::cerr<<"Too many failed attempts. ATM stopped.\n";
              return ;
            }
      
         }  


         else
         {
           std::cout<<"ATM is stoped\n";
           return ;
         }
        }

        //When password is right
      std::cout<<"Welcome back,"<<currentUser->GetHolderName()<<".\n";

      UserMenuLoop();
    }
    else
    {
        //about Wrong LOG IN
      std::cerr<<"Invalid ID or Password\n";
    }
}   










void BankSystem::UserMenuLoop() //USE IN LOGIN
{
    //store values form struct
  BalanceDetails details = currentUser->GetBalanceDetails();

  int choiceMenu;
  double amount;

     
   

  do 
   {
       //this is a part of (choices)
     BankUtils::ShowMenu();
     std::cout<<"enter your choice.\n";

     if(!(std::cin>>choiceMenu)) //clear buffer
      {
        BankUtils::BufferCleaner();
        std::cerr<<"Invalid input! Please input number\n";
        continue;//cancel switch and return do_while
      }
     if(choiceMenu < 1 || choiceMenu > 9)
      {
        std::cout << "Invalid choice! Please enter a number between 1 and 9.\n";
        continue;
      }
  

     switch(choiceMenu)
     {
      case 1 :      /*function balance*/
       { 
         details = currentUser->GetBalanceDetails();
         std::cout<<"Your Total balance is : "<<details.total_balance<<"\n";
         if(currentUser->GetAccountType() == "Saving Account")
         {
          std::cout<<"Your Invest balance is : "<< details.invest_balance<<"\n";
          std::cout<<"Your Available balance is : "<<details.available_balance <<"\n";
         }  

         break;
       }


      case 2:      /*function deposit*/
       { 
         std::cout<<"enter your amount of deposit : \n";
         while(!(std::cin>>amount) || amount<=0 || amount > 5000)
         { 
           BankUtils::BufferCleaner();
          std::cerr<<"Invalid input! Enter positive number for deposite ( 0 < amount <= 5000 ) : \n";
         }
         if(currentUser-> Deposit(amount , currentUser->GetAccountNumber()))
         {
          details = currentUser->GetBalanceDetails();  // RENEW STRUCT
          std::cout<<"your deposit is successfuly.\n";
          std::cout<<"your balance is : "<<details.total_balance<<"\n";  
          SaveDataProfile(); 
         }

         break;
       }


      case 3:     /*function withdraw*/
       { 
         std::cout<<"enter your amount of withdraw : \n";

         while(!(std::cin>>amount) || amount<=0 || amount > 5000)
         { 
          BankUtils::BufferCleaner();
          std::cerr<<"Invalid input! Enter positive number for withdraw (0 < amount <= 5000): \n";
         }
         if(currentUser-> Withdraw(amount , currentUser->GetAccountNumber()))
         {
          details = currentUser->GetBalanceDetails();  // RENEW STRUCT
          std::cout<<"your withdraw is successfuly. \n";
          std::cout<<"your balance is : "<<details.total_balance<<"\n";
          SaveDataProfile();    
         } 
         else
         {
          std::cout<<"Insufficient balance .\n"; 
         } 

         break;
       }

       
      case 4:     /*Transfer Money*/
       { 
         details = currentUser->GetBalanceDetails();
         Account* targetUser = nullptr;
         std::string target_account_number;

         std::cout<<"Enter target account number\n";
         std::cin>>target_account_number;

         if(currentUser->GetAccountNumber() == target_account_number)
         {
          std::cerr<<"You cannot transfer to yourself .\n";
         }
         else
         {  
          for(auto &acc : accounts)
           {
             if(acc->GetAccountNumber()==target_account_number)
             {
               targetUser=acc.get();
               break;
             }
           }
          if(targetUser == nullptr )
           { 
             std::cerr<<"Error: Target account number not found. Please check the account number and try again.\n";
           }

          else if(targetUser != nullptr)
           {
             std::cout<<"enter your amount of transfer : \n";

             while(!(std::cin>>amount) || amount<=0 || amount > 50000)
             { 
               BankUtils::BufferCleaner();
               std::cerr<<"Invalid input! Enter positive number for transfer (0 < amount <= 50000): \n";
             }
             if(currentUser-> TransferSend(amount , targetUser->GetAccountNumber()))
             {
               targetUser-> TransferReceive(amount , currentUser->GetAccountNumber());
               details = currentUser->GetBalanceDetails();  // RENEW STRUCT
               std::cout<<"your Transfer is successfuly. \n";
               std::cout<<"your balance is : "<<details.total_balance<<"\n"; 
               SaveDataProfile();
               SaveDataTransactions();
             } 
             else
             {
               std::cerr<<"Transfer failed! Please check your available balance or your amount.\n"; 
             } 
           }
         }

         break;
        }

       
       /*Function Transaction History*/
      case 5:
       {
         currentUser->PrintTransactionHistory();
         break;
       }


      case 6:  /*Function Profile*/
       { 
         details = currentUser->GetBalanceDetails();
         std::cout<<"Your name is : "<<currentUser-> GetHolderName()<<"\n";
         std::cout<<"Your national id is : "<<currentUser-> HideNationalId()<<"\n";
         std::cout<<"Your account number is : "<<currentUser-> GetAccountNumber()<<"\n";
         std::cout<<"Your Total balance is : "<<details.total_balance<<"\n";
         if(currentUser->GetAccountType() == "Saving Account")
         {
          std::cout<<"Your Account type is : "<<"Saving Account\n";
          std::cout<<"Your Invest balance is : "<< details.invest_balance<<"\n";
          std::cout<<"Your Available balance is : "<<details.available_balance<<"\n";
         }
         else
         {
          std::cout<<"Your Account type is : "<<"Current Account\n";
         }
         break;
       }


      case 7:   /*Function Change pass word*/
       { 
         std::string input_old_password , input_new_password;
         int old_check=1;
         bool old_password_valid=false; 

       
         while( old_check<=3 )
         {
          std::cout<<"Enter the old pass word.\n";
          std::cin>>input_old_password;

          if(currentUser-> VerifyPassword(input_old_password))
          {
           old_password_valid=true;
           break;
          }
          std::cerr<<"Wrong pass word! Attmepts becomes : "<<(3-old_check)<<" . Try again.\n";
          old_check++;
         }
         if(!old_password_valid)
         {
          std::cerr<<"Too many wrong attempts . Pass word changed canceled.\n";
          break;
         } 
       
         std::cout<<"Enter your new pass word.\n";
         std::cin>>input_new_password;
         while(!BankUtils::CheckPassword(input_new_password))
         {
          BankUtils::BufferCleaner();
          std::cerr<<"You entered the new pass word wrong that must be ( >= 8 Character) consists of [Upper case - Lower case - Numbers - !@#$%^&] : \n";
          std::cin>>input_new_password;
         }

         if(currentUser-> ChangePassword(input_old_password , input_new_password))
         {
          std::cout<<"Pass word changed succesfuly.\n";
          SaveDataProfile();
         }
         else
         {
          std::cerr<<"Error changing pass word . The new pass word cannot be as the same as the old pass word\n";
         }
       
         break;
        }
       
       case 8:   // LOG OUT
       {
         SaveDataProfile();
         SaveDataTransactions();
         break;
       }

       case 9: 
       {     
         std::cout<<"BANK is stopped\n";
         SaveDataProfile();
         SaveDataTransactions();
        exit(0) ;
       }

       default:
       { 
        std::cerr<<"your choice is not valid\n";
       }

     }

    } 
    while(choiceMenu!=8);
}
    











void BankSystem::HandleRegister()
{
    BankUtils::BufferCleaner();//To avoid"\n" when we register after login
     /*Prepare name to store it in constractor*/
    std::cout<<"Enter user name : \n";
    std::string input_name;
    std::getline(std::cin,input_name);//to can enter full name separated
    while(!BankUtils::CheckName(input_name))
    {
      std::cerr<<"Error! Name can not be empty or spaces only .Press Enter to: Enter your name again\n";
      BankUtils::BufferCleaner();
      std::cout<<"Enter user name\n";
      std::getline(std::cin,input_name);
    }
     /*To delete any spaces in the first or end of name*/
    BankUtils::EditName( input_name );

  

     /*Prepare national ID to store it in constractor*/
    std::cout<<"Enter national ID , (Is consist of 14 digits only) : \n";
    std::string input_national_id;
    std::cin>>input_national_id;
    bool exist = false;
    for(const auto &acc : accounts)
    {
      if(input_national_id == acc->GetNationalId())
      {
        exist = true;
        break;
      }
    }
    while(!BankUtils::EnterNationalID(input_national_id) || exist)
    {
      if(exist)
      {
        std::cerr<<"This National ID is already registered!\n";
        std::string exit_or_keep;
        std::cout<<"If you need to exit . Enter [1]\n";
        std::cout<<"If you need to exit . Enter any thing else\n";
        std::cin>>exit_or_keep;
        if(exit_or_keep == "1")
        {
          return ;
        }
      }
      std::cerr<<"Error . Enter your national_Id again , It must be consist of 14 digits only.....\n";
      std::cin>>input_national_id;

      exist = false;
      for(const auto &acc : accounts)
      {
        if(input_national_id == acc->GetNationalId())
        {
          exist = true;
          break;
        }
      }
    }
  


      /*Prepare Account Type to store it in constractor*/
    std::string choiceType;
    AccountType inputAccountType;
    std::cout<<"Enter your choice to determine Account Type : \n";
    std::cout<<"1 . Saving Account .\n";
    std::cout<<"2 . Current Account .\n"; 
    std::cin>>choiceType;
    while(true)
    {  
      if(choiceType=="1")
      { 
         inputAccountType=AccountType::Saving;
         break;
      }   
      else if(choiceType=="2")
      {
         inputAccountType=AccountType::Current; 
         break; 
      }   
     else
     { 
        std::cerr<<"Invalide choice . try again .\n";
        std::cout<<"Enter your Account Type .\n"; 
        std::cin>>choiceType;  
     }    
    }
  


     /*Prepare balance to store it in constractor*/
     std::cout<<"Enter the balance , (Minimum balance is 50.0) : \n";
     const double MIN_BALANCE=50.0;
     double input_balance;
     double input_invest_balance;

   if(inputAccountType == AccountType::Saving) 
   {  
      while( !(std::cin>> input_balance) || input_balance < MIN_BALANCE)
      {
         BankUtils::BufferCleaner();
         std::cerr<<"Error . Enter your balance again , the minimum balance is (50.0) .\n";
      }  
     std::cout<<"Enter the invest balance : \n";
     while( !(std::cin>> input_invest_balance) || input_invest_balance < 0 || input_invest_balance > input_balance )
      {
         BankUtils::BufferCleaner();
         std::cerr<<"Error . Enter your invest balance again , It must be <= input balance .\n";
      }  
    }
    else if(inputAccountType == AccountType::Current) 
    {  
     while( !(std::cin>> input_balance) || input_balance < MIN_BALANCE)
      {
         BankUtils::BufferCleaner();
         std::cerr<<"Error . Enter your balance again , the minimum balance is (50.0) .\n";
      }  
    }

   
     /*Prepare password to store it in constractor*/
     std::cout<<"Enter the password must be ( >= 8 Character) consists of [Upper case - Lower case - Numbers - Special character] & mustnot spaces : \n";
     std::string input_password;
     std::cin>>input_password;
     while(!BankUtils::CheckPassword(input_password))
     {
       std::cerr<<"Error . Enter your Pass Word again , Pass Word must be ( >= 8 Character) consists of [Upper case - Lower case - Numbers - Special character] & mustnot spaces : \n";
       std::cin>>input_password;
     }

      /*Prepare constractor*/
    if(inputAccountType == AccountType::Saving)
    {
      accounts.push_back(std::make_unique<SavingAccount>(input_name , input_national_id ,
          input_balance , input_password , input_invest_balance ));
      SaveDataProfile();    
      std::cout << "\nAccount created successfully! Please Log In.\n";
    }
    else if(inputAccountType == AccountType::Current)
    {
      accounts.push_back(std::make_unique<CurrentAccount>(input_name, 
        input_national_id , input_balance , input_password )); 
      SaveDataProfile();      
      std::cout << "\nAccount created successfully! Please Log In.\n";
    }
}

























void BankSystem::SaveDataProfile()
{
    std::ofstream WriteFile("FileHandling/account.txt", std::ios::trunc);

    if(!WriteFile.is_open())
    {
        std::cerr << "Error: Could not open file for saving data!\n";
        return;
    }

    for(const auto& acc : accounts)
    {
        BalanceDetails details = acc->GetBalanceDetails();

        std::string rawData = acc->GetAccountType() + "," +
                              acc->GetHolderName() + "," +
                              acc->GetNationalId() + "," +
                              acc->GetAccountNumber() + "," +
                              acc->GetPassword() + "," + 
                              std::to_string(details.total_balance);

        if(acc->GetAccountType() == "Saving Account")
        {
            rawData += "," + std::to_string(details.invest_balance);
        }

        WriteFile << rawData << "\n";
    }

    WriteFile.close();
}

void BankSystem::LoadDataProfile()
{
    std::ifstream readFile("FileHandling/account.txt");

    if(!readFile.is_open())
    {
        accounts.clear();
        Account::SetNextAccountNumber(1001); 
        return;
    }

    accounts.clear(); 

    std::string rawData;
    int maxAccountNumber = 1000;

    auto trim = [](std::string& str) {
        while (!str.empty() && (str.back() == '\r' || str.back() == ' ' || str.back() == '\n')) {
            str.pop_back();
        }
        while (!str.empty() && (str.front() == ' ' || str.front() == '\r')) {
            str.erase(0, 1);
        }
    };

    while(std::getline(readFile, rawData))
    {
        trim(rawData);
        if(rawData.empty())
            continue; 

        std::stringstream parsing(rawData);
        std::string accountType, name, nationalId, accountNum, passHash, balanceStr, investStr;

        std::getline(parsing, accountType, ',');
        trim(accountType);

        std::getline(parsing, name, ',');
        trim(name);

        std::getline(parsing, nationalId, ',');
        trim(nationalId);

        std::getline(parsing, accountNum, ',');
        trim(accountNum);

        std::getline(parsing, passHash, ',');
        trim(passHash);

        std::getline(parsing, balanceStr, ',');
        trim(balanceStr);

        try
        {
            if (balanceStr.empty()) continue;

            double balance = std::stod(balanceStr);
            int parsedAccountNum = accountNum.empty() ? -1 : std::stoi(accountNum);

            if(parsedAccountNum > maxAccountNumber)
            {
                maxAccountNumber = parsedAccountNum;
            }

            if(accountType == "Saving Account")
            {
                std::getline(parsing, investStr, ',');
                trim(investStr);
                double investBalance = investStr.empty() ? 0.0 : std::stod(investStr);

          
                accounts.push_back(std::make_unique<SavingAccount>(
                    name, nationalId, balance, passHash, investBalance, parsedAccountNum, true));
            }
            else if(accountType == "Current Account")
            {
                
                accounts.push_back(std::make_unique<CurrentAccount>(
                    name, nationalId, balance, passHash, parsedAccountNum, true)); 
            }
        }
        catch(const std::exception& e)
        {
            std::cerr << "Error parsing line: " << rawData << " | Exception: " << e.what() << "\n";
            continue;
        }
    }   
    
    readFile.close();

    if(maxAccountNumber >= 1001)
    {
        Account::SetNextAccountNumber(maxAccountNumber + 1);
    }
}








void BankSystem::SaveDataTransactions()
{
    std::ofstream WriteFile("FileHandling/Transactions.txt", std::ios::trunc);

    if(!WriteFile.is_open())
    {
        std::cerr << "Error: Could not open file for saving transactions!\n";
        return;
    }

    for(const auto& acc : accounts)
    {
        const auto& history = acc->GetTransactionHistory();
        
        for(const auto& trans : history)
        {
            std::string transactionLine = acc->GetAccountNumber() + "," +
                                          trans.typeTransaction + "," +
                                          std::to_string(trans.amountTransaction) + "," +
                                          trans.accountNumberTransfer;

            WriteFile << transactionLine << "\n";
        }
    }

    WriteFile.close();
}

void BankSystem::LoadDataTransactions()
{
    std::ifstream readFile("FileHandling/Transactions.txt");

    if(!readFile.is_open())
        return;

    std::string line;
    auto trim = [](std::string& str) {
        while (!str.empty() && (str.back() == '\r' || str.back() == ' ' || str.back() == '\n')) {
            str.pop_back();
        }
        while (!str.empty() && (str.front() == ' ' || str.front() == '\r')) {
            str.erase(0, 1);
        }
    };

    while(std::getline(readFile, line))
    {
        trim(line);
        if(line.empty())
            continue; 

        std::stringstream parsing(line);
        std::string accNumStr, typeTrans, amountStr, targetAccStr;

        std::getline(parsing, accNumStr, ',');
        trim(accNumStr);

        std::getline(parsing, typeTrans, ',');
        trim(typeTrans);

        std::getline(parsing, amountStr, ',');
        trim(amountStr);

        std::getline(parsing, targetAccStr, ',');
        trim(targetAccStr);

        try
        {
            if (accNumStr.empty() || amountStr.empty()) continue;

            double amount = std::stod(amountStr);
          
            for (auto& acc : accounts)
            {
                if (acc->GetAccountNumber() == accNumStr)
                {
                    acc->AddLoadedTransaction(typeTrans, amount, targetAccStr);
                    break;
                }
            }
        }
        catch(const std::exception& e)
        {
            std::cerr << "Error parsing transaction line: " << line << " | Exception: " << e.what() << "\n";
            continue;
        }
    }   
    
    readFile.close();
}


