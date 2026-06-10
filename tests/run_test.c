#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include "../src/lib/list.h"
#include "../src/lib/hash_table.h"
#include "../src/lib/queue.h"
#include "../src/modules/studente.h"
#include "../src/modules/prenotazione.h"
#include "../src/modules/data_ora.h"
#include "../src/utils/load.h"
#include "../src/utils/report.h"

void testRegistrazioneStudenti() {
    FILE *f = fopen("tc_studenti.txt", "r");
    assert(f!=NULL);

    char buffer[512];
    const char delimitatori[] = ";\n";

    hashtable h = newHashtable(5);
    assert(h != NULL);

    while(fgets(buffer, sizeof(buffer), f) != NULL) {
        char *nome = strtok(buffer, delimitatori);
        char *matricola = strtok(NULL, delimitatori);
        char *corso_laurea = strtok(NULL, delimitatori);

        studente s = creaStudente(nome, matricola, corso_laurea);
        assert(s != NULL);

        int r = registraStudente(s);
        assert(r!=0);
        
        int i = InsertHash(h, matricola, s);
        assert(i!=0);
    }

    fclose(f);
    
    printf("-> testRegistrazioneStudenti superato con successo!\n");
}

void testInserimentoPrenotazione() {
    FILE *f = fopen("tc_prenotazioni.txt", "r");
    assert(f!=NULL);

    char buffer[512];
    const char delimitatori[] = ";\n";

    list l = newList();
    assert(l == NULL);

    while(fgets(buffer, sizeof(buffer), f) != NULL) {
        char *matricola = strtok(buffer, delimitatori);
        char *giorno_sett = strtok(NULL, delimitatori);
        char *data_str = strtok(NULL, delimitatori);
        char *ingresso_str = strtok(NULL, delimitatori);
        char *uscita_str = strtok(NULL, delimitatori);
        char *posto_str = strtok(NULL, delimitatori);

        int giorno_settimana = atoi(giorno_sett);
        int posto_assegnato = atoi(posto_str);

        int giorno, mese, anno;
        sscanf(data_str, "%d/%d/%d", &giorno, &mese, &anno);

        int ora_ingresso, minuti_ingresso;
        sscanf(ingresso_str, "%d:%d", &ora_ingresso, &minuti_ingresso);

        int ora_uscita, minuti_uscita;
        sscanf(uscita_str, "%d:%d", &ora_uscita, &minuti_uscita);

        prenotazione p = creaPrenotazione(
            matricola, 
            nuovaData(giorno_settimana, giorno, mese, anno), 
            nuovoOrario(ora_ingresso, minuti_ingresso), 
            nuovoOrario(ora_uscita, minuti_uscita), 
            posto_assegnato
        );
        assert (p != NULL);

        int r = registraPrenotazione(p);
        assert(r != 0);

        l = consList(p, l);
        assert(l != NULL);
    }

    fclose(f);
    
    printf("-> testInserimentoPrenotazione superato con successo!\n");
}

void testVerificaDisponibilitaPosti(void) {
    list settimana = inizializzaPianoSettimanale();
    assert(settimana != NULL);

    int giorno_test = 4;
    int fascia_test = 1;

    // Verifica posto libero
    aggiornaPosto(settimana, giorno_test, fascia_test, 15, 0);
    int stato_posto = verificaPosto(settimana, giorno_test, fascia_test, 15);
    assert(stato_posto == 0);

    // Verifica posto prenotato
    aggiornaPosto(settimana, giorno_test, fascia_test, 15, 1);
    stato_posto = verificaPosto(settimana, giorno_test, fascia_test, 15);
    assert(stato_posto == 1);

    // Verifica posto occupato
    aggiornaPosto(settimana, giorno_test, fascia_test, 15, 2);
    stato_posto = verificaPosto(settimana, giorno_test, fascia_test, 15);
    assert(stato_posto == 2);

    // Verifica confini dell'aula (posto 0 e 99)
    aggiornaPosto(settimana, giorno_test, fascia_test, 0, 2);
    assert(verificaPosto(settimana, giorno_test, fascia_test, 0) == 2);

    aggiornaPosto(settimana, giorno_test, fascia_test, 99, 2);
    assert(verificaPosto(settimana, giorno_test, fascia_test, 99) == 2);

    printf("-> testVerificaDisponibilitaPosti superato con successo!\n");
}

