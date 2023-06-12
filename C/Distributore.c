#include <stdio.h>
#include <stdlib.h>

/*La traccia richiede di simulare un distributore di carburante.
Si hanno 3 tipi di carburante identificati da un nome, da un codice identificativo e dal numero e il prezzo
di litri presenti nella scorta.

Bisogna permettere all'utente di 
1 Inserire 5,10, 20, 50 euro
2 Scegliere il tipo carburante
3 Controllare se � possibile soddisfare la richiesta
4 Nel caso sia possibile soddisfare la richiesta rifornire di carburante(aggiornando la scorta)
5 Periodicamente controllare i prodotti nella scorta (minore di 10 litri)
6 Dato un tipo di carburante visualizzare il giorno in cui si � avuta la massima vendita. 

Creo la struttura del mio tipo che chiamo Carburante composta da 4 variabili
una string col nome del carburante, un char con un identificativo del carburante 
(per convenienza:1 per la benzina, 2 per il metano, 3 per il gpl),
e due double, una per il numero di litri nella scorta ed una per il prezzo del carburante al litro

Il programma funziona in questo modo:
Si parte dal Luned�
Creo tre tipi di carburante
Le scorte le pongo inizialmente a 200.
Ciascun tipo di carburante ha un vettore di 7 elementi, inizialmente settati a 0, questo mi serve� per calcolare quanti euro
di carburante sono stati venduti in un dato giorno della settimana.
Sfrutto l'indice per regolarmi col giorno della settimana
Un vettore di stringhe viene utilizzato per stampare a video, mediante l'indice del giorno, il giorno in cui ci troviamo;
L'utente si trova in un menu' innestato in un ciclo do-while, dove, a seconda del numero inserito, vengono effettuate
diverse operazioni:
1) Scegli il tipo di carburante con cui vuole rifornirsi,
2) Inserisci i soldi nel distributore,
3) Rifornimento del veicolo, laddove la scorta lo consente, altrimenti il distributore dà indietro i soldi
all'utente.
4) Visualizza in quale giorno della settimana si � venduto pi� carburante.
Con qualsiasi altro numero do-while resta dentro fino a quando la variabile menu � compresa tra 1 e 4
Ogni 5 erogazioni di carburante andate a buon fine viene effettuato il controllo periodico sulle scorte di carburante
ed inoltre viene cambiato il giorno della settimana, che avanza di 1.*/



struct carburante{
    char nome[20];
    char id;
    double num;
    double prezzo;
};
typedef struct carburante Carburante;    //assegno al tipo Carburante la struttura da me creata
typedef enum{lunedi,martedi,mercoledi,giovedi,venerdi,sabato,domenica} Giorno;   //creo un tipo enumerato per i giorni della settimana

Giorno set_giorno(Giorno giorno);/*function che prende in ingresso un tipo Giorno e ritorna un tipo Giorno che utilizzo
									per cambiare il giorno della settimana*/
void rifornimento(Carburante *carburante, int* conta_carburante, double* soldi);  /*procedura che prende in ingresso la struttura
																					Carburante mediante puntatore, un puntatore ad un 
																					intero che conta il carburante in quel dato giorno della settimana ed
																					un puntatore alla variabile double per i soldi da rifornire col distributore*/
void controllo_scorta(Carburante *carburante);/*procedura che prende in input il puntatore alla struttura carburante
e controlla se il numero dei litri è inferiore a 10, se si, rifornisce la scorta di carburante.*/
void in_soldi(double *soldi);/*procedura che inserisce i soldi nel distributore, accetta 5,10,20 o 50€
Prende in input il puntatore alla variabile soldi*/
int indice_max(int giorni[]);/*function che ritorna l'indice del giorno dove si e' venduto il massimo per lo specifico carburante
Prende input un vettore con all'interno i soldi di carburante venduti durante la settimana*/



