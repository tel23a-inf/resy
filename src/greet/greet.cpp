#include <string>

#include "test.h"

namespace resy {

std::string greet(const std::string& name) { return "Hello, " + name + "!"; }

TEST_CASE("greet") {
  CHECK(greet("Alice") == "Hello, Alice!");
  CHECK(greet("Bob") == "Hello, Bob!");
}
}  // namespace resy
