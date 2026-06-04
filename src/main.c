#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "modules/studente.h"
#include "modules/prenotazione.h"
#include "modules/data_ora.h"
#include "lib/list.h"
#include "lib/queue.h"
#include "lib/hash_table.h"
#include "file_utils.h" 


void stampaMenu() {
    printf("\n");
    printf("=========================================================\n");
    printf("              SISTEMA GESTIONE AULE STUDIO               \n");
    printf("=========================================================\n\n");
    printf("  1. Registrazione Studente\n");
    printf("  2. Inserimento Prenotazione\n");
    printf("  3. Annullamento Prenotazione\n");
    printf("  4. Verifica Disponibilità Posti per Fascia Oraria\n");
    printf("  5. Check-in\n");
    printf("  6. Registrazione Uscita di uno Studente\n");
    printf("  7. Visualizzazione Studenti (Prenotati, Presenti, Attesa)\n");
    printf("  8. Gestione Lista di Attesa\n");
    printf("  9. Visualizzazione Storico degli Accessi\n");
    printf(" 10. Generazione Report\n\n");
    printf("  0. Esci dal Programma\n\n");
    printf("=========================================================\n");
    printf("\nSeleziona un'opzione: ");
}

void aggiungiStudente(hashtable studenti) {
    printf("\033[H\033[J");
                
    char nome_cognome[100];
    char matricola[20];
    char corso_laurea[100];

    // Svuota il '\n' rimasto dalla scanf del menu principale
    while (getchar() != '\n');

    printf("=========================================================\n");
    printf("               REGISTRAZIONE NUOVO STUDENTE              \n");
    printf("=========================================================\n");
                
    printf("-> Inserisci Nome e Cognome: ");
    fgets(nome_cognome, sizeof(nome_cognome), stdin);
    nome_cognome[strcspn(nome_cognome, "\n")] = '\0'; 
                
    printf("-> Inserisci Matricola: ");
    fgets(matricola, sizeof(matricola), stdin);
    matricola[strcspn(matricola, "\n")] = '\0';
                
    printf("-> Inserisci Corso di Laurea: ");
    fgets(corso_laurea, sizeof(corso_laurea), stdin);
    corso_laurea[strcspn(corso_laurea, "\n")] = '\0';

    printf("=========================================================\n");
    printf("Elaborazione dati in corso...\n");

    if(searchHash(studenti, matricola) != NULL) {
        printf("\n[ATTENZIONE] Matricola gia' esistente nel sistema!\n");
        printf("Premere INVIO per tornare al menu principale...");
        getchar();
        return;
    }

    studente nuovo = creaStudente(nome_cognome, matricola, corso_laurea);

    if (nuovo == NULL) {
        printf("[ERRORE] Impossibile allocare memoria per lo studente.\n");
        printf("Premere INVIO per tornare al menu principale...");
        getchar();
        return;
    }

    int esito = registraStudente(nuovo);

    if (esito == 1) {
        printf("Studente \"%s\" registrato nel database!\n", nome_cognome);
        InsertHash(studenti, matricola, nuovo);
    } else {
        printf("[ERRORE] Impossibile scrivere i dati nel database.\n");
        distruggiStudente(nuovo); 
    }
                
    printf("Premere INVIO per tornare al menu principale...");
    getchar();
}

