#include "list.h"
#include "hash_table.h"
#include "modules/studente.h"
#include "modules/prenotazione.h"
#include "data_ora.h"
#include "giorno_settimana.h"

// Salva i dati di un singolo studente in coda al file, usando ';' come delimitatore
// Parametri: puntatore allo studente da aggiungere
// Restituisce un intero : 1 se l'operazione va a buon fine, 0 altrimenti
int registraStudente(studente s);

// Carica tutti gli studenti dal file
// Restituisce una tabella hash contenente tutti gli studenti
hashtable caricaStudenti();

// Salva i dati di una prenotazione in coda al file, 
// Usa ';' come delimitatore per i campi di prenotazione
// Usa '/' come delimitatore per i campi di data
// Usa ':' come delimitatore per i campi di orario 
// Parametri: puntatore alla prenotazione da aggiungere
// Restituisce un intero : 1 se l'operazione va a buon fine, 0 altrimenti
int registraPrenotazione(prenotazione s);

// Carica tutte le prenotazioni dal file in una lista l
// Restituisce una lista contenenti tutte le prenotazioni della settimana corrente
list caricaPrenotazioni();


// Inizializza il piano orario e le aule per la settimana corrente.
// Restituisce una lista in cui la testa è il lunedì e la coda è il venerdì della settimana corrente.
list inizializzaPianoSettimanale(void);