int main(){
    Carburante benzina ={"Benzina",'1',200,1.55};//generazione della variabile benzina col tipo Carburante
    Carburante metano ={"Metano",'2',200,1.00};//generazione della variabile metano col tipo Carburante
    Carburante gpl ={"GPL",'3',200,0.68};//generazione della variabile gpl col tipo Carburante
    int giorni_b[7] = {0,0,0,0,0,0,0};
    int giorni_m[7] = {0,0,0,0,0,0,0};
    int giorni_g[7] = {0,0,0,0,0,0,0};
    double soldi = 0; //variabile per il conteggio dei soldi nel distributore
    char* giorni[] = {"lun","mar","mer","gio","ven","sab","dom"};
    Giorno giorno = 0;//variabile di tipo Giorno per gestire l'indice del giorno in cui ci troviamo.
    int massimo; //variabile utilizzata per trovare il giorno della settimana in cui si e' venduto più carburante
    int menu;//variabile utilizzata per l'input dell'utente del menù
    int controllo_periodico = 0;//contatore del controllo periodico incrementato di 1 ogni volta che viene erogato carburante
    int tipo_carburante = 0;//variabile utilizzata per gestire il tipo di carburante, l'id corrisponde al tipo di carburante
    printf("DISTRIBUTORE CORSO DI INFORMATICA\n");
    printf("Abbiamo tre tipi di carburante diverso.\nBenzina, Metano e GPL.\n");
    printf("La benzina costa %-.2lf al litro\nIl metano costa %-.2lf al litro\nIL GPL costa %-.2lf al litro\n",
           benzina.prezzo,metano.prezzo,gpl.prezzo);
    printf("\n");
    do{
            printf("1)scegli il tipo di carburante\n2)Per inserire i soldi\n3)Per rifornire il tuo veicolo\n4)Visualizza in quale giorno della settimana si e' avuta la massima vendita di un carburante\nQualsiasi altro numero per uscire dal distributore di carburante\n\nOgni cinque rifornimenti viene effettuato un controllo sulle scorte e\ncambia il giorno della settimana\nOggi e' %s\n",giorni[giorno]);
            scanf("%d",&menu);//richiesta all'utente di quale operazione effettuare

            /*Se men�=1 allora viene richiesto all'utente quale tipo di carburante vuole settare
            1 per la benzina, 2 per il metano e 3 per il gpl (in pratica gli id dei rispettivi carburanti)
            La richiesta viene ripetuta se l'utente non inserisce un numero compreso tra 1 e 3*/
            
			if(menu == 1){
                    do{
                        printf("1)Per la benzina\n2)Per il metano\n3)Per il GPL\n");
                        scanf("%d",&tipo_carburante);
                        if((tipo_carburante < 1)|| (tipo_carburante > 3))
                           printf("Il numero inserito non e' associato ad un tipo di carburante, si prega di riprovare\n");
                    }while((tipo_carburante < 1)|| (tipo_carburante > 3));
                    if(tipo_carburante == 1)
                        printf("Hai selezionato la benzina\n");
                    if(tipo_carburante == 2)
                        printf("Hai selezionato il metano\n");
                    if(tipo_carburante == 3)
                        printf("Hai selezionato il GPL\n");
            }
            if(menu == 2){
                in_soldi(&soldi);//chiamo la procedura per l'inserimento dei soldi passando l'indirizzo di soldi
            }
            if(menu == 3){
                if(tipo_carburante == 1){
                    rifornimento(&benzina,&giorni_b[giorno],&soldi);/*Rifornisco benzina se tipo_carburante è 1
                    Passo l'indirizzo della struttura Carburante, l'indirizzo della variabile giorni_benzina con l'indice
                    giorno (che indica il giorno della settimana in cui ci troviamo) e l'indirizzo della variabile soldi*/
                    printf("\n");
                    controllo_periodico++;//incremento di 1 controllo periodico
                }
                if(tipo_carburante == 2){
                    rifornimento(&metano,&giorni_m[giorno],&soldi);/*Rifornisco metano se tipo_carburante è 2
                    Passo l'indirizzo della struttura Carburante, l'indirizzo della variabile giorni_benzina con l'indice
                    giorno (che indica il giorno della settimana in cui ci troviamo) e l'indirizzo della variabile soldi*/
                    printf("\n");
                    controllo_periodico++;//incremento di 1 controllo periodico
                }
                if(tipo_carburante == 3){
                    rifornimento(&gpl,&giorni_g[giorno],&soldi);/*Rifornisco gpl se tipo_carburante è 3
                    Passo l'indirizzo della struttura Carburante, l'indirizzo della variabile giorni_benzina con l'indice
                    giorno (che indica il giorno della settimana in cui ci troviamo) e l'indirizzo della variabile soldi*/
                    printf("\n");
                    controllo_periodico++;//incremento di 1 controllo periodico
                }
                if(tipo_carburante == 0){
                    printf("Non hai inserito il tipo di carburante con cui vuoi rifornirti, riprova dopo averlo impostato\n");
                    /*Se l'utente non ha ancora inserito il tipo di carburante, prima di rifornirsi, allora stampo un errore*/
                }
            }
            if(menu == 4){
                /*In base all'id del tipo del carburante richiamo la function indice_max assegnando il ritorno ad
                indice_massimo.
                Indice_max non è altro che una function che ritorna la posizione del valore più alto tra gli elementi
                del vettore giorni_benzina
                Anche in questo caso gioco con l'indice del vettore, che coincide esattamente con l'indice dei giorni settimanali
                Servendomi dell'indice stampo il giorno in cui si e' venduto di più ed il valore in euro del carburante erogato*/
                if(tipo_carburante == 1){
                    massimo = indice_max(giorni_b);
                    printf("Nel giorno di %s, si e' avuta la vendita piu' alta di %s con %d euro spesi\n",
                           giorni[massimo], benzina.nome,giorni_b[massimo]);
                    printf("\n");
                }
                if(tipo_carburante == 2){
                    massimo = indice_max(giorni_m);
                    printf("Nel giorno di %s, si e' avuta la vendita piu' alta di %s con %d euro spesi\n",
                           giorni[massimo], metano.nome,giorni_m[massimo]);
                    printf("\n");
                }
                if(tipo_carburante == 3){
                    massimo = indice_max(giorni_g);
                    printf("Nel giorno di %s, si e' avuta la vendita piu' alta di %s con %d euro spesi\n",
                           giorni[massimo], gpl.nome,giorni_g[massimo]);
                    printf("\n");
                }
                if(tipo_carburante == 0){
                    printf("Non hai inserito il tipo di carburante, riprova dopo averlo impostato\n");
                    printf("\n");
                    /*Se l'utente non ha ancora inserito il tipo di carburante, prima di richiedere
                      in quale giorno si è venduto più carburante, allora stampo un errore*/
                }
            }

            /*Se controllo_periodico � 5 allora richiamo la procedura che controlla le scorte di carburante
            passando l'indirizzo della struttura di tipo Carburante
            Inoltre richiamo la function set_giorno passando il giorno, assegnando al giorno il nuovo valore
            Infine setto a 0 controllo_periodico per poter eseguire altre 5 erogazioni prima del nuovo controllo*/
            
            
            if((controllo_periodico) == 5){
                controllo_scorta(&benzina);
                controllo_scorta(&metano);
                controllo_scorta(&gpl);
                giorno = set_giorno(giorno);
                controllo_periodico = 0;
            }
    }while((menu >= 1) && (menu <= 4));
    printf("Grazie per aver utilizzato il nostro distributore automatico!\n");
    /*Esco dal programma se l'utente inserisce un numero non compreso tra 1 e 4*/
    return 0;
}

