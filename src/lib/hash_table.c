#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_table.h"


struct hash {
    int size;              
    struct item **table;   
};


int hashFun(char *key, int size);                
// struct item* newItem(char *key, ); 
static void deleteList(struct item *p);


// Calcola l'indice della tabella hash per una data chiave (matricola) utilizzando l'algoritmo DJB2.
int hashFun(char *key, int size) {
    // Numero iniziale per ottimizzare la distribuzione
    unsigned long hash = 5381;
    int c;

    while ((c = *key++)) {
        hash = ((hash << 5) + hash) + c; 
    }

    // Restituisce un intero compreso tra 0 e (size - 1).
    return (int)(hash % size);
}


// Crea e inizializza una nuova tabella hash.
hashtable newHashtable(int size) {
    hashtable h = (struct hash *) malloc(sizeof(struct hash));
    if (h == NULL) {       
        return NULL;
    }

    h->size = size;  

    h->table = (struct item **) calloc(size, sizeof(struct item *));
    if (h->table == NULL) {  
        free(h);             
        return NULL;
    }

    return h;  
}


// Inserisce un nuovo elemento nella tabella hash.
int InsertHash(hashtable h, item elem) {
    int idx = hashFun(elem.key, h->size);
    struct item *head = h->table[idx];
    struct item *curr = head;

    while (curr) {
        if (strcmp(curr->key, elem.key) == 0) {
            return 0;  
        }
        curr = curr->next;
    }

    h->table[idx] = newItem(elem.key, elem.intero1, elem.intero2);
    h->table[idx]->next = head;

    return 1;  
}


/*
 * Rimuove un elemento dalla tabella in base alla sua chiave univoca.
 * Ricollega i puntatori della lista concatenata per non spezzare la catena.
 */
struct item *hashDelete(hashtable h, char *key) {
    int idx = hashFun(key, h->size);
    struct item *prev = h->table[idx];
    struct item *curr = prev;
    struct item *head = prev;

    while(curr) {
        if(strcmp(curr->key, key) == 0) { 
            // Gestione del caso in cui l'elemento da rimuovere sia la testa della lista
            if(curr == head) {
                h->table[idx] = curr->next;
            } else {
                prev->next = curr->next;
            }
            return curr; 
        }
        prev = curr;
        curr = curr->next;
    }
    return NULL; 
}


/*
 * Dealloca completamente la tabella hash e tutte le liste ad essa collegate.
 */
void DestroyHashtable(hashtable h) {
    for(int i = 0; i < h->size; i++) {
        deleteList(h->table[i]);
    }
    free(h->table);
    free(h);
}


/*
 * Dealloca iterativamente tutti i nodi di una lista concatenata,
 * per evitare il rischio di overflow dello stack in caso di moltissime collisioni.
 */
static void deleteList(struct item *p) {
    struct item *nextNode;
    while (p != NULL) {
        nextNode = p->next;  
        free(p);             
        p = nextNode;        
    }
}