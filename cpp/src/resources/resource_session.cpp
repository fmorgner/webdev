#include "resources/resource_session.h"
#include "support/access.h"

#include <algorithm>

namespace webdev
  {

  using httpserver::http_request;
  using httpserver::http_response;
  using httpserver::http_response_builder;

  resource_session::resource_session(redox::Redox & redis) : m_redis{redis}
    {
    disallow_all();
    set_allowing("GET", true);
    set_allowing("DELETE", true);
    }

  void resource_session::render_GET(http_request const & request, http_response * * const response)
    {
    auto session = request.get_cookie("session");
    auto builder = http_response_builder{""};

    if(session.length() && session_exists(m_redis, session))
      {
      builder = http_response_builder{"valid"};
      }
    else
      {
      builder = http_response_builder{"invalid"};
      }

    *response = new http_response{builder};
    }

  void resource_session::render_DELETE(http_request const & request, http_response * * const response)
    {
    auto session = request.get_cookie("session");
    auto builder = http_response_builder{""};

    if(session.length() && session_remove(m_redis, session))
      {
      builder = http_response_builder{"Logged out"};
      }
    else
      {
      builder = http_response_builder{"No such session", 400};
      }

    *response = new http_response{builder};
    }

  }

