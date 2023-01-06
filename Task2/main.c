#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

/**
 * inicializiramo funkcije
*/
//Izbere eno od 10 besed
char* Izbira_besede();
//Napise besedo z eno crko in "_"
char* Print_beseda(char* beseda,char crka);
//Prebere input uporabnika
int Input(char* beseda,int n);
//preveri ali je pravilen vnos
bool Preveri_Vnos(char* crka,char* beseda);
//Funkcije z katero naredimo loop
void Menu(char* beseda,int n);
//Preverja koliko zivljen imamo
int zivljenja(int n);
//Izpise naso figuto
void Print_zivljenja(char* head, char* body,char* Larm, char* Rarm, char* Lleg, char* Rleg);
//Preverja ali smo zmagali
bool victory(char* beseda);
//Shranimo nas napačne vnose v file
void Napake(char* crka);


int main (){
   //Uvedemo random seed, da je vedno random stevilka
   srand(time(0));
   //Inicializiramo char* beseda in Senzored
   char* beseda;
   char* Senzored;
   //Dobimo char* iz funkcije in ga shranimo v beseda
   beseda = Izbira_besede();
   /** 
    * inicaliziramo l-dolzino stringa,
    * r-random stevilka(od 0 - l),
    * n-napake (max 6 napak)
   */
   int l = strlen(beseda);
   int r = rand() % l;
   int n = 6;
   //odpremo Beseda.txt za pisanje
   FILE* file = fopen("Beseda.txt","w");
   //preverimo ali lahko odpremo file
   if(file==NULL){
      printf("File can not bo open for writing.\n");
      exit(0);
   }
   /**
    * Dobimo char* iz funkcije in ga shranimo v Senzord
    * zapisemo Senzored v file
    * zapremo file
    * poklicemo funkcijo Menu;
   */
   Senzored = Print_beseda(beseda,beseda[r]);
   fwrite(Senzored,l,1,file);
   fclose(file);
   Menu(beseda,n);

}

//Funkcije z katero naredimo loop
void Menu(char* beseda,int n){
   /**
    * Dobimo int a iz funkcije
    * poklicemo funkcijo zivljenje in ji damo int a
    * Če funkicja victory vrne True smo zmagali 
    * Izpisemo čestitko za zmago in koncamo program
   */
   int a = Input(beseda,n);
   zivljenja(a);   
   if(victory(beseda)){
      printf("\n\n*****************************\n");
      printf("            YOU WIN!\n");
      printf    ("*****************************\n");
      exit(0);
   }

   //Opremo file Napake.txt za branje
   FILE* file = fopen("Napake.txt", "r");  
   //inicializiramo c
   char c;
   printf("\n");
   printf("Wrong letter: ");
   // Preberemo črko iz datoteke, dokler ni konec datoteke
   while ((c = fgetc(file)) != EOF) {  
   // Izpišemo prebrano črko
   printf("%c", c);  
  }
   printf("\n\n");
   //zapremo file
   fclose(file);
   
   //Poklicemo funkcijo Menu in ji damo char* besedo in int a
   //dobimo loop dokler ne user zamaga ali izgubi
   Menu(beseda,a);  
}

//Izpise naso figuto
void Print_zivljenja(char* head, char* body,char* Larm, char* Rarm, char* Lleg, char* Rleg){
      printf("___   \n");
      printf("|  |  \n");
      printf("|  %s  \n",head);
      printf("| %s",Rarm);
      printf("%s",body);
      printf("%s  \n",Larm);
      printf("| %s",Lleg);
      printf(" %s  \n",Rleg);
}
//Preverja koliko zivljen imamo in naredimo naso figuro
int zivljenja(int n){
   //figura
   char* head = "o";
   char* body = "0";
   char* Larm = "\\";
   char* Rarm = "/";
   char* Lleg = "/";
   char* Rleg = "\\";
   //preverimo koliko zivljen imamo
   //in glede na to naredi naso figuro
   if(n == 0){
      Print_zivljenja(head, body, Larm, Rarm, Lleg, Rleg);
      printf("\n\n*****************************\n");
      printf("            GAME OVER!\n");
      printf("            YOU LOSE!\n");
      printf    ("*****************************\n");
      printf("GAME OVER!\n");
      FILE* file = fopen("Napake.txt", "w");
      fwrite("\n",1,1,file);
      fclose(file);    

      exit(0);
   }else if(n == 1){
      Rleg = "";
      Print_zivljenja(head, body, Larm, Rarm, Lleg, Rleg);
   }else if (n == 2){
      Rleg = " ";
      Lleg = " ";
      Print_zivljenja(head, body, Larm, Rarm, Lleg, Rleg);
   }else if (n == 3){
      Rleg = " ";
      Lleg = " ";
      Rarm = " ";
      Print_zivljenja(head, body, Larm, Rarm, Lleg, Rleg);
   }else if (n == 4){
      Rleg = " ";
      Lleg = " ";
      Rarm = " ";
      Larm = " ";
      Print_zivljenja(head, body, Larm, Rarm, Lleg, Rleg);
   }else if (n == 5){
      Rleg = " ";
      Lleg = " ";
      Rarm = " ";
      Larm = " ";
      body = " ";
      Print_zivljenja(head, body, Larm, Rarm, Lleg, Rleg);
   }else if (n == 6){
      Rleg = " ";
      Lleg = " ";
      Rarm = " ";
      Larm = " ";
      body = " ";
      head = " ";
      Print_zivljenja(head, body, Larm, Rarm, Lleg, Rleg);
      
   }
}


