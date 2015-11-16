// @CMAKE_CUTE_LIBRARY=gnutls
// @CMAKE_CUTE_DEPENDENCY=src/support/encoding.cpp
// @CMAKE_CUTE_DEPENDENCY=src/support/hash.cpp

#include "third_party/cute/cute.h"
#include "third_party/cute/cute_runner.h"
#include "third_party/cute/ide_listener.h"
#include "third_party/cute/xml_listener.h"

#include "hash.h"

void test_hash_zero_length_string()
  {
  auto out = webdev::hash("");
  ASSERT_EQUAL("e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855", out);
  }

void test_hash_string_webdev()
  {
  auto out = webdev::hash("webdev");
  ASSERT_EQUAL("326829359aaf8a6f282fd9a43b6c616397dd6b529fc1e1640caac286584bc98b", out);
  }

int main(int argc, char ** argv)
  {
  auto suite = cute::suite{};

  suite += CUTE(test_hash_zero_length_string);
  suite += CUTE(test_hash_string_webdev);

  auto xml = cute::xml_file_opener{argc, argv};
  auto listener = cute::xml_listener<cute::ide_listener<>>{xml.out};
  auto runner = cute::makeRunner(listener, argc, argv);

  return !runner(suite);
  }
