typedef struct Data *data;
typedef struct Orario *orario;

/*
Alloca dinamicamente e inizializza una nuova struttura data.
Parametri:
giorno_settimana: intero da 1 (Lunedì) a 5 (Venerdì)
giorno, mese, anno
Ritorna: puntatore alla nuova data creata, o NULL in caso di errore.
*/
data nuovaData(int giorno_settimana, int giorno, int mese, int anno);


// Stampa a video la data nel formato "Giorno_della_settimana gg/mm/aa.
// Parametri: d (puntatore alla data da visualizzare)
void visualizzaData(data d);


// Alloca dinamicamente e inizializza una nuova struttura orario.
// Parametri: ora, minuti (componenti numeriche dell'orario)
// Ritorna: puntatore al nuovo orario creato, o NULL in caso di errore.
orario nuovoOrario(int ora, int minuti);


// Stampa a video l'orario nel formato hh:mm.
// Parametri: o (puntatore all'orario da visualizzare)
void visualizzaOrario(orario o);

// Dealloca la struttura Data presa come parametro
void distruggiData(data d);

// Dealloca la struttura orario presa come parametro
void distruggiOrario(orario o);