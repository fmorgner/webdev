#ifndef __WEBDEV_RESOURCE_SHOUT
#define __WEBDEV_RESOURCE_SHOUT

#include "redox.hpp"
#include <httpserver.hpp>

namespace webdev
  {

  using httpserver::http_request;
  using httpserver::http_response;
  using redox::Redox;

  struct resource_shout : httpserver::http_resource<resource_shout>
    {
    explicit resource_shout(Redox & redis);

    void render_POST(http_request const & request, http_response * * const response);

    private:
      redox::Redox & m_redis;

    private:
      static constexpr char const * kSuccessHead{"{ \"success\": true,\n  \"user\": \n"};
      static constexpr char const * kSuccessTail{"}\n"};
      static constexpr char const * kCreationFailed{"{ \"success\": false,\n  \"code\": 1 }\n"};
      static constexpr char const * kJSONInvalid{"{ \"success\": false,\n  \"code\": 2 }\n"};
      static constexpr char const * kDataNotJSON{"{ \"success\": false,\n  \"code\": 3 }\n"};
      static constexpr char const * kSessionInvalid{"{ \"success\": false,\n  \"code\": 4 }\n"};
    };

  }

#endif

