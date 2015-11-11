#ifndef __WEBDEV_ENCODING
#define __WEBDEV_ENCODING

#include <string>

namespace webdev
  {
  std::string encode_hex(std::string const &rawBytes);
  std::string decode_hex(std::string const &hexDigits);
  }

#endif