list nuovaPrenotazione(hashtable studenti, list prenotazioni, list settimana) {
    printf("\033[H\033[J");

    char matricola[20];
    char buffer_input[10];

    printf("\033[H\033[J");
    while (getchar() != '\n');

    printf("=========================================================\n");
    printf("               INSERIMENTO NUOVA PRENOTAZIONE            \n");
    printf("=========================================================\n");

    printf("-> Inserisci la tua Matricola: ");
    fgets(matricola, sizeof(matricola), stdin);
    matricola[strcspn(matricola, "\n")] = '\0'; 

    if (searchHash(studenti, matricola) == NULL) {
        printf("\n[ERRORE] Matricola '%s' non trovata nel sistema!\n", matricola);
        printf("Devi prima registrarti (Opzione 1 del menu principale).\n");
        printf("\nPremere INVIO per tornare al menu...");
        getchar();
        return prenotazioni; 
    }

    time_t tempo = time(NULL);
    struct tm d = *localtime(&tempo);

    if (d.tm_wday == 6 || d.tm_wday == 0) {
        printf("\nNessuna prenotazione per la settimana in corso.\n");
        printf("Premere INVIO per tornare al menu...");
        getchar();
        return prenotazioni;
    }

    printf("\n--- GIORNI DELLA SETTIMANA ---\n");
    switch(d.tm_wday) {
        case 1: 
            printf("  1. Lunedi'\n");
            printf("  2. Martedi'\n");
            printf("  3. Mercoledi'\n");
            printf("  4. Giovedi'\n");
            printf("  5. Venerdi'\n");
            break;
        case 2:
            printf("  2. Martedi'\n");
            printf("  3. Mercoledi'\n");
            printf("  4. Giovedi'\n");
            printf("  5. Venerdi'\n");
            break;
        case 3: 
            printf("  3. Mercoledi'\n");
            printf("  4. Giovedi'\n");
            printf("  5. Venerdi'\n");
            break;
        case 4:
            printf("  4. Giovedi'\n");
            printf("  5. Venerdi'\n");
            break;
        case 5:
            printf("  5. Venerdi'\n");
            break;
    }
                
    printf("-> Seleziona il giorno desiderato (1-5): ");
    fgets(buffer_input, sizeof(buffer_input), stdin);
    int giorno_scelto = atoi(buffer_input); 

    if (giorno_scelto < 1 || giorno_scelto > 5 || giorno_scelto < d.tm_wday) {
        printf("\n[ERRORE] Scelta non valida o giorno della settimana gia' trascorso.\n");
        printf("Premere INVIO per tornare al menu...");
        getchar();
        return prenotazioni;
    }

    data data_prenotazione = ottieniDataDaGiornoSettimana(giorno_scelto);

    printf("\n--- FASCE ORARIE DISPONIBILI ---\n");
    printf("  0. 09:00 - 11:00\n");
    printf("  1. 11:00 - 13:00\n");
    printf("  2. 13:00 - 15:00\n");
    printf("  3. 15:00 - 17:00\n");
                
    printf("-> Seleziona la fascia oraria (0-3): ");
    fgets(buffer_input, sizeof(buffer_input), stdin);
    int fascia_scelta = atoi(buffer_input);

    if (fascia_scelta < 0 || fascia_scelta > 3) {
        printf("\n[ERRORE] Scelta non valida. La fascia deve essere compresa tra 0 e 3.\n");
        printf("Premere INVIO per tornare al menu...");
        getchar();
        return prenotazioni;
    }

    orario ingresso, uscita;

    switch(fascia_scelta) {
        case 0:
            ingresso = nuovoOrario(9, 0);
            uscita = nuovoOrario(11, 0);
            break;
        case 1:
            ingresso = nuovoOrario(11, 0);
            uscita = nuovoOrario(13, 0);
            break;
        case 2:
            ingresso = nuovoOrario(13, 0);
            uscita = nuovoOrario(15, 0);
            break;
        case 3:
            ingresso = nuovoOrario(15, 0);
            uscita = nuovoOrario(17, 0);
            break;
    }

    int i;
    for(i = 0; i < 100; i++) {
        if(verificaPosto(settimana, giorno_scelto, fascia_scelta, i) == 0) {
            break;
        }
    }

    printf("\n=========================================================\n");
    printf("Ricerca di un posto disponibile in corso...\n");

    if (i == 100) {
        printf("\n[ATTENZIONE] Nessun posto disponibile per questa fascia oraria!\n");
        printf("Premere INVIO per tornare al menu...");
        getchar();
        return prenotazioni;
    }

    if (data_prenotazione != NULL) {
        prenotazione nuova_p = creaPrenotazione(matricola, data_prenotazione, ingresso, uscita, i);
        
        if (nuova_p != NULL) {
            prenotazioni = consList(nuova_p, prenotazioni);
            
            aggiornaPosto(settimana, giorno_scelto, fascia_scelta, i, 1);
            if (registraPrenotazione(nuova_p) == 1) {
               printf("[SUCCESSO] Prenotazione confermata. Posto assegnato: %d\n", i); 
            } else {
                printf("[ERRORE] Impossibile scrivere i dati nel database.\n");
                rimuoviPrenotazione(nuova_p);
            }
        }
    } 

    printf("\n[SUCCESSO] Inserimento terminato\n");
    printf("Premere INVIO per tornare al menu principale...");
    getchar();

    return prenotazioni;
}

