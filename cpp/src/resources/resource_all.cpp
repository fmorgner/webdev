#include "resources/resource_all.h"
#include "support/access.h"

#include <algorithm>
#include <vector>

namespace webdev
  {

  resource_all::resource_all(redox::Redox & redis) : resource_frontend{redis}
    {

    }

  std::string resource_all::content() const
    {
    using namespace std::literals;

    auto shouts = shouts_getall(m_redis);
    auto entries = mstch::array{};

    for_each(shouts.cbegin(), shouts.cend(), [&](auto const & shout){
      entries.push_back(mstch::map(shout));
      });

    auto fragment = read_file("static/html/fragments/all.html");
    return mstch::render(fragment, mstch::map{{"shouts", entries}});
    }

  }

