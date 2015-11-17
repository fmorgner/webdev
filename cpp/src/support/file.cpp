#include "support/file.h"

#include <fstream>
#include <iterator>

namespace webdev
  {
  std::string read_file(std::string const & name)
    {
    auto buffer = std::string{};

    auto file = std::ifstream{name};

    if(file)
      {
      file.seekg(0, std::ios::end);
      buffer.reserve(file.tellg());
      file.seekg(0, std::ios::beg);

      buffer.assign(std::istreambuf_iterator<char>{file}, std::istreambuf_iterator<char>{});
      }

    return buffer;
    }
  }

