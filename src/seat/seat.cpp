#include "seat.h"

#include "test.h"

namespace {

/// Liefert die Position einer Station in einer Route.
size_t station_pos(std::vector<std::string> const& route,
                   std::string const& station) {
  for (size_t i = 0; i < route.size(); ++i) {
    if (route[i] == station) {
      return i;
    }
  }
  return route.size();
}

/// Prüft, ob eine Station in einer Route gültig ist.
bool station_valid_for_route(std::vector<std::string> const& route,
                             std::string const& station) {
  // HINWEIS: Verwenden Sie station_pos.
  return station_pos(route, station) < route.size();
}

}  // namespace

namespace resy {

bool Seat::reservations_valid_for_route(
    std::vector<std::string> const& route) const {
  // HINWEIS: Verwenden Sie Reservation::is_valid_for_route.
  for (auto r : reservations) {
    if (!r.is_valid_for_route(route)) {
      return false;
    }
  }
  return true;
}

bool Seat::reservations_overlap_for_route(
    std::vector<std::string> const& route) const {
  // HINWEIS: Verwenden Sie Reservation::origin_pos und
  //          Reservation::destination_pos in einer geschachtelten Schleife.
  for (size_t i = 0; i < reservations.size(); ++i) {
    for (size_t j = i + 1; j < reservations.size(); ++j) {
      if (reservations[i].origin_pos(route) <
              reservations[j].destination_pos(route) &&
          reservations[j].origin_pos(route) <
              reservations[i].destination_pos(route)) {
        return true;
      }
    }
  }
  return false;
}

bool Seat::seat_valid(std::vector<std::string> const& route) const {
  // HINWEIS: Verwenden Sie reservations_valid_for_route und
  //          reservations_overlap_for_route.
  return reservations_valid_for_route(route) &&
         !reservations_overlap_for_route(route);
}

std::vector<Reservation> Seat::reservations_sorted(
    std::vector<std::string> const& route) const {
  // HINWEIS: Erstellen Sie eine Kopie der Reservierungen und sortieren Sie
  //          diese anschließend. Dafür können Sie z.B. die Funktion std::sort
  //          aus der STL verwenden.
  //          Alternativ können Sie auch ihre eigene Sortierfunktion schreiben.
  //          Wichtig: Ist die Sitzplatzbelegung ungültig, so macht die Funktion
  //          keinen Sinn. Dies sollte also vorher geprüft werden.
  if (!seat_valid(route)) return {};

  std::vector<Reservation> result = reservations;
  std::sort(result.begin(), result.end(),
            [&route](Reservation const& a, Reservation const& b) {
              return a.destination_pos(route) < b.destination_pos(route);
            });
  return result;
}

std::string Seat::display_for_station(std::vector<std::string> const& route,
                                      std::string const& station) const {
  // HINWEIS: Verwenden Sie reservations_sorted und station_pos.
  //          Prüfen Sie vorher, ob die Sitzplatzbelegung gültig ist
  //          und ob die Station in der Route enthalten ist.
  if (!seat_valid(route)) return "ggf. freigeben";
  if (!station_valid_for_route(route, station)) return "ggf. freigeben";
  size_t current_pos = station_pos(route, station);

  for (auto r : reservations_sorted(route)) {
    if (current_pos < r.destination_pos(route)) {
      return r.origin + " -> " + r.destination;
    }
  }
  return "frei";
}

TEST_CASE("reservations_valid_for_route") {
  std::vector<Reservation> reservations{
      {"Mannheim", "Darmstadt"},
      {"Darmstadt", "Frankfurt"},
  };
  Seat seat{42, reservations};

  SUBCASE("all valid") {
    CHECK(seat.reservations_valid_for_route(
        {"Mannheim", "Darmstadt", "Frankfurt"}));
  }

  SUBCASE("one invalid") {
    CHECK_FALSE(seat.reservations_valid_for_route({"Mannheim", "Frankfurt"}));
  }
}

TEST_CASE("reservations_overlap_for_route") {
  std::vector<std::string> route{"Mannheim", "Darmstadt", "Frankfurt"};

  SUBCASE("no overlap") {
    std::vector<Reservation> reservations{
        {"Mannheim", "Darmstadt"},
        {"Darmstadt", "Frankfurt"},
    };
    Seat seat{42, reservations};
    CHECK_FALSE(seat.reservations_overlap_for_route(route));
  }

  SUBCASE("overlap") {
    std::vector<Reservation> reservations{
        {"Mannheim", "Frankfurt"},
        {"Darmstadt", "Frankfurt"},
    };
    Seat seat{42, reservations};
    CHECK(seat.reservations_overlap_for_route(route));
  }
}

TEST_CASE("seat_valid") {
  std::vector<std::string> route{"Mannheim", "Darmstadt", "Frankfurt"};

  SUBCASE("valid") {
    std::vector<Reservation> reservations{
        {"Mannheim", "Darmstadt"},
        {"Darmstadt", "Frankfurt"},
    };
    Seat seat{42, reservations};
    CHECK(seat.seat_valid(route));
  }

  SUBCASE("missing station") {
    std::vector<Reservation> reservations{
        {"Mannheim", "Darmstadt"},
        {"Darmstadt", "Kassel"},
    };
    Seat seat{42, reservations};
    CHECK_FALSE(seat.seat_valid(route));
  }

  SUBCASE("overlap") {
    std::vector<Reservation> reservations{
        {"Mannheim", "Frankfurt"},
        {"Darmstadt", "Frankfurt"},
    };
    Seat seat{42, reservations};
    CHECK_FALSE(seat.seat_valid(route));
  }
}

TEST_CASE("reservations_sorted") {
  std::vector<Reservation> reservations{
      {"Hannover", "Hamburg"},
      {"Frankfurt", "Kassel"},
      {"Mannheim", "Frankfurt"},
  };
  Seat seat{42, reservations};

  SUBCASE("valid") {
    std::vector<std::string> route{"Mannheim",   "Frankfurt", "Kassel",
                                   "Goettingen", "Hannover",  "Hamburg"};
    auto sorted = seat.reservations_sorted(route);
    REQUIRE(sorted.size() == 3);
    CHECK(sorted[0].origin == "Mannheim");
    CHECK(sorted[0].destination == "Frankfurt");
    CHECK(sorted[1].origin == "Frankfurt");
    CHECK(sorted[1].destination == "Kassel");
    CHECK(sorted[2].origin == "Hannover");
    CHECK(sorted[2].destination == "Hamburg");
  }

  SUBCASE("missing station") {
    std::vector<std::string> route{"Mannheim", "Frankfurt", "Kassel"};
    auto sorted = seat.reservations_sorted(route);
    REQUIRE(sorted.size() == 0);
  }

  SUBCASE("overlap") {
    std::vector<std::string> route{"Mannheim",   "Kassel",   "Frankfurt",
                                   "Goettingen", "Hannover", "Hamburg"};
    auto sorted = seat.reservations_sorted(route);
    REQUIRE(sorted.size() == 0);
  }
}

#define CHECK_DISPLAY(seat, route, station, expected) \
  CHECK(seat.display_for_station(route, station) == expected)

TEST_CASE("display_for_station") {
  std::vector<Reservation> reservations{
      {"Mannheim", "Frankfurt"},
      {"Frankfurt", "Kassel"},
      {"Hannover", "Hamburg"},
  };
  Seat seat{42, reservations};

  SUBCASE("valid") {
    std::vector<std::string> route{"Mannheim",   "Frankfurt", "Kassel",
                                   "Goettingen", "Hannover",  "Hamburg"};
    CHECK_DISPLAY(seat, route, "Mannheim", "Mannheim -> Frankfurt");
    CHECK_DISPLAY(seat, route, "Frankfurt", "Frankfurt -> Kassel");
    CHECK_DISPLAY(seat, route, "Kassel", "Hannover -> Hamburg");
    CHECK_DISPLAY(seat, route, "Goettingen", "Hannover -> Hamburg");
    CHECK_DISPLAY(seat, route, "Hannover", "Hannover -> Hamburg");
    CHECK_DISPLAY(seat, route, "Hamburg", "frei");
  }

  SUBCASE("missing station") {
    std::vector<std::string> route{"Mannheim", "Frankfurt", "Kassel"};
    CHECK_DISPLAY(seat, route, "Mannheim", "ggf. freigeben");
    CHECK_DISPLAY(seat, route, "Frankfurt", "ggf. freigeben");
    CHECK_DISPLAY(seat, route, "Kassel", "ggf. freigeben");
    CHECK_DISPLAY(seat, route, "Goettingen", "ggf. freigeben");
    CHECK_DISPLAY(seat, route, "Hannover", "ggf. freigeben");
    CHECK_DISPLAY(seat, route, "Hamburg", "ggf. freigeben");
  }

  SUBCASE("wrong order") {
    std::vector<std::string> route{"Mannheim",   "Kassel",   "Frankfurt",
                                   "Goettingen", "Hannover", "Hamburg"};
    CHECK_DISPLAY(seat, route, "Mannheim", "ggf. freigeben");
    CHECK_DISPLAY(seat, route, "Frankfurt", "ggf. freigeben");
    CHECK_DISPLAY(seat, route, "Kassel", "ggf. freigeben");
    CHECK_DISPLAY(seat, route, "Goettingen", "ggf. freigeben");
    CHECK_DISPLAY(seat, route, "Hannover", "ggf. freigeben");
    CHECK_DISPLAY(seat, route, "Hamburg", "ggf. freigeben");
  }
}

}  // namespace resy

std::ostream& operator<<(std::ostream& os, resy::Seat const& seat) {
  os << "Seat " << seat.number << ": [";
  for (auto const& r : seat.reservations) {
    os << r << " ";
  }
  os << "]";
  return os;
}
