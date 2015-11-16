// @CMAKE_CUTE_LIBRARY=gnutls
// @CMAKE_CUTE_LIBRARY=jsoncpp
// @CMAKE_CUTE_DEPENDENCY=src/support/encoding.cpp
// @CMAKE_CUTE_DEPENDENCY=src/support/hash.cpp
// @CMAKE_CUTE_DEPENDENCY=src/dto/user.cpp
// @CMAKE_CUTE_DEPENDENCY=src/dto/shout.cpp

#include "third_party/cute/cute.h"
#include "third_party/cute/cute_runner.h"
#include "third_party/cute/ide_listener.h"
#include "third_party/cute/xml_listener.h"

#include "dto/shout.h"

#include <json/json.h>

using namespace std::literals;

void test_shout_json_with_zero_length_text_and_zero_length_user_name()
  {
  auto user = webdev::user{""s};
  auto shout = webdev::shout{"", user};

  auto expectedUser = Json::Value{};
  expectedUser["name"] = "";
  expectedUser["hash"] = "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855";

  auto expectedShout = Json::Value{};
  expectedShout["hash"] = "15c3b370d0556fe69311ea72490b95a06b2cae45926274b58b7becad850c963a";
  expectedShout["text"] = "";
  expectedShout["user"] = expectedUser;

  ASSERT_EQUAL(expectedShout, shout.json());
  }

int main(int argc, char ** argv)
  {
  auto suite = cute::suite{};

  suite += CUTE(test_shout_json_with_zero_length_text_and_zero_length_user_name);

  auto xml = cute::xml_file_opener{argc, argv};
  auto listener = cute::xml_listener<cute::ide_listener<>>{xml.out};
  auto runner = cute::makeRunner(listener, argc, argv);

  return !runner(suite);
  }