/*set_giorno prende in input una variabile di tipo giorno e ritorna un tipo giorno
Creo un vettore di stringhe per i nomi dei giorni
Incremento di 1 giorno
Poi assegno a giorno quello che ottengo dal resto di giorno/7
Questo lo faccio per impedire che giorno superi l'indice massimo che in questo caso � 6, altrimenti mi troverei
fuori il vettore.
Infine stampo il nuovo giorno della settimana a video e ritorno il nuovo valore di giorno*/
Giorno set_giorno(Giorno giorno){
    							 char* giorni[] = {"lun","mar","mer","giov","ven","sab","dom"};
    							 giorno++;
    							 giorno = (giorno%7);
    							 printf("E' cambiato il giorno della settimana, siamo a: %s\n", giorni[giorno]);
    							 printf("\n");
    							 return giorno;
}

/*La procedura rifornimento che prende in input ha i puntatori per carburante, a conta_carburante ed a soldi
Controlla innanzitutto che ci siano soldi nel distributore.
Se il puntatore di soldi � 0, allora stampa errore e ritorna al men�, altrimenti:
Rifornisce il veicolo se i soldi moltiplicati il prezzo per litro sono minori del numero dei litri di quel carburante
Se entra nell'if, allora viene soddisfatta la richiesta e quindi vengono aggiornati i litri della scorta
Viene incrementato il puntatore a conta_carburante ed azzera i soldi.
Altrimenti, nel caso la scorta fosse minore della richiesta, stampo a video che non � possibile soddisfare l'utente ed
il distributore ritorna indietro i soldi.
*/
void rifornimento(Carburante *carburante, int* conta_carburante, double* soldi){
    if(*soldi == 0){
        printf("Devi inserire prima i soldi!\n");
    }else{
        printf("Hai scelto di rifornire di %s il tuo veicolo\n",carburante ->nome);
        if((*soldi * carburante->prezzo)< carburante->num){
            printf("\n");
            printf("E' possibile soddisfare la richiesta, procedo ad erogare %s\n", carburante->nome);
            carburante->num = (carburante->num - (*soldi * carburante->prezzo));
            printf("\n");
            *conta_carburante = *conta_carburante+ (int)*soldi;
            *soldi = 0;
        }else{
            printf("%s non sufficiente a soddisfare la richiesta, restituisco i %-.lf euro\n",
                    carburante->nome,*soldi);
            printf("\n");
            *soldi = 0;
        }
    }
}

