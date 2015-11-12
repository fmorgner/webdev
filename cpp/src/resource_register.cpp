#include "resource_register.h"
#include "user.h"
#include "access.h"
#include <json/reader.h>
#include <iostream>

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

    if(Json::Reader{}.parse(body, json, false))
      {
      if(json.isMember("name") && json["name"].isString())
        {
        auto newUser = user{json["name"].asString()};
        if(user_exists(m_redis, newUser))
          {
          *response = new http_response{http_response_builder{"user exists", 400}};
          }
        else if(user_create(m_redis, newUser))
          {
          *response = new http_response{http_response_builder{newUser.json().toStyledString(), 200}};
          }
        else
          {
          *response = new http_response{http_response_builder{"could not create user", 500}};
          }
        }
      else
        {
        *response = new http_response{http_response_builder{"invalid json", 400}.string_response()};
        }
      }
    else
      {
      *response = new http_response{httpserver::http_response_builder{"invalid request", 400}.string_response()};
      }

    m_redis.del("register");
    }

  }

