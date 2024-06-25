#include "files.h"

#include <fstream>

#include "reservation/reservation.h"
#include "seat/seat.h"
#include "test.h"

namespace resy {

std::vector<std::string> read_file(std::string const& filename) {
  std::vector<std::string> lines;
  std::string line;
  std::ifstream file(filename);
  while (std::getline(file, line)) {
    if (!line.empty()) {
      lines.push_back(line);
    }
  }
  return lines;
}

}  // namespace resy
