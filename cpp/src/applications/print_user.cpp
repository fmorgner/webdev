#include "dto/user.h"
#include "support/names.h"

#include <iostream>

using namespace webdev;

int main(int argc, char ** argv)
  {
  auto name = std::string{};

  if(argc != 2)
    {
    name = name_create();
    }
  else
    {
    name = std::string{argv[1]};
    }


  std::cout << user{name}.json().toStyledString();
  }

