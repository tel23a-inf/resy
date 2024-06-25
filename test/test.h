#ifndef TEST_H
#define TEST_H

/* ANMERKUNG:
    Dies ist ein "Proxy"-Header.
    Es wird nur eine einzige Datei aus einem Unterverzeichnis eingebunden.
    Dort wiederum passiert das eigentliche Setup für das Testsystem (doctest).

    Um Tests in Quelldateien zu aktivieren, muss dieser Setup-Header jedes Mal
    eingebunden werden. Der Vorteil dieses Proxy-Headers ist, dass so in den
    Quelldateien die Include-Zeile einfach bleibt (nur `#include "test.h"`).
    Außerdem ist es so einfacher, bei Bedarf die Verzeichnisstruktur des
    Test-Ordners zu ändern, ohne dass alle Quelldateien angepasst werden müssen.
*/

#include "doctest_setup/doctest_setup.h"

#endif
