#ifndef FILES_FILES_H
#define FILES_FILES_H

#include <string>
#include <vector>

namespace resy {

struct Seat;

/// Erwartet eine Liste von Dateinamen.
/// Liest die Dateien ein und erstellt eine Liste von Listen von Strings.
/// Jede der äußeren Listen enthält die Zeilen einer Datei.
std::vector<std::string> read_file(std::string const& filename);

}  // namespace resy

#endif
