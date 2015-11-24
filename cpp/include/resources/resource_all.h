#ifndef __WEBDEV_RESOURCE_ALL
#define __WEBDEV_RESOURCE_ALL

#include "resources/resource_frontend.h"

namespace webdev
  {

  struct resource_all : resource_frontend<resource_all>
    {
    resource_all(redox::Redox & redis);

    std::string content() const;
    };

  }

#endif

