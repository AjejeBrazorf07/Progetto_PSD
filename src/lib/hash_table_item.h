#include "modules/studente.h" 

// Definizione della struttura nodo.
struct hash_item {
    char *key;
    studente s;
    struct hash_item *next;
};

typedef struct hash_item *item;

/*
 * Alloca dinamicamente e inizializza un nuovo nodo per la tabella hash.
 * Parametri: key (la matricola), s (i dati dello studente)
 * Ritorna: puntatore al nuovo elemento (item) o NULL in caso di errore di memoria.
 */
item newItem(char *key, studente s);

/*
 * Libera in modo sicuro la memoria allocata per l'item e per la sua chiave.
 * Parametri: i (l'elemento da distruggere)
 */
void freeItem(item i);