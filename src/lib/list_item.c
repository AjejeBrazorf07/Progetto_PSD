#include <stdio.h>
#include <string.h>
#include "../modules/prenotazione.h"
#include "../modules/data_ora.h"
#include "list_item.h"



// Confronta due prenotazioni e stabilisce se sono uguali.
int comparaPrenotazioni(item p1, item p2) {
    if (p1 == NULL || p2 == NULL) return 0;

    if (strcmp(ottieniMatricolaPR(p1), ottieniMatricolaPR(p2)) != 0) return 0;
    if (comparaData(ottieniDataPrenotazione(p1), ottieniDataPrenotazione(p2)) == 0) return 0;
    if (comparaOrario(ottieniOrarioIngresso(p1), ottieniOrarioIngresso(p2)) == 0) return 0;
    if (comparaOrario(ottieniOrarioUscita(p1), ottieniOrarioUscita(p2)) == 0) return 0;
    if (ottieniPostoAssegnato(p1) != ottieniPostoAssegnato(p2)) return 0;

    return 1;
}