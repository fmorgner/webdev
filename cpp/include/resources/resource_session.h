#ifndef __WEBDEV_RESOURCE_SESSION
#define __WEBDEV_RESOURCE_SESSION

#include "dto/user.h"
#include "redox.hpp"
#include <httpserver.hpp>

namespace webdev
  {

  struct resource_session : httpserver::http_resource<resource_session>
    {
    resource_session(redox::Redox & redis);

    void render_GET(httpserver::http_request const & request, httpserver::http_response * * const response);
    void render_DELETE(httpserver::http_request const & request, httpserver::http_response * * const response);

    private:
      redox::Redox & m_redis;
    };

  }

#endif
