#include "../modules/prenotazione.h"

// Il tipo item è definito come un puntatore generico perchè non è noto a priori se l'item è una pretazione o un giorno della settimana
typedef void *item;

// Definizione del valore nullo per l'item.
#define NULLITEM NULL

// Confronta due prenotazioni e stabilisce se sono uguali.
// Restituisce 1 se sono uguali, 0 altrimenti.
// Prende come parametro due prenotazioni.
int comparaPrenotazioni(item p1, item p2);