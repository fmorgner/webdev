#include "resources/resource_user.h"
#include "support/access.h"

#include <algorithm>
#include <vector>

namespace webdev
  {

  resource_user::resource_user(redox::Redox & redis) : resource_frontend{redis}
    {

    }

  std::string resource_user::content() const
    {
    using namespace std::literals;

    auto userId = m_path.size() > 1 ? m_path[1] : ""s;
    auto entries = mstch::array{};

    if(userId.size())
      {
      if(user_exists(m_redis, userId))
        {
        auto shouts = shouts_getall_for_user(m_redis, userId);

        if(shouts.empty())
          {
          auto fragment = read_file("static/html/fragments/user_no_shouts.html");
          return mstch::render(fragment, mstch::map{{"id", userId}});
          }

        for_each(shouts.cbegin(), shouts.cend(), [&](auto const & shout){
          entries.push_back(mstch::map(shout));
          });
        }
      else
        {
        auto fragment = read_file("static/html/fragments/user_inexistent.html");
        return mstch::render(fragment, mstch::map{{"id", userId}});
        }
      }
    else
      {
      return read_file("static/html/fragments/user_missing.html");
      }

    auto fragment = read_file("static/html/fragments/user.html");
    return mstch::render(fragment, mstch::map{{"shouts", entries}});
    }

  }