list annullaPrenotazione(list prenotazioni, list settimana) {
    char matricola[20];
    char buffer_input[10];

    prenotazione trovate[50]; 
    int contatore_trovate = 0;

    printf("\033[H\033[J");
    while (getchar() != '\n'); 

    printf("=========================================================\n");
    printf("               ANNULLAMENTO PRENOTAZIONE                 \n");
    printf("=========================================================\n");

    printf("-> Inserisci la tua Matricola: ");
    fgets(matricola, sizeof(matricola), stdin);
    matricola[strcspn(matricola, "\n")] = '\0';

    printf("\nRicerca prenotazioni in corso...\n");
    printf("---------------------------------------------------------\n");

    int totale_prenotazioni = sizeList(prenotazioni);
    for (int i = 1; i <= totale_prenotazioni; i++) {
        prenotazione p = (prenotazione) getItem(prenotazioni, i);
        
        if (p != NULL && strcmp(ottieniMatricolaPR(p), matricola) == 0) {
            trovate[contatore_trovate] = p;
            contatore_trovate++;

            visualizzaPrenotazione(p);
        }
    }

    if (contatore_trovate == 0) {
        printf("\nNessuna prenotazione attiva trovata per la matricola %s.\n", matricola);
        printf("Premere INVIO per tornare al menu principale...");
        getchar();
        return;
    }

    printf("---------------------------------------------------------\n");
    printf("-> Digita il numero della prenotazione da annullare (1-%d, oppure 0 per uscire): ", contatore_trovate);
    
    int scelta;
    scanf("%d", &scelta);

    if (scelta == 0) {
        printf("\nOperazione annullata. Ritorno al menu principale...\n");
        return; 
    }

    if (scelta < 1 || scelta > contatore_trovate) {
        printf("\n[ERRORE] Scelta non valida.\n");
        printf("Premere INVIO per tornare al menu principale...");
        getchar();
        return;
    }

    prenotazione da_cancellare = trovate[scelta - 1];

    data d_canc = ottieniDataPrenotazione(da_cancellare);
    orario ing_canc = ottieniOrarioIngresso(da_cancellare);
    orario usc_canc = ottieniOrarioUscita(da_cancellare);
    int posto_canc = ottieniPostoAssegnato(da_cancellare);
    int giorno_sett = ottieniGiornoSettimana(d_canc);
    

    int fascia_oraria = (ottieniOra(ing_canc) - 9) / 2;

    printf("\nElaborazione in corso...\n");

    if (cancellaPrenotazione(prenotazioni, matricola, d_canc, ing_canc, usc_canc) == 1) {
        aggiornaPosto(settimana, giorno_sett, fascia_oraria, posto_canc, 0);

        int pos;
        if ((pos = posItem(prenotazioni, da_cancellare)) != -1) {
            prenotazioni = removeList(prenotazioni, pos);
        }

        printf("[SUCCESSO] La prenotazione e' stata annullata correttamente!\n");
        printf("Il posto %d e' di nuovo disponibile.\n", posto_canc);
    } else {
        printf("[ERRORE] Si e' verificato un problema nella rimozione dal database.\n");
    }

    printf("\nPremere INVIO per tornare al menu principale...");
    getchar();

    return prenotazioni;
}

void aggiornamentoPosti(list settimana) {
    printf("\033[H\033[J");
    printf("=========================================================\n");
    printf("                    POSTI DISPONIBILI        \n");
    printf("=========================================================\n");

    time_t tempo = time(NULL);
    struct tm d = *localtime(&tempo);

    int giorno_settimana = d.tm_wday;

    while(giorno_settimana <= 5) {
        visualizzaAulaStudio(giorno_settimana, settimana);
        giorno_settimana--;
    }

    
}

