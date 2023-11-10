#include <stdio.h>
#include <stdlib.h>
#include "gamelib.h"
#include <string.h>
#include <time.h>
//strutture implementate e definite per lo scorrimento tra le stanze
static struct Giocatore *giocatori=NULL;                                       //struct dei giocatori
static struct Stanza *stanza_inizio=NULL;                                      //struct di stanza inizio per spostare tutti i giocatori a stanza inizio
static struct Stanza *lista_stanze=NULL;                                       //struct di lista stanze per permettere un collegamento tra le stanze
static struct Stanza *ultima_stanza=NULL;                                      //struct ultima stanza per collegare l'ultima stanza con la nuova stanza creata
//Funzioni statice definite accanto la riga di codice
static int Impostore_crewmate(int c);                                           //154
static void StampaGiocatori(int a);                                             //211
static int Percentuale_stanza();                                                //322
static void Stanza_Iniziale();                                                  //225
static void Inzializza_stanza(struct Stanza *Values);                           //311
static void Turno_Astronauta(struct Giocatore *Player,struct Stanza *Room,int p); //352
static void Turno_Impostore(struct Giocatore *Player,struct Stanza *Room,int p);  //390
static int Avanza(struct Giocatore *Player,struct Stanza *Room,int p);            //433
static void Uccidi_Astronauta(struct Giocatore *Player,struct Stanza *Room);      //614
static void Defestra_giocatore(struct Giocatore *Player,struct Stanza *Room);     //655
static void Esegui_quest(struct Giocatore *Player, struct Stanza *Room);          //577
static void Chiamata_emergenza(struct Giocatore *Player,struct Stanza *Room);     //724
static void Sabotaggio(struct Giocatore *Player,struct Stanza *Room);             //704
static void Usa_botola(struct Giocatore *Player,struct Stanza *Room);             //801
static int Numero_quest();                                                        //865
void Inizia_gioco(){
}
static int calcolo_probabilita(int prob);                                        //877


unsigned int sleep(unsigned int seconds);//questa veriabile serve per mettere in pausa i processi di tot secondi
unsigned short quest_da_finire=0;
char *colore[] ={"\033[0;91mrosso\033[0m","\033[0;34mblu\033[0m","\033[0;33mgiallo\033[0m","\033[0;32mverde\033[0m","\033[0;93marancione\033[0m","\033[0;31mrosa\033[0m","\033[40m\033[0;37mbianco\033[0m\033[0m","\033[0;30m\033[47mnero\033[0m","\033[0;35mviola\033[0m","\033[0;95mmarrone\033[0m"};
char *stato[]={"astronauta","\033[0;91mimpostore\033[0m","\033[0;31massassinato\033[0m","defenestrato"};
char *Tstanza[]={"\033[1;32mvuota\033[0m","\033[1;32mquest_semplice\033[0m","\033[1;32mquest_complicata\033[0m","\033[1;32mbotola\033[0m"};
int Random[10]={0,1,2,3,4,5,6,7,8,9};
//VARIABILI GLOBALI DEFINITE
int n_giocatori=0;
int turno=0;
int n_botole=0;
int n_stanze=0;
int n_impostori=0;
int n_astronauti=0;
int quit=0;

