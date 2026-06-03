typedef struct Data *data;
typedef struct Orario *orario;

// Alloca dinamicamente e inizializza una nuova struttura data.
// Parametri:
// giorno_settimana: intero da 1 (Lunedì) a 5 (Venerdì)
// giorno, mese, anno
// Ritorna: puntatore alla nuova data creata, o NULL in caso di errore.
data nuovaData(int giorno_settimana, int giorno, int mese, int anno);

// Stampa a video la data nel formato "Giorno_della_settimana gg/mm/aa.
// Parametri: d (puntatore alla data da visualizzare)
void visualizzaData(data d);

// Confronta due date e stabilisce se sono uguali.
// Restituisce 1 se sono uguali, 0 altrimenti.
// Prende come parametro due date.
int comparaData(data d1, data d2);

// Dealloca la struttura Data presa come parametro
void distruggiData(data d);

//Restituisce il giorno della settimana o -1 per indicare un errore
// Prende come parametro una data
int ottieniGiornoSettimana(data d);

// Restituisce il giorno della data o -1 per indicare un errore
// prende come parametro una data
int ottieniGiorno(data d);

// Restituisce il mese della data o -1 per indicare un errore
// Prende come parametro una data
int ottieniMese(data d);

// Restituisce l'anno della data o -1 per indicare un errore
// Prende come parametro una data
int ottieniAnno(data d);

// Calcola la data esatta (gg/mm/aaaa) della settimana in corso a partire dal numero del giorno (1 = Lunedì, 5 = Venerdì).
// Parametri: il giorno della settimana (da 1 a 5)
// Restituisce la data corrispondente
data ottieniDataDaGiornoSettimana(int giorno_scelto);

// Alloca dinamicamente e inizializza una nuova struttura orario.
// Parametri: ora, minuti (componenti numeriche dell'orario)
// Ritorna: puntatore al nuovo orario creato, o NULL in caso di errore.
orario nuovoOrario(int ora, int minuti);

// Stampa a video l'orario nel formato hh:mm.
// Parametri: o (puntatore all'orario da visualizzare)
void visualizzaOrario(orario o);

// Confronta due orari e stabilisce se sono uguali.
// Restituisce 1 se sono uguali, 0 altrimenti.
// Prende come parametro due orari.
int comparaOrario(orario o1, orario o2);

// Dealloca la struttura orario presa come parametro
void distruggiOrario(orario o);

// Restituisce l'ora o -1 per indicare un errore
// Prende come parametro un orario
int ottieniOra(orario o);

// Restituisce i minuti, o -1 per indicare un errore
// Prende come parametro un orario
int ottieniMinuti(orario o);