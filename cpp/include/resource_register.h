#ifndef __WEBDEV_RESOURCE_REGISTER
#define __WEBDEV_RESOURCE_REGISTER

#include "redox.hpp"
#include <httpserver.hpp>

namespace webdev
  {

  using httpserver::http_request;
  using httpserver::http_response;
  using redox::Redox;

  struct resource_register : httpserver::http_resource<resource_register>
    {

    explicit resource_register(Redox & redis);

    void render_POST(http_request const & request, http_response * * const response);

    private:
      redox::Redox & m_redis;
    };

  }

#endif

