#include <stdio.h>
#include <stdlib.h>
#include "data_ora.h"

struct Data {
    int giorno_settimana;
    int giorno;
    int mese;
    int anno;
};

struct Orario {
    int ora;
    int minuti;
};

// Crea e inizializza una nuova data.
data nuovaData(int giorno_settimana, int giorno, int mese, int anno) {
    data d = malloc(sizeof(struct Data));
    if (d == NULL) {
        return NULL; 
    }
    
    d->giorno_settimana = giorno_settimana;
    d->giorno = giorno;
    d->mese = mese;
    d->anno = anno;

    return d;
}

// Visualizza la data formattata nel formato giorno_settimana gg/mm/aa.
void visualizzaData(data d) {
    if (d == NULL) return;

    switch(d->giorno_settimana) {
        case 1:
            printf("Lunedì ");
            break;
        case 2:
            printf("Martedì ");
            break;
        case 3:
            printf("Mercoledì ");
            break;
        case 4:
            printf("Giovedì ");
            break;
        case 5:
            printf("Venerdì ");
            break;
        default:
            printf("Giorno non valido ");
            break;
    }

    printf("%d/%d/%d\n", d->giorno, d->mese, d->anno);
}

// Crea e inizializza un nuovo orario.
orario nuovoOrario(int ora, int minuti) {
    orario o = malloc(sizeof(struct Orario));
    if (o == NULL) {
        return NULL;
    }

    o->ora = ora;
    o->minuti = minuti;
    
    return o;
}

// Formatta l'output per l'orario nel formato hh:mm
void visualizzaOrario(orario o) {
    if (o == NULL) return;
    
    printf("%02d:%02d\n", o->ora, o->minuti);
}