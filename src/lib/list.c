#include <stdio.h>
#include <stdlib.h>
#include "list_item.h"
#include "list.h"
#include "modules/prenotazione.h"

struct node {
    list_item value;
    struct node *next;
};

// Inizializza una lista vuota restituendo un puntatore nullo. 
list newList(void) {
    return NULL;
}

// Verifica se la lista è vuota.
// Ritorna: 1 se vuota, 0 altrimenti.
int emptyList(list l) {
    return l == NULL;
}

// Inserisce un elemento in testa alla lista.
// Se l'allocazione fallisce, interrompe il programma per evitare 
// comportamenti indefiniti a valle.
list consList(list_item val, list l) {
    list new_node = (list)malloc(sizeof(struct node));
    if (new_node == NULL) {
        fprintf(stderr, "Errore: impossibile allocare memoria.\n");
        exit(EXIT_FAILURE);
    }
    new_node->value = val;
    new_node->next = l;
    return new_node;
}

// Restituisce il resto della lista escludendo il primo nodo.
list tailList(list l) {
    if (emptyList(l)) {
        fprintf(stderr, "Errore: coda di una lista vuota.\n");
        exit(EXIT_FAILURE);
    }
    return l->next;
}

// Restituisce il valore in testa alla lista senza rimuoverlo.
list_item getFirst(list l) {
    if (emptyList(l)) {
        fprintf(stderr, "Errore: primo elemento di una lista vuota.\n");
        exit(EXIT_FAILURE);
    }
    return l->value;
}

// Calcola la lunghezza della lista.
// Richiede lo scorrimento completo dell'intera struttura
int sizeList(list l) {
    int count = 0;
    while (l != NULL) {
        count++;
        l = l->next;
    }
    return count;
}

// Cerca la prima occorrenza di un valore.
// Parametri: l (lista da scorrere), val (valore da cercare)
// Restituisce posizione (in base 1) o -1 se non trovato.
// Vale solo per l'item prenotazione
int posItem(list l, list_item val) {
    int pos = 1;
    while (l != NULL) {
            if (comparaPrenotazioni(val, l->value) == 1) {
                return pos;
            }
        
        pos++;
        l = l->next;
    }
    return -1;
}

// Recupera il valore alla posizione specificata (in base 1).
list_item getItem(list l, int pos) {
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

// Inverte l'ordine dei nodi nella lista modificando i puntatori (in-place).
// Restituisce la nuova testa della lista invertita.
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

// Elimina l'elemento in posizione pos dalla lista
list removeList(list l, int pos) {
    list l1, prec; 

    if (pos == 0 && l != NULL) {
        l1 = l;
        l = tailList(l);
        free(l1);
    }
    else { 
        int i = 0;
        prec = l;
        while (i < pos - 1 && prec != NULL) {
            prec = prec->next;
            i++;
        }

        if (prec != NULL && prec->next != NULL) {
            l1 = prec->next;
            prec->next = l1->next;
            free(l1);
        }
    }

    return l;
}

// Stampa tutti i valori della lista su una singola riga. 
// Parametri: l (lista da scorrere), data_type (tipo di dato da gestire)
void outputList(list l, int data_type) {
    while (l != NULL) {
        // Decide se gestire prenotazioni (0) o giorni della settimana (1).
        if (data_type == 0) {
            visualizzaPrenotazione(l->value);
        } else if (data_type == 1) {
            // output_item(l->value);
        }
        printf(" ");
        l = l->next;
    }
    printf("\n");
}