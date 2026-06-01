#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "modules/studente.h"
#include "lib/list.h"
#include "lib/queue.h"
#include "lib/hash_table.h"
#include "file_utils.h" 



// Funzione di supporto per stampare l'interfaccia a video
void stampaMenu() {
    printf("\n");
    printf("=========================================================\n");
    printf("              SISTEMA GESTIONE AULE STUDIO               \n");
    printf("=========================================================\n\n");
    printf("  1. Registrazione Studente\n");
    printf("  2. Inserimento Prenotazione\n");
    printf("  3. Annullamento Prenotazione\n");
    printf("  4. Verifica Disponibilita' Posti per Fascia Oraria\n");
    printf("  5. Aggiornamento dei Posti Disponibili\n");
    printf("  6. Gestione Check-in Prenotati\n");
    printf("  7. Gestione Check-in Non Prenotati\n");
    printf("  8. Registrazione Uscita di uno Studente\n");
    printf("  9. Visualizzazione Studenti (Prenotati, Presenti, Attesa)\n");
    printf(" 10. Gestione Lista di Attesa\n");
    printf(" 11. Visualizzazione Storico degli Accessi\n");
    printf(" 12. Generazione Report\n\n");
    printf("  0. Esci dal Programma\n\n");
    printf("=========================================================\n");
    printf("\nSeleziona un'opzione: ");
}