void testcheckInPrenotati() {
    char matricola[20] = "NF12100059";

    prenotazione p = creaPrenotazione(matricola, nuovaData(4, 10, 6, 2026), nuovoOrario(11, 0), nuovoOrario(13, 0), 15);
    assert(p != NULL);

    list settimana = inizializzaPianoSettimanale();
    assert(settimana != NULL);

    list studenti_in_aula = newList();
    assert(studenti_in_aula == NULL);

    struct tm orario_finto;
    orario_finto.tm_hour = 10;
    orario_finto.tm_min = 45;
    orario_finto.tm_wday = 4;
    orario_finto.tm_mday = 10;
    orario_finto.tm_mon = 6;
    orario_finto.tm_year = 2026;
    
    int minuti_correnti_totali = (orario_finto.tm_hour * 60) + orario_finto.tm_min;
    int tolleranza = 30;
    int minuti_inizio_prenotazione = (ottieniOra(ottieniOrarioIngresso(p)) * 60) + ottieniMinuti(ottieniOrarioIngresso(p));
    int fascia_oraria = (ottieniOra(ottieniOrarioIngresso(p)) - 9) / 2;

    data oggi = nuovaData(orario_finto.tm_wday, orario_finto.tm_mday, orario_finto.tm_mon, orario_finto.tm_year);
    assert(oggi!=NULL);

    assert(strcmp(ottieniMatricolaPR(p), matricola) == 0);

    assert(comparaData(ottieniDataPrenotazione(p), oggi) == 1);

    // Arrivo in anticipo (10:45)
    int correnti_anticipo = (10 * 60) + 45;
    assert(correnti_anticipo < minuti_inizio_prenotazione);
    assert(!(correnti_anticipo > (minuti_inizio_prenotazione + tolleranza))); 

    // Arrivo puntuale (11:15)
    int correnti_puntuale = (11 * 60) + 15;
    assert(!(correnti_puntuale < minuti_inizio_prenotazione));
    assert(!(correnti_puntuale > (minuti_inizio_prenotazione + tolleranza)));

    int ingresso = aggiornaPosto(settimana, orario_finto.tm_wday, fascia_oraria, 15, 2);
    assert(ingresso==1);

    studenti_in_aula = consList(matricola, studenti_in_aula);
    assert(studenti_in_aula!=NULL);


    // Arrivo in ritardo (11:45)
    int correnti_ritardo = (11 * 60) + 45;
    assert(!(correnti_ritardo < minuti_inizio_prenotazione));
    assert(correnti_ritardo > (minuti_inizio_prenotazione + tolleranza));

    printf("-> testCheckIn superato con successo!\n");
}

void testCheckOut() {
    char matricola[20] = "NF12100059";

    int giorno_settimana = 4;
    int fascia_corrente = 1;

    int pos_da_rimuovere = 15;

    prenotazione p = creaPrenotazione(matricola, nuovaData(4, 10, 6, 2026), nuovoOrario(11, 0), nuovoOrario(13, 0), 15);
    assert(p != NULL);

    list settimana = inizializzaPianoSettimanale();
    assert(settimana != NULL);

    int ingresso = aggiornaPosto(settimana, giorno_settimana, fascia_corrente, 15, 2);
    assert(ingresso==1);

    list studenti_in_aula = newList();
    studenti_in_aula = consList(matricola, studenti_in_aula);
    assert(studenti_in_aula!=NULL);

    int occupato = verificaPosto(settimana, giorno_settimana, fascia_corrente, pos_da_rimuovere);
    assert(occupato==2);
    
    studenti_in_aula = removeList(studenti_in_aula, 0);
    assert(studenti_in_aula == NULL);

    int liberato = aggiornaPosto(settimana, giorno_settimana, fascia_corrente, pos_da_rimuovere, 0);
    assert(liberato==1);

    printf("-> testCheckOut superato con successo!\n");
}

