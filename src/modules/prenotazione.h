typedef struct Prenotazione *prenotazione;

// Crea una nuova prenotazione vuota e restituisce un puntatore ad essa
prenotazione creaPrenotazione(char *matricola, data nuova_data, orario ingresso, orario uscita);

// Dealloca la prenotazione e i suoi campi
// Prende come parametro un puntatore a Prenotazione
void rimuoviPrenotazione(prenotazione p);

// stampa i campi di Prenotazione presa come parametro
void visualizzaPrenotazione(prenotazione p);

