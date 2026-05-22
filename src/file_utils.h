#include "modules/studente.h"

// Salva i dati di un singolo studente in coda al file, usando ';' come delimitatore
// Parametri: puntatore allo studente da aggiungere
// Restituisce un intero : 1 se l'operazione va a buon fine, 0 altrimenti
int registraStudente(studente s);

// Carica tutti gli studenti dal file
// Restituisce il numero totale di studenti
hashtable caricaStudenti();

// Salva i dati di una prenotazione in coda al file, 
// Usa ';' come delimitatore per i campi di prenotazione
// Usa '/' come delimitatore per i campi di data
// Usa ':' come delimitatore per i campi di orario 
// Parametri: puntatore alla prenotazione da aggiungere
// Restituisce un intero : 1 se l'operazione va a buon fine, 0 altrimenti
int registraPrenotazione(prenotazione s);

// Carica tutte le prenotazioni dal file in una lista l
// Restituisce il numero totale di prenotazioni
list caricaPrenotazioni();