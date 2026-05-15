typedef struct Studente *studente;

// Crea una nuova struct Studente e restituisce un puntatore ad essa
studente creaStudente(void);

// Dealloca completamente lo studente e i suoi campi
 
void rimuoviStudente(studente s);

// Prende un puntatore a Studente come parametro e stampa i campi della struttura
void visualizzaStudente(studente s);

// Modifica un campo specifico dello studente (1: Nome, 2: Matricola, 3: Corso).
/* Prende come parametri un puntatore alla struttura da modificare, un intero che indica il campo da modificare
e la modifica da attuare */
 * Nota: 'modifica' deve essere una stringa allocata dinamicamente.
void modificaStudente(studente s, int operazione, char *modifica);