void Imposta_gioco(){
        time_t t;
        printf("\033[1;32m");
        printf("\n  +----------------------------------------------------------------------------+\n");
        printf(" |                           BENUVENUTO IN IMPOSTA GIOCO!                       |\n");
        printf("  +----------------------------------------------------------------------------+\n");
        printf("\033[0m");
        printf("                               PREMI PER CONTINUARE...                           \n");
        while(getchar()!='\n');
        printf("\n");



        int choose=0;
        do{

                printf("Inserisci numero Giocatori da 4 fino a 10 giocatori : \n");
                scanf("%d",&n_giocatori);
                while(getchar()!='\n');
        }while (n_giocatori<4 || n_giocatori>10);


        giocatori=(struct Giocatore*)malloc(n_giocatori * sizeof(struct Giocatore));// creo una memoria dinamica in base a quanti giocatori vogliono giocare

        srand((unsigned)time(&t));
        n_impostori=Impostore_crewmate(n_giocatori); //con questa funzione mi ritorna il numero di impostori e li assegno alla variabile n_impostori

        for(int i=n_giocatori-1; i>0; i--) {
                //random di giocatori senza ripetizione
                int temp=Random[i];
                int randomIndex = rand()%i;
                Random[i]=Random[randomIndex];
                Random[randomIndex]=temp;

        }


        for(int i=0; i<n_giocatori; i++) {
                switch (Random[i]) {
                //assegno tramite uno switch il risultato della random al rispettivo colore
                case 0:
                        giocatori[i].nome=rosso;
                        break;
                case 1:
                        giocatori[i].nome=blu;
                        break;
                case 2:
                        giocatori[i].nome=giallo;
                        break;
                case 3:
                        giocatori[i].nome=verde;
                        break;
                case 4:
                        giocatori[i].nome=arancione;
                        break;
                case 5:
                        giocatori[i].nome=rosa;
                        break;
                case 6:
                        giocatori[i].nome=bianco;
                        break;
                case 7:
                        giocatori[i].nome=nero;
                        break;
                case 8:
                        giocatori[i].nome=viola;
                        break;
                case 9:
                        giocatori[i].nome=marrone;
                        break;
                }
        }
        printf("Adesso decidi quante Quest inserire per far vincere gli astronauti.\nASPETTA..\n");
        sleep(1);
        Numero_quest();//funzione dichiarate di chiedere il numero di quest da completare per finire il gioco
        system("@cls||clear");

        do{
                printf("+------------------------------------------------------------------------------------+\n");
                printf("|                           IMPOSTA GIOCO COMPLETATA:                                |\n");
                printf("|                         1) Stampa i giocatori e inizia a giocare                   |\n");
                printf("|                         2) Inizia a giocare                                        |\n");
                printf("+------------------------------------------------------------------------------------+\n");
                scanf("%d",&choose);
                while(getchar()!='\n');
                printf("\n");
                switch (choose) {
                case 1:
                        StampaGiocatori(n_giocatori); //funzione dichiarata per visualizzare a schermo tutti i giocatori e lo stato del giocatore
                        printf("PREMI INVIO PER TORNARE AL MENU\n");
                        while(getchar()!='\n');
                        system("@cls||clear");

                        Inizia_gioco();//inizia gioco è una funzione che non fa nulla serve solo per richiamare il main
                        break;
                case 2:
                        system("@cls||clear");
                        Inizia_gioco();
                        break;
                default:
                        printf("Devi scegliere tra 1 e 2 !\n");
                        break;
                }
        }while(choose<1 || choose>2);
}





static int Impostore_crewmate(int c){  //Questa funzione assegna casualmente gli impostori dipendentemente dal numero di giocatori scelti in imposta gioco
        int i_primo=0;
        int i_secondo=0;
        int i_terzo=0;
        int ritorno=0;
        if(c==4||c==5) {
                i_primo=rand()%c;
                for(int i=0; i<c; i++) {
                        if(i==i_primo) {
                                giocatori[i].giocatore=impostore;
                        }
                }
                ritorno=1;

        }
        if(c==6||c==7) {
                do{
                        i_primo=rand()%c;
                        i_secondo=rand()%c;
                }while(i_primo==i_secondo);
                for(int i=0; i<c; i++) {
                        if(i==i_primo) {
                                giocatori[i].giocatore=impostore;
                        }
                        if(i==i_secondo) {
                                giocatori[i].giocatore=impostore;
                        }

                }
                ritorno=2;

        }
        if(c==8||c==9||c==10) {
                do{
                        i_primo=rand()%c;
                        i_secondo=rand()%c;
                        i_terzo=rand()%c;
                }while(i_primo==i_secondo || i_secondo==i_terzo || i_terzo==i_primo);
                for(int i=0; i<c; i++) {
                        if(i==i_primo) {
                                giocatori[i].giocatore=impostore;
                        }
                        if(i==i_secondo) {
                                giocatori[i].giocatore=impostore;
                        }
                        if(i==i_terzo) {
                                giocatori[i].giocatore=impostore;
                        }
                }
                ritorno=3;


        }
        return ritorno;// siccome è una fuzione con variabile int ritorna il numero di impostori per distinguerli con il numero dei astronauti
}
static void StampaGiocatori(int a) {
        printf("+----------------------------------------------------------------------------+\n");
        printf("|                                ELENCO GIOCATORI:                            |\n");
        printf("+----------------------------------------------------------------------------+\n");
        int persona =1;
        for (size_t i = 0; i <a; i++) {
                printf("Giocatore \033[0;31m%d\033[0m, colore :%s  \n",persona,colore[giocatori[i].nome]);
                printf("Stato:%s\n",stato[giocatori[i].giocatore]);
                printf("\n");
                persona++;
        }

}

static void Stanza_Iniziale(){
        stanza_inizio=(struct Stanza *)malloc(sizeof(struct Stanza));
        stanza_inizio->Nextavanti=NULL;
        stanza_inizio->Nextsinistra=NULL;
        stanza_inizio->Nextdestra=NULL;
        stanza_inizio->stanza_Precedente=NULL;
        for (int i = 0; i < n_giocatori; i++) {
                giocatori[i].posizione=stanza_inizio;
        }
        lista_stanze=stanza_inizio;
        ultima_stanza=stanza_inizio;
        printf("Stanza iniziale tipo: %s\n",Tstanza[Percentuale_stanza(stanza_inizio)]);
        if(stanza_inizio->stanza==botola) {
                n_botole++;
        }
        n_stanze++;
        sleep(2);
        system("@cls||clear");
}


