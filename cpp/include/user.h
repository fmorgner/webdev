#ifndef __WEBDEV_USER
#define __WEBDEV_USER

#include <json/value.h>

#include <string>

namespace webdev
  {

  struct user
    {
    explicit user(std::string const & name);

    std::string name();
    std::string hash();

    Json::Value json();

    private:
      std::string const m_name;
      std::string const m_hash;
    };

  }


#endif
