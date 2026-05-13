#include <stdio.h> 
#include <stdlib.h>
#include "item.h"
#include "queue.h"

struct node {       
    item value;
    struct node *next; 
};

struct c_queue {
    struct node *head, *tail;
    int numel; 
};

/*
 * Inizializza una nuova coda vuota allocando la memoria necessaria.
 * Ritorna: puntatore alla nuova coda, o NULL in caso di errore.
 */
queue newQueue(void) {
    struct c_queue *q = malloc(sizeof(struct c_queue));

    if (q == NULL)
        return NULL;

    q->numel = 0;
    q->head = NULL;
    q->tail = NULL;
    return q;
} 

/*
 * Verifica lo stato della coda.
 * Parametri: q (puntatore alla coda)
 * Ritorna: 1 se vuota, 0 se contiene elementi, -1 se la struttura è NULL.
 */
int emptyQueue(queue q) {
     if (q == NULL) 
            return -1; 
     return q->numel == 0; 
}

/*
 * Inserisce un nuovo elemento in fondo alla coda (FIFO).
 * Parametri: val (elemento da inserire), q (coda di destinazione)
 * Ritorna: 1 se successo, 0 o -1 in caso di errore.
 */
int enqueue(item val, queue q) {
    if (q == NULL)
            return -1;

    struct node *nuovo = malloc(sizeof(struct node));
    if (nuovo == NULL) return 0;

    nuovo->value = val;
    nuovo->next = NULL;

    // Se la coda era vuota, il nuovo nodo è contemporaneamente head e tail
    if (q->head == NULL)
         q->head = nuovo;
    else 
         q->tail->next = nuovo;

    q->tail = nuovo; 
    (q->numel)++;
    return 1;
}

/*
 * Estrae e restituisce l'elemento in testa alla coda.
 * Rilascia la memoria del nodo estratto per prevenire memory leak.
 * Parametri: q (coda da cui estrarre)
 * Ritorna: l'elemento estratto o NULLITEM in caso di coda vuota/non allocata.
 */
item dequeue(queue q) {
    if (q == NULL || q->numel == 0) 
        return NULLITEM;

    item result = q->head->value;
    struct node *temp = q->head;

    q->head = q->head->next;
    free(temp);

    // Se abbiamo rimosso l'ultimo elemento rimasto, resettiamo anche tail
    if (q->head == NULL)
        q->tail = NULL;

    (q->numel)--;

    return result;
}