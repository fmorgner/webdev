#ifndef __WEBDEV_RESOURCE_USERS
#define __WEBDEV_RESOURCE_USERS

#include "dto/user.h"
#include "redox.hpp"
#include <httpserver.hpp>

namespace webdev
  {

  struct resource_users : httpserver::http_resource<resource_users>
    {
    resource_users(redox::Redox & redis);

    void render_GET(httpserver::http_request const & request, httpserver::http_response * * const response);

    private:
      redox::Redox & m_redis;
    };

  }

#endif
