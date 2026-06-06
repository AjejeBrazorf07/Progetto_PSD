#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "file_utils.h"


/*

studenti.txt

2
Antonio Sollo;NF12100059;Informatica
Eva Soldà;NF12100520;Informatica


prenotazioni.txt

1
NF12100059;01;01/01/2026;12:00;14:00;1;1

*/

// Salva i dati di un singolo studente in coda al file, usando ';' come delimitatore tra i campi.
int registraStudente(studente s) {
    if (s == NULL) return 0;

    FILE *f = fopen("data/studenti.txt", "r+");

    if (f==NULL) return 0;

    int c;
    fscanf(f, "%d", &c);
    c++;

    rewind(f);
    fprintf(f, "%-5d", c);

    fseek(f, 0, SEEK_END);
    fprintf(f, "%s;%s;%s\n", ottieniNome(s), ottieniMatricolaST(s), ottieniCorsoLaurea(s));

    fclose(f); 
    return 1;
}

// Carica tutti gli studenti dal file e restituisce il numero totale di studenti.
hashtable caricaStudenti() {
    FILE *f = fopen("data/studenti.txt", "r");

    if (f==NULL) return NULL;

    char buffer[512];
    const char delimitatori[] = ";\n";

    fgets(buffer, sizeof(buffer), f);
    int studenti_totali = atoi(buffer);

    // se studenti_totali = 0, size = 10, altrimenti size = studenti_totali/0.75
    int size = (studenti_totali > 0) ? (studenti_totali / 0.75) : 10;

    hashtable h = newHashtable(10);
    if (h == NULL) {
        fclose(f);
        return NULL;
    }
    

    while(fgets(buffer, sizeof(buffer), f) != NULL) {
        char *nome = strtok(buffer, delimitatori);
        char *matricola = strtok(NULL, delimitatori);
        char *corso_laurea = strtok(NULL, delimitatori);

        studente s = creaStudente(nome, matricola, corso_laurea);
        
        int i = InsertHash(h, matricola, s);

        if (i == 0) {
            perror("Errore nell'inserimento di uno studente nella tabella");
            fclose(f);
            return NULL;
        }
    }

    fclose(f);
    return h;
}

// Salva i dati di una prenotazione in coda al file, 
// Usa ';' come delimitatore per i campi di prenotazione
// Usa '/' come delimitatore per i campi di data
// Usa ':' come delimitatore per i campi di orario 
int registraPrenotazione(prenotazione p) {
    if (p == NULL) return 0;

    FILE *f = fopen("data/prenotazioni.txt", "r+");

    if (f==NULL) return 0;

    int c;
    fscanf(f, "%d", &c);
    c++;
    
    rewind(f);
    fprintf(f, "%-5d", c);

    fseek(f, 0, SEEK_END);

    data d = ottieniDataPrenotazione(p);
    orario ingresso = ottieniOrarioIngresso(p);
    orario uscita = ottieniOrarioUscita(p);
    fprintf(
        f, 
        "%s;%d;%02d/%02d/%04d;%02d:%02d;%02d:%02d;%d;%d\n", 
        ottieniMatricolaPR(p), 
        ottieniGiornoSettimana(d), 
        ottieniGiorno(d), ottieniMese(d), ottieniAnno(d), 
        ottieniOra(ingresso),ottieniMinuti(ingresso),
        ottieniOra(uscita), ottieniMinuti(uscita), 
        ottieniPostoAssegnato(p),
        1 // 1 indica prenotazione attiva, 0 prenotazione cancellata
    );

    fclose(f); 
    return 1;
}

