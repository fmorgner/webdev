#include "resources/resource_shouts.h"
#include "support/access.h"

#include <iostream>

namespace webdev
  {

  using httpserver::http_response_builder;

  resource_shouts::resource_shouts(Redox & redis) : m_redis{redis}
    {
    disallow_all();
    set_allowing("GET", true);
    }

  void resource_shouts::render_GET(http_request const & request, http_response * * const response)
    {
    auto json = Json::Value{};
    auto builder = http_response_builder{""};
    auto id = request.get_path_piece(1);

    if(id.size())
      {
      if(user_exists(m_redis, id))
        {
        auto shouts = shouts_getall_for_user(m_redis, id);

        for_each(shouts.cbegin(), shouts.cend(), [&](auto const & shout){
          json.append(shout.json());
          });

        builder = http_response_builder{json.toStyledString(), 200, "application/json"};
        }
      else
        {
        builder = http_response_builder{kUserInvalid, 400};
        }
      }
    else
      {
      auto shouts = shouts_getall(m_redis);

      for_each(shouts.cbegin(), shouts.cend(), [&](auto const & shout){
        json.append(shout.json());
        });

      builder = http_response_builder{json.toStyledString(), 200, "application/json"};
      }

    *response = new http_response{builder};
    }

  }
