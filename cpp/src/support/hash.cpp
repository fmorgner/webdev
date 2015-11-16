#include "hash.h"
#include "encoding.h"

#include <gnutls/gnutls.h>
#include <gnutls/crypto.h>

#include <array>

namespace webdev
  {

  std::string hash(std::string const & input)
    {
    std::array<unsigned char, 32> hash{};
    gnutls_hash_fast(GNUTLS_DIG_SHA256, input.c_str(), input.length(), hash.data());
    return encode_hex({hash.cbegin(), hash.cend()});
    }

  }

