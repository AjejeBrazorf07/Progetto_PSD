#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_table.h"
#include "hash_table_item.h"

struct hash {
    int size;              
    struct hash_item **table; 
};

int hashFun(char *key, int size);
static void deleteList(struct hash_item *p);

// Calcola l'indice della tabella hash per una data chiave (matricola) utilizzando l'algoritmo DJB2.
int hashFun(char *key, int size) {
    unsigned long hash = 5381;
    int c;

    while ((c = *key++)) {
        hash = ((hash << 5) + hash) + c; 
    }

    return (int)(hash % size);
}

// Crea e inizializza una nuova tabella hash.
hashtable newHashtable(int size) {
    hashtable h = (struct hash *) malloc(sizeof(struct hash));
    if (h == NULL) {       
        return NULL;
    }

    h->size = size;  

    h->table = (struct hash_item **) calloc(size, sizeof(struct hash_item *));
    if (h->table == NULL) {  
        free(h);             
        return NULL;
    }

    return h;  
}

// Inserisce un nuovo elemento nella tabella hash.
int InsertHash(hashtable h, item elem) {
    if (elem == NULL || elem->key == NULL) return 0; // Controllo di sicurezza

    int idx = hashFun(elem->key, h->size);
    struct hash_item *head = h->table[idx];
    struct hash_item *curr = head;

    // Controllo duplicati
    while (curr) {
        if (strcmp(curr->key, elem->key) == 0) {
            return 0;  
        }
        curr = curr->next;
    }

    // Inserimento in testa: l'elem viene direttamente agganciato
    elem->next = head;
    h->table[idx] = elem;

    return 1;  
}

/*
 * Rimuove un elemento dalla tabella in base alla sua chiave univoca.
 * Ricollega i puntatori della lista concatenata per non spezzare la catena.
 */
item hashDelete(hashtable h, char *key) {
    int idx = hashFun(key, h->size);
    struct hash_item *prev = h->table[idx];
    struct hash_item *curr = prev;
    struct hash_item *head = prev;

    while(curr) {
        if(strcmp(curr->key, key) == 0) { 
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
static void deleteList(struct hash_item *p) {
    struct hash_item *nextNode;
    while (p != NULL) {
        nextNode = p->next;  
        freeItem(p);      
        p = nextNode;        
    }
}