// @CMAKE_CUTE_LIBRARY=gnutls
// @CMAKE_CUTE_LIBRARY=jsoncpp
// @CMAKE_CUTE_DEPENDENCY=src/encoding.cpp
// @CMAKE_CUTE_DEPENDENCY=src/user.cpp
// @CMAKE_CUTE_DEPENDENCY=src/hash.cpp

#include "third_party/cute/cute.h"
#include "third_party/cute/cute_runner.h"
#include "third_party/cute/ide_listener.h"
#include "third_party/cute/xml_listener.h"

#include "user.h"

#include <json/json.h>

#include <sstream>

void test_user_hash_empty_name()
  {
  auto user = webdev::user{""};
  ASSERT_EQUAL("e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855", user.hash());
  }

void test_user_hash_name_webdev()
  {
  auto user = webdev::user{"webdev"};
  ASSERT_EQUAL("326829359aaf8a6f282fd9a43b6c616397dd6b529fc1e1640caac286584bc98b", user.hash());
  }

void test_user_name_empty_name()
  {
  auto user = webdev::user{""};
  ASSERT_EQUAL("", user.name());
  }

void test_user_name_name_webdev()
  {
  auto user = webdev::user{"webdev"};
  ASSERT_EQUAL("webdev", user.name());
  }

void test_user_json_name_empty_name()
  {
  auto user = webdev::user{""};
  auto json = Json::Value{};

  json["name"] = "";
  json["hash"] = "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855";

  auto expected = std::ostringstream{};
  expected << json;

  auto actual = std::ostringstream{};
  actual << user.json();

  ASSERT_EQUAL(expected.str(), actual.str());
  }

void test_user_json_name_webdev()
  {
  auto user = webdev::user{"webdev"};
  auto json = Json::Value{};

  json["name"] = "webdev";
  json["hash"] = "326829359aaf8a6f282fd9a43b6c616397dd6b529fc1e1640caac286584bc98b";

  auto expected = std::ostringstream{};
  expected << json;

  auto actual = std::ostringstream{};
  actual << user.json();

  ASSERT_EQUAL(expected.str(), actual.str());
  }

int main(int argc, char ** argv)
  {
  auto suite = cute::suite{};

  suite += CUTE(test_user_hash_empty_name);
  suite += CUTE(test_user_hash_name_webdev);
  suite += CUTE(test_user_name_empty_name);
  suite += CUTE(test_user_name_name_webdev);
  suite += CUTE(test_user_json_name_empty_name);
  suite += CUTE(test_user_json_name_webdev);

  auto xml = cute::xml_file_opener{argc, argv};
  auto listener = cute::xml_listener<cute::ide_listener<>>{xml.out};
  auto runner = cute::makeRunner(listener, argc, argv);

  return !runner(suite, "User tests");
  }

