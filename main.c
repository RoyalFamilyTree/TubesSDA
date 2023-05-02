
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
	char choose, choose2;
	char str[]="";
	char searchName[20];
	unsigned char choice;
	getKingdomFromFile(&pTree);
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
	printFromFile("ilustrasi/king.txt");
	printf("\n");

	if(isFileEmpty()){
		InsertKing(&pTree);	
	}else{
		getDataFromFile(&pTree);
//		getPartnerFromFile(&pTree);
	}
	
	do{
		system("CLS");
		king = pTree.root;
		if((!isEmpty) && (king->info.age >= 80)){
            deleteNode(&king, &pTree);
		}
		system("CLS");
		printf("\t   Keadaan Pohon Keluarga\n");
		printf("\t   ~~~~~~~~~~~~~~~~~~~~~~\n\n");
		if (isEmpty(pTree)){
			printf("\tTree kosong");
		}
		else{
//           printTree(pTree.root,str);
			levelOrderTraversal(pTree.root);
		}
		gotoxy(60, 7);
        printf("    ************************************************\n");
        gotoxy(60, 8);
		printf(" []                                                  []\n");
        gotoxy(60, 9);
		printf(" []   [1] Tambah anggota keluarga kerajaan           []\n");
        gotoxy(60, 10);
		printf(" []   [2] Tambah pasangan                            []\n");
		gotoxy(60, 11);
		printf(" []   [3] Hapus/turunkan takhta Raja sekarang        []\n");
		gotoxy(60, 12);
		printf(" []   [4] Matikan/hapus anggota keluarga kerajaan    []\n");
		gotoxy(60, 13);
		printf(" []   [5] Tampilkan informasi keluarga kerajaan      []\n");
		gotoxy(60, 14);
		printf(" []   [6] Tampilkan penerus takhta                   []\n");
		gotoxy(60, 15);
		printf(" []   [7] Lakukan timeskip                           []\n");
		gotoxy(60, 16);
		printf(" []   [0] Exit                                       []\n");
		gotoxy(60, 17);
	    printf(" []                                                  []\n");
	    gotoxy(60, 18);
        printf("  ***************************************************\n");
        gotoxy(74, 19);
		printf("\tPilihan %c ", 175); fflush(stdin); scanf("%d", &choose);
		system("cls");
		switch(choose){
			case 1:
				system("cls");
				printFromFile("ilustrasi/throne.txt");
				InputMember(&pTree);
				break;
			case 2:
				system("cls");
				printFromFile("ilustrasi/Queen.txt");
				InsertVPartner(&pTree);
				break;
			case 3:
				system("cls");
  		  		if (!isEmpty(pTree)){
                    do{
                    system("CLS");
                    fflush(stdin);
                    printf("\n\n\n\t Pilih penyebab turunnya tahta raja : \n");
                    printf("\t 1. Tewas karena penyakit/terbunuh atau alasan mendadak lainnya\n");
                    printf("\t   (Tahta akan diteruskan, sekaligus Raja turun tahta di umur yang sama) \n");
                    printf("\t 0. Kembali");
                    printf("\n\n\t Pilihan %c ", 175);
                    choose2 = getchar();
                    if(choose2=='1'){
                        fflush(stdin);
                        if(king != NULL){
                            printf("\n\t%c Apakah anda yakin ingin menghapus data ini? [Y/N] : ", 175);
                            choice = getchar();
                            if(choice == 'Y'){
                                printf("\n\t[o] Data anggota keluarga bernama \"\%s\"\ telah dihapus\n", king->info.name);
                                deleteNode(&king, &pTree);
                                printf("\t");
                                system("PAUSE");
                            }
                            else{
                                printf("\n\t[o] Data batal dihapus\n");
                                printf("\t");
								system("PAUSE");
                            }
                        }
                        break;
                    }
                    else if(choose2=='0'){
                        break;
                    }
                    else{
                        printf("\n\t[x] INPUT TIDAK VALID!");
                        system("PAUSE");
                    }
                    }while(choose2 != 0);
                }
                else{
                    printf("\n\t[x] Anggota Keluarga Masih Kosong!\n");
                }
                system("PAUSE");
                  break;
			case 4:
			fflush(stdin);
                system("cls");
                printf("\n\t%c Nama anggota keluarga yang hendak dihapus: ", 175);
                scanf(" %[^\n]",&searchName);
                fflush(stdin);
                node = Search(pTree.root, searchName);
                if (node != NULL){
                	if (node == king){
                		printf("Tidak dapat menghapus raja/ratu\n");
                		system("PAUSE");
					} else {
                    printf("\t%c Apakah anda yakin ingin menghapus data ini? [Y/N] : ", 175);
                    scanf("%c",&choice);
                    if(choice == 'Y'){
                        printf("\n\t[o] Data anggota keluarga telah dihapus\n");
                        deleteNode(&node, &pTree);
                        system("PAUSE");
                        break;
                    }
                    else{
                        printf("\n\t[o] Data batal dihapus\n");
                        system("PAUSE");
                    }
                }
                }
                else{
                    printf("\n\t[x] Data bernama %s tidak ditemukan di dalam daftar anggota keluarga\n");
                    system("PAUSE");
                }
                break;
			case 5:
				printFromFile("ilustrasi/castle.txt");
				printf("\n\t%c Nama: ", 175);
            	scanf(" %[^\n]", &searchName);
            	node = Search(pTree.root, searchName);
            	if(node!=NULL){
            		printNodeInfo(node, searchName);
            		printf("\n\tTekan tombol apapun untuk kembali");
					getch();
				}else{
					printf("\n\t[x] %s tidak terdapat pada pohon keluarga");
					printf("\n\tTekan tombol apapun untuk kembali");
					getch();
				}
				break;
			case 6:
				system("cls");
				nextKing(pTree.root);
				break;
			case 7:
				system("cls");
				printf("\n\tFungsi ini akan menambahkan umur semua anggota keluarga kerajaan sesuai input yang diterima\n");
                printf("\t%c Input jumlah tahun yang akan ditambahkan : ", 175);
                scanf("%d",&year);
				ProceedTimeSkip(&pTree.root, year);
				fflush(stdin);
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

