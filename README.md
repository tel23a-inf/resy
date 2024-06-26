# Projekt: Reservierungssystem

Mit den Aufgaben in diesem Repo wird die Logik für ein einfaches Reservierungssystem
in C++ entwickelt, wie es in Zügen eingesetzt werden kann.

## Überblick

Das Reservierungssystem besteht i.W. aus zwei Klassen: `Reservation` und `Seat`.
Ein Objekt vom Typ `Reservation` repräsentiert dabei eine einzelne Reservierung
und enthält zwei Strings, `origin` und `destination`, die den Start- und Zielort
speichern.
Ein `Seat`-Objekt enthält eine Liste solcher Reservierungen sowie eine Sitzplatznummer.
Zusätzlich gibt es eine Reihe von Hilfsfunktionen, um den unten beschriebenen Ablauf
umzusetzen, sowie ein Programm mit einer `main`-Funktion, in der ein Beispiel umgesetzt
ist.

## Anforderungen

Das hier entwickelte System soll folgenden Ablauf umsetzen:

* Einlesen von Reservierungsdaten aus CSV-Dateien
* Erzeugen von Reservierungsobjekten aus den Daten
* Abfahren einer Beispielroute und Ausgabe der Reservierungen

Solch ein Beispiel ist in der `main`-Funktion in der Datei `resy.cpp`
im Ordner `src/resy` umgesetzt.

### Einlesen von Reservierungsdaten
  
* Pro Sitzplatz gibt es eine Datei im CSV-Format ("_Comma Separated Values_"),
  in der die Reservierungen für diesen Sitzplatz gespeichert sind.
* Eine Zeile enthält dabei jeweils die Daten einer Reservierung im Format
  `<von>;<nach>`, also Start- und Zielname mit einem Semikolon getrennt.

### Erzeugen von Reservierungsobjekten aus den Daten

* Für jede Sitzplatzdatei wird ein `Seat`-Objekt erzeugt, das die Reservierungen
  für diesen Sitzplatz enthält.
* Die Reservierungen müssen dafür aus den Zeilen der Eingabedateien erzeugt
  und in einer `Reservation`-Objekten gespeichert werden.
  Für jeden Sitz gibt es eine solche Liste.
* Anschließend wird aus diesen Listen jeweils ein `Seat`-Objekt erzeugt.

### Abfahren einer Beispielroute und Ausgabe der Reservierungen

* Im Beispielprogramm wird eine Beispielroute mit einigen Stationen definiert.
* Die `Seat`-Klasse bietet eine Methode `display_for_station` an,
  mit der die Reservierungsanzeige für eine bestimmte Station der Route
  abgefragt werden kann.
* Diese Funktion wird im Beispielprogramm für jede Station der Route und jeden
  Sitzplatz einmal aufgerufen, um die Reservierungsdaten für diese Station
  auszugeben.

## Detail-Überblick

### Klasse `Reservation`

* Attribute: `origin` und `destination` vom Typ `std::string`.
* Methoden `origin_pos` und `destination_pos`:
  Erwarten jeweils eine Route und liefern die Positionen der Stationen
  `origin` und `destination` in dieser Route.
* Methode `is_valid_for_route`:
  Erwartet eine Route und prüft, ob die Reservierung für diese Route gültig ist.
  D.h. ob die Stationen `origin` und `destination` in der passenden Reihenfolge
  in der Route vorkommen.

### Klasse `Seat`

* Attribute: `reservations` vom Typ `std::vector<Reservation>` und `seat_number` vom Typ `int`.
* Methoden zur Validierung: `reservations_valid_for_route`, `reservations_overlap_for_route` und `seat_valid`.
  Prüfen verschiedene Aspekte der Reservierungen bzw. ob die Gesamtliste bzgl. einer Route gültig ist.
* Methode `reservations_sorted`:
  Eine Hilfsmethode, die die interne Reservierungsliste nach den jeweiligen Zielstationen sortiert.
* Methode `display_for_station`:
  Erwartet eine Route und eine Station und gibt die Reservierungen für diese Station
  auf diesem Sitzplatz aus.

In der Datei `seat.cpp` gibt es außerdem noch einige Hilfsfunktionen,
die nur intern dort gebraucht werden und daher nicht in der Header-Datei,
sondern in der Quelldatei in einem sog. _anonymen Namensraum_ definiert sind.

### Paket `factories`

Enthält zwei freie Funktionen `reservation_from_string` und `reservations_from_strings`.
Diese sind dafür verantwortlich, die Reservierungen aus den eingelesenen Strings
zu erzeugen.

### Paket `resy`

Enthält die `main`-Funktion, in der das Beispielprogramm implementiert ist.

## Aufgaben

### Implementierung der Klassen `Reservation` und `Seat` sowie der Hilfsfunktionen in `factories`

* Die Klassen/Funktionen sind in den jeweiligen Header-Dateien beschrieben.
  Die Header-Dateien müssen nicht verändert werden.
* In den jeweiligen Quelldateien sind Methoden- und Funktionsrümpfe vorgegeben,
  die Sie vervollständigen müssen.
* In den Quelldateien gibt es auch Tests, die Sie ausführen können, um Ihre
  Implementierung zu überprüfen.

### Erweiterung der `main`-Funktion in `resy.cpp`

* Die `main`-Funktion ist bereits implementiert und enthält ein Beispiel,
  wie die Klassen `Reservation` und `Seat` verwendet werden können.
* Sie können die `main`-Funktion erweitern, um z.B. die interaktive Eingabe
  von Reservierungen oder Routen zu ermöglichen oder um die Ausgabe zu verbessern.
