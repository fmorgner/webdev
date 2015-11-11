#include "user.h"

#include <iostream>

using namespace webdev;

int main(int argc, char ** argv)
  {
  if(argc != 2)
    {
    std::cerr << "usage " << argv[0] << " <user_name>\n";
    return 1;
    }

  std::cout << user{argv[1]}.json().toStyledString();
  }

