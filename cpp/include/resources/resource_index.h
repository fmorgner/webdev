#ifndef __WEBDEV_RESOURCE_INDEX
#define __WEBDEV_RESOURCE_INDEX

#include "resources/resource_frontend.h"

namespace webdev
  {

  struct resource_index : resource_frontend<resource_index>
    {
    resource_index(redox::Redox & redis);

    std::string content() const;
    };

  }

#endif