void testCheckInNonPrenotati() {
    char matricola[20] = "NF12100059";

    int giorno_settimana = 4;
    int fascia_corrente = 1;

    list settimana = inizializzaPianoSettimanale();
    assert(settimana != NULL);

    list studenti_in_aula = newList();
    assert(studenti_in_aula==NULL);

    int posto_trovato = -1;
    for (int i = 0; i < 100; i++) {
        if (verificaPosto(settimana, giorno_settimana, fascia_corrente, i) == 0) {
            posto_trovato = i;
            break;
        }
    }
    assert(posto_trovato != -1);

    int ingresso = aggiornaPosto(settimana, giorno_settimana, fascia_corrente, 15, 2);
    assert(ingresso==1);

    studenti_in_aula = consList(matricola, studenti_in_aula);
    assert(studenti_in_aula!=NULL);

    printf("-> testCheckInNonPrenotato superato con successo!\n");
}

void testInserimentoListaAttesa() {
    // Inserimento in coda vuota
    queue q = newqueue();
    assert(q != NULL);
 
    char *m1 = strdup("NF12100059");
    enqueue(m1, q);
    assert(emptyqueue(q) == 0); 
 
    // Inserimento in coda con più elementi
    q = newqueue();
    assert(q != NULL);

    char *m2 = strdup("NF12100010");
    char *m3 = strdup("NF12100020");
    char *m4 = strdup("NF12100030");
 
    enqueue(m2, q);
    enqueue(m3, q);
    enqueue(m4, q);
 
    assert(emptyqueue(q) == 0);
 
    printf("-> testInserimentoListaAttesa superato con successo!\n");
}

void testRimozioneListaAttesa() {
    queue q;
    char *r1, *r2, *r3;
 
    // Studente in cima alla coda
    q = newqueue();
    enqueue(strdup("NF12100011"), q);
    enqueue(strdup("NF12100022"), q);
    enqueue(strdup("NF12100033"), q);
 
    char *m = dequeue(q);
    assert(strcmp(m, "NF12100011")==0);
 
    // Studente in mezzo alla coda
    q = newqueue();
    enqueue(strdup("NF12100011"), q);
    enqueue(strdup("NF12100022"), q);
    enqueue(strdup("NF12100033"), q);

    while(emptyqueue(q)!=0) {
        char *m = dequeue(q);
        if (m != NULL) {
            if(strcmp(m, "NF12100022") == 0) {
                free(m);
            } else enqueue(m, q);
        } 
    }
 
    // Studente in fondo alla coda
    q = newqueue();
    enqueue(strdup("NF12100011"), q);
    enqueue(strdup("NF12100022"), q);
    enqueue(strdup("NF12100033"), q);

    while(emptyqueue(q)!=0) {
        char *m = dequeue(q);
        if (m != NULL) {
            if(strcmp(m, "NF12100033") == 0) {
                free(m);
            } else enqueue(m, q);
        } 
    }

    printf("-> testRimozioneListaAttesa superato con successo!\n");
}


