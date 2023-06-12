#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

/*
La traccia richiede di sviluppare un algoritmo per la risoluzione di un labirinto 15x15 con delle mura sia esterne che interne 
da parte di un robot, che gestisco tramite una variabile globale di tipo struttura contenente:
int r per l'indice di riga
int c per l'indice di colonna
seguendo due movimenti, che chiamiamo rispettivamente 
ONE_MOV e BET_MOV, che vengono selezionati rispettivamente il 30% ed il 70% delle volte.

ONE_MOV ci permette di spostare il robot nelle quattro direzioni (avanti, indietro, sinistra, destra), se libere,
se ci sono più direzioni libere, la direzione viene scelta in modo randomico.

BET_MOV ci permette invece, di selezionare la direzione nella quale compiere lo spostamento, mediante il confronto tra i percorsi più lunghi, come nel
precedente movimento, se ci sono percorsi della stessa lunghezza, la direzione viene scelta casualmete.

Infine abbiamo all'interno del labirinto, 10 botole, suddivise in 5 che teletrasportano in una posizione casuale il robot, denominate RND_HOLE
e 5 che sanciscono la fine della partita denominate END_HOLE.

Il programma sarà strutturato in questo modo:

L'utente si trova in un menu' innestato in un ciclo do-while, dove, a seconda del numero inserito, vengono effettuate
diverse operazioni:
1)Vengono generati il labirinto ed il robot
2)Si avvia il movimento del robot
3)Uscita
In seguito ad un numero indefinito di spostamenti:
Se il robot finisce su un ? viene riposizionato casualmente
Se il robot finisce su una X il robot esplode
Se il robot riesce ad uscire dal labirinto vince

*/

struct robot{   //STRUTTURA CREATA PER LE CORDINATE PER LA DICHIARAZIONE DEL ROBOT
int r;
int c;
};

/*
TUTTE LE PROCEDURE HANNO COME UNICO INPUT LA MATRICE CHE GESTISCE IL LABIRINTO
*/

void gen_L(char a[][100]);               // FUNZIONE PRINCIPALE DELLA GENERAZIONE DEL LABIRINTO
void gen_wall(char a[][100]);            // GENERA I MURI INTERNI AL LABIRINTO
void gen_exit(char a[][100]);            // GENERA LE USCITE 
void gen_ost(char a[][100]);             // GENERA GLI OSTACOLI (RANDOM HOLE E BLACK HOLE)
void gen_rob(char a[][100]);             // GENERA IL ROBOT E AGGIORNA IL ROBOT DURANTE GLI SPOSTAMENTI
void end_hole(char a[][100]);            // GESTIONE BLACK HOLE
void rnd_hole(char a[][100]);            // GESTIONE RANDOM HOLE 
void win_game(char a[][100]);		   	 // GESTIONE VITTORIA


void cho_mov(char a[][100]);             // SCEGLIE IL MOVIMENTO DA EFFETTUARE
void bet_mov(char a[][100]);             // MOVIMENTO SEGUENDO IL PERCOSO PIU' LUNGO
void one_mov(char a[][100]);             // MOVIMENTO CASUALE IN UNA DELLE 4 DIREZIONI CONSENTITE 


void partita (char a[][100]);            // FUNZIONE PER AVVIARE LA PARTITA


struct robot B;                   	     //VARIABILE ROBOT
int gameover=0;                   	     //CONTROLLO GAMEOVER
int win=0;                        		 //CONTROLLO WIN



int main(){
srand((unsigned) time(0));               //Unico richiamo alla funzione random utilizzata in tutte le funzioni per la generazione degli elementi
char L[100][100];                        //Matrice 100x100 per la generazione del labirinto, ho preferito lavorare con una 100x100 per permettere al robot di tendere verso l'uscita utilizzando il bet_mov 
partita(L);
return 0;
}

/* Procedura che gestisce gli input dell'utente tramite uno switch e controlla ad ogni esecuzione di un movimento se la partita è stata vinta o persa
   utilizzando le due variabili globali win e gameover, come si nota nel codice, ho utlizzato anche il comando system("cls") per evitare di stampare a schermo
   la mappa di gioco per ogni movimento eseguito, e per simulare un movimento più fluido
 */
