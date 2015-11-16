#include "resources/resource_users.h"
#include "support/access.h"

#include <algorithm>

namespace webdev
  {

  resource_users::resource_users(redox::Redox & redis) : m_redis{redis}
    {

    }

  void resource_users::render_GET(httpserver::http_request const & request, httpserver::http_response * * const response)
    {
    auto const & users = users_getall(m_redis);
    auto json = Json::Value{};

    if(users.size() && !(users.size() % 2))
      {
      auto temp = Json::Value{};

      for(decltype(users.size()) i{}; i < users.size(); ++i)
        {
        if(!(i%2))
          {
          temp["name"] = users[i];
          }
        else
          {
          temp["hash"] = users[i];
          json.append(temp);
          }
        }
      }

    * response = new httpserver::http_response{httpserver::http_response_builder{json.toStyledString()}};
    }

  }

