#include "resources/resource_index.h"
#include "resources/resource_register.h"
#include "resources/resource_session.h"
#include "resources/resource_users.h"
#include "resources/resource_shout.h"
#include "resources/resource_shouts.h"
#include "resources/resource_all.h"
#include "redox.hpp"

int main()
  {
  auto webserver = httpserver::webserver{httpserver::create_webserver{8000}.max_threads(5)};

  redox::Redox redis{};
  if(!redis.connect())
    {
    return 1;
    }

  auto users = webdev::resource_users{redis};
  auto regis = webdev::resource_register{redis};
  auto sessi = webdev::resource_session{redis};
  auto index = webdev::resource_index{redis};
  auto shout = webdev::resource_shout{redis};
  auto shouts = webdev::resource_shouts{redis};
  auto all = webdev::resource_all{redis};

  webserver.register_resource("/", &index, true);
  webserver.register_resource("/users", &users, true);
  webserver.register_resource("/register", &regis, true);
  webserver.register_resource("/session", &sessi, true);
  webserver.register_resource("/shout", &shout, true);
  webserver.register_resource("/shouts", &shouts, true);
  webserver.register_resource("/all", &all, true);

  webserver.start(true);
  }