void checkInPrenotati(list prenotazioni, list settimana) {
    char matricola[20];

    int trovata = 0;

    printf("\033[H\033[J");
    printf("=========================================================\n");
    printf("               CHECK-IN STUDENTE PRENOTATO               \n");
    printf("=========================================================\n");
    
    printf("-> Inserisci la tua Matricola: ");
    fgets(matricola, sizeof(matricola), stdin);
    matricola[strcspn(matricola, "\n")] = '\0';

    time_t tempo = time(NULL);
    struct tm d = *localtime(&tempo);
    int minuti_correnti_totali = (d.tm_hour * 60) + d.tm_min;
    int tolleranza = 30;
    data oggi = nuovaData(d.tm_wday, d.tm_mday, d.tm_mon+1, d.tm_year+1900);

    printf("\nRicerca prenotazioni per oggi in corso...\n");
    printf("---------------------------------------------------------\n");

    int totale_prenotazioni = sizeList(prenotazioni);
    for (int i = 1; i <= totale_prenotazioni; i++) {
        prenotazione p = (prenotazione) getItem(prenotazioni, i);

        int minuti_inizio_prenotazione = (ottieniOra(ottieniOrarioIngresso(p)) * 60) + ottieniMinuti(ottieniOrarioIngresso(p));
        
        if (p != NULL && strcmp(ottieniMatricolaPR(p), matricola) == 0) {
            if (
                comparaData(ottieniDataPrenotazione(p), oggi) == 1 && 
                minuti_correnti_totali >= minuti_inizio_prenotazione && 
                minuti_correnti_totali <= (minuti_inizio_prenotazione + tolleranza)
            ) {
                visualizzaPrenotazione(p);

                int fascia_oraria = (ottieniOra(ottieniOrarioIngresso(p)) - 9) / 2;
        
                aggiornaPosto(settimana, ottieniGiornoSettimana(ottieniDataPrenotazione(p)), fascia_oraria, ottieniPostoAssegnato(p), 2);

                int pos;
                if ((pos = posItem(prenotazioni, p)) != -1) {
                    prenotazioni = removeList(prenotazioni, pos);
                }

                printf("\n[SUCCESSO] Check-in completato! Puoi accomodarti al posto %d.\n", ottieniPostoAssegnato(p));
            } else {
                printf("[ERRORE] Si e' verificato nelle operazioni di check-in.\n");
            }

            trovata++;
            break;
        }
    }

    if (trovata == 0) {
        printf("\nNessuna prenotazione trovata per oggi con la matricola %s.\n", matricola);
        printf("Premere INVIO per tornare al menu...");
        getchar();
        return;
    }
    
    printf("Premere INVIO per continuare...");
    getchar();
}

void checkInNonPrenotati(list settimana, queue lista_attesa) {
    char matricola[20];

    printf("\033[H\033[J");
    printf("=========================================================\n");
    printf("             CHECK-IN STUDENTE NON PRENOTATO             \n");
    printf("=========================================================\n");

    printf("-> Inserisci la tua Matricola: ");
    fgets(matricola, sizeof(matricola), stdin);
    matricola[strcspn(matricola, "\n")] = '\0';

    time_t tempo = time(NULL);
    struct tm d = *localtime(&tempo);
    
    int giorno_settimana = d.tm_wday;

    int fascia_corrente = (d.tm_hour - 9) / 2;

    printf("\nOrario rilevato: %02d:%02d\n", d.tm_hour, d.tm_min);
    printf("Verifica disponibilità posti in corso...\n");
    printf("---------------------------------------------------------\n");

    // Ricerca di un posto libero
    int posto_trovato = -1;
    for (int i = 0; i < 100; i++) {
        if (verificaPosto(settimana, giorno_settimana, fascia_corrente, i) == 0) {
            posto_trovato = i;
            break;
        }
    }

    if (posto_trovato != -1) {
        // posto libero
        aggiornaPosto(settimana, giorno_settimana, fascia_corrente, posto_trovato, 2);
            
        printf("[SUCCESSO] Ingresso autorizzato senza prenotazione!\n");
        printf("Ti è stato assegnato il posto: %d.\n", posto_trovato);
    } else {
        // aula piena
        printf("\n[ATTENZIONE] Aula PIENA! Nessun posto disponibile nella fascia corrente.\n");
        printf("Vuoi essere inserito nella Lista d'Attesa per questa fascia? (1 = Si', 0 = No): ");
        
        int risposta;
        scanf("%d", &risposta);

        if (risposta == 1) {
            enqueue(lista_attesa, matricola); 
            
            printf("\n[SUCCESSO] Sei stato inserito nella lista d'attesa.\n");
            printf("Se qualcuno effettuerà il check-out o annullerà, verrai chiamato automaticamente.\n");
        } else {
            printf("\nOperazione annullata. Ingresso negato per mancanza di posti.\n");
        }
    }

    printf("\nPremere INVIO per tornare al menu principale...");
    getchar();
}

