#include "resources/resource_index.h"
#include "support/access.h"
#include "support/file.h"
#include "support/names.h"

#include "mstch/mstch.hpp"

#include <algorithm>

#include <iostream>

namespace webdev
  {

  using httpserver::http_request;
  using httpserver::http_response;
  using httpserver::http_response_builder;

  using namespace std::literals;

  resource_index::resource_index(redox::Redox & redis, std::string const & templ) :
    m_redis{redis},
    m_template{read_file(templ)}
    {
    disallow_all();
    set_allowing("GET", true);
    }

  void resource_index::render_GET(http_request const & request, http_response * * const response)
    {
    auto session = request.get_cookie("session");
    auto content = ""s;
    auto name = name_create();

    while(user_exists(m_redis, user{name}))
      {
      name = name_create();
      }

    if(session_exists(m_redis, session))
      {
      auto user = user_get_by_id(m_redis, session);
      content = read_file("static/html/welcome.html");
      auto data = mstch::map{};
      data["user"] = user;
      content = mstch::render(content, data);
      }
    else
      {
      content = read_file("static/html/register.html");
      content = mstch::render(content, mstch::map{{"name", name}});
      }

    auto builder = http_response_builder{mstch::render(m_template, mstch::map{{"content", content}}), 200, "text/html"};
    *response = new http_response{builder};
    }

  }

