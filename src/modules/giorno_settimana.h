#include "data_ora.h"
#include "../lib/list.h"

typedef struct Giorno_settimana *giorno_settimana;

#define NUM_FASCE 4
#define NUM_POSTI 100

// Crea e inizializza un elemento del tipo giorno_settimana.
// Parametri: puntatore a un elemento data d corrispondente al giorno da creare
// Restituisce un puntatore a giorno_settimana creato.
giorno_settimana creaGiornoSettimana(data giorno);

// Verifica se una data appartiene alla settimana corrente (Lun-Ven).
// Parametri: puntatore a un elemento data d.
// Restituisce 1 se la data fa parte della settimana corrente, 0 altrimenti.
int verificaDataSettimana(data d);

// Scorre la lista settimana e aggiorna il posto che corrisponde alla fascia oraria con lo stato (0 libero, 1 prenotato, 2 occupato)
/* Parametri: lista contenente i giorni della settimana, il giorno da ottenere,
il posto e la fascia oraria della prenotazione, lo stato da associare al posto */
// Restituisce 1 se l'operazione è andata a buon fine, 0 altrimenti
int aggiornaPosto(list settimana, int giorno_sett, int fascia_oraria, int posto, int stato);

// Scorre la lista dei giorni della settimana 
// Parametri: lista contenente i giorni della settimana, il giorno da ottenere (compreso tra 1 e 5), il posto e la fascia oraria della prenotazione
// Restituisce lo stato del posto corrispondente al giorno e alla fascia oraria della prenotazione, oppure -1 per indicare un errore
int verificaPosto(list settimana, int giorno_sett, int fascia_oraria, int posto);

// Stampa il numero di posti disponibili per ogni fascia oraria di giorno_sett (come side effect)
// Parametri: giorno_sett è il giorno della settimana ( 1 <= giorno_sett <= 5). Settimana è la lista che contiene i giorni della settimana
void visualizzaAulaStudio(int giorno_sett, list settimana);
    