void partita (char a[][100]){
int uscita=0;								 //USCITA CON PRESSIONE TASTO 
char choice;
printf("LEGGENDA \nROBOT:%c\nBOTOLA:%c\nBUCO NERO:%c\nMURO:%c\n",'R',63,88,'#');
while(gameover == 0 && win == 0 && uscita == 0){                          //Ciclo while per la gestione delle varie variabili che potrebbero far finire la partita
        printf("\nCOMANDI:\n1)Creazione mappa\n2)Movimento\n3)Uscita\nINPUT:");
        choice=getch();
switch (choice) {
  case '1' :                                            //INPUT 1: Generazione labirinto, da la possibilità anche di riavviare la partita
            gen_L(a);
            stampa_L(a);
            break;
  case '2' :                                            //INPUT 2: Permette il movimento del robot
            system("cls");
			cho_mov(a);
            stampa_L(a);
            break;
  case '3':                                             //INPUT 3: Uscita prematura dal gioco
  			uscita=1;
            break;
            
  default : printf("!!!!INSERIRE UN NUMERO DA 1 A 3!!!!");
			   }
							  }
if(gameover == 1){
					system("cls");
					printf("BB-8 E' ESPLOSO ");
				 }
if(win == 1){
					system("cls");
					printf("BB-8 E' USCITO DAL LABIRINTO, EVVAI'");
				 }
if(uscita == 1){
					printf("USCITA DAL GIOCO");
				 }
}

/*
	Procedura principale per la generazione del labirinto,
	si occupa di generare il labirinto privo di ostacoli, attraverso dei cicli for ed un if
	per generare i muri di confine del labirinto
	e richiama le funzioni per la creazione degli ostacoli, 
	modificando i valori massimi contenuti nell'IF, si può cambiare la dimensione del labirinto
*/
void gen_L(char a[][100]){
int i,j;
for (i=0;i<=16;i++){
                    for (j=0;j<=16;j++){
                                        if(((i==0)||(i==15))||((j==0)||(j==15))){
                                                             a[i][j]='#';
                                                           						}else{
                                                                                       a[i][j]=' ';
                                                                                     }
                                     }
                  }
gen_wall(a);
gen_exit(a);
gen_ost(a);
gen_rob(a);
                            }
                            
/*
Procedura per la stampa del labirinto
*/
void stampa_L(char a[100][100]){
int i,j;
for (i=0;i<16;i++){
    				printf("\n");
    				for (j=0;j<16;j++){
                        	  			printf(" %c ", a[i][j]);
                      				  }
				  }
}

/*
Procedura per la generazione casuale dei muri presenti internamente al labirinto, viene richiamata la funzione rand
per determinare le cordinate di riga e colonna dalle quali far partite i muri.
Ho utilizzato una variabile denominata k, da sommare alla variabile indice di riga o colonna tramite alcuni cicli for in base all'orientamento del muro
*/
              