//Shranimo nas napačne vnose v file
void Napake(char* crka){
   //Odpremo file Napake.txt
  FILE* file = fopen("Napake.txt", "a");
  // Preverimo, ali se je datoteka "Napake.txt" uspešno odprla
  if (file == NULL) {  
    printf("Can not open the file for apiling\n");
    exit(0);
  }
  /**
   * napisemo char c v file
   * napisemo se presledek v file
   * zapremo file
  */
  fputc(*crka, file);
  fputc(' ', file);
  fclose(file);
 
}

//Preverja ali smo zmagali
bool victory(char* beseda){
   //Odpremo file Beseda.txt za branje
  FILE* file = fopen("Beseda.txt", "r");
  /**
   * inicializiramo int l-dolzina besede
   * char PravaBeseda[l+1]-array dolzine l+1;
  */
  int l = strlen(beseda);
  char PravaBeseda[l + 1];
  //Naredimo for loop ki se ponovi l-krat
  //in izpisemo char v array PravaBeseda 
  for (int i = 0; i < l; i++) {
    PravaBeseda[i] = fgetc(file);  
  }
  //zadnji element arraya
  PravaBeseda[l] = '\0'; 
  //Zapremo file 
  fclose(file);
  //Naredimo for loop ki se ponovi l-krat
  for (int i = 0; i < l; i++) {
   //preverimo ali je beseda na indeksu i enaka PravaBeseda na indeksu i
   //ce ni enaka vremo false
    if (beseda[i] != PravaBeseda[i]) {
      return false;
    }
  }
  /**
   * Odpremo file Napake.txt
   * file se celoten izbrise
   * To se zgodi ko zmagamo
  */
  FILE* file2 = fopen("Napake.txt", "w");
      fwrite("\n",1,1,file);
      fclose(file2);
  return true;
}

//preveri ali je pravilen vnos
bool Preveri_Vnos(char* crka, char* beseda) {
  // int l-dolzina besede
  int l = strlen(beseda);
  //for loop ki se ponovi 7 krat
  for (int i = 0; i < l; i++) {
    //preverimo ali je crka enaka besedi na indeksu i
    //ce je enaka vremo true drugace false
    if (*crka == beseda[i]) {
      return true;
    }
  }
  
  return false;
}
//Prebere input uporabnika
int Input(char* beseda,int n) {
  printf("Enetr a letter here: ");
  // spremenljivka "a" se inicializira z dovolj velikim poljem da lahko shrani vnešeno črko
  char a[2];  
  //shranomo uporabnikov vnos v a
  scanf(" %c",a);  
  printf("\n");
  //če funcija Preveri_Vnos vrne true
  if (Preveri_Vnos(a, beseda)) {
   //Odpremo file za branje
    FILE* file = fopen("Beseda.txt", "r");
    //inicializiramo recrka[128]
    char recrke[128];
    //preberemo iz fila in damo v recrke
    fread(recrke, 128, 1, file);
    //l-dolzina besede
    int l = strlen(beseda);
    //zapremo file
    fclose(file);
    //opremo file Beseda.txt za pisanje(file postane prazen)
    FILE* file2 = fopen("Beseda.txt","w");
    //for loop ki se 7-krat ponovi
    for (int i = 0; i < l; i++) {
      //Če beseda na indeksu i ni enaka a
      //potem napisemo recrko na indeksu i in hkrati ti recrko zapisemo v file
      if (beseda[i] != a[0]) {
        printf("%c", recrke[i]);
        fputc(recrke[i], file2);
        //Če je enako izpisemo a in a zapisemo v file
      } else {
        fputc(a[0], file2);
        printf("%c", a[0]);
      }
    }
    printf("\n");
    fclose(file2);
    //vrnemo n-zivljen
    return n;
  //če funcija Preveri_Vnos vrne false
  } else {
   //Napisemo da je napacen vnos
   printf("Napacen vnos.\n");
   //Odpremo file Beseda.txt za branje
   FILE* file3 = fopen("Beseda.txt","r");
   /**
    * inicializiramo char nevidna_beseda[128]
    * izpisemo iz fila v nevidna_beseda(napake)
    * in napisemo nevidan_beseda(napake)
   */
   char nevidna_beseda[128];
   fgets(nevidna_beseda,128,file3);
   printf("%s\n",nevidna_beseda);
   //poklicemo funkicja napake in ji damo char a
   Napake(a);
   fclose(file3);
   //vrenmo n-1 (zmanjsamo zivljenja)
   return n-1;
  }
}

//Izbere eno od 10 besed
char* Izbira_besede(){
   //polje z besedami
   char* besede[10] = {"orange","berral","cannon","discord",
   "potion","grass","rock","power","pokemon","minecraft"};
   //int n-random stevila od 0-10
   int n = rand()%10;
   //vrnemo besedo na indexu n
   return besede[n];
}

//Napise besedo z eno crko in "_"

char* Print_beseda(char* beseda,char crka){
   //int l-dolzina besede
   int l = strlen(beseda);
   //Inicializiramo dva char eno polje z dolzino l+1 in char ki ima vrednost "_"
   char Se_beseda[l+1];
   char c = '_';
   //for loop ki se ponovi l-krat
   for(int i =  0; i < l; i++){
      //Če je beseda na indeksu i enaka crka
      if(beseda[i] == crka){
         //napisemo beseda na indeksu i
         //Se_beseda na indeksu i je enaka beseda na indeksu i
         printf("%c",beseda[i]);
         Se_beseda[i] = beseda[i];
      //Če je beseda na indeksu i ni enak crka
      }else{
         //napis "_"
         //Se_beseda na indeksu i je enak char c
         printf("_");
         Se_beseda[i] = c;
      }
   }
   //inicializiramo char* a in ga enacimo z celotnim poljem od Se_besede
   char* a;
   a = Se_beseda;
   printf("\n");
   //vrenemo char* a
   return a;
}
