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
#include "utils/report.h"
#include "utils/load.h"


int main() {
    int scelta = -1;

    hashtable studenti = caricaStudenti();
    list prenotazioni = caricaPrenotazioni();
    list settimana = inizializzaPianoSettimanale();

    associaPosti(prenotazioni, settimana);

    list studenti_in_aula = newList();
    queue lista_attesa = newqueue();

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
                lista_attesa = checkIn(prenotazioni, settimana, studenti_in_aula, lista_attesa);
                break;

            case 6:
                checkOut(settimana, studenti_in_aula, lista_attesa);
                break;

            case 7:
                visualizzaStudenti(studenti_in_aula, lista_attesa, settimana);
                break;

            case 8:
                lista_attesa = gestioneListaAttesa(lista_attesa);
                break;

            case 9:
                cancellaPrenotazioniScadute(settimana, lista_attesa, studenti_in_aula);
                break;

            case 10:
                menuStoricoAccessi();
                break;

            case 11:
                report(settimana, prenotazioni, lista_attesa);
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