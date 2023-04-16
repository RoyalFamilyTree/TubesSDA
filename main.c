#include <stdio.h>
#include <conio.h>
#include <windows.h>

#include "royalTree.h"

#define CREATOR "Created by Adinda Fauzia Puspita, Muhammad Fikri Nursyabani & Welsya Almaira Indra"

int main(){
	nkTree pTree;
	CreateNode(&pTree);
	nkAddr node;
	int year;
	char tombol,tombol2;
	char str[]="";
	char searchname[20];
	unsigned char choice;
	printf(CREATOR);
	printf("\n\n");
	system("Pause");
	system("cls");
	InsertKing(&pTree);
}