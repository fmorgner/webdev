#include "dto/user.h"
#include "resources/resource_register.h"
#include "support/access.h"

#include <json/reader.h>

namespace webdev
  {

  using httpserver::http_response_builder;

  resource_register::resource_register(Redox & redis) : m_redis{redis}
    {
    disallow_all();
    set_allowing("POST", true);
    }

  void resource_register::render_POST(http_request const & request, http_response * * const response)
    {
    auto body = request.get_content();
    auto json = Json::Value{body};
    auto builder = http_response_builder{""};

    if(Json::Reader{}.parse(body, json, false))
      {
      if(json.isMember("name") && json["name"].isString())
        {
        auto newUser = user{json["name"].asString()};
        if(user_exists(m_redis, newUser))
          {
          builder = http_response_builder{kUserExists, 400};
          }
        else if(user_create(m_redis, newUser))
          {
          if(session_store(m_redis, newUser.hash()))
            {
            auto response = std::string{kSuccessHead} + newUser.json().toStyledString() + kSuccessTail;
            builder = http_response_builder{response, 200}.with_cookie("session", newUser.hash());
            }
          else
            {
            builder = http_response_builder{kSessionAllocationFailed, 500};
            }
          }
        else
          {
          builder = http_response_builder{kUnknownError, 500};
          }
        }
      else
        {
        builder = http_response_builder{kJSONInvalid, 400};
        }
      }
    else
      {
      builder = http_response_builder{kDataNotJSON, 400};
      }

    *response = new http_response{builder};
    }

  }

