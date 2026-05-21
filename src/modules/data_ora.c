#include <stdio.h>
#include <stdlib.h>
#include "data_ora.h"


struct Data {
    int giorno_settimana;
    int giorno;
    int mese;
    int anno;
};

struct Orario {
    int ora;
    int minuti;
};


// Crea e inizializza una nuova data.
data nuovaData(int giorno_settimana, int giorno, int mese, int anno) {
    data d = malloc(sizeof(struct Data));
    if (d == NULL) {
        return NULL; 
    }
    
    d->giorno_settimana = giorno_settimana;
    d->giorno = giorno;
    d->mese = mese;
    d->anno = anno;

    return d;
}


// Visualizza la data formattata nel formato giorno_settimana gg/mm/aaaa.
void visualizzaData(data d) {
    if (d == NULL) return;

    switch(d->giorno_settimana) {
        case 1:
            printf("Lunedì ");
            break;
        case 2:
            printf("Martedì ");
            break;
        case 3:
            printf("Mercoledì ");
            break;
        case 4:
            printf("Giovedì ");
            break;
        case 5:
            printf("Venerdì ");
            break;
        default:
            printf("Giorno non valido ");
            break;
    }

    printf("%d/%d/%d\n", d->giorno, d->mese, d->anno);
}


// Confronta due date e stabilisce se sono uguali.
int comparaData(data d1, data d2) {
    if (d1 == NULL || d2 == NULL) {
        return 0;
    }

    if (d1->giorno_settimana != d2->giorno_settimana) return 0;
    if (d1->giorno != d2->giorno) return 0;
    if (d1->mese != d2->mese) return 0;
    if (d1->anno != d2->anno) return 0;

    return 1;
}


// Crea e inizializza un nuovo orario.
orario nuovoOrario(int ora, int minuti) {
    orario o = malloc(sizeof(struct Orario));
    if (o == NULL) {
        return NULL;
    }

    o->ora = ora;
    o->minuti = minuti;
    
    return o;
}


// Formatta l'output per l'orario nel formato hh:mm
void visualizzaOrario(orario o) {
    if (o == NULL) return;
    
    printf("%02d:%02d\n", o->ora, o->minuti);
}


// Confronta due orari e stabilisce se sono uguali.
int comparaOrario(orario o1, orario o2) {
    if (o1 == NULL || o2 == NULL) {
        return 0;
    }

    if (o1->ora != o2->ora) return 0;
    if (o1->minuti != o2->minuti) return 0;

    return 1;
}


// Dealloca la struttura data
void distruggiData(data d) {
    if (d != NULL) {
        free(d);
    }
}


// Dealloca la struttura orario
void distruggiOrario(orario o) {
    if (o != NULL) {
        free(o);
    }
}

// Restituisce il giorno della settimana o -1 per indicare un errore
int ottieniGiornoSettimana(data d) {
    if(d==NULL) return -1;
    return d->giorno_settimana;
}

// Restituisce il giorno della data o -1 per indicare un errore
int ottieniGiorno(data d) {
    if(d==NULL) return -1;
    return d->giorno;
}

// Restituisce il mese della data o -1 per indicare un errore
int ottieniMese(data d) {
    if(d==NULL) return -1;
    return d->mese;
}

// Restituisce l'anno della data o -1 per indicare un errore
int ottieniAnno(data d) {
    if(d==NULL) return -1;
    return d->anno;
}

// Restituisce l'ora o -1 per indicare un errore
int ottieniOra(orario o) {
    if(o==NULL) return -1;
    return o->ora;
}

// Restituisce i minuti, o -1 per indicare un errore
int ottieniMinuti(orario o) {
    if(o==NULL) return -1;
    return o->minuti;
}