#include "factories.h"

#include "reservation/reservation.h"
#include "seat/seat.h"
#include "test.h"

namespace resy {

Reservation reservation_from_string(std::string const& str) {
  // HINWEIS: Sie können z.B. die Methode std::string::find verwenden,
  //          um die Position des Trennzeichens ';' zu finden.
  //          Anschließend können Sie die Methode std::string::substr
  //          verwenden, um die beiden Teile des Strings zu extrahieren.
  // TODO
  return {};
}

std::vector<Reservation> reservations_from_strings(
    std::vector<std::string> const& strings) {
  std::vector<Reservation> reservations;
  // HINWEIS: Verwenden Sie reservation_from_string in einer Schleife.
  // TODO
  return reservations;
}

TEST_CASE("reservation_from_string") {
  auto reservation = reservation_from_string("A;B");
  CHECK(reservation.origin == "A");
  CHECK(reservation.destination == "B");
}

TEST_CASE("reservations_from_strings") {
  std::vector<std::string> strings = {"A;B", "B;C"};
  auto reservations = reservations_from_strings(strings);
  CHECK(reservations.size() == 2);
  auto res_seat_1 = reservations[0];
  auto res_seat_2 = reservations[1];
  CHECK(res_seat_1.origin == "A");
  CHECK(res_seat_1.destination == "B");
  CHECK(res_seat_2.origin == "B");
  CHECK(res_seat_2.destination == "C");
}

}  // namespace resy
