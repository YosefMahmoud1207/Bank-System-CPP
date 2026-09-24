#ifndef BANKUTILS_H
#define BANKUTILS_H
#pragma once
#include<string>

namespace BankUtils
{
  void BufferCleaner();
  bool CheckName(const std::string& name );
  void EditName( std::string& name );
  bool EnterNationalID(const std::string& ID);
  bool CheckPassword(const std::string& pass_word);
  std::string HashingStrInput(const std::string& Input);
  void ShowMenu();
}

#endif