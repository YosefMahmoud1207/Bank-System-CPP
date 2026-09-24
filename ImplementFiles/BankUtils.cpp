#include "BankUtils.h"
#include<iostream>
#include<cctype>//Inspection Function [isalpha - isupper - ispunct - isspace]
#include<limits>//Input Buffer Cleaner
#include<functional>//Hashing



namespace BankUtils
{ 


void BufferCleaner()
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max() , '\n');
    }  



/*Check name before store it in class*/
bool CheckName(const std::string& name )
    {
      if(name.empty()) return false;
      bool has_alpha=false;

      for(char x : name)
      {
       if(!isalpha(x) && !isspace(x))   return false;
       if(isalpha(x)) has_alpha=true;//to check name at least have a one character
      }

      return has_alpha;
    }



void EditName( std::string& name )
    {
      int count = 0;
      int startIndex = 0;
      int endIndex = (name.length() - 1);


      for(int i = 0 ; i <= endIndex ; i++)
      {
       if(isalpha(name[i]))  break;
  
       count+=1;
      }
      if(count>0)
       name.erase(startIndex,count);

       count=0; 
  
  
      for(int j = endIndex ; j >= 0 ; j--)
      {
        if(isalpha(name[j]))  break;
  
        count+=1;
      }
      if(count>0)
        name.erase((endIndex-count)+1 ,count);

    }   



    
/*Enter national ID before store it in class*/
bool EnterNationalID(const std::string& ID)
    {

      if(ID.length() != 14) return false;
      for(char x : ID)
      {
        if(!isdigit(x))
        {
          std::cout<<"The national ID must consists of digits only without spaces .\n";
          return false;
        } 
      }
      std::cout<<"Enter the previos national ID again : \n";
      std::string verify_id;
      std::cin>>verify_id;
      for(char y : verify_id)
       {
        if(!isdigit(y))
        {
         std::cout<<"The national ID must consists of digits only\n";
         return false;
        } 
       }
   
      if(!(ID==verify_id))
       {
        std::cout<<"The new national ID isnot as the same as the prevois national ID\n";
        return false;
       }
      return true;
    }


/*Check input intiale pass word*/
bool CheckPassword(const std::string& pass_word)
    {
      bool upper_case=false;
      bool lower_case=false;
      bool contain_number=false;
      bool contain_special_char=false;

      if(pass_word.length() < 8)
        return false;

      for(char x : pass_word)
       {
        if(isspace(x))
        {
         std::cout<<"The password mustnot have a spaces.\n";
         return false;
        }
        if(isupper(x)) upper_case=true;
        if(islower(x)) lower_case=true;
        if(isdigit(x)) contain_number=true;
        if(ispunct(x)) contain_special_char=true; 
       }

      return upper_case && lower_case && contain_number && contain_special_char; //if it pass from condetions
    }  


    

/*Function Hashing input*/
std::string HashingStrInput(const std::string& Input)
    {
  
      uint64_t hashvalue = 14695981039346656037ULL; // offset basis
      uint64_t fnv_prime = 1099511628211ULL;  // prime

      for (char c : Input)
       {
          hashvalue ^= static_cast<uint64_t>(c); // XOR byte
          hashvalue *= fnv_prime;                // Multiply by prime
       }

      return std::to_string(hashvalue);
    }




void ShowMenu()
{
  std::cout<<" ============BANK MENU============ \n";
  std::cout<<" Enter [1] : Show Balace \n";  
  std::cout<<" Enter [2] : Deposit \n";   
  std::cout<<" Enter [3] : Withdraw \n";
  std::cout<<" Enter [4] : Transfer Money \n";
  std::cout<<" Enter [5] : Transaction History \n";
  std::cout<<" Enter [6] : Show Profile \n";   
  std::cout<<" Enter [7] : Change Pass Word \n";
  std::cout<<" Enter [8] : Log out \n";
  std::cout<<" Enter [9] : Exit \n";    
}


}