void gioca(){

        n_astronauti=n_giocatori-n_impostori; //controlla il numero dei impostori ed il numero degli astronauti.


        int Random1[10]={0,1,2,3,4,5,6,7,8,9};
        printf("                                                                                     \n");
        printf(" _______  _______  __    _  __   __  _______  __    _  __   __  _______  _______  __ \n");
        printf("|  _    ||       ||  |  | ||  | |  ||       ||  |  | ||  | |  ||       ||       ||  |\n");
        printf("| |_|   ||    ___||   |_| ||  |_|  ||    ___||   |_| ||  | |  ||_     _||   _   ||  |\n");
        printf("|       ||   |___ |       ||       ||   |___ |       ||  |_|  |  |   |  |  | |  ||  |\n");
        printf("|  _   | |    ___||  _    ||       ||    ___||  _    ||       |  |   |  |  |_|  ||__|\n");
        printf("| |_|   ||   |___ | | |   | |     | |   |___ | | |   ||       |  |   |  |       | __ \n");
        printf("|_______||_______||_|  |__|  |___|  |_______||_|  |__||_______|  |___|  |_______||__|\n");
        printf("                                                                                     \n");
        printf("                                                                                     \n");

        printf("\n");

        printf("\033[0;93mPrima di tutto creiamo la stanza iniziale\033[0m\n");
        printf("\n");
        printf("PREMI PER CONTINUARE....\n");
        while(getchar()!='\n');
        printf("\n");
        Stanza_Iniziale();


        do{ //ciclo infinito per i giocatori
                for(int i=n_giocatori-1; i>0; i--) { // random dei giocatori per non ripetere il turno dello stesso giocatore
                        int temp=Random1[i];
                        int randomIndex = rand()%i;
                        Random1[i]=Random1[randomIndex];
                        Random1[randomIndex]=temp;

                }
                for (int i = 0; i < n_giocatori; i++) {

                        turno=Random1[i];
                        printf("Turno di: %s\n",colore[giocatori[turno].nome]);
                        printf("\n");

                        if(giocatori[turno].giocatore==astronauta) {

                                Turno_Astronauta(&giocatori[turno],lista_stanze,turno);// turno dell'astronauta

                        }
                        else if(giocatori[turno].giocatore==impostore) {

                                Turno_Impostore(&giocatori[turno],lista_stanze,turno);//turno impostore

                        }
                        else if(giocatori[turno].giocatore==assassinato) {
                                printf("Sei stato assassinato!  \n");
                                sleep(1);
                                system("@cls||clear");
                        }
                        else if(giocatori[turno].giocatore==defenestrato) {
                                printf("Sei stato defenestrato dall'Astronave\n");
                                sleep(1);
                                system("@cls||clear");

                        }
                }
        }while (1);
}



static void Inzializza_stanza(struct Stanza *Values){ //funzione per inizializzare la stanza
        (*Values).Nextavanti=NULL;
        (*Values).Nextdestra=NULL;
        (*Values).Nextsinistra=NULL;
        (*Values).Pnext=NULL;
        (*Values).Emergency_flag=false;


}



static int Percentuale_stanza(struct Stanza *Room){// funzione da utilizzare per assegna randomicamente la stanza
        time_t t;
        int ritorno;
        srand((unsigned)time(&t));
        printf("\n");
        int r=rand()%100;
        if(r<=24) {
                Room->stanza = botola;
                ritorno=3;
                printf("\n");
        }
        else if(r >=25 && r<=39) {
                Room->stanza=quest_complicata;
                ritorno=2;

        }
        else if(r >=40&& r<=69) {
                Room->stanza=quest_semplice;
                ritorno=1;

        }
        else if (r >=70 && r<=99) {
                Room->stanza=vuota;
                ritorno=0;

        }
        return ritorno;
}


static void Turno_Astronauta(struct Giocatore *Player,struct Stanza *Room,int p){ // funzione turno astronauta
        int scelta=0;


        printf("Sei in una stanza di tipo : %s\n",Tstanza[giocatori[turno].posizione->stanza] ); //visualizzare a video il tipo di stanza dove si trova il giocatore

        printf("Sei in stanza con:\n");
        for(int i=0; i<n_giocatori; i++) {// visualizza a video i giocatore nella stanza con lui
                if(Player->posizione==giocatori[i].posizione &&i!=p && giocatori[i].giocatore!=defenestrato) {
                        printf("%s \n",colore[giocatori[i].nome]);
                }

        }
        printf("--------------------------------------\n");
        printf("\n");
        do{
                printf("\033[0;93mAstronauta. Hai 3 opzioni:\033[0m\n\n1)Provare ad avanzare nella stanza successiva\n2)Eseguire la quest\n3)Chiamata di emergenza\n");
                scanf("%d",&scelta);
                while (getchar() != '\n');
                printf("\n");
                switch (scelta) {
                case 1:
                        Avanza(Player,Room,p);
                        break;
                case 2:
                        Esegui_quest(Player,Room);
                        break;
                case 3:
                        Chiamata_emergenza(Player,Room);
                        break;
                default:
                        printf("\033[0;91mValore inserito non valido!\033[0m\n");
                        printf("\n");
                        break;
                }
        }while (scelta<1||scelta>3);
}

