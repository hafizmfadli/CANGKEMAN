#include "Cangkulan.h"
#include "menu.h"

#include <stdlib.h>
#include <string.h>

/* Note : table card adalah struktur data untuk menyimpan kartu
          yang dikeluarkan seluruh player

   table card dan array of player akan dijadikan variabel global
   di main program

*/

// cek ulang yang passing parameter table card

/* Private Method */
card getBiggestCard(tableCard *table,int jumlahPlayer);
player getOwnerCard(card c,player *p,int jumlahPlayer);
void pushCardtoTable(card c,tableCard *table);
card popDeckCard(deckCard *d);
bool isValidCard(card c);
bool isTableCardFull(tableCard *table,int totalPlayer);
bool isTableCardEmpty(tableCard *table);
void shiftCardCollection(player *p,card c);
void copyTableCard(tableCard *des,tableCard *src);
void swapPlayer(player *p, player *q);


void setPlayerProfile(player *p,int jumlahPlayer)
{
	// STATUS : WORKED (TESTED)
	// p adalah pointer untuk nunjuk arr of player
	int i;
	char nama[SIZE];
	for(i = 0 ; i < jumlahPlayer ; i++){
		  printf("\n\n\n\n\n\n\n\n\n\n\n");
		  printf("\t\t\t\t\t\tMasukan nama player ke %d : ",i+1);
		  fgets(nama,SIZE,stdin);
		  strcpy((p + i)->name,nama);
		  system("cls");
	}
}

void randomUrutanMain(player *p, int jumlahPlayer)
{
	// STATUS : WORKED (TESTED)
	//function untuk mengacak urutan main

	int i;
	//int n = 4; //jumlah elemen array, masih statis

	//agar tidak mendapat hasil yang sama tiap menjalankan modul
	srand (time(NULL) );

	for (i = jumlahPlayer-1; i > 0;i--) {
		//mengambil indeks secara random
		int j = rand() % i;

		//swap elemen pada array of player
		swapPlayer((p+i),(p+j));
	}
}
// pake algoritma shuffle
// p adalah pointer untuk nunjuk arr of player
/*
void setUrutanMain(player *p,tableCard *table,int jumlahPlayer)
{
	// procedure untuk set urutan main
	// table card harus di sort descending order terlebih dahulu
	int i;
	card c;
	player owner,tempPlayer;
	for(i = 0 ; i < jumlahPlayer ; i++){
		c = table->kartu[i];
		//tempPlayer = *(p + i);
		swapPlayer(,(p+i));
	}
}*/
// p adalah pointer untuk nunjuk arr of player


bool isSameCardSymbol(card *playerCard,tableCard *table)
{
	if(strcmp(playerCard->symbol,table->kartu[table->top].symbol) == 0)
	 return true;
	else return false;
}


void showPlayerCard(player *p)
{
	// STATUS : WORKED (TESTED)
	// menampilkan kartu yang dimiliki player tertentu

	if(isPlayerCardRunOut(p)){
		printf("kartu anda habis ");
		return;
	}

	int i;
	for(i = 0 ; i < p->card_amount ; i++){
		//int cardNumber = p->kartu[i].number;
		switch(p->kartu[i].number) {
			case 11:
				printf("J%s ",p->kartu[i].symbol);
				break;
			case 12:
				printf("Q%s ",p->kartu[i].symbol);
				break;
			case 13:
				printf("K%s ",p->kartu[i].symbol);
				break;
			case 14:
				printf("A%s ",p->kartu[i].symbol);
				break;
			default:
				printf("%d%s ",p->kartu[i].number,p->kartu[i].symbol);
				break;
		}
	}

}

void keluarkanKartu(player *p,tableCard *table)
{
  // STATUS : WORKED (TESTED)
  // hanya berlaku untuk player ybs
  // jumlah kartu player blm berkurang
  // kartu hanya di copy ke table card
  card myCard;
  myCard = searchCard(p);
  if(isValidCard(myCard)){
  	if(isTableCardEmpty(table)){
  		pushCardtoTable(myCard,table);
	}
	else {
		if(isSameCardSymbol(&myCard,table)){
			pushCardtoTable(myCard,table);
		}
		else {
			printf("Simbol kartu tidak sama !\n");
			keluarkanKartu(p,table);
			
		}
	}
  }else{
  	printf("Kartu tidak valid,silahkan coba lagi\n");
	keluarkanKartu(p,table);
  }
}

