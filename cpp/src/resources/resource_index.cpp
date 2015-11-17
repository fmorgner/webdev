#include "resources/resource_index.h"
#include "support/access.h"
#include "support/file.h"

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
    auto builder = http_response_builder{""};

    std::cout << session << '\n' << session_exists(m_redis, session) << '\n';

    if(session_exists(m_redis, session))
      {
      auto content = "<div ng-controller=\"ShoutController as shout\">\n"
                     "  <div ng-repeat=\"user in shout.users\">\n"
                     "    <h2>{{user.hash}}</h2>\n"
                     "    <p>{{user.name}}</p>\n"
                     "  </div>\n"
                     "</div>\n"s;

      builder = http_response_builder{mstch::render(m_template, mstch::map{{"content", content}}), 200, "text/html"};
      }
    else
      {
      auto content = "<div ng-controller=\"RegisterController\">\n"
                     "  <button ng-click=\"register()\">Register</button>\n"
                     "</div>\n"s;

      builder = http_response_builder{mstch::render(m_template, mstch::map{{"content", content}}), 200, "text/html"};
      }

    *response = new http_response{builder};
    }

  }