static void Turno_Impostore(struct Giocatore *Player,struct Stanza *Room,int p){ //turno impostore
        int scelta=0;
        printf("Sei in una stanza di tipo : %s\n",Tstanza[giocatori[turno].posizione->stanza] ); //visualizzare a video il tipo di stanza dove si trova il giocatore

        printf("Sei in stanza con:\n");
        for(int i=0; i<n_giocatori; i++) {// visualizza a video i giocatore nella stanza con lui
                if(Player->posizione==giocatori[i].posizione &&i!=p && giocatori[i].giocatore!=defenestrato) {
                        printf("%s-(%s)\n",colore[giocatori[i].nome],stato[giocatori[i].giocatore]);
                }
        }
        printf("--------------------------------------\n");

        printf("\n");
        do{
                printf("\033[0;93mImpostore. Hai 5 opzioni:\033[0m\n\nHai il compito di uccidere gli astronauti per vincere\nCosa scegli:\n1)Avanza\n2)Sabotaggio\n3)Uccidi Astronauta\n4)Chiamata emergenza\n5)Usa botola\n");
                scanf("%d",&scelta);
                while (getchar() != '\n');
                printf("\n");
                switch (scelta) {
                case 1:
                        Avanza(Player,Room,p);
                        break;
                case 2:
                        Sabotaggio(Player,Room);
                        break;
                case 3:
                        Uccidi_Astronauta(Player,Room);
                        Defestra_giocatore(Player,Room);
                        break;
                case 4:
                        Chiamata_emergenza(Player,Room);
                        break;
                case 5:
                        Usa_botola(Player,Room);
                        break;
                default:
                        printf("\033[0;91mValore inserito non valido!\033[0m\n");
                        printf("\n");
                        break;
                }
        }while (scelta<1 || scelta>5);
}

