#include "dto/shout.h"
#include "support/hash.h"

namespace webdev
  {

  shout::shout(std::string const & text, struct user const & shouter) :
    m_user{shouter},
    m_text{text},
    m_hash{webdev::hash(text + shouter.json().toStyledString())}
    {

    }

  shout::shout(Json::Value const & json) :
    m_user{json["user"]},
    m_text{json["text"].asString()},
    m_hash{webdev::hash(m_text + m_user.json().toStyledString())}
    {

    }

  shout::operator mstch::map() const
    {
    return {{"text", m_text}, {"hash", m_hash}, {"user", mstch::map(m_user)}};
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

