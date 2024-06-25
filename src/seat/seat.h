#ifndef SEAT_SEAT_H
#define SEAT_SEAT_H

#include <ostream>
#include <string>
#include <vector>

#include "reservation/reservation.h"

namespace resy {

/// Repräsentiert einen Sitzplatz mit Reservierungen.
struct Seat {
  int number;
  std::vector<Reservation> reservations;

  /// Erwartet eine Route und prüft, ob alle Reservierungen dafür gültig sind.
  bool reservations_valid_for_route(
      std::vector<std::string> const& route) const;

  /// Erwartet eine Route und prüft, ob die Reservierungen sich überschneiden.
  bool reservations_overlap_for_route(
      std::vector<std::string> const& route) const;

  /// Erwartet eine Route und prüft, ob die Reservierungsliste gültig ist.
  bool seat_valid(std::vector<std::string> const& route) const;

  /// Erwartet eine Route und liefert eine Liste von Reservierungen, die nach
  /// der Zielstation sortiert ist.
  /// Liefert eine leere Liste, wenn es eine ungültige Reservierung gibt.
  std::vector<Reservation> reservations_sorted(
      std::vector<std::string> const& route) const;

  /// Erwartet eine Route und einen Stationsnamen.
  /// Liefert die Reservierungsanzeige für den Sitz, wenn die Station der
  /// nächste Halt ist.
  std::string display_for_station(std::vector<std::string> const& route,
                                  std::string const& station) const;
};

}  // namespace resy

std::ostream& operator<<(std::ostream& os, resy::Seat const& seat);

#endif