static int Avanza(struct Giocatore *Player,struct Stanza *Room,int p){
        int avanza=0;
        int dAvanza=0;
        printf("\033[0;93mCosa scegliere di fare:\033[0m\n1) Avanzare alla prossima stanza\n2) Rimanere nella stanza\n");
        scanf("%d",&avanza);
        while(getchar()!='\n');
        if(avanza==1) {
                do{
                        printf("\033[0;93mDove voler Avanzare :\033[0m\n1) Avanti \n2) Destra \n3) Sinistra\n");
                        scanf("%d",&dAvanza);
                        while(getchar()!='\n');
                        switch (dAvanza) {
                        case 1:
                                if((Player->posizione)->Nextavanti==NULL) { //controllare se muovendosi avanti il puntatore è inizializzato a NULL e quindi la stanza non esiste e bisogna crearla
                                        struct Stanza *Nuova_stanza =(struct Stanza*) malloc(sizeof(struct Stanza));
                                        Inzializza_stanza(Nuova_stanza);//funzione inizializza stanza
                                        Nuova_stanza->stanza_Precedente=ultima_stanza;//assegno la nuova stanza come ultima stanza
                                        Nuova_stanza->stanza_Precedente=Player->posizione;//assegno la posizione del giocatore corrente alla nuova stanza
                                        Percentuale_stanza(Nuova_stanza);//funzione percentuale stanza
                                        ultima_stanza->Pnext=Nuova_stanza;//assegno il puntatore della Nuova stanza al campo Pnext di ultima stanza
                                        ultima_stanza=Nuova_stanza;//infine assegno nuova stanza come ultima stanza
                                        Player->posizione->Nextavanti=Nuova_stanza;//Sposto il giocatore nella nuova stanza
                                        Player->posizione=Nuova_stanza;
                                        if(Nuova_stanza->stanza==botola) {//se la stanza creata è di tipo botola incrementa il contatore delle botole
                                                n_botole++;
                                        }
                                        n_stanze++;
                                        printf("Sei il primo ad entrare nella stanza.\nATTENDI...\n");
                                        sleep(1);
                                        system("@cls||clear");
                                }else{ //se entra nell'else la stanza è gia stata creata e quindi assegna il puntatore del giocatore alla stanza successiva
                                        printf("Stanza gia creata...\n");


                                        Player->posizione=Room;
                                        giocatori[turno].posizione=giocatori[turno].posizione->Nextavanti;

                                }
                                printf("----------------------------------------\n");

                                system("@cls||clear");

                                break;
                        case 2:
                                if((Player->posizione)->Nextdestra==NULL) {//controllare se muovendosi destra il puntatore è inizializzato a NULL e quindi la stanza non esiste e bisogna crearla
                                        struct Stanza *Nuova_stanza =(struct Stanza*) malloc(sizeof(struct Stanza));
                                        Inzializza_stanza(Nuova_stanza);//funzione inizializza stanza
                                        Nuova_stanza->stanza_Precedente=ultima_stanza;//assegno la nuova stanza come ultima stanza
                                        Nuova_stanza->stanza_Precedente=Player->posizione;//assegno la posizione del giocatore corrente alla nuova stanza
                                        Percentuale_stanza(Nuova_stanza);//funzione percentuale stanza
                                        ultima_stanza->Pnext=Nuova_stanza;//assegno il puntatore della Nuova stanza al campo Pnext di ultima stanza
                                        ultima_stanza=Nuova_stanza;//infine assegno nuova stanza come ultima stanza
                                        Player->posizione->Nextdestra=Nuova_stanza;//Sposto il giocatore nella nuova stanza
                                        Player->posizione=Nuova_stanza;
                                        if(Nuova_stanza->stanza==botola) {//se la stanza creata è di tipo botola incrementa il contatore delle botole
                                                n_botole++;
                                        }
                                        n_stanze++;
                                        printf("Sei il primo ad entrare nella stanza.\nATTENDI..\n");
                                        sleep(1);
                                        system("@cls||clear");
                                }else{
                                        printf("Stanza gia creata...\n");

                                        Player->posizione=Room;
                                        giocatori[turno].posizione=giocatori[turno].posizione->Nextdestra;

                                }
                                printf("----------------------------------------\n");
                                system("@cls||clear");

                                break;
                        case 3:
                                if((Player->posizione)->Nextsinistra==NULL) {//controllare se muovendosi sinistra il puntatore è inizializzato a NULL e quindi la stanza non esiste e bisogna crearla
                                        struct Stanza *Nuova_stanza =(struct Stanza*) malloc(sizeof(struct Stanza));
                                        Inzializza_stanza(Nuova_stanza);//funzione inizializza stanza
                                        Nuova_stanza->stanza_Precedente=ultima_stanza;//assegno la nuova stanza come ultima stanza
                                        Nuova_stanza->stanza_Precedente=Player->posizione;//assegno la posizione del giocatore corrente alla nuova stanza
                                        Percentuale_stanza(Nuova_stanza);//funzione percentuale stanza
                                        ultima_stanza->Pnext=Nuova_stanza;//assegno il puntatore della Nuova stanza al campo Pnext di ultima stanza
                                        ultima_stanza=Nuova_stanza;//infine assegno nuova stanza come ultima stanza
                                        Player->posizione->Nextsinistra=Nuova_stanza;//Sposto il giocatore nella nuova stanza
                                        Player->posizione=Nuova_stanza;
                                        if(Nuova_stanza->stanza==botola) {//se la stanza creata è di tipo botola incrementa il contatore delle botole
                                                n_botole++;
                                        }
                                        n_stanze++;
                                        printf("Sei il primo ad entrare nella stanza.\n");
                                        sleep(1);
                                        system("@cls||clear");
                                }else{
                                        printf("Stanza gia creata...\n");

                                        Player->posizione=Room;
                                        giocatori[turno].posizione=giocatori[turno].posizione->Nextsinistra;

                                }
                                printf("----------------------------------------\n");
                                system("@cls||clear");
                                break;
                        default:
                                printf("Il valore inserito non è quello richiesto...\n");
                                break;
                        }
                }while (dAvanza<1 || dAvanza>3);
        }else{
                system("@cls||clear");
        }

        return 1;
}

