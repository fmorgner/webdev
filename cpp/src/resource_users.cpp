#include "resource_users.h"

#include <algorithm>

namespace webdev
  {

  resource_users::resource_users(std::vector<user> const & users) : m_users{users}
    {

    }

  void resource_users::render_GET(httpserver::http_request const & request, httpserver::http_response * * const response)
    {
    Json::Value users{};

    for_each(m_users.cbegin(), m_users.cend(), [&](auto const & user){
      users.append(user.json());
      });

    auto builder = httpserver::http_response_builder{users.toStyledString(), 200};

    * response = new httpserver::http_response{builder};
    }

  }