bool isPlayerCardRunOut(player *p)
{
	// function untuk cek jumlah kartu yang dimiliki player tertentu
	// return true jika kartu habis
	if(p->card_amount == 0) return true;
	return false;
}

bool isDeckCardRunOut(deckCard *d)
{
	// function untuk cek jumlah deckcard habis atau tidak
	// return true jika deckcard habis
	if(d->top == -1) return true;
	return false;
}

bool isSatuPutaran(tableCard *table, int jumlahPlayer)
{
	// satu putaran tercapai jika jumlah kartu
	// yang ada di table sama dengan jumlah pemain
	if(isTableCardFull(table,jumlahPlayer)) return true;
	return false;
}

player getMostHaveFewCard(player *p,int jumlahPlayer)
{
	// p adalah pointer untuk nunjuk arr of player
	// function untuk mendapatkan player yang memiliki
	// jumlah kartu paling sedikit

	player mostFewCard;
	int i;
	int min = 100;
	for(i = 0; i < jumlahPlayer ; i++){

	     if((p + i)->card_amount < min){
	     	min = (p + i)->card_amount;
	     	mostFewCard = *(p + i);
		 }
	}
	return mostFewCard;
}

card getBiggestCard(tableCard *table,int jumlahPlayer)
{
	// STATUS : WORKED (TESTED)
	// procedure untuk mendapatkan kartu terbesar dar table
	// digunakan setelah tableCard penuh

	int i,max = -1;
	card biggestCard;
	biggestCard.number = -1;
	for(i = 0; i <= table->top ; i++){
		if(table->kartu[i].number > biggestCard.number){
			biggestCard.number = table->kartu[i].number;
			strcpy(biggestCard.symbol,table->kartu[i].symbol);
		}
	}
	return biggestCard;
}



void reduceCardAllPlayer(player *p,int jumlahPlayer,tableCard *table)
{
	// STATUS : WORKED (TESTED)
	// procedure untuk mengurangi 1 kartu seluruh pemain
	// tableCard dan player harus disort terlebih dahulu
	card c;
	int i;
	
	for(i = 0 ; i < jumlahPlayer ; i++){
		c = table->kartu[i];
		shiftCardCollection((p + i),c);
	}
	
}

player getOwnerCard(card c,player *p,int jumlahPlayer)
{
	// STATUS : WORKED (TESTED)
	// hanya digunakan untuk mencari pemilik kartu
	int i,j;
	player ownerCard;
	for(i = 0 ; i < jumlahPlayer ; i++){

		for(j = 0 ; j < (p + i)->card_amount ; j++){

			bool isNumberCardSame = (p + i)->kartu[j].number == c.number;
			int isSymbolCardSame = strcmp((p + i)->kartu[j].symbol,c.symbol);

			if(isNumberCardSame && (isSymbolCardSame == 0)){
				ownerCard = *(p + i);
				return ownerCard;
			}
		}
	}

}

player comparePlayerCard(player *p,tableCard *table,int jumlahPlayer)
{

	// p adalah pointer untuk nunjuk arr of player
	// funtion untuk menentukan player yang akan menjadi pionner putaran selanjutnya
	// digunakan setelah satu putaran
	int i,j;
	player pioneerPlayer;
	card biggestCard;

	biggestCard = getBiggestCard(table,jumlahPlayer);
	pioneerPlayer = getOwnerCard(biggestCard,p,jumlahPlayer);

	return pioneerPlayer;
}


void cangkulKartu(player *p,deckCard *d)
{
	// STATUS : WORKED (TESTED)
	// deckcard berkurang 1
	// card milik player bertambah 1

	int lastIndexCard = p->card_amount -1;
	p->kartu[lastIndexCard + 1] = popDeckCard(d);
	p->card_amount = p->card_amount + 1;
}

