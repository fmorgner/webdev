#include "user.h"
#include "hash.h"

namespace webdev
  {

  user::user(std::string const & name) : m_name{name}, m_hash{webdev::hash(name)}
    {

    }

  std::string user::name()
    {
    return m_name;
    }

  std::string user::hash()
    {
    return m_hash;
    }

  Json::Value user::json()
    {
    auto json = Json::Value{};

    json["name"] = m_name;
    json["hash"] = m_hash;

    return json;
    }

  }

