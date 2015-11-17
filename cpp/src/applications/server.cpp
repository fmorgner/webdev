#include "resources/resource_index.h"
#include "resources/resource_register.h"
#include "resources/resource_session.h"
#include "resources/resource_users.h"
#include "redox.hpp"

int main()
  {
  auto webserver = httpserver::webserver{httpserver::create_webserver{8000}.max_threads(5)};

  redox::Redox redis{};
  redis.connect();

  auto users = webdev::resource_users{redis};
  auto regis = webdev::resource_register{redis};
  auto sessi = webdev::resource_session{redis};
  auto index = webdev::resource_index{redis, "static/html/index.html"};

  webserver.register_resource("/", &index, true);
  webserver.register_resource("/users", &users, true);
  webserver.register_resource("/register", &regis, true);
  webserver.register_resource("/session", &sessi, true);

  webserver.start(true);
  }