card popDeckCard(deckCard *d)
{
	// STATUS : WORK (TESTED)
	// function untuk pop deck card
	// return card
	card kartu;
	int topIndex;

	topIndex = d->top;
	kartu = d->kartu[topIndex];
	d->top = d->top - 1;

	return kartu;
}

void swapPlayer(player *p, player *q)
{
	 player *temp = (player*)malloc(sizeof(player));
	 strcpy(temp->name,p->name);
	 strcpy(p->name,q->name);
	 strcpy(q->name,temp->name);

	 int k;
	 for(k = 0;k < 20;k++) {
	  temp->kartu[k] = p->kartu[k];
	  p->kartu[k] = q->kartu[k];
	  q->kartu[k] = temp->kartu[k];
	 }

	 temp->card_amount = p->card_amount;
	 p->card_amount = q->card_amount;
	 q->card_amount = temp->card_amount;
}

void bandarShareCard(player *p,int jumlahPlayer,deckCard *d)
{
	// STATUS : WORKED (TESTED)
	// procedure untuk membagikan tujuh kartu kepada setiap pemain
	// digunakan hanya satu kali (diawal permainan)
	int i,j;
	card temp;
	for(i = 0 ; i < jumlahPlayer ; i++){
		for(j = 0; j < 7 ; j++){
			(p + i)->kartu[j] = popDeckCard(d);
			(p + i)->card_amount += 1;
		}
	}
}

int readCardNumber()
{
	// STATUS : WORKED (TESTED)
	// funtion untuk read int x dari stdin
	// return x
	int cardNumber;
	char cardNumberC[5];
	char trash;
	char temp;

	printf("Masukan nilai kartu :");
	fgets(cardNumberC,5,stdin);
	
	temp = tolower(cardNumberC[0]);
	
	
	switch(temp) {
		case '2':
			cardNumber = 2;
			break;
		case '3':
			cardNumber = 3;
			break;
		case '4':
			cardNumber = 4;
			break;
		case '5':
			cardNumber = 5;
			break;
		case '6':
			cardNumber = 6;
			break;
		case '7':
			cardNumber = 7;
			break;
		case '8':
			cardNumber = 8;
			break;
		case '9':
			cardNumber = 9;
			break;
		case '1':
			cardNumber = 10;
			break;
		case 'j':
			cardNumber = 11;
			break;
		case 'q':
			cardNumber = 12;
			break;
		case 'k':
			cardNumber = 13;
			break;
		case 'a':
			cardNumber = 14;
			break;
	}
	
	return cardNumber;
}

char readCardSymbol()
{
	// STATUS : WORKED (TESTED)
	// funtion untuk read char c dari stdin
	// return char c

	char tempSymbol[5];
	char cardSymbol[5];

	printf("\t\t\t\tMasukan symbol kartu :");
	fgets(tempSymbol,5,stdin);
	cardSymbol[0] = tempSymbol[0];

	return cardSymbol[0];
}

int searchMatchCard(player *p,int searchedNumber,char searchedSymbol[])
{
	// STATUS : WORKED (TESTED)
	// function untuk memilih kartu
	// return index kartu jika player punya kartu ybs
	// return -99 jika player tidak punya kartu ybs

	int i;
	card dummyCard;

	for(i = 0 ; i < p->card_amount ; i++){

		int myCardNumber = p->kartu[i].number;
		char myCardSymbol[5];
		strcpy(myCardSymbol,p->kartu[i].symbol);

		if((myCardNumber == searchedNumber) && (myCardSymbol[0] == searchedSymbol[0])){
			// player punya kartu tsb
			return i;
		}
	}

	// jika search gagal (kartu tidak ditemukan)
	return -99;
}

bool isValidCard(card c)
{
	// STATUS : WORKED (TESTED)
	// function untuk cek kartu
	// return true jika valid
	// return false jika ngaco
	if(((c.number >= 2) && (c.number <= 14)) && ((strcmp(c.symbol,"d") == 0) || (strcmp(c.symbol,"h") == 0) || (strcmp(c.symbol,"s") == 0) || (strcmp(c.symbol,"c") == 0))){
		return true;
	}else return false;
}


