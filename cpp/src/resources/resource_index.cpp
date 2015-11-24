#include "resources/resource_index.h"
#include "support/access.h"
#include "support/file.h"
#include "support/names.h"

#include "mstch/mstch.hpp"

#include <algorithm>

#include <iostream>

namespace webdev
  {

  using namespace std::literals;

  resource_index::resource_index(redox::Redox & redis) : resource_frontend(redis)
    {

    }

  std::string resource_index::content() const
    {
    auto content = ""s;

    if(session_exists(m_redis, m_session))
      {
      auto user = user_get_by_id(m_redis, m_session);
      auto data = mstch::map{{"user", user}};
      auto fragment = std::map<std::string, std::string>{{"shout_form", read_file("static/html/fragments/shout_form.html")}};
      fragment["shout"] = read_file("static/html/fragments/shout.html");
      content = read_file("static/html/fragments/welcome.html");
      std::cout << mstch::render(content, data, fragment);
      content = mstch::render(content, data, fragment);
      }
    else
      {
      auto name = name_create();

      while(user_exists(m_redis, user{name}))
        {
        name = name_create();
        }

      content = read_file("static/html/fragments/register.html");
      content = mstch::render(content, mstch::map{{"name", name}});
      }

    return content;
    }

  }

