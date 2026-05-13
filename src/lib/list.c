#include <stdio.h>
#include <stdlib.h>
#include "list_item.h"
#include "list.h"

struct node {
    item value;
    struct node *next;
};

/* Inizializza una lista vuota restituendo un puntatore nullo. */
list newList(void) {
    return NULL;
}

/*
 * Verifica se la lista è vuota.
 * Ritorna: 1 se vuota, 0 altrimenti.
 */
int emptyList(list l) {
    return l == NULL;
}

/*
 * Inserisce un elemento in testa alla lista.
 * Se l'allocazione fallisce, interrompe il programma per evitare 
 * comportamenti indefiniti a valle.
 */
list consList(item val, list l) {
    list new_node = (list)malloc(sizeof(struct node));
    if (new_node == NULL) {
        fprintf(stderr, "Errore: impossibile allocare memoria.\n");
        exit(EXIT_FAILURE);
    }
    new_node->value = val;
    new_node->next = l;
    return new_node;
}

/* Ritorna il resto della lista escludendo il primo nodo. */
list tailList(list l) {
    if (emptyList(l)) {
        fprintf(stderr, "Errore: coda di una lista vuota.\n");
        exit(EXIT_FAILURE);
    }
    return l->next;
}

/* Ritorna il valore in testa alla lista senza rimuoverlo. */
item getFirst(list l) {
    if (emptyList(l)) {
        fprintf(stderr, "Errore: primo elemento di una lista vuota.\n");
        exit(EXIT_FAILURE);
    }
    return l->value;
}

/* * Calcola la lunghezza della lista.
 * Richiede lo scorrimento completo dell'intera struttura (costo lineare).
 */
int sizeList(list l) {
    int count = 0;
    while (l != NULL) {
        count++;
        l = l->next;
    }
    return count;
}

/*
 * Cerca la prima occorrenza di un valore.
 * Parametri: l (lista da scorrere), val (valore da cercare), data_type (tipo di dato da gestire)
 * Ritorna: posizione (in base 1) o -1 se non trovato.
 */
int posItem(list l, item val, int data_type) {
    int pos = 1;
    while (l != NULL) {
        // Decide se gestire prenotazioni (0) o giorni della settimana (1).
        if (data_type==0) {

        } else if (data_type==1) {

        }

        /*if (eq(l->value, val)) {
            return pos;
        }
        pos++;
        l = l->next;*/
    }
    return -1;
}

/* Recupera il valore alla posizione specificata (in base 1). */
item getItem(list l, int pos) {
    int count = 1;
    while (l != NULL) {
        if (count == pos) {
            return l->value;
        }
        count++;
        l = l->next;
    }
    return NULLITEM;
}

/* * Inverte l'ordine dei nodi nella lista modificando i puntatori (in-place).
 * Ritorna: la nuova testa della lista invertita.
 */
list reverseList(list l) {
    list prev = NULL;
    list current = l;
    list next = NULL;
    
    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    return prev;
}

/* Stampa tutti i valori della lista su una singola riga. 
Parametri: l (lista da scorrere), data_type (tipo di dato da gestire)
*/
void outputList(list l, int data_type) {
    while (l != NULL) {
        // Decide se gestire prenotazioni (0) o giorni della settimana (1).
        if (data_type == 0) {
            // visualizzaPrenotazioni è operatore dell'ADT Studente
            // output_item(l->value);   
        } else if (data_type == 1) {
            // output_item(l->value);
        }
        printf(" ");
        l = l->next;
    }
    printf("\n");
}