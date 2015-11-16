#ifndef __WEBDEV_ACCESS
#define __WEBDEV_ACCESS

#include "dto/user.h"
#include "redox/client.hpp"

#include <vector>
#include <string>

namespace webdev
  {

  bool user_exists(redox::Redox & redis, user const & user);
  bool user_create(redox::Redox & redis, user const & user);
  std::vector<std::string> users_getall(redox::Redox & redis);

  bool session_exists(redox::Redox & redis, std::string const & sessionId);
  bool session_store(redox::Redox & redis, std::string const & sessionId, std::string const & name);
  bool session_remove(redox::Redox & redis, std::string const & sessionId);

  }

#endif