// Carica tutte le prenotazioni attive dal file nella lista l e restituisce il numero totale di prenotazioni.
list caricaPrenotazioni() {
    list l = newList();

    FILE *f = fopen("data/prenotazioni.txt", "r");

    if (f==NULL) return NULL;

    char buffer[512];
    const char delimitatori[] = ";\n";
    
    fgets(buffer, sizeof(buffer), f);
    // int prenotazioni_totali = atoi(buffer);

    while(fgets(buffer, sizeof(buffer), f) != NULL) {
        char *matricola = strtok(buffer, delimitatori);
        int giorno_settimana = atoi(strtok(NULL, delimitatori));
        char *data_str = strtok(NULL, delimitatori);
        char *ingresso_str = strtok(NULL, delimitatori);
        char *uscita_str = strtok(NULL, delimitatori);
        int posto_assegnato = atoi(strtok(NULL, delimitatori));
        int stato_prenotazione = atoi(strtok(NULL, delimitatori));

        int giorno, mese, anno;
        sscanf(data_str, "%d/%d/%d", &giorno, &mese, &anno);

        int ora_ingresso, minuti_ingresso;
        sscanf(ingresso_str, "%d:%d", &ora_ingresso, &minuti_ingresso);

        int ora_uscita, minuti_uscita;
        sscanf(uscita_str, "%d:%d", &ora_uscita, &minuti_uscita);

        data data_prenotazione = nuovaData(giorno_settimana, giorno, mese, anno);

        if (verificaDataSettimana(data_prenotazione) == 1 && stato_prenotazione==1) {
            prenotazione p = creaPrenotazione(
                matricola, 
                data_prenotazione, 
                nuovoOrario(ora_ingresso, minuti_ingresso), 
                nuovoOrario(ora_uscita, minuti_uscita), 
                posto_assegnato
            );
        
            if (p != NULL) {
                l = consList(p, l);
            } else {
                distruggiData(data_prenotazione);
            }
        } else {
            distruggiData(data_prenotazione);
        }
    }

    fclose(f);
    
    return l;
}


// Annulla una prenotazione sul file impostando il flag di stato finale a 0 (Cancellazione Logica).
// Ritorna 1 in caso di successo, 0 se la prenotazione non esiste.
int cancellaPrenotazione(list prenotazioni, char *matr, data d_pr, orario i, orario u) {
    FILE *f = fopen("data/prenotazioni.txt", "r+");

    if (f==NULL) return NULL;

    char buffer[512];
    const char delimitatori[] = ";\n";
    int trovato = 0;

    fgets(buffer, sizeof(buffer), f);
    // int prenotazioni_totali = atoi(buffer);

    while(fgets(buffer, sizeof(buffer), f) != NULL) {
        char *matricola = strtok(buffer, delimitatori);
        int giorno_settimana = atoi(strtok(NULL, delimitatori));
        char *data_str = strtok(NULL, delimitatori);
        char *ingresso_str = strtok(NULL, delimitatori);
        char *uscita_str = strtok(NULL, delimitatori);
        int posto_assegnato = atoi(strtok(NULL, delimitatori));
        int stato = atoi(strtok(NULL, delimitatori));

        if (stato == 0) {
            continue;
        }

        int giorno, mese, anno;
        sscanf(data_str, "%d/%d/%d", &giorno, &mese, &anno);

        int ora_ingresso, minuti_ingresso;
        sscanf(ingresso_str, "%d:%d", &ora_ingresso, &minuti_ingresso);

        int ora_uscita, minuti_uscita;
        sscanf(uscita_str, "%d:%d", &ora_uscita, &minuti_uscita);

        data data_prenotazione = nuovaData(giorno_settimana, giorno, mese, anno);
        orario ingresso = nuovoOrario(ora_ingresso, minuti_ingresso);
        orario uscita = nuovoOrario(ora_uscita, minuti_uscita);

        if (strcmp(matricola, matr) == 0 && comparaData(d_pr, data_prenotazione) == 1 && comparaOrario(i, ingresso) == 1 && comparaOrario(u, uscita) == 1) {
            trovato = 1;

            fseek(f, -2, SEEK_CUR); 
            
            fprintf(f, "0");
            
            fflush(f);

            distruggiData(data_prenotazione);
            distruggiOrario(ingresso);
            distruggiOrario(uscita);
            break; 
        }

        distruggiData(data_prenotazione);
        distruggiOrario(ingresso);
        distruggiOrario(uscita);
    }

    fclose(f);
    return trovato;
}


// Genera la struttura del tabellone settimanale (da lunedì a venerdì).
list inizializzaPianoSettimanale() {
    list l = newList();
    if (l == NULL) return NULL;

    time_t tempo = time(NULL);
    struct tm d = *localtime(&tempo);

    // Trasforma la domenica da 0 a 7
    if (d.tm_wday == 0) d.tm_wday = 7;

    // Calcola i giorni di distanza da lunedì
    int giorni_da_lunedi = d.tm_wday - 1;

    // Sposta la data a lunedì
    d.tm_mday -= giorni_da_lunedi;
    mktime(&d);

    for (int i = 5; i > 0; i--) {
        struct tm g = d;

        // Calcola il giorno del mese corretto
        g.tm_mday += (i - 1);
        mktime(&g);

        data data_giorno = nuovaData(i, g.tm_mday, g.tm_mon + 1, g.tm_year + 1900);

        giorno_settimana gs = creaGiornoSettimana(data_giorno);

        if (gs != NULL) {
            l = consList(gs, l);
        }
    }
    
    return l;
}