static void Esegui_quest(struct Giocatore *Player,struct Stanza *Room){//funzione esegui quest

        if(Player->posizione->stanza==vuota||Player->posizione->stanza==botola) { //controllo il tipo di stanza dove si trova il giocatore
                printf("La stanza dove sei ora è una stanza vuota....");
                printf("\n");
                sleep(1);
                system("@cls||clear");
                return;
        }
        else if(Player->posizione->stanza==quest_semplice) {//controllo se la stanza è di tipo quest semplice esegue l'if
                printf("\033[0;93mHai eseguito la quest semplice.\033[0m\n");
                quest_da_finire--; //decrementa il contatore delle quest
                Room->stanza=vuota;//dopo il decremento assegna la stanza come stanza vuota per non fa eseguire più la quest
                sleep(1);
                system("@cls||clear");
                if(quest_da_finire==0) {//controllo se le quest  da finire sono arrivate a 0 se è TRUE eseguo la condizione
                        printf("gioco terminato...\nI giocatori hanno completato tutte le quest.\n");
                        while (getchar() != '\n');
                        quit=1;
                        Termina_Gioco(); //funzione termina gioco
                }
        }
        else if(Player->posizione->stanza==quest_complicata) { // se la stanza è di tipo quest  complicata esegue la condizione
                printf("\033[0;93mHai eseguito la quest complicata.\033[0m\n");
                quest_da_finire=quest_da_finire-2; //decremento del contatore delle quest
                Room->stanza=vuota; // assegnamento di tipo stanza a stanza vuota
                sleep(1);
                system("@cls||clear");
                if(quest_da_finire==0) { //condizione se dovessero finire le quest
                        printf("Gioco terminato...\nI giocatori hanno competato tutte le quest.\n");
                        while (getchar() != '\n');
                        Termina_Gioco();
                }
        }
}



static void Uccidi_Astronauta(struct Giocatore *Player,struct Stanza *Room){ //funzione uccidi astronauta
        int contatore=1;
        int Ncrewmate=1;
        int kill=0;
        int var=0;
        for(int i=0; i<n_giocatori; i++) { //controllare tutti i giocatori

                if(giocatori[turno].posizione==giocatori[i].posizione)  { //controllare i giocatori nella stanza con l'impostore
                        var=1;
                        if(giocatori[i].giocatore==astronauta) { // controllare quanti astronauti sono nella stessa stanza dell'impostore
                                printf("Astronauti nella stanza\n %d)  %s\n",Ncrewmate,colore[giocatori[i].nome]);
                                Ncrewmate++;
                        }



                }else if(var==0) {
                        printf("Nessun astronauta nella stanza!!\n");
                        sleep(1);
                        system("@cls||clear");
                        return;
                }


        }

        do{
                printf("\033[0;93mChi vuoi uccidere :\033[0m\nScegliere tra i numeri elencati.");
                scanf("%d",&kill);
                while(getchar()!='\n');
        }while(kill<1||kill>Ncrewmate);

        for(int i=0; i<n_giocatori; i++) {//controllare tutti i giocatori e confrontarlo con quello scelto dall impostore
                if(giocatori[i].giocatore==0 &&(giocatori[i].posizione==giocatori[turno].posizione)) {
                        if(kill==contatore) {
                                giocatori[i].giocatore=assassinato;//assegnare il nuovo stato dell'astronauta
                                printf("Giocatore %s è stato assassinato!! (%s)\n",colore[giocatori[i].nome],stato[giocatori[i].giocatore]);
                                n_astronauti--;//decremento del numero di astronauti
                                sleep(1);
                                system("@cls||clear");
                                if(n_impostori>=n_astronauti) { //se il numero di astronauti è almeno uguale o inferiore al numero di impostori termina il gioco
                                        quit=1;
                                        Termina_Gioco();
                                        exit(0);
                                }
                        }
                        contatore++;
                }
        }
}
static void Defestra_giocatore(struct Giocatore *Player,struct Stanza *Room){ //funzione defenestra giocatore
        int n_presenti_same_room=0;
        int n_presenti_previous_room=0;
        int n_impostori_same_room=0;
        for(int i=0; i<n_giocatori; i++) {//conta il numero di astronauti presenti nella stanza
                if(Player->posizione==giocatori[i].posizione && giocatori[i].giocatore==astronauta) {
                        n_presenti_same_room++;
                }
                if((Player->posizione)->stanza_Precedente == giocatori[i].posizione && giocatori[i].giocatore==astronauta) {//controlla il numero di astronauti presenti nella stanza precedente
                        n_presenti_previous_room++;
                }
                if(Player->posizione==giocatori[i].posizione && giocatori[i].giocatore==impostore) {//controlla il numero di impostori nella stanza corrente
                        n_impostori_same_room++;
                }
        }
        if(n_presenti_same_room >0 || n_presenti_previous_room > 0) {
                if(calcolo_probabilita((50*n_presenti_same_room)+(20*n_presenti_previous_room))==1) {//calcola la probabilità totale e se il risultato è uguale a 1  defenestra un impostore altrimenti nessuno verrà defenestrato
                        printf("Impostore %s è stato defenestrato\n",colore[Player->nome]);
                        n_impostori=n_impostori-1;//decremento del numero di impostori
                        sleep(1);
                        system("@cls||clear");
                        Player->giocatore=defenestrato;//cambia lo stato dell impostore
                        Room->Emergency_flag=true;// assegna la chiamata di emergenza a true per non chiamare un altra volta
                        if(n_impostori==0) {//se il numero di impostori è uguale a 0 termina il gioco
                                quit=1;
                                Termina_Gioco();
                                exit(0);
                        }
                }
                else{
                        printf("Nessun giocatore è stato defenestrato!\n");
                        sleep(1);
                        system("@cls||clear");
                }

        }

}





