#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prenotazione.h"
#include "data_ora.h"


struct Prenotazione {
    char *matricola;
    data data_prenotazione;
    orario fascia_oraria[2];
    int posto_assegnato;
};


// Definizione della funzione creaPrenotazione, che crea e inizializza una nuova struttura Prenotazione
prenotazione creaPrenotazione(char *matricola, data nuova_data, orario ingresso, orario uscita, int *posto_assegnato) {
    if (matricola == NULL) {
        return NULL;
    }

    struct Prenotazione *p = malloc(sizeof(struct Prenotazione));
    if (p == NULL) {
        return NULL;
    }

    p->matricola = malloc(strlen(matricola) + 1);

    if (p->matricola == NULL) {
        free(p);
        return NULL;
    }

    strcpy(p->matricola, matricola);
    p->data_prenotazione = nuova_data;
    p->fascia_oraria[0] = ingresso;
    p->fascia_oraria[1] = uscita;

    // Gestione del parametro opzionale posto_assegnato
    if (posto_assegnato != NULL) {
        p->posto_assegnato = *posto_assegnato;
    } else {
        // valore provvisorio
        p->posto_assegnato = -1; 
    }

    return p;
}

// Definizione della funzione rimuoviPrenotazione, che dealloca i campi e successivamente la struttura Prenotazione
void rimuoviPrenotazione(prenotazione p) {
    if(p!=NULL) {
        free(p->matricola);

        distruggiData(p->data_prenotazione);

        distruggiOrario(p->fascia_oraria[0]);
        distruggiOrario(p->fascia_oraria[1]);

        free(p);
    }
}


// Restituisce la matricola o NULL se la prenotazione non è valida
char* otteniMatricolaPR(prenotazione p) {
    if (p == NULL) return NULL;
    return p->matricola;
}

// Restituisce la data o NULL se la prenotazione non è valida
data ottieniDataPrenotazione(prenotazione p) {
    if (p == NULL) return NULL;
    return p->data_prenotazione;
}

// Restituisce l'orario di ingresso
orario otteniOrarioIngresso(prenotazione p) {
    if (p == NULL) return NULL;
    return p->fascia_oraria[0];
}

// Restituisce l'orario di uscita
orario otteniOrarioUscita(prenotazione p) {
    if (p == NULL) return NULL;
    return p->fascia_oraria[1];
}

// Restituisce il posto assegnato, o -1 per indicare un errore
int ottieniPostoAssegnato(prenotazione p) {
    if (p == NULL) return -1; 
    return p->posto_assegnato;
}


// Stampa i campi della struttura Prenotazione
void visualizzaPrenotazione(prenotazione p) {
    if(p==NULL) return;

    printf("Matricola: %s", p->matricola ? p->matricola : "N/D");
    
    visualizzaData(p->data_prenotazione);
    
    printf("Orario di ingresso: "); 
    visualizzaOrario(p->fascia_oraria[0]);
    
    printf("Orario di uscita: ");
    visualizzaOrario(p->fascia_oraria[1]);
    
    printf("Posto assegnato:%d", p->posto_assegnato);
}