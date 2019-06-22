/****************************************************************
 * header card
 * Author : Hafiz Muhammad Fadli
 * NIM : 181514010
 * Compiler : TDM GCC
 * tgl : 7 Juni 2019
 ****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "card.h"

/* Private method */
void swap(card *a, card *b);
void shuffleDeckCard(deckCard *deck);
void pushCard(deckCard *deck,card c);
void pushOneSeriesCard(deckCard *deck,char symbol[]);



card* createCard(int number,char symbol[])
{
	// STATUS : WORK (TESTED)
	// function untuk alokasi card
	// return address card jika alokasi berhasil
	// return NULL jika alokasi gagal

	card *c = (card *)malloc(sizeof(card));

	if(c != NULL){

		c->number = number;
		strcpy(c->symbol,symbol);
	}

	return c;
}

void intializeDeckCard(deckCard *deck)
{
	deck->top = -1;
}

void intializeTableCard(tableCard *table)
{
	// STATUS : WORKED (TESTED)
	// procedure untuk inisialisasi table card
	table->top = -1;

}

void pushCard(deckCard *deck,card c)
{
	// procedure untuk push card ke stack (deck card)
	// deckcard harus di inisiasi dahulu (initializeDeckCard)
	deck->top += 1;
	deck->kartu[deck->top] = c;
}

void pushOneSeriesCard(deckCard *deck,char symbol[])
{
	// procedure untuk push satu seri card ke stack (deck card)

	card *c;
	int i;

	for(i = 2 ; i <= 14 ; i++){

		c = createCard(i,symbol);

		if(c != NULL){
			pushCard(deck,*c);
		}else{
			printf("ALOKASI CARD GAGAL !");
			return;
		}


	}
}

void createDeckCard(deckCard *deck)
{
	// STATUS : WORK (TESTED)
	// procedure untuk membuat deck card
	intializeDeckCard(deck);
	pushOneSeriesCard(deck,"s");
	pushOneSeriesCard(deck,"h");
	pushOneSeriesCard(deck,"d");
	pushOneSeriesCard(deck,"c");
	shuffleDeckCard(deck);
}

void swap(card *a, card *b)
{
	card temp= *a;
	*a = *b;
	*b = temp;
}

void shuffleDeckCard(deckCard *deck)
{
	// STATUS : WORK (TESTED)

	//function untuk mengkocok deck card

	int i;
	int n = sizeof(deck->kartu) / sizeof(deck->kartu[0]); //jumlah elemen array

	//agar tidak mendapat hasil yang sama tiap menjalankan modul
	srand (time(NULL) );

	for (i = n-1; i > 0;i--) {
		//mengambil indeks secara random
		int j = rand() % (i + 1);

		swap(&(deck->kartu[i]),&(deck->kartu[j]));
	}

}