static void Sabotaggio( struct Giocatore *Player,struct Stanza *Room){// funzione sabotaggio
        if(Player->posizione->stanza==vuota || Player->posizione->stanza==botola) {// se la stanza è di tipo vuota o botola stampa un messaggio dove non c'è niente da sabotare
                printf("La stanza non contiene nessuna quest da sabotare...");
                sleep(1);
                system("@cls||clear");
        }
        else if(Player->posizione->stanza==quest_semplice) { // se la stanza è di tipo quest semplice assegna la stanza a vuota
                printf("L'impostore ha sabotato la quest di questa stanza\nAdesso gli astronauti non potranno più eseguirla\n");
                Room->stanza=vuota;
                sleep(1);
                system("@cls||clear");
        }
        else if(Player->posizione->stanza==quest_complicata) {//se la stanza è di tipo quest complicata assegna la stanza a vuota
                printf("L'impostore ha sabotato la quest di questa stanza\nAdesso gli astronauti non potranno più eseguirla\n");
                Room->stanza=vuota;
                sleep(1);
                system("@cls||clear");
        }
}

static void Chiamata_emergenza(struct Giocatore *Player,struct Stanza *Room){// funzione chiamata di emergenza

        int s=0;
        time_t t;
        int n_presenti_same_room=0;
        int n_impostori_same_room=0;
        int r;
        srand((unsigned)time(&t));
        if(Room->Emergency_flag==true) {//se la chiamata è gia stata effettuata nella stanza non può essere richiamata
                printf("Non puoi utilizzare la chiamata di emergenza in questa stanza impostore già defenestrato\n");
                while (getchar() != '\n');
                return;
        }else{
                for(int i=0; i<n_giocatori; i++) {

                        if(Player->posizione==giocatori[i].posizione)  {// se nella stanza si trova un cadavere visualizza il messaggio seguente
                                if(giocatori[i].giocatore==assassinato) {
                                        printf("E' stato trovato un cadevere nella stanza...\n");
                                        s=1;
                                        sleep(1);
                                        printf("\n");
                                        printf("I giocatori stanno decidento chi cacciare dall'astronave Skelt...\n");
                                        sleep(1);
                                }
                                else{//se non si trova nessun cadavere nella stanza visualizza il messaggio seguente
                                        printf("Non è stato trovato nessun cadavere nella stanza...\n");
                                        sleep(1);
                                        system("@cls||clear");
                                        return;
                                }
                        }
                }
                if(s==1) {
                        for (int i = 0; i <n_giocatori; i++) {

                                if(Player->posizione==giocatori[i].posizione && giocatori[i].giocatore==astronauta) {// controlla il numero di astronauti nella stanza
                                        n_presenti_same_room++;
                                }
                                else if(Player->posizione==giocatori[i].posizione && giocatori[i].giocatore==impostore) {//controlla il numero di astronauti nella stanza
                                        n_impostori_same_room++;
                                }
                                if(n_presenti_same_room>0 || n_impostori_same_room>0) {
                                        int prob_Impostors=calcolo_probabilita(30+(20*n_presenti_same_room)-(30*n_impostori_same_room));//calcola la probilità dei impostori
                                        int prob_astronauts=calcolo_probabilita(30+(20*n_impostori_same_room)-(30*n_presenti_same_room));//calcola la probabilita dei astronauti
                                        int z=rand()%100;
                                        if(z<prob_Impostors) {//se la probabilità è maggiore della random allora defenestra un impostore
                                                do{
                                                        r=rand()%n_giocatori;
                                                }while (r==(giocatori[i].nome));
                                                if(giocatori[r].giocatore==impostore) {
                                                        printf("Giocatore %s era un Impostore.\n",colore[giocatori[r].nome]);
                                                        giocatori[r].giocatore=defenestrato;
                                                        Room->Emergency_flag=true;
                                                        n_impostori=n_impostori-1;
                                                        if(n_impostori==0) {
                                                                quit=1;
                                                                Termina_Gioco();
                                                                exit(0);
                                                        }
                                                        system("@cls||clear");
                                                }
                                        }else if(z<prob_astronauts) { //se la probabilità è maggiore della random defenestra un astronauta
                                                do{
                                                        r=rand()%n_giocatori;
                                                }while(r==(giocatori[i].nome));
                                                if(giocatori[r].giocatore==astronauta) {
                                                        printf("Giocatore %s non era un Impostore.\n",colore[giocatori[r].nome]);
                                                        giocatori[r].giocatore=defenestrato;
                                                        Room->Emergency_flag=true;
                                                        n_astronauti=n_astronauti-1;
                                                        if(n_impostori>=n_astronauti) {
                                                                quit=1;
                                                                Termina_Gioco();
                                                                exit(0);
                                                        }
                                                        system("@cls||clear");
                                                }
                                        }
                                }else{//altrimenti non defenestra nessun giocatore
                                        printf("Nessun giocatore defenestrato...\n");
                                        Room->Emergency_flag=true;
                                        sleep(1);
                                        system("@cls||clear");
                                }
                        }
                }
        }
}

