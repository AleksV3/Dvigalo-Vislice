#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Funkcija za nalaganje seznama nadstropij na datoteke
void Load_Nadstropja();

// Funkcija za izpis seznama nadstropij
void Print_Nadstropja();

// Funkcija za izpis trenutnega nadstropja uporabnika
void Trenutno_nadstropje();

// Funkcija za branje vnosa uporabnika
void User_Input();

// Glavna funkcija za delovanje programa
void Menu();

// Funkcija za preverjanje veljavnosti vnosa uporabnika
int Preveri_Input(char c[10]);

int main(){
   Load_Nadstropja();
   Menu();
}

void Menu(){
   Trenutno_nadstropje();
   Print_Nadstropja();
   User_Input();
   Menu();
}

// Funkcija za nalaganje seznama nadstropij na file
void Load_Nadstropja(){

//Odpri file za pisanje
FILE* file = fopen("Nadstropje.txt","w");

//Preveri ali lahko odpres file za pisanje
if(file == NULL){
   printf("Napaka file se ne more odpreti za pisanje!!\n");
   return;
}

//Inicilarizirali smo nadstropja
char *Nadstropje[7] = {"5","4","3","2","1","P","E"};

//Gremo skozi vse elemente v polju nadstropje in jih napisemo v file
for (int i = 0; i < 7; i++){
   int n = strlen(Nadstropje[i]);
   fwrite(Nadstropje[i],n,1,file);
   fwrite("\n",1,1,file);
}

//Zapremo file
fclose(file);
}

// Funkcija za izpis trenutnega nadstropja uporabnika
void Trenutno_nadstropje(){
 
   // Odpremo file
   FILE* fileR = fopen("Trenutno_Nadstropje.txt","a+");

   // Preverimo ali lahko odpremo file za branje
   if(fileR == NULL){
      printf("Napaka file se ne more odpreti za branje!!\n");
      return;
   }

   // Inicializiramo character
   char c[128];

   // Inicializiramo int size
   int size = 128;

   // Preberemo iz fila in ga napisemo v charecter c
   fgets(c,size,fileR);

   // Premaknemo se na konec file
   fseek (fileR, 0, SEEK_END);

   // Pregledamo ali je file prazen
   size = ftell(fileR);

      // Če je prazen sprintamo da smo v P
      if(size == 0){
         printf("\nNahajaste se v P.\n");

      // Če pa ni prazen napišemo, da se nahajamo vi nadstropju, katerga smo dobili iz file 
      }else{
         printf("\nNahajaste se v %s\n",c);
      }
}

// Funkcija izpise nadstropja, katere ima uporabnikna izbiro
void Print_Nadstropja(){

   // Opremo file za branje
   FILE* fileR1 = fopen("Nadstropje.txt","r");

   // Preverimo ali lahko odpremo file
   if(fileR1 == NULL){
      printf("Napaka file se ne more odpreti za branje!!\n");
      return;
   }
   // Opremo file za branje
   FILE* fileR2 = fopen("Trenutno_Nadstropje.txt","r");

   // Preverimo ali lahko odpremo file
   if(fileR2 == NULL){
      printf("Napaka file se ne more odpreti za branje!!\n");
      exit(0);
   }

   // Inicializiramo file
   char c[128];   
   // Inicializiramo file
   char n[128];
   // Inicializiramo int size
   int size = 10;

   // Premaknemo se na konec file
   fseek (fileR2, 0, SEEK_END);
   // Pregledamo ali je file prazen
   size = ftell(fileR2);
   
   // Izpisemo navodila
   printf("Nadstropja na voljo so (P-prikličje, E-exit) : \n");
      
      // Če je file prazen inicializiramo int size
      // Izpisemo vse char c iz file kateri niso enaki P
      if(size == 0){ 
         char P[10] = "P";
         for (int i = 0; i < 7; i++){
         int size = 4;
         fgets(c,128,fileR1);
         if(*c != *P){
            printf("%s",c);
         }
      }

      // Če file ni prazen
      // Inicializiramo char P
      // Dobimo char P iz fila "Tranutno_Nadstropje.txt
      // Izpisemo vse char c iz file kateri niso enaki char P
      }else{
      char P[128];
      fgets(P,128,fileR2);
         for (int i = 0; i < 7; i++){
            int size = 128;
            fgets(c,size,fileR1);
            if(*c != *P){
               printf("%s",c);
               }
            }
         }
      //Izpisemo prazno vrstico
      printf("\n");

   // Zapremo file
   fclose(fileR1);
}

// Funkcija za branje vnosa uporabnika
void User_Input(){

   // Inicializiramo char c,s,E
   char c[128];
   char s[128];
   char E[128] = "E";
   
   // Izpisemo navodilo
   printf("Izberite nadstropje: \n\n");

   // Pridobimo vnos od uporabnika in ga shranimo v char c
   scanf("%s",c);
   
   // Funkcija Preveri_Input vrne int 
   // Preverimo ali vren int, ki je vecji od 0
   if(Preveri_Input(c) > 0){

      // Če je char c enak char E končamo delovanje programa
      if(*c == *E){
         exit(0);

      // Če niso char c in char E enaki
      }else{
         // Opremo file za branje
         FILE* fileR = fopen("Trenutno_Nadstropje.txt","w+");
         
         // Prevreimo ali lahko odpremo file za branje 
         if(fileR == NULL){ 
            printf("Napaka file se ne more odpreti za branje!\n");
            exit(0);
         }
         // Preberemo iz fila in shranimo v char s
         fgets(s,128,fileR);
            // Preverimo, da char c ni enak char s
            if(*c != *s){
               // Napisis char c v file "Trenurno_Nadstropje.txt"
               int n = strlen(c);
               fwrite(c,n,n,fileR); 
            // če je char c enak char s
            }else{
                        
               // Izpisemo, da se ze nahajaste v tem nadstropju
               printf("\nSe že nahajaste na izbranem nadstropji!\n");
            }
         // Zapremo file
         fclose(fileR);
         }
   // Če Preveri_Input vrne 0
   }else{

      // Izpisi Napacen vnos podatkov
      printf("\n");
      printf("Napacen vnos uporabite podana nadstropja!\n");
      printf("\n");
   }
}

// Funkcija za preverjanje veljavnosti vnosa uporabnika
int Preveri_Input(char c[128]){

   // Preverimo file za branje
   FILE* file = fopen("Nadstropje.txt","r");
   
   //Preverimo ali lahko odpremo file za branje
   if(file == NULL){
      printf("Napaka file se ne more odpreti za branje!!\n");
      exit(0);
   }
   // Inicializiramo char nadstropje in int sum
   char nadstropja[128];
   int sum = 0;

   // 10-krat doimo char nadstropje iz fila Nadstropje.txt 
   for (int i = 0; i < 7; i++){
      fgets(nadstropja,sizeof(nadstropja),file);
      if(strlen(c) == 1){
         // Ce je char nadstropje enako char c dodamo sum+1
         if(*nadstropja == *c){
            sum++;
         }
      }
   }
   // Vremo sum
   return sum;
}
