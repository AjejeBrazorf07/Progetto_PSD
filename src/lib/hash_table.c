#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_table.h"

struct hash_item {
    char *key;
    studente s;
    struct hash_item *next;
};

struct hash {
    int size;              
    struct hash_item **table; 
};

static int hashFun(char *key, int size);
static void deleteList(struct hash_item *p);
static struct hash_item* newItem(char *key, studente s);
static void freeItem(struct hash_item *i);static void deleteList(struct hash_item *p);

// Calcola l'indice della tabella hash per una data chiave (matricola) utilizzando l'algoritmo DJB2.
static int hashFun(char *key, int size) {
    unsigned long hash = 5381;
    int c;

    while ((c = *key++)) {
        hash = ((hash << 5) + hash) + c; 
    }

    return (int)(hash % size);
}

static struct hash_item* newItem(char *key, studente s) {
    struct hash_item *nuovo = malloc(sizeof(struct hash_item));
    if (!nuovo) return NULL;
    
    nuovo->key = strdup(key);
    if (!nuovo->key) { free(nuovo); return NULL; }
    
    nuovo->s = s;
    nuovo->next = NULL;
    return nuovo;
}

static void freeItem(struct hash_item *i) {
    if (i) {
        if (i->key) free(i->key);
        free(i);
    }
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
int InsertHash(hashtable h, char *key, studente s) {
    if (h == NULL || key == NULL || s == NULL) return 0;

    int idx = hashFun(key, h->size);
    struct hash_item *head = h->table[idx];
    struct hash_item *curr = head;

    // Controllo duplicati
    while (curr) {
        if (strcmp(curr->key, key) == 0) return 0;  
        curr = curr->next;
    }

    struct hash_item *elem = newItem(key, s);
    if (elem == NULL) return 0;

    elem->next = head;
    h->table[idx] = elem;
    return 1;  
}

/*
 * Rimuove un elemento dalla tabella in base alla sua chiave univoca.
 * Ricollega i puntatori della lista concatenata per non spezzare la catena.
 */
studente hashDelete(hashtable h, char *key) {
    if (h == NULL || key == NULL) return NULL;

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
            studente estratto = curr->s;
            freeItem(curr);
            return estratto;
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