static void Usa_botola(struct Giocatore *Player,struct Stanza *Room){//funzione usa botola
        static struct Stanza *botole;// creo una struct di botole

        if(giocatori[turno].posizione->stanza==3) { //se il giocatore si trova in una stanza di tipo botola entra nella condizione
                if(n_botole>=2) {

                        int r=0;
                        int count=0;
                        int c=0;
                        botole=lista_stanze;//assegno il puntatore lista stanze a botole
                        r=rand()%n_stanze;//faccio una random del numero delle stanze
                        do{



                                if(count==r && botole->stanza==3 &&(botole!=Player->posizione)) { //vedere la stanza botola non è quella dove si trova il giocatore
                                        giocatori[turno].posizione=botole;

                                        printf("L'impostore %s è entrato nella botola ed è uscito in un altra stanza\n",colore[giocatori[turno].nome]);
                                        c=1;
                                }
                                if(count>r) {//altrimenti azzera il contatore e riassegna una random del numero delle stanze finchè non trova una stanza di tipo botola
                                        count=0;
                                        r=rand()%n_stanze;
                                        botole=lista_stanze;
                                }
                                count++;
                                botole=botole->Pnext;


                        }while (c==0);
                }else if(n_stanze>1) {//altrimenti se non esiste un altra stanza di tipo botola l'impostore viene spostato in una stanza randomica
                        int r=0;
                        int count =0;
                        int c=0;
                        r=rand()%n_stanze;
                        do{
                                if(count==r &&(botole!=giocatori[turno].posizione)) {
                                        giocatori[turno].posizione=botole;

                                        printf("L'impostore %s non ha trovato stanze con la botola e si è spostato in una stanza casuale\n",colore[giocatori[turno].nome]);
                                        c=1;

                                }
                                if(count>r) {
                                        count=0;
                                        r=rand()%n_stanze;
                                        botole=lista_stanze;
                                }
                                count++;
                                botole=botole->Pnext;

                        }while (c==0);

                }else{//altrimenti se non ci sono stanze al di fuori di quella iniziale stampa il seguente messaggio
                        printf("NON CI SONO ABBASTANZA STANZE PER AVANZARE..\n");
                        sleep(1);
                        system("@cls||clear");
                }
        }else{//se la stanza dove si trova non è una stanza di tipo botola stampa il seguente messaggio
                printf("La stanza dov3e sei ora non ha una botola...\n");
                sleep(1);
                system("@cls||clear");
        }



}

static int Numero_quest(){ // funzione numero quest
        do{
                printf("\n");
                printf("QUANTE QUEST VOLETE INSERIRE NEL GIOCO PER VINCERE?\nQUANDO GLI ASTRONAUTI AVRANNO COMPLETATO LE QUEST AVRANNO AUTOMATICMANTE VINTO \nUN MINIMO DI 15 E UN MASSIMO DI 30:\n");
                scanf("%hd",&quest_da_finire);
                while(getchar()!='\n');
                printf("\n");
        }while(quest_da_finire<15 || quest_da_finire>30);
        return quest_da_finire;
}


static int calcolo_probabilita (int prob){
        return (rand()%100)<prob;
}

void Termina_Gioco(){ //funzione termina gioco
        struct Stanza *Pulisci; //creo una struct per assegnargli successivamente lista stanze per pulirla

        printf("GIOCO TERMINATO....\n");
        sleep(2);
        if(quit==1) {





                printf("******************************************\n");
                printf("|               GAME OVER                |\n");
                printf("******************************************\n");
                printf("\n");
                //condizioni per detereminare chi vince.
                if(n_impostori>=n_astronauti) {
                        printf("VINCONO GLI IMPOSTORI!!!!!!\n");
                }else if(quest_da_finire==0) {
                        printf("VINCONO GLI ASTRONAUTI!!!!!!\n");
                }else if(n_impostori==0) {
                        printf("VINCONO GLI ASTRONAUTI!!!!!!\n");
                }
        }

        printf("Spero di rivederti presto....\nATTENDI LA CHUSURA\n");
        sleep(1);

//pulire i puntatori delle stanze
        while(lista_stanze!=NULL) {
                Pulisci=lista_stanze;
                lista_stanze=lista_stanze->Pnext;
                free(Pulisci);
        }
        free(giocatori);
        printf("ALLA PROSSIMA....\n");
}
