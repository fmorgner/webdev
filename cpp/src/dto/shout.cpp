#include "dto/shout.h"
#include "support/hash.h"

namespace webdev
  {

  shout::shout(std::string const & text, struct user const & shouter) :
    m_text{text},
    m_hash{webdev::hash(text + shouter.json().toStyledString())},
    m_user{shouter}
    {

    }

  std::string shout::text() const
    {
    return m_text;
    }

  std::string shout::hash() const
    {
    return m_hash;
    }

  struct user shout::user() const
    {
    return m_user;
    }

  Json::Value shout::json() const
    {
    auto json = Json::Value{};

    json["hash"] = m_hash;
    json["text"] = m_text;
    json["user"] = m_user.json();

    return json;
    }

  }

