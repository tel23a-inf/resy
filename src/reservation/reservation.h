#ifndef RESERVATION_RESERVATION_H
#define RESERVATION_RESERVATION_H

#include <ostream>
#include <string>
#include <vector>

namespace resy {

/// Repräsentiert eine Reservierung für einen Sitzplatz.
struct Reservation {
  std::string origin;
  std::string destination;

  /// Erwartet eine Liste von Stationsnamen und liefert die Position der
  /// Abfahrtsstation in der Route. Falls die Station nicht enthalten ist, wird
  /// die Größe der Route geliefert.
  size_t origin_pos(std::vector<std::string> const& route) const;

  /// Erwartet eine Liste von Stationsnamen und liefert die Position der
  /// Zielstation in der Route. Falls die Station nicht enthalten ist, wird die
  /// Größe der Route geliefert.
  size_t destination_pos(std::vector<std::string> const& route) const;

  /// Erwartet eine Liste von Stationsnamen und prüft, ob die Reservierung für
  /// diese Route gültig ist. Eine Reservierung ist gültig, wenn die Route die
  /// Haltestellen aus der Reservierung in der richtigen Reihenfolge enthält.
  bool is_valid_for_route(std::vector<std::string> const& route) const;
};

}  // namespace resy

std::ostream& operator<<(std::ostream& os, resy::Reservation const& res);

#endif
