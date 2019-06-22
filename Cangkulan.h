/* Nama Program      : Cangkulan.h
 * Deskripsi         : Header dari Cangkulan.c
 * Tanggal / Versi   : 2 Juni 2019/ 1.0
 * Author 		     : Raihan Ibrahim Risyad
 * Compiler          : Dev-C++ 5.11 
 * Modifikasi 		 : Hafiz Muhammad Fadli 
 */
 
#ifndef cangkulan_H
#define cangkulan_H

#include<stdio.h>
#include <stdbool.h>
#include "card.h"
#define SIZE 100
#define MAX 20

typedef struct {
	char name[SIZE];
	card kartu[MAX];
	int card_amount;
}player;


void setPlayerProfile(player *p,int jumlahPlayer);

void swapPlayer(player *p, player *q);
void randomUrutanMain(player *p, int jumlahPlayer);
// pake algoritma shuffle

void setUrutanMain(player *p,tableCard *table,int jumlahPlayer);
bool isSameCardSymbol(card *playerCard,tableCard *table);
bool isPlayerCardRunOut(player *p);
bool isDeckCardRunOut(deckCard *d);
bool isSatuPutaran(tableCard *table, int jumlahPlayer);
void keluarkanKartu(player *p,tableCard *table);

player getMostHaveFewCard(player *p,int jumlahPlayer);
void shuffleCard(deckCard *d);
//algoritma shuffle

void cangkulKartu(player *p,deckCard *d);
player comparePlayerCard(player *p,tableCard *table,int jumlahPlayer);
card searchCard(player *p);

void programCangkulan(player *p);

#endif
