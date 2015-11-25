#ifndef __WEBDEV_RESOURCE_FRONTEND
#define __WEBDEV_RESOURCE_FRONTEND

#include "support/file.h"

#include "mstch/mstch.hpp"
#include "redox.hpp"

#include <httpserver.hpp>


namespace webdev
  {

  template<typename Derived>
  struct resource_frontend : httpserver::http_resource<resource_frontend<Derived>>
    {
    resource_frontend(redox::Redox & redis) :
      m_redis{redis},
      m_template{read_file("static/html/frontend.html")}
      {
      httpserver::http_resource<resource_frontend<Derived>>::disallow_all();
      httpserver::http_resource<resource_frontend<Derived>>::set_allowing("GET", true);
      }

    void render_GET(httpserver::http_request const & request, httpserver::http_response * * const response)
      {
      m_session = request.get_cookie("session");
      m_path = request.get_path_pieces();
      auto result = mstch::render(m_template, mstch::map{{"content", content()}});
      auto builder = httpserver::http_response_builder{result , 200, "text/html"};
      *response = new httpserver::http_response{builder};
      }

    std::string content() const { return ((Derived*)this)->content(); }

    protected:
      redox::Redox & m_redis;
      std::string m_session;
      std::vector<std::string> m_path;

    private:
      std::string const m_template;
    };

  }

#endif

