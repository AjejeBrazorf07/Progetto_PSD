#include "data_ora.h"

typedef struct Prenotazione *prenotazione;

// Crea una nuova prenotazione vuota e restituisce un puntatore ad essa
// Parametri: la stringa matricola, una struttura data, due strutture orario e un puntatore al posto assegnato
prenotazione creaPrenotazione(char *matricola, data nuova_data, orario ingresso, orario uscita, int posto_assegnato);

// Dealloca la prenotazione e i suoi campi
// Prende come parametro un puntatore a Prenotazione
void rimuoviPrenotazione(prenotazione p);

// stampa i campi di Prenotazione presa come parametro
void visualizzaPrenotazione(prenotazione p);

// Restituisce il puntatore alla stringa contenente la matricola dello studente.
// Parametri: p (il puntatore alla prenotazione)
// Restituisce: la stringa della matricola, oppure NULL se la prenotazione non è valida.
char* ottieniMatricolaPR(prenotazione p);

// Restituisce l'oggetto data associato al giorno della prenotazione.
// Parametri: p (il puntatore alla prenotazione)
// Restituisce: l'oggetto 'data', oppure NULL se la prenotazione non è valida.
data ottieniDataPrenotazione(prenotazione p);

// Restituisce l'orario previsto per l'inizio dell'occupazione del posto.
// Parametri: p (il puntatore alla prenotazione)
// Restituisce: l'oggetto 'orario' di ingresso, oppure NULL se la prenotazione non è valida.
orario ottieniOrarioIngresso(prenotazione p);

// Restituisce l'orario previsto per il termine dell'occupazione del posto.
// Parametri: p (il puntatore alla prenotazione)
// Restituisce: l'oggetto 'orario' di uscita, oppure NULL se la prenotazione non è valida.
orario ottieniOrarioUscita(prenotazione p);

// Restituisce il numero identificativo del posto in aula assegnato allo studente.
// Parametri: p (il puntatore alla prenotazione)
// Restituisce: un intero rappresentante il posto, oppure -1 se la prenotazione non è valida.
int ottieniPostoAssegnato(prenotazione p);