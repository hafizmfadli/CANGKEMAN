#include "menu.h"
#include<stdio.h>

void gameRules()
{	
	printf("\n\n\n\n\n\n\n");
	printf("\t\t\t");printf("------------------------------------------------------------------------\n");
	printf("\t\t\t");printf("|                     PERATURAN PERMAINAN CANGKULAN                    |\n");
	printf("\t\t\t");printf("------------------------------------------------------------------------\n");
	printf("\t\t\t");printf("| 1.Player berjumlah 2 s.d 4 orang                                     |\n");
	printf("\t\t\t");printf("| 2.Setiap player akan mengeluarkan kartu secara bergiliran            |\n");
	printf("\t\t\t");printf("| 3.Kartu yang dikeluarkan harus memiliki simbol yang sama dengan      |\n");
	printf("\t\t\t");printf("|   kartu yang telah dikeluarkan oleh player sebelumnya                |\n");
	printf("\t\t\t");printf("| 4.Player wajib 'nyangkul' jika tidak memenuhi ketentuan              |\n");
	printf("\t\t\t");printf("| 5.Player yang kartunya habis akan keluar sebagai pemenang            |\n");
	printf("\t\t\t");printf("------------------------------------------------------------------------\n");
	
}



void mainMenu()
{
	printf("\n\n\n\n\n\n\n");
	printf("\t\t\t\t\t");printf("--------------------------------------------\n");
	printf("\t\t\t\t\t");printf("|                CANGKEMAN                 |\n");
	printf("\t\t\t\t\t");printf("|           (CANGKULAN E MANTAP)           |\n");
	printf("\t\t\t\t\t");printf("-------------------------------------------|\n");
	printf("\t\t\t\t\t");printf("| 1.MAIN KUY !                             |\n");
	printf("\t\t\t\t\t");printf("| 2.PETUNJUK PERMAINAN                     |\n");
	printf("\t\t\t\t\t");printf("| 3.EXIT GAME                              |\n");
	printf("\t\t\t\t\t");printf("--------------------------------------------\n");
}

int selectMenu()
{
	int ch;
	printf("\t\t\t\t\t");
	printf("Masukan pilihan : ");
	scanf("%d",&ch);
	
	return ch;
}





