#include "resources/resource_index.h"
#include "support/access.h"
#include "support/file.h"

#include "mstch/mstch.hpp"

#include <algorithm>

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
    session_exists(m_redis, session);

    auto data = mstch::map{};

    auto builder = http_response_builder{mstch::render(m_template, data), 200, "text/html"};

    *response = new http_response{builder};
    }

  }

