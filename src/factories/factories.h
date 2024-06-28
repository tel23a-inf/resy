#ifndef FACTORIES_FACTORIES_H
#define FACTORIES_FACTORIES_H

#include <string>
#include <vector>

namespace resy {

struct Reservation;

/// Erwartet einen String und erstellt ein Reservierungsobjekt.
/// Der String hat das Format "origin;destination".
Reservation reservation_from_string(std::string const& str);

/// Erwartet eine Liste von Strings und erstellt eine Liste von Reservierungen.
std::vector<Reservation> reservations_from_strings(
    std::vector<std::string> const& strings);

}  // namespace resy

#endif
