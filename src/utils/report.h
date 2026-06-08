
// Legge nel file prenotazioni.txt e restituisce il numero di prenotazioni totali contenuto in esso
// Restituisce: il numero totale di prenotazioni registrate
int mostraPrenotazioni(void);

// Aumenta di uno il numero di accessi effettivi nel file accessi_effettivi.txt 
// Restituisce: il numero di accessi effettivi aggiornato
int aggiornaAccessiEffettivi(void);

// Legge nel file accessi_effettivi.txt e restituisce il numero di accessi effettivi totali contenuto in esso
// Restituisce: il numero totale di accessi effettivi registrati
int mostraAccessiEffettivi(void);

// Legge nel file studenti_in_attesa.txt e restituisce il numero di studenti in attesa contenuti in esso
// Restituisce: il numero attuale di studenti in lista d'attesa
int mostraStudentiInAttesa(void);

// Modifica il numero di studenti in attesa nel file studenti_in_attesa.txt in base all'operazione specificata
// Parametri: operazione (1 per incrementare di uno, 0 per decrementare di uno)
// Restituisce: il numero aggiornato di studenti in attesa
int aggiornaStudentiInAttesa(int operazione);

// Legge nel file studenti_noshow.txt e restituisce il numero totale di assenze registrate
// Restituisce: il numero totale di studenti che non si sono presentati (No-Show)
int mostraStudentiNoshow(void);

// Aumenta di uno il numero di studenti assenti nel file studenti_noshow.txt 
// Restituisce: il numero aggiornato di studenti No-Show
int aggiornaStudentiNoshow(void);

// Legge nel file storico_accessi.txt e restituisce il contatore degli accessi totali storici
// Restituisce: il numero progressivo globale di ingressi registrati dall'apertura del sistema
int mostraStoricoAccessi(void);

// Aumenta di uno il contatore globale degli accessi storici nel file storico_accessi.txt
// Restituisce: il numero aggiornato di accessi storici totali
int aggiornaStoricoAccessi(void);

// Analizza il file delle prenotazioni calcolando la distribuzione degli studenti per ciascuna delle 4 fasce orarie
// Parametri: fasce_orarie (array di interi in cui accumulare i conteggi per ogni fascia da 0 a 3)
void occupazionePerFasciaOraria(int fasce_orarie[]);