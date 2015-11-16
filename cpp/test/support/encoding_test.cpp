// @CMAKE_CUTE_DEPENDENCY=src/support/encoding.cpp

#include "third_party/cute/cute.h"
#include "third_party/cute/xml_listener.h"
#include "third_party/cute/ide_listener.h"
#include "third_party/cute/cute_runner.h"

#include "support/encoding.h"

using namespace std::literals;
using namespace webdev;

void test_encode_webdev()
  {
  ASSERT_EQUAL("776562646576"s, encode_hex("webdev"s));
  }

void test_encode_empty_string()
  {
  ASSERT_EQUAL("", encode_hex(""));
  }

void test_decode_313938323f()
  {
  ASSERT_EQUAL("1982?", decode_hex("313938323f"s));
  }

void test_decode_empty_string()
  {
  ASSERT_EQUAL(""s, decode_hex(""s));
  }

void test_decode_invalid_characters()
  {
  ASSERT_EQUAL(""s, decode_hex("qwerty"s));
  }

void test_decode_odd_number_of_characters()
  {
  ASSERT_EQUAL(""s, decode_hex("ffcd1"));
  }

int main(int argc, char * * argv)
  {
  auto suite = cute::suite{};

  suite += CUTE(test_encode_empty_string);
  suite += CUTE(test_encode_webdev);
  suite += CUTE(test_decode_empty_string);
  suite += CUTE(test_decode_313938323f);
  suite += CUTE(test_decode_invalid_characters);
  suite += CUTE(test_decode_odd_number_of_characters);

  auto xml = cute::xml_file_opener{argc, argv};
  auto listener = cute::xml_listener<cute::ide_listener<>>{xml.out};

  return !cute::makeRunner(listener, argc, argv)(suite, "Byte to HEX encoding");
  }

