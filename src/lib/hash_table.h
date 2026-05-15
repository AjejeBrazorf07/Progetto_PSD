#include "hash_table_item.h"

typedef struct hash *hashtable;

// Crea una nuova tabella hash di dimensioni specificate e restituisce un puntatore ad essa.
// Prende come parametro un intero che rappresenta il numero di "bucket" (celle) della tabella.
// Restituisce il puntatore alla tabella creata o NULL in caso di fallimento dell'allocazione.
hashtable newHashtable(int size);

// Inserisce un nuovo elemento all'interno della tabella hash.
// Prende come parametri il puntatore alla tabella e l'elemento da inserire (di tipo 'item').
// Restituisce un intero che indica il successo dell'operazione (1) o il fallimento 
// (0) nel caso in cui l'elemento sia già presente (chiave duplicata).
int InsertHash(hashtable h, item elem);

// Rimuove un elemento dalla tabella hash individuandolo tramite la sua chiave.
// Prende come parametri il puntatore alla tabella e una stringa che rappresenta la chiave dell'elemento.
// Restituisce un puntatore all'elemento rimosso per consentirne la gestione, oppure NULL se l'elemento non viene trovato.
item *hashDelete(hashtable h, char *key);

// Dealloca completamente la tabella hash e tutti gli elementi in essa contenuti.
// Prende come parametro il puntatore alla tabella da eliminare.
// Non restituisce alcun valore (void), ma libera tutta la memoria associata alla struttura.
void DestroyHashtable(hashtable h);