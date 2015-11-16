#include "resource_users.h"
#include "resource_register.h"
#include "redox.hpp"

#include <iostream>

int main()
  {
  auto webserver = httpserver::webserver{httpserver::create_webserver{8000}.max_threads(5)};

  redox::Redox redis{};
  redis.connect();

  auto users = webdev::resource_users{redis};
  auto regis = webdev::resource_register{redis};

  webserver.register_resource("/users", &users, true);
  webserver.register_resource("/register", &regis, true);

  webserver.start(true);
  }

