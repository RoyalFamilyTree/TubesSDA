#include <stdio.h>
#include <conio.h>
#include <windows.h>

#include "royalTree.h"

#define CREATOR "Created by Adinda Fauzia Puspita, Muhammad Fikri Nursyabani & Welsya Almaira Indra"

int main(){
	struct nkTree pTree;
	//CreateNode();
	nkAddr node;
	int year;
	char choose;
	char str[]="";
	char searchname[50];
	unsigned char choice;
	printf(CREATOR);
	printf("\n\n");
	system("Pause");
	system("cls");
	InsertMember(&pTree);
}
	do{
		system("CLS");
		printf("\n\n\n\t[1] Tambah anggota keluarga kerajaan\n");
		printf("\t[2] Hapus/turunkan tahta Raja sekarang\n");
		printf("\t[3] Matikan/hapus anggota keluarga kerajaan\n");
		printf("\t[4] Tambah pasangan\n");
		printf("\t[5] Tampilkan informasi keluarga kerajaan\n");
		printf("\t[6] Tampilkan Silsilah\n");
		printf("\t[7] Jumlah Generasi\n");
		printf("\t[8] Jumlah Anak\n");
		printf("\t[0] Exit\n\n");
		printf("\tPilihan %c ", 175); fflush(stdin); scanf("%c", &choose);
		switch(choose){
			case '1':
				system("cls");
				InsertMember(&pTree);
				break;
		}while(choose!=0);
		 exit(1);	
	}
}
