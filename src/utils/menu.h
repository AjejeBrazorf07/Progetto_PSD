#include "../lib/list.h"
#include "../lib/hash_table.h"
#include "../lib/queue.h"

// Mostra il menu principale con le opzioni del sistema di gestione dell'aula studio
void stampaMenu(void);

// Gestisce l'interfaccia di registrazione per un nuovo studente, salvandolo in memoria (hashtable) e su file
// Parametri: studenti (tabella hash in cui inserire il nuovo studente)
void aggiungiStudente(hashtable studenti);

// Gestisce l'inserimento di una nuova prenotazione, verificando la disponibilità e aggiornando lo stato dei posti
// Parametri: studenti (hashtable per validare la matricola), prenotazioni (lista attuale), settimana (mappa dei posti)
// Restituisce: la lista aggiornata delle prenotazioni
list nuovaPrenotazione(hashtable studenti, list prenotazioni, list settimana);

// Permette a uno studente di cancellare una propria prenotazione futura, liberando il posto associato
// Parametri: prenotazioni (lista attuale), settimana (struttura per resettare lo stato del posto)
// Restituisce: la lista aggiornata delle prenotazioni
list annullaPrenotazione(list prenotazioni, list settimana);

// Visualizza graficamente lo stato dell'aula studio (libero/occupato) per tutta la settimana
// Parametri: settimana (struttura che mantiene lo stato aggiornato dei posti)
void aggiornamentoPosti(list settimana);

// Esegue il check-in per uno studente che ha già una prenotazione per il giorno e la fascia oraria corrente
// Parametri: prenotazioni (lista per la validazione), settimana (mappa posti), studenti_in_aula (lista presenti)
void checkInPrenotati(list prenotazioni, list settimana, list studenti_in_aula);

// Assegna un posto immediato a uno studente senza prenotazione, oppure lo inserisce in lista d'attesa se l'aula è piena
// Parametri: settimana (mappa posti), lista_attesa (coda studenti), studenti_in_aula (lista presenti)
// Restituisce: la coda aggiornata della lista d'attesa
queue checkInNonPrenotati(list settimana, queue lista_attesa, list studenti_in_aula);

// Interfaccia per la gestione del check-in (prenotati e non prenotati)
// Parametri: prenotazioni, settimana, studenti_in_aula, lista_attesa
// Restituisce: la coda aggiornata della lista d'attesa
queue checkIn(list prenotazioni, list settimana, list studenti_in_aula, queue lista_attesa);

// Cerca una matricola all'interno della coda e la cancella dalla lista d'attesa
// Parametri: lista_attesa (la coda degli studenti)
// Restituisce: la coda aggiornata senza lo studente cancellato
queue cancellaDaListaAttesa(queue lista_attesa);

// Stampa a video la posizione e l'elenco di tutte le matricole attualmente in lista d'attesa
// Parametri: lista_attesa (la coda da scorrere e stampare)
void visualizzaListaAttesa(queue lista_attesa);

// Menu per la gestione della d'attesa
// Parametri: lista_attesa (la coda su cui operare)
// Restituisce: la coda aggiornata
queue gestioneListaAttesa(queue lista_attesa);

// Registra l'uscita di uno studente, libera il suo posto e fa subentrare in automatico il primo in lista d'attesa (se presente)
// Parametri: settimana (mappa posti), studenti_in_aula (lista presenti da aggiornare), lista_attesa (coda per il subentro)
void checkOut(list settimana, list studenti_in_aula, queue lista_attesa);

// Mostra l'affluenza per la fascia oraria corrente
// Parametri: studenti_in_aula, lista_attesa, settimana
void visualizzaStudenti(list studenti_in_aula, queue lista_attesa, list settimana);

// azzera i posti prenotati ma mai occupati (No-Show dopo 30 min) e fa avanzare la coda
// Parametri: settimana, lista_attesa, studenti_in_aula
void cancellaPrenotazioniScadute(list settimana, queue lista_attesa, list studenti_in_aula);

// Mostra il numero progressivo totale di accessi storici dell'aula
void menuStoricoAccessi(void);

// Mostra il resoconto globale dell'aula, incluse prenotazioni, accessi effettivi, no-show e distribuzione fasce
// Parametri: settimana, prenotazioni, lista_attesa
void report(list settimana, list prenotazioni, queue lista_attesa);

// Dealloca la memoria delle strutture usate dal programma alla sua chiusura
/* Parametri: settimana (mappa posti), studenti_in_aula (lista presenti da aggiornare), lista_attesa (coda per il subentro), 
studenti (tabella hash che contiene tutti gli studenti registrati), prenotazioni (lista di tutte le prenotazioni) */
void chiusuraProgramma(list settimana, list studenti_in_aula, queue lista_attesa, list prenotazioni, hashtable studenti);