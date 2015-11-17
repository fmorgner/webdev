#include "dto/user.h"
#include "support/access.h"

#include <vector>

namespace webdev
  {

  using std::string;
  using std::vector;
  using redox::Redox;

  bool user_exists(Redox & redis, user const & user)
    {
    return redis.commandSync<int>({"HEXISTS", "users", user.name()}).reply();
    }

  bool user_create(Redox & redis, user const & user)
    {
    return redis.commandSync<string>({"HMSET", "user:" + user.hash(), "name", user.name()}).ok() &&
           redis.commandSync<int>({"HSET", "users", user.name(), user.hash()}).ok();
    }

  user user_get_by_id(Redox & redis, std::string const & id)
    {
    return user{redis.commandSync<string>({"HGET", "user:" + id, "name"}).reply()};
    }

  vector<string> users_getall(Redox & redis)
    {
    auto & result = redis.commandSync<vector<string>>({"HGETALL", "users"});
    return result.ok() ? result.reply() : vector<string>{};
    }

  bool session_exists(Redox & redis, string const & sessionId)
    {
    return redis.commandSync<int>({"HEXISTS", "sessions", sessionId}).reply();
    }

  bool session_store(Redox & redis, string const & sessionId, string const & name)
    {
    return redis.commandSync<int>({"HSET", "sessions", sessionId, name}).reply();
    }

  bool session_remove(Redox & redis, string const & sessionId)
    {
    return redis.commandSync<int>({"HDEL", "sessions", sessionId}).reply();
    }

  }

