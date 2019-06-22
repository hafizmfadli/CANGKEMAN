/****************************************************************
 * header card
 * Author : Hafiz Muhammad Fadli
 * NIM : 181514010
 * Compiler : TDM GCC
 * tgl : 7 Juni 2019
 ****************************************************************/
 
#ifndef card_H
#define card_H

typedef struct cardType{
	int number;
	char symbol[5];
}card;

typedef struct stackType{

	card kartu[52];
	int top;

}stack;


typedef stack deckCard;
typedef stack tableCard;

// function untuk alokasi card dengan number
// dan symbol tertentu
card* createCard(int number,char symbol[]);

// procedure untuk membuat deck card
void createDeckCard(deckCard *deck);


#endif

