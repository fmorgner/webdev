#include "resource_users.h"

int main()
  {
  auto webserver = httpserver::webserver{httpserver::create_webserver{8080}.max_threads(5)};

  auto userVec = std::vector<webdev::user>{webdev::user{"flix"}, webdev::user{"stefan"}, webdev::user{"benny"}};

  auto users = webdev::resource_users{userVec};

  webserver.register_resource("/users", & users, true);

  webserver.start(true);
  }

