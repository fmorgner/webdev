#include "dto/user.h"
#include "resources/resource_register.h"
#include "support/access.h"

#include <json/reader.h>

namespace webdev
  {

  using httpserver::http_response_builder;

  resource_register::resource_register(Redox & redis) : m_redis{redis}
    {

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
          builder = http_response_builder{"The user already exists", 400};
          }
        else if(user_create(m_redis, newUser))
          {
          if(session_store(m_redis, newUser.hash(), newUser.name()))
            {
            builder = http_response_builder{newUser.json().toStyledString(), 200}.with_cookie("session", newUser.hash());
            }
          else
            {
            builder = http_response_builder{"The session could not be allocated", 500};
            }
          }
        else
          {
          builder = http_response_builder{"An error occurred while trying to create the user", 500};
          }
        }
      else
        {
        builder = http_response_builder{"The received json data was invalid", 400};
        }
      }
    else
      {
      builder = http_response_builder{"The data received was invalid", 400};
      }

    *response = new http_response{builder};
    }

  }