void checkIn(list prenotazioni, list settimana, queue lista_attesa) {
    char buffer_input[10];

    printf("\033[H\033[J");
    printf("=========================================================\n");
    printf("                   GESTIONE CHECK-IN INGRESSO            \n");
    printf("=========================================================\n");
    printf("  1. Check-in Studenti PRENOTATI\n");
    printf("  2. Check-in Studenti NON PRENOTATI\n");
    printf("---------------------------------------------------------\n");
    printf("  0. Torna al Menu Principale\n");
    printf("=========================================================\n");
    printf("Seleziona un'opzione: ");

    fgets(buffer_input, sizeof(buffer_input), stdin);
    int scelta = atoi(buffer_input);

    switch(scelta) {
        case 1:
            checkInPrenotati(prenotazioni, settimana);
            break;
        case 2:
            checkInNonPrenotati(settimana, lista_attesa);
            break;
        case 0:
            return;
        default:
            printf("\nOpzione non valida. Premere INVIO per tornare...");
            getchar();
            break;
    }
}


int main() {
    int scelta = -1;

    hashtable studenti = caricaStudenti();
    list prenotazioni = caricaPrenotazioni();
    list settimana = inizializzaPianoSettimanale();

    associaPosti(prenotazioni, settimana);

    queue lista_attesa = newQueue();

    do {
        stampaMenu();
        
        if (scanf("%d", &scelta) != 1) {
            while (getchar() != '\n');
            scelta = -1; 
        }

        printf("\n");

        switch (scelta) {
            case 1: {
                aggiungiStudente(studenti);
                break;
            }

            case 2: {
                prenotazioni = nuovaPrenotazione(studenti, prenotazioni, settimana);
                break;
            }

            case 3:
                prenotazioni = annullaPrenotazione(prenotazioni, settimana);
                break;

            case 4:
                aggiornamentoPosti(settimana);
                break;

            case 5:
                checkIn(prenotazioni, settimana, lista_attesa);
                break;

            case 6:
                printf("\033[H\033[J");
                printf("--- REGISTRAZIONE USCITA STUDENTE ---\n");
                break;

            case 7:
                printf("\033[H\033[J");
                printf("--- VISUALIZZAZIONE STUDENTI ---\n");
                break;

            case 8:
                printf("\033[H\033[J");
                printf("--- GESTIONE LISTA DI ATTESA ---\n");
                break;

            case 9:
                printf("\033[H\033[J");
                printf("--- STORICO DEGLI ACCESSI ---\n");
                break;

            case 10:
                printf("\033[H\033[J");
                printf("--- GENERAZIONE REPORT ---\n");
                break;

            case 0:
                printf("\nChiusura del sistema. Salvataggio dati in corso...\n");
                // TODO: Freeing della memoria
                break;

            default:
                printf("\033[H\033[J");
                printf("\nATTENZIONE: Scelta non valida. Inserisci un numero tra 0 e 12.\n");
                break;
        }

    } while (scelta != 0);

    printf("\nArrivederci!\n");
    return 0;
}