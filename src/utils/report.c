#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "report.h"

// Legge nel file prenotazioni.txt e restituisce il numero di prenotazioni totali contenuto in esso
int mostraPrenotazioni(void) {
    FILE *f = fopen("data/prenotazioni.txt", "r");

    if (f == NULL) return 0;

    char buffer[50];
    fgets(buffer, sizeof(buffer), f);
    int prenotazioni_totali = atoi(buffer);

    fclose(f);

    return prenotazioni_totali;
}

// Legge nel file accessi_effettivi.txt e restituisce il numero di accessi effettivi totali contenuto in esso
int mostraAccessiEffettivi(void) {
    FILE *f = fopen("data/report/accessi_effettivi.txt", "r");

    if (f == NULL) return -1;

    char buffer[50];
    fgets(buffer, sizeof(buffer), f);
    int accessi_effettivi = atoi(buffer);

    fclose(f);

    return accessi_effettivi;
}

// Aumenta di uno il numero di accessi effettivi nel file accessi_effettivi.txt
int aggiornaAccessiEffettivi(void) {
    int accessi_effettivi = mostraAccessiEffettivi();

    FILE *f = fopen("data/report/accessi_effettivi.txt", "w");

    if (f==NULL) return -1;

    accessi_effettivi++;
    fprintf(f, "%d", accessi_effettivi);

    fclose(f);

    return accessi_effettivi;
}

// Legge nel file studenti_in_attesa.txt e restituisce il numero di studenti in attesa contenuto in esso
int mostraStudentiInAttesa(void) {
    FILE *f = fopen("data/report/studenti_in_attesa.txt", "r");

    if (f == NULL) return -1;

    char buffer[50];
    fgets(buffer, sizeof(buffer), f);
    int studenti_in_attesa = atoi(buffer);

    fclose(f);

    return studenti_in_attesa;
}

// Modifica il numero di studenti in attesa nel file studenti_in_attesa.txt in base all'operazione specificata
int aggiornaStudentiInAttesa(int operazione) {
    int studenti_in_attesa = mostraStudentiInAttesa(); 

    FILE *f = fopen("data/report/studenti_in_attesa.txt", "w");

    if(operazione == 1) { 
        studenti_in_attesa++;
        fprintf(f, "%d", studenti_in_attesa);
    } else {
        studenti_in_attesa--;
        fprintf(f, "%d", studenti_in_attesa);
    }

    fclose(f);

    return studenti_in_attesa;
}

// Legge nel file studenti_noshow.txt e restituisce il numero totale di assenze registrate
int mostraStudentiNoshow(void) {
    FILE *f = fopen("data/report/studenti_noshow.txt", "r");

    if (f == NULL) return 0;

    char buffer[50];
    fgets(buffer, sizeof(buffer), f);
    int studenti_noshow = atoi(buffer);

    fclose(f);

    return studenti_noshow;
}

// Aumenta di uno il numero di studenti assenti nel file studenti_noshow.txt 
int aggiornaStudentiNoshow(void) {
    int studenti_noshow = mostraStudentiNoshow();

    FILE *f = fopen("data/report/studenti_noshow.txt", "w");

    studenti_noshow++;
    fprintf(f, "%d", studenti_noshow);

    fclose(f);

    return studenti_noshow;
}

// Legge nel file storico_accessi.txt e restituisce il contatore degli accessi totali storici
int mostraStoricoAccessi(void) {
    FILE *f = fopen("data/report/storico_accessi.txt", "r");

    if (f == NULL) return 0;

    char buffer[50];
    fgets(buffer, sizeof(buffer), f);
    int storico_accessi = atoi(buffer);

    fclose(f);

    return storico_accessi;
}

// Aumenta di uno il contatore globale degli accessi storici nel file storico_accessi.txt
int aggiornaStoricoAccessi(void) {
    int storico_accessi = mostraStoricoAccessi();

    FILE *f = fopen("data/report/storico_accessi.txt", "w");

    if (f==NULL) return -1;

    storico_accessi++;
    fprintf(f, "%d", storico_accessi);

    fclose(f);

    return storico_accessi;
}

// Analizza il file delle prenotazioni calcolando la distribuzione degli studenti per ciascuna fascia oraria
void occupazionePerFasciaOraria(int fasce_orarie[]) {
    FILE *f = fopen("data/prenotazioni.txt", "r");

    if (f == NULL) {
        return;
    }

    char buffer[512];
    const char delimitatori[] = ";\n";
    
    fgets(buffer, sizeof(buffer), f);

    while(fgets(buffer, sizeof(buffer), f) != NULL) {
        char *matricola = strtok(buffer, delimitatori);
        int giorno_settimana = atoi(strtok(NULL, delimitatori));
        char *data_str = strtok(NULL, delimitatori);
        char *ingresso_str = strtok(NULL, delimitatori);
        char *uscita_str = strtok(NULL, delimitatori);
        int posto_assegnato = atoi(strtok(NULL, delimitatori));
        int stato_prenotazione = atoi(strtok(NULL, delimitatori));

        int ora_ingresso, minuti_ingresso;

        if (ingresso_str != NULL && sscanf(ingresso_str, "%d:%d", &ora_ingresso, &minuti_ingresso) == 2) {
            
            if (stato_prenotazione == 1) {
                int fascia = (ora_ingresso - 9) / 2;
                
                if (fascia >= 0 && fascia <= 3) {
                    fasce_orarie[fascia]++;
                }
            }
        }
    }

    fclose(f);
}