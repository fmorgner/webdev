#ifndef __WEBDEV_SHOUT
#define __WEBDEV_SHOUT

#include "dto/user.h"

namespace webdev
  {

  struct shout
    {
    shout(std::string const & text, user const & shouter);

    std::string text() const;
    std::string hash() const;
    user user() const;

    Json::Value json() const;

    private:
      std::string const m_text;
      std::string const m_hash;
      struct user const & m_user;
    };

  };

#endif

