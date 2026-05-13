typedef struct c_queue *queue;

// Crea una nuova coda e restituisce un puntatore ad essa.
// Non richiede parametri in ingresso.
queue newQueue(void);

// Verifica se la coda specificata è vuota.
// Prende come parametro un puntatore a una coda e restituisce un intero.
// Tipicamente, restituisce 0 se la coda non è vuota e un valore non-zero (solitamente 1) se la coda è vuota.
int emptyQueue(queue q);

// Rimuove e restituisce l'elemento dalla parte anteriore della coda.
// Se la coda è vuota, il comportamento di questa funzione dipende dalla sua implementazione (potrebbe restituire un valore speciale o generare un errore).
// Prende come parametro un puntatore a una coda.
item dequeue(queue q);

// Aggiunge un nuovo elemento alla parte posteriore della coda.
// Prende come parametri l'elemento da aggiungere (di tipo 'item', che deve essere definito altrove nel codice) e un puntatore alla coda a cui aggiungere l'elemento.
// Restituisce un intero, che solitamente indica il successo o il fallimento dell'operazione (ad esempio 0 per successo, -1 per fallimento).
int enqueue(item val, queue q);