card searchCard(player *p)
{
	// STATUS : WORKED (TESTED)
	// function untuk mencari kartu x di koleksi kartu player ybs
	// return card x jika ada
	// return dummyCard jika x tidak ada

	int searchedNumber;
	char searchedSymbol[5];
	int myIndexCard;
	card myCard,dummyCard;
	char sampahASU;

	searchedNumber = readCardNumber();
	//scanf("%c",&sampahASU);
	searchedSymbol[0] = readCardSymbol();
	myIndexCard = searchMatchCard(p,searchedNumber,searchedSymbol);

	if(myIndexCard != -99){
		myCard = p->kartu[myIndexCard];
		return myCard;
	}else{
		dummyCard.number = -99;
		strcpy(dummyCard.symbol,"x");
		return dummyCard;
	}
}

void pushCardtoTable(card c,tableCard *table)
{
	// STATUS : WORKED (TESTED)
	// procedure untuk push kartu ke table card
	table->top += 1;
	table->kartu[table->top] = c;
}

void createTableCard(tableCard *table)
{
	// STATUS : WORKED (TESTED)
	// procedure untuk membuat table card
	intializeTableCard(table);
}

bool isTableCardFull(tableCard *table,int totalPlayer)
{
	// STATUS : WORKED (TESTED)
	// function untuk cek table card
	int indexLastPlayer = totalPlayer - 1;
	if(table->top == indexLastPlayer) return true;
	return false;
}

bool isTableCardEmpty(tableCard *table)
{
	if(table->top == -1) return true;
	else return false;
}

void showTableCard(tableCard *table)
{
	// STATUS : WORKED (TESTED)
	// procedure untuk menampilkan kartu yang ada di table
	int i;
	for(i = 0 ; i <= table->top ; i++){
		int cardNumber = table->kartu[i].number;
		switch(cardNumber) {
			case 11:
				printf("J%s ",table->kartu[i].symbol);
				break;
			case 12:
				printf("Q%s ",table->kartu[i].symbol);
				break;
			case 13:
				printf("K%s ",table->kartu[i].symbol);
				break;
			case 14:
				printf("A%s ",table->kartu[i].symbol);
				break;
			default:
				printf("%d%s ",cardNumber,table->kartu[i].symbol);
				break;
		}
	}
}



void sortTableCard(tableCard *table)
{
	// STATUS : WORKED (TESTED)
	// procedure untuk sort table card

	tableCard *temp = table;
	int i,j;

	for(i = 0 ; i <= table->top ; i++){

		for(j = i + 1 ; j <= table->top ; j++){
			if(temp->kartu[i].number < temp->kartu[j].number){
				swap(&(temp->kartu[i]),&(temp->kartu[j]));
			}
		}
	}
}

void shiftCardCollection(player *p,card c)
{
	// STATUS : WORK (TESTED)
	// procedure untuk shift kartu player
	// setelah di shift jumlah kartu berkurang 1
	int myCardNumber;
	char myCardSymbol[5];
	int currIndex,lastIndex;
	int i;

	myCardNumber = c.number;
	strcpy(myCardSymbol,c.symbol);
	currIndex = searchMatchCard(p,myCardNumber,myCardSymbol);
	lastIndex = p->card_amount -2;

	if(currIndex != (p->card_amount - 1)){
		for(i = currIndex ; i <= lastIndex ; ++i){
			p->kartu[i] = p->kartu[i + 1];
		}
		p->card_amount = p->card_amount - 1;
	}else p->card_amount = p->card_amount - 1;
}

void copyTableCard(tableCard *des,tableCard *src)
{
	// STATUS : WORKED (TESTED)
	// procedure untuk copy table card
	int i;
	card c;
	for(i = 0 ; i <= src->top ; i++){
		c = src->kartu[i];
		printf("kartu yang dicopy : %d%s\n",c.number,c.symbol);
		pushCardtoTable(c,des);
	}
}

void copyCangkulanPlayers(player *des,player *src,int jumlahPlayer)
{
	// STATUS : WORKED (TESTED)
	// procedure untuk copy array of player
	int i;
	for(i = 0 ; i < jumlahPlayer ; i++){
		*(des + i) = *(src + i);
	}
}

