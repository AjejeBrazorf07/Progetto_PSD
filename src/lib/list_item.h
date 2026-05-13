#ifndef LIST_ITEM_H
#define LIST_ITEM_H

// Il tipo item è definito come un puntatore generico perchè non è noto a priori se l'item è una pretazione o un giorno della settimana
typedef void *item;

// Definizione del valore nullo per l'item.
#define NULLITEM NULL

// Confronta due item.
int eq(item a, item b);


#endif