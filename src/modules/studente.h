typedef struct Studente *studente;

// Crea una nuova struct Studente  e restituisce un puntatore ad essa
// Inizializza la stringa con le stringhe prese come parametri
// Restituisce un puntatore alla struttura
studente creaStudente(char *nome, char *matricola, char *corso_laurea);

// Dealloca completamente lo studente e i suoi campi
void rimuoviStudente(studente s);

// Prende un puntatore a Studente come parametro e stampa i campi della struttura
void visualizzaStudente(studente s);


// Prende un puntatore a Studente come parametro
// Restituisce un puntatore alla stringa nome
char* ottieniNome(studente s);

// Prende un puntatore a Studente come parametro
// Restituisce un puntatore alla stringa matricola
char* ottieniMatricolaST(studente s);

// Prende un puntatore a Studente come parametro
// Restituisce un puntatore alla stringa corso_laurea
char* ottieniCorsoLaurea(studente s);