void playerInfo(player *p)
{
	// STATUS : WORKED (TESTED)
	// procedure untuk menampilkan nickname player
	printf("nickname : %s",p->name);
	printf("\t\t\t\t| card amount : %d\n",p->card_amount);
	printf("\t\t\t\t| card collection : ");
	showPlayerCard(p);
}

void setUrutanMain(player *p,tableCard *table,int jumlahPlayer)
{

	player sortedPlayer[4];
	player temp;
	card c;
	int i;

	for(i = 0 ; i < jumlahPlayer ; i++){
		c = table->kartu[i];
		temp = getOwnerCard(c,p,jumlahPlayer);
		sortedPlayer[i] = temp;
	}
	copyCangkulanPlayers(p,sortedPlayer,jumlahPlayer);
}

void resetTableCard(tableCard *table)
{
	intializeTableCard(table);
}

void visualTableCard(tableCard *table)
{
		printf("\t\t\t\t\t\t   TABLE CARD \n");
		printf("\t\t\t\t------------------------------------------------\n");
		printf("\t\t\t\t| ");showTableCard(table);
		printf("\n\t\t\t\t------------------------------------------------\n");
}

void visualPlayerChair(player *p)
{
		printf("\n\n\t\t\t\tPlayer Info\n");
		printf("\t\t\t\t------------------------------------------------\n");
		printf("\t\t\t\t| ");playerInfo(p);
		printf("\n\t\t\t\t------------------------------------------------\n");
}

void visualCardInformation()
{
	printf("\t");printf("-------------------\n");
	printf("\t");printf("| informasi kartu |\n");
	printf("\t");printf("-------------------\n");
	printf("\t");printf("| s = spade       |\n");
	printf("\t");printf("| h = heart       |\n");
	printf("\t");printf("| c = clover      |\n");
	printf("\t");printf("| d = diamond     |\n");
	printf("\t");printf("-------------------\n");
}

void prosesMain(player *p,int jumlahPlayer,tableCard *table)
{
	int i;
	
	//printf("Tekan x untuk nyangkul");
	for(i = 0 ; i < jumlahPlayer ; i++){
		
		visualCardInformation();
		visualTableCard(table);
		visualPlayerChair(p+i);
		
		printf("\t\t\t\t");
		keluarkanKartu(p+i,table);
		system("cls");
		printf("\n");
	}
}

int setJumlahPlayer()
{
	int jumlahPlayer;
	char dump;
	
	printf("\n\n\n\n\n\n\n\n\n\n\n");
	printf("\t\t\t\t\t\t Masukan jumlah player : ");scanf("%d",&jumlahPlayer);scanf("%c",&dump);
	
	
	return jumlahPlayer;
}


void startGame(player *p)
{
	
	int i,jumlahPlayer;
	deckCard d;
	tableCard table;

	player temp[4];
	
	
	// Menentukan jumlah player yg ikut barmain
	jumlahPlayer = setJumlahPlayer();
	system("cls");
	
	// set profile tiap player
	setPlayerProfile(p,jumlahPlayer);
	system("cls");
		
	// Membuat peralatan cangkulan
	intializeTableCard(&table);
	createDeckCard(&d);
	
	// tiap player mendapat 7 kartu random
	bandarShareCard(p,jumlahPlayer,&d);
	
	// urutan bermain di random
	randomUrutanMain(p,jumlahPlayer);
	
	// Putaran pertama 
	prosesMain(p,jumlahPlayer,&table);
	
	
	while(1)
	{
		// Penentuan pioneer player putaran selanjutnya
		// (kurangi jumlah kartu tiap player dahulu)
		sortTableCard(&table);
		setUrutanMain(p,&table,jumlahPlayer);
		reduceCardAllPlayer(p,jumlahPlayer,&table);
	
		// Putaran selajutnya
		prosesMain(p,jumlahPlayer,&table);
	
	}
	
}

void programCangkulan(player *p)
{
	int ch;
	mainMenu();
	ch = selectMenu();
	
	switch(ch)
	{
		case 1 : system("cls");
				 startGame(p);
				 break;
		case 2 : system("cls"); 
				 gameRules();
				 break;
		case 3 : exit(0);
				 break;
	}
	
	
}
