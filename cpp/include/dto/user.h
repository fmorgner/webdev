#ifndef __WEBDEV_USER
#define __WEBDEV_USER

#include <json/value.h>
#include "mstch/mstch.hpp"

#include <string>

namespace webdev
  {

  struct user
    {
    explicit user(std::string const & name);
    explicit user(Json::Value const & json);

    operator mstch::map() const;

    std::string name() const;
    std::string hash() const;

    Json::Value json() const;

    private:
      std::string const m_name;
      std::string const m_hash;
    };

  }


#endif
