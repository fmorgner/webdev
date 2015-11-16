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

    private:
      static constexpr char const * kInvalidSession{"{ \"valid\": false }\n"};
      static constexpr char const * kValidSession{"{ \"valid\": true }\n"};
      static constexpr char const * kLogOutSuccess{"{ \"success\": true }\n"};
      static constexpr char const * kLogOutFailure{"{ \"success\": false }\n"};
    };

  }

#endif
