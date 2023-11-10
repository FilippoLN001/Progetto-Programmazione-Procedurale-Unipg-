#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>




enum Stato_giocatore {astronauta,impostore,assassinato,defenestrato};
enum Nome_giocatore {rosso,blu,giallo,verde,arancione,rosa,bianco,nero,viola,marrone};
enum Tipo_stanza {vuota,quest_semplice,quest_complicata,botola};

struct Giocatore {
        struct Stanza *posizione;
        enum Stato_giocatore giocatore;
        enum Nome_giocatore nome;
};

struct Stanza {
        struct Stanza *Nextavanti;
        struct Stanza *Nextdestra;
        struct Stanza *Nextsinistra;
        struct Stanza *Pnext;
        struct Stanza (*stanza_Precedente) ;
        enum Tipo_stanza stanza;
        bool Emergency_flag;
};


void Imposta_gioco();
void gioca();
void Termina_Gioco();
int main();
