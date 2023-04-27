
#include <stdio.h>
#include <conio.h>
#include <windows.h>

#include "royalTree.h"

#define CREATOR "Created by Adinda Fauzia Puspita, Muhammad Fikri Nursyabani & Welsya Almaira Indra"

int main(){
	struct nkTree pTree;
	Create_Tree(&pTree);
	nkAddr node, king;
	int year;
	char choose;
	char str[]="";
	char searchname[20];
	unsigned char choice;
	loading_screen();
	system("cls");
	printFromFile("ilustrasi/opening.txt");
	printf("\n\n\t\t");
	printf(CREATOR);
	printf("\n\n\t\t");
	system("Pause");
	system("cls");
	printFromFile("ilustrasi/AturanPenurunanTahta.txt");
	printf("\n\n\t\t");
	system("Pause");
	system("cls");
	printFromFile("ilustrasi/AturanPenambahanAnggota.txt");
	printf("\n\n\t\t");
	system("Pause");
	system("cls");
	InsertKing(&pTree);
	do{
		system("CLS");
		king = pTree.root;
		if((!isEmpty) && (king->info.age >= 80)){
            deleteNode(&king, &pTree);
		}
		system("CLS");
		printf("\t\t\t\t\tKeadaan Pohon Keluarga: \n");
		if (isEmpty(pTree)){
			printf("\tTree kosong");
		}
		else{
           printTree(pTree.root,str);
		}
		gotoxy(36, 10);
        printf("    ************************************************\n");
        gotoxy(36, 11);
		printf(" []                                                  []\n");
        gotoxy(36, 12);
		printf(" []   [1] Tambah anggota keluarga kerajaan           []\n");
        gotoxy(36, 13);
		printf(" []   [2] Tambah pasangan                            []\n");
		gotoxy(36, 14);
		printf(" []   [3] Hapus/turunkan takhta Raja sekarang        []\n");
		gotoxy(36, 15);
		printf(" []   [4] Matikan/hapus anggota keluarga kerajaan    []\n");
		gotoxy(36, 16);
		printf(" []   [5] Tampilkan informasi keluarga kerajaan      []\n");
		gotoxy(36, 17);
		printf(" []   [6] Tampilkan penerus takhta                   []\n");
		gotoxy(36, 18);
		printf(" []   [0] Exit                                       []\n");
		gotoxy(36, 19);
	    printf(" []                                                  []\n");
	    gotoxy(36, 20);
        printf("  ***************************************************\n");
        gotoxy(40, 21);
		printf("\tPilihan %c ", 175); fflush(stdin); scanf("%d", &choose);
		system("cls");
		switch(choose){
			case 1:
				system("cls");
				InputMember(&pTree);
				break;
			case 2:
				system("cls");
				printFromFile("ilustrasi/wedding.txt");
				InsertVPartner(&pTree);
				break;
			case 3:
				system("cls");
				printf("sabar ya modul deletenya belum jadi\n");
				break;
			case 4:
				system("cls");
				printf("sabar juga ya modul deletenya belum jadi\n");
				break;
			case 5:
				system("cls");
				printf("sabarr modulnya belum jadi\n");
				break;
			case 6:
				system("cls");
				levelOrderTraversal(pTree.root);
				break;	
			case 7:
				system("cls");
				nextKing(pTree.root);
				break;
			case 0:
    			system("CLS");
    			gotoxy(44, 8); printf("Sukses Keluar dari Program\n\n");
    			system("PAUSE");
    			exit(1);
    			break;
    		default:
				printf("\n\tInput tidak valid");
				printf("\n\tTekan tombol apapun untuk kembali");
				getch();
				break;
		}
	}while(choose!=0);
		exit(1);	
		
return 0;
}

