#ifndef __WEBDEV_SHOUT
#define __WEBDEV_SHOUT

#include "dto/user.h"

namespace webdev
  {

  struct shout
    {
    shout(std::string const & text, user const & shouter);
    explicit shout(Json::Value const &);

    operator mstch::map() const;

    std::string text() const;
    std::string hash() const;
    user user() const;

    Json::Value json() const;

    private:
      struct user const m_user;
      std::string const m_text;
      std::string const m_hash;
    };

  };

#endif

