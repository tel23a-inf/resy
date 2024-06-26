#include "reservation.h"

#include "test.h"

namespace resy {

size_t Reservation::origin_pos(std::vector<std::string> const& route) const {
  // TODO
  return 0;
}

size_t Reservation::destination_pos(
    std::vector<std::string> const& route) const {
  // TODO
  return 0;
}

bool Reservation::is_valid_for_route(
    std::vector<std::string> const& route) const {
  // TODO
  return false;
}

TEST_CASE("origin_pos") {
  Reservation res{"Mannheim", "Frankfurt"};

  SUBCASE("found") {
    CHECK(res.origin_pos({"Mannheim", "Darmstadt", "Frankfurt"}) == 0);
  }

  SUBCASE("not found") {
    CHECK(res.origin_pos({"Darmstadt", "Frankfurt"}) == 2);
  }
}

TEST_CASE("destination_pos") {
  Reservation res{"Mannheim", "Frankfurt"};

  SUBCASE("found") {
    CHECK(res.destination_pos({"Mannheim", "Darmstadt", "Frankfurt"}) == 2);
  }

  SUBCASE("not found") {
    CHECK(res.destination_pos({"Mannheim", "Darmstadt"}) == 2);
  }
}

TEST_CASE("is_valid_for_route") {
  Reservation res{"Mannheim", "Frankfurt"};

  SUBCASE("ok") {
    CHECK(res.is_valid_for_route({"Mannheim", "Darmstadt", "Frankfurt"}));
  }

  SUBCASE("wrong order") {
    CHECK_FALSE(res.is_valid_for_route({"Frankfurt", "Darmstadt", "Mannheim"}));
  }

  SUBCASE("missing stop") {
    CHECK_FALSE(res.is_valid_for_route({"Mannheim", "Darmstadt"}));
  }
}

}  // namespace resy

std::ostream& operator<<(std::ostream& os, resy::Reservation const& res) {
  return os << res.origin << " -> " << res.destination;
}
