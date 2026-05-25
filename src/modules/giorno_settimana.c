#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "giorno_settimana.h"


struct Giorno_settimana {
    data giorno;
    int mappa_posti[NUM_FASCE][NUM_POSTI];
};


// Crea e inizializza una struttura giorno_settimana.
giorno_settimana creaGiornoSettimana(data giorno) {
    struct Giorno_settimana *g = malloc(sizeof(struct Giorno_settimana));

    if (g == NULL) {
        return NULL;
    }

    g->giorno = giorno; 

    for (int i = 0; i < NUM_FASCE; i++) {
        g->mappa_posti[i] = calloc(NUM_POSTI, sizeof(int));

        if (g->mappa_posti[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(g->mappa_posti[j]);
            }
            free(g);
            return NULL;
        }
    }

    return g;
}


// Verifica se la data passata come parametro appartiene alla settimana corrente
int verificaDataSettimana(data d) {
    time_t tempo = time(NULL);
    struct tm data_corrente = *localtime(&tempo);

    // Trasforma la domenica da 0 a 7
    if (data_corrente.tm_wday == 0) data_corrente.tm_wday = 7;

    // Calcola i giorni di distanza da lunedì
    int giorni_da_lunedi = data_corrente.tm_wday - 1;

    // Sposta la data a lunedì
    data_corrente.tm_mday -= giorni_da_lunedi;
    mktime(&d);

    for (int i = 1; i < 6; i++) {
        struct tm g = data_corrente;

        // Calcola il giorno del mese corretto
        g.tm_mday += (i - 1);
        mktime(&g);

        data data_giorno = nuovaData(i, g.tm_mday, g.tm_mon + 1, g.tm_year + 1900);

        if (comparaData(d, data_giorno) == 1) {
            distruggiData(d);
            return 1;
        }


        distruggiData(d);
    }

    return 0;
}