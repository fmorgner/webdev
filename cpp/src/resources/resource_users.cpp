#include "resources/resource_users.h"
#include "support/access.h"

#include <algorithm>
#include <vector>

namespace webdev
  {

  resource_users::resource_users(redox::Redox & redis) : resource_frontend{redis}
    {

    }

  std::string resource_users::content() const
    {
    using namespace std::literals;

    auto ids = users_getall(m_redis);
    auto users = mstch::array{};

    for_each(ids.cbegin(), ids.cend(), [&](auto const & id){
      auto user = user_get_by_id(m_redis, id);
      auto map = mstch::map(user);

      if(m_session == id)
        {
        map["class"] = "active"s;
        }

      users.push_back(map);
      });

    auto data = mstch::map{{"users", users}};
    auto fragment = read_file("static/html/fragments/users.html");

    return mstch::render(fragment, data);
    }

  }

