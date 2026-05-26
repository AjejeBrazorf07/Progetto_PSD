#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "giorno_settimana.h"


// FASCE ORARIE
// 0 = 9-11
// 1 = 11-13
// 2 = 13-15
// 3 = 15-17

struct Giorno_settimana {
    data giorno;
    int mappa_posti[NUM_FASCE][NUM_POSTI];
};


// Crea e inizializza una struttura giorno_settimana.
giorno_settimana creaGiornoSettimana(data giorno) {
    struct Giorno_settimana *g = calloc(1, sizeof(struct Giorno_settimana));

    if (g == NULL) {
        return NULL;
    }

    g->giorno = giorno; 

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

// Scorre la lista settimana e aggiorna il posto che corrisponde alla fascia oraria con lo stato (0 libero, 1 prenotato, 2 occupato)
int aggiornaPosto(list settimana, int giorno_sett, int fascia_oraria, int posto, int stato) {
    giorno_settimana g = getItem(settimana, giorno_sett);
    
    if (g != NULL && fascia_oraria >= 0 && fascia_oraria < NUM_FASCE && posto >= 0 && posto < NUM_POSTI) {
        g->mappa_posti[fascia_oraria][posto] = stato;
        return 1;
    } 
    
    return 0;
}

// Scorre la lista dei giorni della settimana 
// Restituisce lo stato del posto corrispondente al giorno e alla fascia oraria della prenotazione, oppure -1 per indicare un errore
int verificaPosto(list settimana, int giorno_sett, int fascia_oraria, int posto) {
    giorno_settimana g = getItem(settimana, giorno_sett);
    
    if (g != NULL && fascia_oraria >= 0 && fascia_oraria < NUM_FASCE && posto >= 0 && posto < NUM_POSTI) {
        return g->mappa_posti[fascia_oraria][posto];
    } 
    
    return -1;
}