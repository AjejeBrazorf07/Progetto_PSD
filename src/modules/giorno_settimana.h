#include "data_ora.h"

typedef struct Giorno_settimana *giorno_settimana;

#define NUM_FASCE 4
#define NUM_POSTI 100

// Crea e inizializza un elemento del tipo giorno_settimana.
// Parametri: puntatore a un elemento data d corrispondente al giorno da creare
// Restituisce un puntatore a giorno_settimana creato.
giorno_settimana creaGiornoSettimana(data giorno);

// Verifica se una data appartiene alla settimana corrente (Lun-Ven).
//Parametri: puntatore a un elemento data d.
// Restituisce 1 se la data fa parte della settimana corrente, 0 altrimenti.
int verificaDataSettimana(data d);