void testAnnullaPrenotazione() {
    char matricola[20] = "NF12100520";

    list settimana = inizializzaPianoSettimanale();
    assert(settimana != NULL);   

    // 1 prenotazione assegnata alla matricola
    prenotazione p = creaPrenotazione(matricola, nuovaData(4,10,6,2026), nuovoOrario(11,0), nuovoOrario(13,0), 15);
    assert(p!=NULL);

    int r = registraPrenotazione(p);
    assert(r != 0);

    list l = newList();
    l = consList(p, l);
    assert(l!=NULL);

    int totale_prenotazioni = sizeList(l);
    for (int i = 1; i <= totale_prenotazioni; i++) {
        prenotazione p = (prenotazione) getItem(l, i);

        int fascia_oraria = (ottieniOra(ottieniOrarioIngresso(p)) - 9) / 2;
        
        if (p != NULL && strcmp(ottieniMatricolaPR(p), matricola) == 0) {
            l = removeList(l, 0);
            assert(cancellaPrenotazione(l, matricola, ottieniDataPrenotazione(p), ottieniOrarioIngresso(p), ottieniOrarioUscita(p)) == 1);
            //aggiornamento disponibilità
            assert(aggiornaPosto(settimana, ottieniGiornoSettimana(ottieniDataPrenotazione(p)), fascia_oraria, ottieniPostoAssegnato(p), 0)==1);
        }
    }

    // 2 prenotazioni assegnate alla stessa matricola
    prenotazione trovate[50]; 
    int contatore_trovate = 0;

    prenotazione p1 = creaPrenotazione(matricola, nuovaData(3,9,6,2026), nuovoOrario(11,0), nuovoOrario(13,0), 15);
    assert(p1!=NULL);

    prenotazione p2 = creaPrenotazione(matricola, nuovaData(2,8,6,2026), nuovoOrario(11,0), nuovoOrario(13,0), 15);
    assert(p2!=NULL);
    

    l = newList();
    l = consList(p, l);
    assert(l!=NULL);
    int scelta = 1;

    totale_prenotazioni = sizeList(l);
    for (int i = 1; i <= totale_prenotazioni; i++) {
        prenotazione p = (prenotazione) getItem(l, i);
        assert(p!=NULL);
        
        assert(strcmp(ottieniMatricolaPR(p), matricola) == 0);

        trovate[contatore_trovate] = p;
        contatore_trovate++;
    }

    prenotazione da_cancellare = trovate[scelta - 1];

    data d_canc = ottieniDataPrenotazione(da_cancellare);
    orario ing_canc = ottieniOrarioIngresso(da_cancellare);
    orario usc_canc = ottieniOrarioUscita(da_cancellare);
    int posto_canc = ottieniPostoAssegnato(da_cancellare);
    int giorno_sett = ottieniGiornoSettimana(d_canc);
    

    int fascia_oraria = (ottieniOra(ing_canc) - 9) / 2;

    assert(cancellaPrenotazione(l, matricola, d_canc, ing_canc, usc_canc) == 1);
    // aggiornamento disponibilità
    assert(aggiornaPosto(settimana, giorno_sett, fascia_oraria, posto_canc, 0)==1);

    int pos;
    if ((pos = posItem(l, da_cancellare)) != -1) {
        l = removeList(l, pos);
    }

    printf("-> testAnnullamentoPrenotazione superato con successo!\n");
}

void testReport() {
 
    // il file accessi_effettivi.txt esiste
    int accessi = mostraAccessiEffettivi();
    assert(accessi >= 0);
 
    // il valore viene aumentato di 1
    int aggiornato = aggiornaAccessiEffettivi();
    assert(aggiornato == accessi + 1);
 
    // deve leggere il valore aggiornato
    int riletto = mostraAccessiEffettivi();
    assert(riletto == aggiornato);

    int prima = mostraStudentiInAttesa();
    assert(prima >= 0);
 
    // incremento 
    int dopo_incremento = aggiornaStudentiInAttesa(1);
    assert(dopo_incremento == prima + 1);
    assert(mostraStudentiInAttesa() == dopo_incremento);
 
    // decremento
    int dopo_decremento = aggiornaStudentiInAttesa(0);
    assert(dopo_decremento == prima);           
    assert(mostraStudentiInAttesa() == prima);

    // il file studenti_noshow.txt esiste
    int noshow = mostraStudentiNoshow();
    assert(noshow >= 0);
 
    // il valore viene aumentato di 1
    aggiornato = aggiornaStudentiNoshow();
    assert(aggiornato == noshow + 1);
 
    // deve leggere il valore aggiornato
    riletto = mostraStudentiNoshow();
    assert(riletto == aggiornato);

    int fasce[4] = {0, 0, 0, 0};
 
    // la funzione popola l'array
    occupazionePerFasciaOraria(fasce);
 
    // ogni fascia ha un valore valido (>=0)
    for (int i = 0; i < 4; i++) {
        assert(fasce[i] >= 0);
    }
 printf("-> testReport superato con successo!\n");

}

void testStoricoAccessi() {
 
    // il file storico_accessi.txt esiste
    int storico = mostraStoricoAccessi();
    assert(storico >= 0);

    // il valore viene aumentato di 1
    int aggiornato = aggiornaStoricoAccessi();
    assert(aggiornato == storico + 1);

    // deve leggere il valore aggiornato
    int riletto = mostraStoricoAccessi();
    assert(riletto == aggiornato);
 
    printf("-> testStoricoAccessi superato con successo!\n");
}

int main() {
    testRegistrazioneStudenti();
    testInserimentoPrenotazione();
    testVerificaDisponibilitaPosti();
    testcheckInPrenotati();
    testCheckOut();
    testCheckInNonPrenotati();
    testInserimentoListaAttesa();
    testRimozioneListaAttesa();
    testAnnullaPrenotazione();
    testReport();
    testStoricoAccessi();
    return 0;
}