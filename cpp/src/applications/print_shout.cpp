#include "dto/shout.h"

#include <iostream>

using namespace webdev;

int main(int argc, char * * argv)
  {
  if(argc != 3)
    {
    std::cerr << "usage: " << argv[0] << " <username> <shout>\n";
    return 1;
    }

  auto name = std::string{argv[1]};
  auto text = std::string{argv[2]};

  auto u = user{name};
  auto s = shout{text, u};

  std::cout << s.json().toStyledString();
  }
