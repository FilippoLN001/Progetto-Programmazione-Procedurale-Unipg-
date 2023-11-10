#include "gamelib.h"


int main() {
  int flag=0;
        printf("\n");
        printf("\n");
        printf("Un gruppo di astronauti si trova in viaggio sull’astronave Skelt, e il loro obiettivo è riuscire a completare tutte le attività previste (le quest)\nper il mantenimento della nave, arrivando così a destinazione.\nTra di loro si celano però anche degli impostori, il cui scopo è eliminare di nascosto gli astronauti senza farsi scoprire da essi.\nRiusciranno ad arrivare a destinazione prima di essere decimati?\n");
        while (getchar() != '\n');
        system("@cls||clear");
        int scelta=0;


        printf(". ,　　　　.　 .　　 .\033[0;34m   _______  ______    _______  __    _  __    _  _______  ___\033[0m . ,　　　　.　 .　　 .\n");
        printf("　。　　 。  . 　.　  \033[0;34m  |       ||    _ |  |   _   ||  |  | ||  |  | ||       ||   |\033[0m　。　　 。  . 　.    \n");
        printf("•　 　ﾟ  　。    .    \033[0;34m  |_     _||   | ||  |  |_|  ||   |_| ||   |_| ||   _   ||   |\033[0m. ,　　ඞ 　.　 .　   .\n");
        printf("　。　　 。  . 　.　  \033[0;34m    |   |  |   |_||_ |       ||       ||       ||  | |  ||   |\033[0m　。　　 。  . 　.    \n");
        printf("•　 　ﾟ　　。 　　.   \033[0;34m    |   |  |    __  ||       ||  _    ||  _    ||  |_|  ||   |\033[0m　。　　 。  . 　.    \n");
        printf(". ,　　　　.　 .　　 .\033[0;34m    |   |  |   |  | ||   _   || | |   || | |   ||       ||   |\033[0m. ,　　　　.　 .　　 .\n");
        printf("　。　　 。  . 　.　  \033[0;34m    |___|  |___|  |_||__| |__||_|  |__||_|  |__||_______||___|\033[0m　。　　 。  . 　.    \n");
        printf("•　 　ﾟ　　。 　　.•　 　ﾟ　　。 　　.•　 　ﾟ　　。 　　. . ,　　　　.　 .　　 .. ,　　　　.　 .　　 .. ,　　　\n");
        printf("      　　\033[0;33mඞ\033[0m 　.　 .　   .  。　   。  . 　.　  1) IMPOSTA GIOCO  。　　 。  . 　.。　　 。  . 　.。　　 。\n");
        printf("     。　　 。  . 　.　。  　 。  .            2) GIOCA         ,　　\033[0;31mඞ\033[0m 　.　 .　     •　 　ﾟ　　。 　　.•\n");
        printf(" 。　　 。  . 　.。　　 。  . 　.。    。  .   3) TERMINA GIOCO 。　　 。  . 　.。　　 。  . 　.。　　 。  \n");
        printf("。　　 。  . 　. 。　　 。  . 　. 。　　 。  . 　. 。　　 。  . 　. 。　　 。  . 　. 。　　 。  . 　. 。　　\n");
        printf("\n");
        do{
                printf("\033[1;33m");
                if (flag==1) {//se l'utente ha gia impostato il gioco visualizza il ben tornato nel menu
                  scelta=0;
                        printf("\n         +----------------------------------------------------------------------------+\n");
                        printf("         |                        BENTORNATO NEL MENU' PRINCIPALE                     |\n");
                        printf("         +----------------------------------------------------------------------------+\n\n");
                        printf("\n");
                        printf("Ora che hai impostato il gioco puoi iniziare a giocare!\nPremi 1 se vuoi reimpostare il Gioco\nPremi 2  per iniziare a giocare\n");
                      }
                scanf("%d",&scelta);
                while(getchar()!='\n');
                printf("\n");
                switch (scelta) {
                case 1: printf("Hai scelto imposta gioco :\n");
                        system("@cls||clear");
                        Imposta_gioco();//funzione imposta gioco
                        flag=1;//variabile per verificare se l'utente ha scelto imposta gioco
                        break;
                case 2: printf("Hai scelto Gioca ! : \n");
                        if(flag!=0) {
                                system("@cls||clear");
                                gioca();
                        }
                        else{
                                printf("DEVI PRIMA IMPOSTARE IL GIOCO PRIMA DI GIOCARE\nPREMI 1 PER IMPOSTARE IL GIOCO\n"); //controllo se il giocatore non ha impostato prima imposta_gioco


                        }
                        break;
                case 3: printf("CHIUSURA DEL GIOCO...\n");
                              sleep(1);
                              Termina_Gioco();//Funzione termina_gioco per chiudere il gioco
                              exit(0);
                        break;
                default:
                        printf("\n");
                        printf("scegli tra Imposta Gioco, Gioca, Termina Gioco\n");
                        printf("\n");
                        sleep(1);
                        system("@cls||clear");
                        break;

                }
        }while(scelta!=3);

}