/*La procedura controllo_scorta che prende in input il puntatore al tipo Carburante controlla quanti litri restano nella scorta
Se sono inferiori a 10 litri, allora il distributore viene rifornito e portato a 200 litri, per convenienza.
Altrimenti stampa semplicemente che non ci sar� un rifornimento, dato che la scorta � maggiore o uguale a 10*/

void controllo_scorta(Carburante *carburante){
    printf("Controllo periodico della scorta di %s restante\n",carburante->nome);
    printf("Restano %-.lf litri di %s\n",carburante->num,carburante->nome);
    if(carburante->num < 10){
        printf("Scorta inferiore a 10 litri, procedo a rifornire il distributore\n");
        printf("\n");
        carburante->num = 200;
        printf("Operazione effettuata!");
        printf("I litri nel distributore di %s sono adesso: %-.lf\n",carburante->nome,carburante->num);
    }else{
        printf("Scorta di %s superiore ai 10 litri, non verra' rifornita\n",carburante->nome);
    }
}

/*La procedura inserimento_soldi prende in input il puntatore a soldi
Chiede all'utente di inserire 5,10,20 o 50 euro.
Quindi con un do-while chiedo all'utente di inserire 5,10, 20 o 50, fin quando non inserisce uno di questi 4 valori
Dopo incremento il puntatore a soldi, con i soldi che ha inserito l'utente.
Stampo poi a video quanti soldi ci sono nel distributore, siccome prevedo la possibilit� di accumulare pi� banconote*/

void in_soldi(double* soldi){
    double soldi_inseriti;
    printf("Hai scelto di inserire soldi nel distributore\n");
    printf("\n");
    printf("Inserisci 5,10,20 o 50 euro\n");
    do{
        scanf("%lf",&soldi_inseriti);
    if((soldi_inseriti != 5)&& (soldi_inseriti != 10) && (soldi_inseriti != 20) && (soldi_inseriti != 50))
        printf("Non puoi inserire una banconota da %-.lf euro\n",soldi_inseriti);
        printf("\n");
    }while((soldi_inseriti != 5)&& (soldi_inseriti != 10) && (soldi_inseriti != 20) && (soldi_inseriti != 50));
    printf("Hai inserito %-.lf euro nel distributore\n",soldi_inseriti);
    printf("\n");
    *soldi = *soldi + soldi_inseriti;
    printf("Nel distributore ci sono %-.lf euro\n",*soldi);
}

/*Con indice_max che prende in input un vettore di interi, cerco nel vettore l'indice dell'elemento col valore più alto
Inizialmente settato al primo elemento sia il valore che l'indice.
Faccio scorrere un ciclo for che parte da 1 fino all'indice-1, ogni volta che il la variabile massimo � minore
dell'elemento del vettore, procedo ad assegnare a massimo il nuovo valore, ed ad indice massimo il nuovo indice.
Infine ritorno l'intero indice_massimo*/

int indice_max(int giorni[]){
    int massimo = giorni[0];
    int indice_massimo = 0;
    int i;
    for(i=1; i<7;i++){
        if (massimo < giorni [i]){
            massimo = giorni [i];
            indice_massimo = i;
        }
    }
    return indice_massimo;
}
