#include "encoding.h"

#include <array>

namespace webdev
  {

  constexpr static std::array<char, 16> oHexMap = {{'0', '1', '2', '3',
    '4', '5', '6', '7',
    '8', '9', 'a', 'b',
    'c', 'd', 'e', 'f'}};

  unsigned char decode_hex_digit(char nDigit)
    {
    if('0' <= nDigit && nDigit <= '9')
      {
      return nDigit - '0';
      }
    else if('a' <= nDigit && nDigit <= 'f')
      {
      return nDigit - 'a' + 10;
      }

    return 0xFF;
    }

  std::string encode_hex(std::string const &roBytes)
    {
    std::string oBuffer(roBytes.size() * 2, 0x00);

    for(size_t nByteIndex = 0; nByteIndex < roBytes.size(); ++nByteIndex)
      {
      oBuffer[2 * nByteIndex] = oHexMap[(roBytes[nByteIndex] & 0xF0) >> 4];
      oBuffer[2 * nByteIndex + 1] = oHexMap[roBytes[nByteIndex] & 0x0F];
      }

    return oBuffer;
    }

  std::string decode_hex(std::string const &roHexString)
    {
    std::string oBuffer{};
    oBuffer.reserve(roHexString.size() / 2);

    for(auto it = roHexString.cbegin(); it < roHexString.cend(); ++it)
      {
      auto nHighNibble = decode_hex_digit(*it);

      if(nHighNibble > 16 || ++it == roHexString.cend())
        {
        return "";
        }

      auto nLowNibble = decode_hex_digit(*it);

      if(nLowNibble > 16)
        {
        return "";
        }

      oBuffer.push_back((nHighNibble << 4) + nLowNibble);
      }

    return oBuffer;
    }

  }


