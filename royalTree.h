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

//Sumber : Tugas Program Struktur Non Binary Tree SDA-P
void Create_Tree(struct nkTree *X);
// Membuat tree kosong

//Dibuat oleh : Adinda
boolean isEmpty (struct nkTree X);
/* Mengirimkan true jika Isi_Tree KOSONG */

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

//Sumber : github
//Modifikasi oleh : Adinda
nkAddr Search(nkAddr root, infoType src);
/* Mencari apakah ada node dengan infoType src*/
/* Jika ada, mengirimkan address node tsb*/
/* Jika tidak ada, mengirimkan NULL*/

//Dibuat oleh : Fikri
void InsertKing(struct nkTree *pTree);
/* IS: pTree kosong*/
/* FS: Meminta input identitas node dari user, mengalokasi node dan menjadikannya root tree*/
/* Menambahkan node raja/ ratu*/

//Dibuat oleh : Fikri
void InputMember();
/* IS: data subvar newNode belum diketahui*/
/* FS: data subvar newNode terinput oleh user*/

//Dibuat oleh : Adinda
void InsertNode(struct nkTree *treeRoot, nkAddr newNode);
/* IS: treeRoot sembarang, newNode sudah dialokasi*/
/* FS: Menambahkan node ber-address newNode pada tree*/

//Dibuat oleh : Adinda
void printTree(nkAddr node, char tab[]);
/* Menampilkan tree pada program secara preorder*/

//Dibuat oleh : Adinda
void InsertPartner(nkAddr familyMember, pairAddr partner);
/* IS: familyMember sembarang, partner sudah dialokasi*/
/* FS: Menambahakn node partner ber-address partner pada node familyMember*/

//Dibuat oleh : Adinda
void InsertVPartner(struct nkTree *myTree);
/* Menambahkan node partner*/

//Dibuat oleh : Welsya
struct Queue *initQueue(int size);

//Dibuat oleh : Welsya
void enQueue(struct Queue *queue, nkAddr node);

//Dibuat oleh : Welsya
nkAddr deQueue(struct Queue *queue);

//Dibuat oleh : Welsya
void levelOrderTraversal(nkAddr root);

//Dibuat oleh : Adinda
void printFromFile(const char* location);
/* Menampilkan teks pada file yang terdapat pada location*/

//sumber : github
void gotoxy(int, int);

//Sumber : github
void loading_screen();
/*Menampilkan tulisan load*/

#endif

