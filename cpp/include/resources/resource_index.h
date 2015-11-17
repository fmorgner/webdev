#ifndef __WEBDEV_RESOURCE_INDEX
#define __WEBDEV_RESOURCE_INDEX

#include "redox.hpp"
#include <httpserver.hpp>

namespace webdev
  {

  struct resource_index : httpserver::http_resource<resource_index>
    {
    resource_index(redox::Redox & redis, std::string const & templ);

    void render_GET(httpserver::http_request const & request, httpserver::http_response * * const response);

    private:
      redox::Redox & m_redis;
      std::string const m_template;
    };

  }

#endif
