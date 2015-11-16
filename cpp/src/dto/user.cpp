#include "dto/user.h"
#include "support/hash.h"

namespace webdev
  {

  user::user(std::string const & name) : m_name{name}, m_hash{webdev::hash(name)}
    {

    }

  user::user(Json::Value const & json) : m_name{json["name"].asString()}, m_hash{webdev::hash(m_name)}
    {

    }

  std::string user::name() const
    {
    return m_name;
    }

  std::string user::hash() const
    {
    return m_hash;
    }

  Json::Value user::json() const
    {
    auto json = Json::Value{};

    json["name"] = m_name;
    json["hash"] = m_hash;

    return json;
    }

  }

