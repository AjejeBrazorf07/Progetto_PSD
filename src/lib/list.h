#include "list_item.h"

typedef struct node *list;

// Crea una nuova lista vuota e restituisce un puntatore ad essa.
// Non richiede parametri in ingresso.
list newList(void);

// Verifica se la lista specificata è vuota.
// Prende come parametro un puntatore a una lista e restituisce un intero.
// Tipicamente, restituisce un valore non-zero (1) se la lista è vuota e 0 se la lista non è vuota.
int emptyList(list l);

// Aggiunge un nuovo elemento in testa alla lista.
// Prende come parametri l'elemento da aggiungere e un puntatore alla lista a cui aggiungere l'elemento.
// Restituisce un puntatore alla nuova testa della lista aggiornata.
list consList(item val, list l);

// Restituisce la lista privata del suo primo elemento (ovvero il puntatore al secondo nodo).
// Se la lista è vuota, il comportamento di questa funzione genera un errore e termina l'esecuzione del programma.
// Prende come parametro un puntatore a una lista.
list tailList(list l);

// Restituisce il valore del primo elemento della lista senza rimuoverlo.
// Se la lista è vuota, il comportamento di questa funzione genera un errore e termina l'esecuzione del programma.
// Prende come parametro un puntatore a una lista e restituisce un valore di tipo item.
item getFirst(list l);

// Calcola e restituisce il numero totale di elementi presenti nella lista.
// Prende come parametro un puntatore a una lista e restituisce un intero.
int sizeList(list l);

// Cerca la posizione della prima occorrenza di un elemento specificato all'interno della lista.
// Prende come parametri un puntatore a una lista e l'elemento da cercare (di tipo item).
// Restituisce un intero che rappresenta la posizione dell'elemento (partendo da 1), oppure -1 se l'elemento non viene trovato.
int posItem(list l, item val);

// Restituisce l'elemento situato in una determinata posizione all'interno della lista.
// Prende come parametri un puntatore a una lista e un intero che rappresenta la posizione desiderata (partendo da 1).
// Restituisce il valore di tipo item trovato, oppure un valore speciale NULLITEM se la posizione non esiste.
item getItem(list l, int pos);

// Inverte l'ordine dei nodi all'interno della lista.
// Prende come parametro un puntatore a una lista.
// Restituisce un puntatore alla nuova testa della lista invertita.
list reverseList(list l);

// Stampa a video tutti gli elementi presenti nella lista in modo sequenziale, separandoli con uno spazio.
// Prende come parametro un puntatore a una lista.
// Non restituisce alcun valore.
void outputList(list l);