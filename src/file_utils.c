#include <stdio.h>
#include <stdlib.h>
#include "modules/studente.h"
#include "modules/prenotazione.h"
#include "data_ora.h"
#include "file_utils.h"


/*

studenti.txt

2
Antonio Sollo;NF12100059;Informatica
Eva Soldà;NF12100520;Informatica


prenotazioni.txt

2
NF12100059;01;01/01/2026;12:00;14:00;1

*/

// Salva i dati di un singolo studente in coda al file, usando ';' come delimitatore tra i campi.
int registraStudente(studente s) {
    if (s == NULL) return 0;

    FILE *f = fopen("data/studenti.txt", "a");

    if (f==NULL) return 0;

    fprintf(f, "%s;%s;%s\n", ottieniNome(s), ottieniMatricolaST(s), ottieniCorsoLaurea(s));

    fclose(f); 
    return 1;
}

// Carica tutti gli studenti dal file e restituisce il numero totale di studenti.
int caricaStudenti() {
    FILE *f = fopen("data/studenti.txt", "r");

    if (f==NULL) return 0;

    char buffer[512];
    const char delimitatori[] = ";\n";
    
    fgets(buffer, sizeof(buffer), f);
    int studenti_totali = atoi(buffer);

    while(fgets(buffer, sizeof(buffer), f) != NULL) {
        char *nome = strtok(buffer, delimitatori);
        char *matricola = strtok(NULL, delimitatori);
        char *corso_laurea = strtok(NULL, delimitatori);

        studente s = creaStudente(nome, matricola, corso_laurea);
        // Carica s nella tabella hash
    }

    fclose(f);
    return studenti_totali;
}

// Salva i dati di una prenotazione in coda al file, 
// Usa ';' come delimitatore per i campi di prenotazione
// Usa '/' come delimitatore per i campi di data
// Usa ':' come delimitatore per i campi di orario 
int registraPrenotazione(prenotazione p) {
    if (p == NULL) return 0;

    FILE *f = fopen("data/prenotazioni.txt", "a");

    if (f==NULL) return 0;

    data d = ottieniDataPrenotazione(p);
    orario ingresso = ottieniOrarioIngresso(p);
    orario uscita = ottieniOrarioUscita(p);
    fprintf(
        f, 
        "%s;%d;%d/%d/%d;%d:%d;%d:%d;%d\n", 
        ottieniMatricola(p), 
        ottieniGiornoSettimana(d), 
        ottieniGiorno(d), ottieniMese(d), ottieniAnno(d), 
        ottieniOra(ingresso),ottieniMinuti(ingresso),
        ottieniOra(uscita), ottieniMinuti(uscita), 
        ottieniPostoAssegnato(p)
    );

    fclose(f); 
    return 1;
}

// Carica tutte le prenotazioni dal file e restituisce il numero totale di prenotazioni.
int caricaPrenotazioni() {
    FILE *f = fopen("data/prenotazioni.txt", "r");

    if (f==NULL) return 0;

    char buffer[512];
    const char delimitatori[] = ";\n";
    const char delimitatore_data[] = "/\n";
    const char delimitatore_orario[] = ":\n";
    
    fgets(buffer, sizeof(buffer), f);
    int prenotazioni_totali = atoi(buffer);

    while(fgets(buffer, sizeof(buffer), f) != NULL) {
        char *matricola = strtok(buffer, delimitatori);
        int giorno_settimana = atoi(strtok(NULL, delimitatori));
        char *data = strtok(NULL, delimitatori);
        char *ingresso = strtok(NULL, delimitatori);
        char *uscita = strtok(NULL, delimitatori);
        char *posto_assegnato = strtok(NULL, delimitatori);

        int giorno = atoi(strtok(data, delimitatore_data));
        int mese = atoi(strtok(NULL, delimitatore_data));
        int anno = atoi(strtok(NULL, delimitatore_data));

        int ora_ingresso = atoi(strtok(ingresso, delimitatore_orario));
        int minuti_ingresso = atoi(strtok(NULL, delimitatore_orario));

        int ora_uscita = atoi(strtok(uscita, delimitatore_orario));
        int minuti_uscita = atoi(strtok(NULL, delimitatore_orario));

        prenotazione p = creaPrenotazione(matricola, nuovaData(giorno_settimana, giorno, mese, anno), nuovoOrario(ora_ingresso, minuti_ingresso), nuovoOrario(ora_uscita, minuti_uscita), posto_assegnato);
        // Carica p nella lista
    }

    fclose(f);
    return prenotazioni_totali;
}