void gen_wall(char a[][100]){
int i,j,k;
//MURO 1 DI 5 CASELLE VERTICALI
i=1+rand()%14;
j=1+rand()%14;
for(k=0;k<5;k++){
    				a[i][j+k]='#';
				}
				
//MURO 2 DI 8 CASELLE VERTICALI
i=1+rand()%14;
j=1+rand()%14;
for(k=0;k<8;k++){
    			  a[i+k][j]='#';
				 }
				 
//MURO 3 DI 8 CASELLE ORIZZONTALI
i=1+rand()%14;
j=1+rand()%14;
for(k=0;k<8;k++){
    				a[i][j+k]='#';
				  }
				  
//MURO 4 DI 3 CASELLE ORIZZONTALI
i=1+rand()%14;
j=1+rand()%14;
for(k=0;k<3;k++){
    				a[i+k][j]='#';
				   }

}
/*
Procedura per la generazione dell'uscita del labirinto, prima mediante la funzione rand, sceglie la parete sulla quale posizionare l'uscita,
si può notare che nella funzione l'indice massimo che si può generare è 12, per eliminare la possibilità di avere uscite inutilizzabili negli angoli
*/                      
void gen_exit(char a[][100]){
    int i,j,k;
  i=1+rand()%4;
  switch (i) {
  case 1 :                      //MURO SUPERIORE
            j=1+rand()%12;
            for(k=0;k<3;k++){
            				 a[0][j+k]=' ';
        		 			}
			break;
  case 2 :						//MURO SINISTRO
            j=1+rand()%12;
            for(k=0;k<3;k++){
            				 a[j+k][0]=' ';
        		 			}
            break;
  case 3:   					//MURO INFERIORE
  		    j=1+rand()%12;
            for(k=0;k<3;k++){
            				 a[15][j+k]=' ';
        		 			}
            break;
            
  case 4:						//MURO DESTRO
  	        j=1+rand()%12;
            for(k=0;k<3;k++){
            				 a[j+k][15]=' ';
        		 			}
			break;
            
  default : printf("ERRORE");
			}
}

/*
Procedura per la generazione delle botole RND_HOLE e END_HOLE, tramite la funzione rand genero le diverse cordinate per le diverse botole, 
che potendo essere generate solo nelle caselle "vuote" non consente alle botole di essere generate o nelle stesse posizioni, oppure al posto delle mura
*/
void gen_ost(char a[][100]){
int i=0,j=0,cont=0;
while(cont<5){                     //GENERAZIONE BOTOLE RANDOM

                i=1+rand()%15;
                j=1+rand()%15;
                if(a[i][j]==' '){
								 cont++;
                                 a[i][j]='?';
                                }
              }
i=0;
j=0;
cont=0;
while(cont<5){                   //GENERAZIONE BUCHI NERI
                i=1+rand()%15;
                j=1+rand()%15;
                if(a[i][j]==' '){
                                 cont++;
                                 a[i][j]='X';
                                }
              }
}

/*
Procedura per la generazione iniziale del robot all'interno del labirinto, genera tramite la funzione rand le cordinate del robot
*/
void gen_rob(char a[][100]){
	B.r=1+rand()%14;
    B.c=1+rand()%14;
    a[B.r][B.c]='R';
}

/*
Procedura che stampa il robot all'interno del labitinto andando a sostituire al carattere contenuto nella casella, il carattere rappresentativo del robot
*/
void stampa_rob(char a[][100]){
    a[B.r][B.c]='R';
}

/*
Procedura che ha il compito, di scegliere quale movimento effettuare e richiamarne la rispettiva funzione, tramite un random da 1 a 10 e due if
genero le percentuali di esecuzioni delle procedure
*/
void cho_mov(char a[][100]){
int i;
i=1+rand()%10;
if(i<=7){
         printf("BET_MOV");
         bet_mov(a);
        }else{
              printf("ONE_MOV");
              one_mov(a);
             }
                            }
                                        

