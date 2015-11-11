#ifndef __WEBDEV_RESOURCE_USERS
#define __WEBDEV_RESOURCE_USERS

#include "user.h"

#include <httpserver.hpp>

#include <vector>

namespace webdev
  {

  struct resource_users : httpserver::http_resource<resource_users>
    {
    resource_users(std::vector<user> const & users);

    void render_GET(httpserver::http_request const & request, httpserver::http_response * * const response);

    private:
      std::vector<user> const & m_users;
    };

  }

#endif
