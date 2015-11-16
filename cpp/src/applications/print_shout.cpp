#include "shout.h"

#include <iostream>

using namespace webdev;

int main(int argc, char * * argv)
  {
  if(argc != 3)
    {
    std::cerr << "usage: " << argv[0] << " <username> <shout>\n";
    return 1;
    }

  auto u = user{argv[1]};
  auto s = shout{argv[2], u};

  std::cout << s.json().toStyledString();
  }