// Scorre la lista prenotazioni e per ogni prenotazione aggiorna il posto nella fascia oraria corrispondente
void associaPosti(list prenotazioni, list settimana) {
    for(int i = 1; i <= sizeList(prenotazioni); i++) {
        prenotazione p = (prenotazione) getItem(prenotazioni, i);

        int giorno_sett = ottieniGiornoSettimana(ottieniDataPrenotazione(p));
        int ingresso = ottieniOra(ottieniOrarioIngresso(p));
        int posto = ottieniPostoAssegnato(p);

        switch (ingresso) {
            case 9:
                aggiornaPosto(settimana, giorno_sett, 0, posto, 1);
                break;
            case 11:
                aggiornaPosto(settimana, giorno_sett, 1, posto, 1);
                break;
            case 13:
                aggiornaPosto(settimana, giorno_sett, 2, posto, 1);
                break;
            case 15:
                aggiornaPosto(settimana, giorno_sett, 3, posto, 1);
                break;
        }
    }
}


// Legge nel file prenotazioni.txt e restituisce il numero di prenotazioni totali contenuto in esso
int mostraPrenotazioni(void) {
    FILE *f = fopen("../data/prenotazioni.txt", "r");

    if (f==NULL) return 0;

    char buffer[50];
    fgets(buffer, sizeof(buffer), f);
    int prenotazioni_totali = atoi(buffer);

    fclose(f);

    return prenotazioni_totali;
}

// Legge nel file accessi_effettivi.txt e restituisce il numero di accessi effettivi totali contenuto in esso
int mostraAccessiEffettivi(void) {
    FILE *f = fopen("../data/report/accessi_effettivi.txt", "r");

    if (f==NULL) return 0;

    char buffer[50];
    fgets(buffer, sizeof(buffer), f);
    int accessi_effettivi = atoi(buffer);

    fclose(f);

    return accessi_effettivi;
}

// Aumenta di uno il numero di accessi effettivi nel file accessi_effettivi.txt e restituisce il numero aggiornato
int aggiornaAccessiEffettivi(void) {
    int accessi_effettivi = mostraAccessiEffettivi();

    FILE *f = fopen("../data/report/accessi_effettivi.txt", "w");

    accessi_effettivi++;
    fprintf(f, "%d", accessi_effettivi);

    fclose(f);

    return accessi_effettivi;
}

// Legge nel file studenti_in_attesa.txt e restituisce il numero di studenti in attesa contenuto in esso
int mostraStudentiInAttesa(void) {
    FILE *f = fopen("../data/report/studenti_in_attesa.txt", "r");

    if (f==NULL) return 0;

    char buffer[50];
    fgets(buffer, sizeof(buffer), f);
    int studenti_in_attesa = atoi(buffer);

    fclose(f);

    return studenti_in_attesa;
}

// Se operazione = 1, aumenta di uno il numero di studenti in attesa nel file studenti_in:attesa.txt
// Se operazione == 0, diminuisce di uno gli studenti in attesa
int aggiornaStudentiInAttesa(int operazione) {
    int studenti_in_attesa = mostraAccessiEffettivi();

    FILE *f = fopen("../data/report/studenti_in_attesa.txt", "w");

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

int mostraStudentiNoshow(void) {
    FILE *f = fopen("../data/report/studenti_noshow.txt", "r");

    if (f==NULL) return 0;

    char buffer[50];
    fgets(buffer, sizeof(buffer), f);
    int studenti_noshow = atoi(buffer);

    fclose(f);

    return studenti_noshow;
}

int aggiornaStudentiNoshow(void) {
    int studenti_noshow = mostraStudentiiNoshow();

    FILE *f = fopen("../data/report/studenti_noshow.txt", "w");

    studenti_noshow++;
    fprintf(f, "%d", studenti_noshow);

    fclose(f);

    return studenti_noshow;
}

int mostraStoricoAccessi(void) {
    FILE *f = fopen("../data/report/storico_accessi.txt", "r");

    if (f==NULL) return 0;

    char buffer[50];
    fgets(buffer, sizeof(buffer), f);
    int storico_accessi = atoi(buffer);

    fclose(f);

    return storico_accessi;
}

// Aumenta di uno il numero di accessi nel file storico_accessi.txt e restituisce il numero aggiornato
int aggiornaStoricoAccessi(void) {
    int storico_accessi = mostraStoricoAccessi();

    FILE *f = fopen("../data/report/storico_accessi.txt", "w");

    storico_accessi++;
    fprintf(f, "%d", storico_accessi);

    fclose(f);

    return storico_accessi;
}
