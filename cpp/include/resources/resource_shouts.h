#ifndef __WEBDEV_RESOURCE_SHOUTS
#define __WEBDEV_RESOURCE_SHOUTS

#include "redox.hpp"
#include <httpserver.hpp>

namespace webdev
  {

  using httpserver::http_request;
  using httpserver::http_response;
  using redox::Redox;

  struct resource_shouts : httpserver::http_resource<resource_shouts>
    {
    explicit resource_shouts(Redox & redis);

    void render_GET(http_request const & request, http_response * * const response);

    private:
      redox::Redox & m_redis;

    private:
      static constexpr char const * kUserInvalid{"{ \"success\": false,\n  \"code\": 1 }\n"};
    };

  }

#endif