/*
Procedura relativa al BET_MOV, attraverso dei cicli while, viene contato il percorso di ogni direzione,
che viene confrontato con una variabile denominata max_bm
che sancisce la direzione verso la quale il percorso libero è maggiore e quindi dove effettuare lo spostamento.
Per gestire il problema di due percorsi uguali, ho creato un vettore di tipo robot, quindi contenente le cordinate
della posizione nella quale potrebbe spostarsi il robot, nel quale inserisco solo le direzioni superiori alla dimensione massima
dato che la prima posizione che si confronta, in questo caso l'UP, finirà sempre nel vettore anche se pari a 0, ho dovuto aggiungere
un altro confronto per aggirare il problema.
Nell'eventualità ci siano più percorsi uguali, una funzione rand ne seleziona uno dal vettore

*/
void bet_mov(char a[][100]){
struct robot cross[4]; //POS 0= UP POS 1= RIGHT POS 2=DOWN POS 3= LEFT
int r=B.r,c=B.c,i=1,max,max_bm=0,bm=0,d=0;


while(a[r-i][c] != '#'){ 			//UP
						bm++;
						i++;
					   }

if(bm>max_bm){
			  max_bm=bm;
			  d=0;
			  cross[d].r=r-1;
			  cross[d].c=c;
			  d++;
			}else{
				  if(bm==max_bm){
				  cross[d].r=r-1;
				  cross[d].c=c;
				  d++;
			  					}
				 }
				 
bm=0;
i=1;

while(a[r][c+i] != '#'){ 			//RIGHT
					    bm++;
						i++;
}
if(bm>max_bm){
			  	max_bm=bm;
				d=0;
				cross[d].r=r;
				cross[d].c=c+1;
				d++;
}else{
		if(bm==max_bm){
						cross[d].r=r;
						cross[d].c=c+1;
						d++;
					  }
	 }
	 
bm=0;
i=1;

while(a[r+i][c] != '#'){ 			//DOWN
						 bm++;
						 i++;
					   }
if(bm>max_bm){
				max_bm=bm;
				d=0;
				cross[d].r=r+1;
				cross[d].c=c;
				d++;
			 }else{
					if(bm==max_bm){
									cross[d].r=r+1;
									cross[d].c=c;
									d++;
								  }
				  }
				  
bm=0;
i=1;

while(a[r][c-i] != '#'){ 			//LEFT
						 bm++;
						 i++;
					   }
if(bm>max_bm){
				max_bm=bm;
				d=0;
				cross[d].r=r;
				cross[d].c=c-1;
				d++;
			 }else{
					if(bm==max_bm){
									cross[d].r=r;
									cross[d].c=c-1;
									d++;
								  }
				  }
i=rand()%d;
a[B.r][B.c]='o';
B=cross[i];
rnd_hole(a);
end_hole(a);
win_game(a);
stampa_rob(a);
}
/*
Procedura per la gestione del movimento casuale in una delle 4 direzioni libere intorno al robot, anche qui ho creato un vettore nel caso ci sia più
di una direzione libera, che tramite una funzione rand andrò a scegliere.
*/

void one_mov(char a[][100]){
int i,d=0;
int r=B.r,c=B.c;
struct robot cross[4];
if(a[r-1][c] != '#') {	//UP

        				cross[d].r=r-1;
        				cross[d].c=c;
        				d++;

                       } 
if(a[r][c+1] != '#') {	//RIGHT

        				cross[d].r=r;
        				cross[d].c=c+1;
        				d++;
					 } 
if(a[r+1][c] != '#') {  //DOWN

        				cross[d].r=r+1;
        				cross[d].c=c;
        				d++;
					 }
if(a[r][c-1] != '#') {  //LEFT

        				cross[d].r=r;
        				cross[d].c=c-1;
        				d++;
					 } 
i=rand()%d;
a[B.r][B.c]='o';
B=cross[i];
rnd_hole(a);
end_hole(a);
win_game(a);
stampa_rob(a);
}


/*
Procedura che controlla se il valore della posizione attuale del robot è pari ad X, se vero mette ad 1 il valore della variabile globale gameover
*/

void end_hole(char a[][100]){
if(a[B.r][B.c] == 'X'){
					   gameover=1;
			   		  }
}

/*
Procedura che controlla se il valore della posizione attuale del robot è pari ad ?, se vero genera casualmente la nuova posizione del robot e la stampa a video
*/
void rnd_hole(char a[][100]){
if(a[B.r][B.c] == '?'){
						B.r=1+rand()%14;
						B.c=1+rand()%14;
						printf("NUOVA POSIZIONE R: %d   C: %d",B.r,B.c);
					  }
}

/*
Procedura che controlla se l'indice di posizione del robot esce dal range del labirinto, quindi potendosi muovere solo negli spazi non occupati
dal carattere #, ciò sancisce l'uscita dal labirinto, quindi rendo la variabile globale win a 1
*/

void win_game(char a[][100]){
	int r=B.r,c=B.c;
	if(r>15 || c>15 || r<0 || c<0){
									win=1;
					  			  }
}

