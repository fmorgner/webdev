#ifndef __WEBDEV_RESOURCE_USERS
#define __WEBDEV_RESOURCE_USERS

#include "dto/user.h"
#include "redox.hpp"
#include "resources/resource_frontend.h"

namespace webdev
  {

  struct resource_users : resource_frontend<resource_users>
    {
    resource_users(redox::Redox & redis);

    std::string content() const;
    };

  }

#endif
