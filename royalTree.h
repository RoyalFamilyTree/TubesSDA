#ifndef royalTree_H
#define royalTree_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include "boolean.h"

#define MALE 1
#define FEMALE 0

#define MAX_LINE_LENGTH 100

/***************************/
/*  	  Type data        */
/***************************/

typedef char infoType[50];
typedef struct kingdomTree *nkAddr;
typedef struct pair *pairAddr;

typedef struct {
	infoType name;
	int age;
	boolean gender;
}identity;

typedef struct pair{
	identity info;
}nkPairNode;

typedef struct kingdomTree{
	nkAddr fs;
	nkAddr nb;
	nkAddr parent;
	identity info;
	pairAddr partner;
}nkTreeNode;

struct nkTree{
	nkAddr root;
};

struct Queue {
    int front, rear, size;
    nkAddr *arr;
};

/***************************/
/*  S P E S I F I K A S I  */
/***************************/

/*********** PROTOTYPE ****************/
/**** Predikat untuk test keadaan Tree  ****/

//Dibuat oleh : SN
boolean isEmpty (struct nkTree X);
/* Mengirimkan true jika Isi_Tree KOSONG */

/**** Konstruktor/Kreator Tree Kosong ****/

//Dibuat oleh : Fikri
boolean isFileEmpty();
/* Cek file kosong */

//Dibuat oleh : Fikri
void getKingdomFromFile(struct nkTree *pTree);
/* IS: tree tersedia, member kosong */
/* FS: tree terisi oleh node hasil dari read sebuah file */

//Sumber : Tugas Program Struktur Non Binary Tree SDA-P
void Create_Tree(struct nkTree *X);
// Membuat tree kosong

/**** Manajemen Memory ****/
/*Penambahan tipe data*/

void getDataFromFile(struct nkTree *pTree);

//void getPartnerFromFile(struct nkTree *pTree)

//Sumber : github 
//Modifikasi oleh : Adinda
nkAddr CreateNode (nkAddr parent, infoType name, int age, boolean gender);
/*Alokasi node*/
 
//Dibuat oleh : Adinda
pairAddr CreateNPartner (infoType name, int age, boolean gender);
/*Alokasi node partner*/

//Dibuat oleh : Adinda
void DeallocNode(nkAddr *Node);
/*IS : Node terdefinisi*/
/*FS : Node dikembalikan ke sistem*/
/* Melakukan dealokasi node*/

/**** Pencarian sebuah node Tree ****/

//Sumber : github
//Modifikasi oleh : Adinda
nkAddr Search(nkAddr root, infoType src);
/* Mencari apakah ada node dengan infoType src*/
/* Jika ada, mengirimkan address node tsb*/
/* Jika tidak ada, mengirimkan NULL*/

/**** Penambahan Node ****/

//Dibuat oleh : Adinda
void InsertKing(struct nkTree *pTree);
/* IS: pTree kosong*/
/* FS: Meminta input identitas node dari user, mengalokasi node dan menjadikannya root tree*/
/* Menambahkan node raja/ ratu*/

//Dibuat oleh : Adinda
void InsertVPartner(struct nkTree *myTree);
/* Menambahkan node partner*/

//Dibuat oleh : Fikri
void InputMember();
/* IS: data subvar newNode belum diketahui*/
/* FS: data subvar newNode terinput oleh user*/

/**** PRIMITIF BERDASARKAN ALAMAT ****/
/**** Penambahan node berdasarkan alamat ****/

//Dibuat oleh : Adinda
void InsertPartner(nkAddr familyMember, pairAddr partner);
/* IS: familyMember sembarang, partner sudah dialokasi*/
/* FS: Menambahakn node partner ber-address partner pada node familyMember*/

//Dibuat oleh : Adinda
void InsertNode(struct nkTree *treeRoot, nkAddr newNode);
/* IS: treeRoot sembarang, newNode sudah dialokasi*/
/* FS: Menambahkan node ber-address newNode pada tree*/

/**** Penghapusan sebuah node ****/

////Dibuat oleh : Fikri
//nkAddr FindParent(nkAddr root, nkAddr node);
///* IS: pointer nkAddr root dan pointer nkAddr node yang akan dicari induknya.*/
///* FS: pointer nkAddr yang menunjuk pada node induk dari node target. Jika tidak ditemukan, akan mengembalikan NULL.*/
//
////Dibuat oleh : Fikri
//nkAddr FindSuccessor(nkAddr root, nkAddr node);
///* IS: pointer nkAddr root dan pointer nkAddr node yang akan dicari penggantinya. */
///* FS: pointer nkAddr yang menunjuk pada node pengganti. Jika tidak ditemukan pengganti, akan mengembalikan NULL. */

//Dibuat oleh : Adinda
void Upgrade(nkAddr *root);
/* IS: */
/* FS: */ 

//Dibuat oleh : Fikri
//Modifikasi oleh : Adinda
void deleteNode(nkAddr *pDel, struct nkTree *pTree);
/* IS: node member dengan info sembarang tersedia/tidak tersedia */
/* FS: apabila node member dengan info sembarang tersedia, maka akan terhapus. apabila tidak tersedia, muncul output "nama anggota tidak tersedia"*/

/**** PROSES SEMUA NODE TREE  ****/

////Dibuat oleh : Adinda
//void printTree(nkAddr node, char tab[]);
///* Menampilkan tree pada program secara preorder*/

//Dibuat oleh : Welsya
struct Queue *initQueue(int size);

//Dibuat oleh : Welsya
void enQueue(struct Queue *queue, nkAddr node);

//Dibuat oleh : Welsya
nkAddr deQueue(struct Queue *queue);

//Dibuat oleh : Welsya
void levelOrderTraversal(nkAddr root);

//Dibuat oleh : Welsya
void nextKing(nkAddr root);

//Dibuat oleh : Adinda
int GetNodeDegree(nkAddr node);
/*Mengirimkan nilai degree dari suatu node*/

//Dibuat oleh : Adinda
void printNodeInfo(nkAddr node, infoType name);
/* IS: node sembarang, name sama dengan node->info.name atau node->partner->info.name*/
/* FS: Menampilkan nama, umur, jenis kelamin, orang tua, saudara, dan anak dari node jika atribut tersebut ada*/

void ProceedTimeSkip(nkAddr *root, int year);

//sumber : github
void gotoxy(int, int);
//Memindahkan kursor ke posisi tertentu di layar 

//Sumber : github
void loading_screen();
/*Menampilkan tulisan load*/

//Dibuat oleh : Adinda
void printFromFile(const char* location);
/* Menampilkan teks pada file yang terdapat pada location*/



#endif


