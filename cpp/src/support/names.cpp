#include "support/names.h"

#include <random>
#include <array>

namespace webdev
  {

  using std::string;
  using std::array;

  namespace
    {
    static const array<string const, 6> prefixes{{"super", "mega", "ultra", "godlike", "berzerk", "heavenly"}};
    static const array<string const, 6> middles{{"turtle", "apple", "walrus", "sheep", "flubber", "sky"}};
    static const array<string const, 6> postfixes{{"slayer", "lover", "bender", "hopper", "ruler", "skipper"}};

    std::mt19937 prng{std::random_device{}()};
    std::uniform_int_distribution<std::size_t> distribution{size_t{}, prefixes.size() - 1};
    }

  string name_create()
    {
    auto prefix = prefixes[distribution(prng)];
    auto middle = middles[distribution(prng)];
    auto postfix = postfixes[distribution(prng)];

    return prefix + " " + middle + " " + postfix;
    }

  }

