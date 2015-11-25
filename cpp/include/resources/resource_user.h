#ifndef __WEBDEV_RESOURCE_USER
#define __WEBDEV_RESOURCE_USER

#include "resources/resource_frontend.h"

namespace webdev
  {

  struct resource_user : resource_frontend<resource_user>
    {
    resource_user(redox::Redox & redis);

    std::string content() const;
    };

  }

#endif