int main() {
    int scelta = -1;

    // TODO: Inserisci qui l'inizializzazione delle strutture dati (Hash, Liste, ecc.)
    hashtable studenti = caricaStudenti();
    list prenotazioni = caricaPrenotazioni();
    list settimana = inizializzaPianoSettimanale();

    associaPosti(prenotazioni, settimana);

    do {
        stampaMenu();
        
        // Lettura sicura dell'input (evita loop infiniti se l'utente inserisce lettere)
        if (scanf("%d", &scelta) != 1) {
            // Svuota il buffer in caso di input non numerico
            while (getchar() != '\n');
            scelta = -1; 
        }

        printf("\n");

        switch (scelta) {
            case 1: {
                printf("\033[H\033[J");
                
                char nome_cognome[100];
                char matricola[20];
                char corso_laurea[100];

                // PULIZIA DEL BUFFER FLUSSO: Svuota il '\n' rimasto dalla scanf del menu principale
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

                if(searchHash(studenti, matricola)!= NULL) {
                    printf("Matricola già esistente!\n");
                    break;
                }

                studente nuovo = creaStudente(nome_cognome, matricola, corso_laurea);

                if (nuovo == NULL) {
                    printf("[ERRORE] Impossibile allocare memoria per lo studente.\n");
                    return;
                }

                int esito = registraStudente(nuovo);

                if (esito == 1) {
                    printf("Studente \"%s\" registrato nel database!\n", nome_cognome);
                    
                    InsertHash(studenti, matricola, nuovo);
                    
                } else {
                    printf("[ERRORE] Impossibile scrivere i dati nel database.\n");
                    // Se il salvataggio fallisce, liberiamo la memoria dello studente per evitare leak
                    distruggiStudente(nuovo); 
                }
                
                printf("Premere INVIO per tornare al menu principale...");
                getchar();
                break;
            }

            case 2:
                printf("\033[H\033[J");
                printf("--- INSERIMENTO PRENOTAZIONE ---\n");

                char matricola[20];
                char buffer_input[10]; // Buffer temporaneo per leggere i numeri in sicurezza
                int giorno_scelto = -1;
                int fascia_scelta = -1;

                // 1. Pulizia schermo e buffer
                while (getchar() != '\n'); // Svuota l'input residuo dal menu principale

                printf("=========================================================\n");
                printf("               INSERIMENTO NUOVA PRENOTAZIONE            \n");
                printf("=========================================================\n");


                // 2. Inserimento e verifica Matricola
                printf("-> Inserisci la tua Matricola: ");
                fgets(matricola, sizeof(matricola), stdin);
                matricola[strcspn(matricola, "\n")] = '\0'; 


                if (SearchHash(studenti, matricola) == NULL) {
                    printf("\n[ERRORE] Matricola '%s' non trovata nel sistema!\n", matricola);
                    printf("Devi prima registrarti (Opzione 1 del menu principale).\n");
                    printf("\nPremere INVIO per tornare al menu...");
                    getchar();
                    return; 
                }


                time_t tempo = time(NULL);
                struct tm d = *localtime(&tempo);

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


                // 3. Stampa e scelta del Giorno della settimana
                
                printf("-> Seleziona il giorno desiderato (1-5): ");
                fgets(buffer_input, sizeof(buffer_input), stdin);
                giorno_scelto = atoi(buffer_input); // Converte la stringa in numero in modo sicuro

                if (giorno_scelto < 1 || giorno_scelto > 5) {
                    printf("\n[ERRORE] Scelta non valida. Il giorno deve essere compreso tra 1 e 5.\n");
                    printf("Premere INVIO per tornare al menu...");
                    getchar();
                    return;
                }

                data data_prenotazione = ottieniDataDaGiornoSettimana(giorno_scelto);

                // 4. Stampa e scelta della Fascia Oraria
                printf("\n--- FASCE ORARIE DISPONIBILI ---\n");
                printf("  0. 09:00 - 11:00\n");
                printf("  1. 11:00 - 13:00\n");
                printf("  2. 13:00 - 15:00\n");
                printf("  3. 15:00 - 17:00\n");
                
                printf("-> Seleziona la fascia oraria (0-3): ");
                fgets(buffer_input, sizeof(buffer_input), stdin);
                fascia_scelta = atoi(buffer_input);

                if (fascia_scelta < 0 || fascia_scelta > 3) {
                    printf("\n[ERRORE] Scelta non valida. La fascia deve essere compresa tra 0 e 3.\n");
                    printf("Premere INVIO per tornare al menu...");
                    getchar();
                    return;
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
                    if( verificaPosto(settimana, giorno_scelto, fascia_scelta, i)) 
                    break;
                }

                printf("\n=========================================================\n");
                printf("Ricerca di un posto disponibile in corso...\n");
                if (data_prenotazione != NULL) {
                prenotazione nuova_p = creaPrenotazione(matricola, data_prenotazione, ingresso, uscita, i);
                } 

                list consList(nuova_p, prenotazioni);

                break;

            case 3:
                printf("\033[H\033[J");
                printf("--- ANNULLAMENTO PRENOTAZIONE ---\n");
                // Richiama la funzione di cancellazione
                break;

            case 4:
                printf("\033[H\033[J");
                printf("--- VERIFICA DISPONIBILITA' POSTI ---\n");
                // Richiama la funzione di controllo fasce
                break;

            case 5:
                printf("\033[H\033[J");
                printf("--- AGGIORNAMENTO POSTI DISPONIBILI ---\n");
                // Logica di aggiornamento manuale o automatico
                break;

            case 6:
                printf("\033[H\033[J");
                printf("--- GESTIONE CHECK-IN PRENOTATI ---\n");
                // Logica di convalida accesso per chi ha già prenotato
                break;

            case 7:
                printf("\033[H\033[J");
                printf("--- GESTIONE CHECK-IN NON PRENOTATI ---\n");
                // Logica per gestire i walk-in se ci sono posti
                break;

            case 8:
                printf("\033[H\033[J");
                printf("--- REGISTRAZIONE USCITA STUDENTE ---\n");
                // Logica per liberare il posto attuale
                break;

            case 9:
                printf("\033[H\033[J");
                printf("--- VISUALIZZAZIONE STUDENTI ---\n");
                // Stampa i contatori: es. printf("Prenotati: %d | Presenti: %d | In Attesa: %d\n", p, pr, a);
                break;

            case 10:
                printf("\033[H\033[J");
                printf("--- GESTIONE LISTA DI ATTESA ---\n");
                // Visualizzazione e scorrimento della coda
                break;

            case 11:
                printf("\033[H\033[J");
                printf("--- STORICO DEGLI ACCESSI ---\n");
                // Lettura e stampa dei log di accesso storici
                break;

            case 12:
                printf("\033[H\033[J");
                printf("--- GENERAZIONE REPORT ---\n");
                // Esportazione o visualizzazione delle statistiche
                break;

            case 0:
                printf("\nChiusura del sistema. Salvataggio dati in corso...\n");
                // TODO: Inserisci qui le funzioni di free() e salvataggio finale su file
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

