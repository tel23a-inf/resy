#include <iostream>
#include <string>
#include <vector>

#include "factories/factories.h"
#include "files/files.h"
#include "reservation/reservation.h"
#include "seat/seat.h"

using namespace std;
using namespace resy;

int main() {
  auto resfile_1 = read_file("seat1.csv");
  std::cout << "resfile_1: " << resfile_1.size() << std::endl;
  for (auto const& line : resfile_1) {
    std::cout << line << std::endl;
  }
  auto resfile_2 = read_file("seat2.csv");
  std::cout << "resfile_2: " << resfile_2.size() << std::endl;
  for (auto const& line : resfile_2) {
    std::cout << line << std::endl;
  }

  auto reservations_1 = reservations_from_strings(resfile_1);
  auto reservations_2 = reservations_from_strings(resfile_2);

  Seat seat_1{1, reservations_1};
  Seat seat_2{2, reservations_2};

  vector<string> route{"Mannheim",   "Frankfurt", "Kassel",
                       "Goettingen", "Hannover",  "Hamburg"};

  for (auto const& station : route) {
    cout << "Station: " << station << endl;
    cout << seat_1 << " " << seat_1.display_for_station(route, station) << endl;
    cout << seat_2 << " " << seat_2.display_for_station(route, station) << endl;
  }

  return 0;
}
