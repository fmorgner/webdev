#include "resources/resource_shout.h"
#include "support/access.h"

#include <json/reader.h>

namespace webdev
  {

  using httpserver::http_response_builder;

  resource_shout::resource_shout(Redox & redis) : m_redis{redis}
    {
    disallow_all();
    set_allowing("POST", true);
    }

  void resource_shout::render_POST(http_request const & request, http_response * * const response)
    {
    auto body = request.get_content();
    auto json = Json::Value{body};
    auto builder = http_response_builder{""};
    auto session = request.get_cookie("session");

    if(Json::Reader{}.parse(body, json, false))
      {
      if(!session_exists(m_redis, session))
        {
        builder = http_response_builder{kSessionInvalid, 400};
        }
      else if(json.isMember("text") && json["text"].isString())
        {
        auto text = json["text"].asString();
        auto user = user_get_by_id(m_redis, session);
        auto newShout = shout{text, user};

        if(shout_create(m_redis, newShout))
          {
          builder = http_response_builder{newShout.json().toStyledString(), 200, "application/json"};
          }
        else
          {
          builder = http_response_builder{kCreationFailed, 500};
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

