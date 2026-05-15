#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "studente.h"

struct Studente {
    char *nome;
    char *matricola;
    char *corso_laurea;
};


// Definizione della funzione creaStudente, che crea e inizializza una nuova stuttura Studente
studente creaStudente(char *nome, char *matricola, char *corso_laurea) {
    struct Studente *s=malloc(sizeof(struct Studente));

    if (s==NULL) {
        return NULL;
    }

    s->nome=malloc(sizeof(strlen(nome)));
    if(s->nome==NULL) {
        return NULL;
    }
    strcpy(s->nome, nome);
    s->matricola=malloc(sizeof(strlen(matricola)));
    if(s->nome==NULL) {
        return NULL;
    }
    strcpy(s->matricola, matricola);
    s->corso_laurea=malloc(sizeof(strlen(corso_laurea)));
    if(s->nome==NULL) {
        return NULL;
    }
    strcpy(s->corso_laurea, corso_laurea);
    return s;
}

// Definizione della funzione rimuoviStudente, che dealloca la memoria prima dei campi interi, e poi della struttura
void rimuoviStudente(studente s) {
    if(s!=NULL) {
        free(s->nome);
        free(s->matricola);
        free(s->corso_laurea);
        free(s);
    }
}

// Definizione della funzione visualizzaStudente, che stampa i campi della struttura
void visualizzaStudente(studente s) {
    if (s == NULL) return; 
    printf("Nome: %s\n", s->nome ? s->nome : "N/D");
    printf("Matricola: %s\n", s->matricola ? s->matricola : "N/D");
    printf("Corso di laurea: %s\n", s->corso_laurea ? s->corso_laurea : "N/D");
}
    

// Definizione della funzione modificaStudente, che gestisce l'aggiornamento dei campi tramite uno switch.
// Il parametro 'modifica' sostituisce il puntatore esistente
void modificaStudente(studente s, int operazione, char *modifica) {
    if(s==NULL || modifica==NULL) return;
    
    switch(operazione) {
        case 1:
            free(s->nome);
            s->nome=modifica;
        break;
        case 2:
            free(s->matricola);
            s->matricola=modifica;
            break;
        case 3:
            free(s->corso_laurea);
            s->corso_laurea=modifica;
            break;
        default:
        printf("Campo non valido. \n");
        break;
    }
}