//#ifndef royalTree_H
#define royalTree_H

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

void Create_Tree(struct nkTree *X);
// Tujuan mengentrykan Non Binary Tree ke array Isi_Tree dengan pola Level Order 
// Jml Node adalah banyaknya elemen dalam Tree yang menjadi parameter input

boolean isEmpty (struct nkTree X);
/* Mengirimkan true jika Isi_Tree KOSONG */

nkAddr CreateNode (nkAddr parent, infoType name, int age, boolean gender);
/*Alokasi node*/

pairAddr CreateNPartner (infoType name, int age, boolean gender);
/*Alokasi node partner*/

void DeleteNode(nkAddr *Node);
/*IS : Node terdefinisi*/
/*FS : Node dikembalikan ke sistem*/
/* Melakukan dealokasi node*/

nkAddr Search(nkAddr root, infoType src);
/* Mencari apakah ada node dengan infoType src*/
/* Jika ada, mengirimkan address node tsb*/
/* Jika tidak ada, mengirimkan NULL*/

void insertMember(struct nkTree *tree, nkAddr parent, identity newIdentity);
/* IS: tree sembarang, parent sembarang, newIdentity NULL */
/* FS: Menambahkan node baru yang menunjuk pada sebuah parent dan memiliki sebuah identitas */

void InsertNode(struct nkTree *treeRoot, nkAddr newNode);
/* IS: treeRoot sembarang, newNode sudah dialokasi*/
/* FS: Menambahkan node ber-address newNode pada tree*/

void insertPartner(nkAddr familyMember, pairAddr partner);
/* IS: familyMember sembarang, partner sudah dialokasi*/
/* FS: Menambahakn node partner ber-address partner pada node familyMember*/

void InsertVPartner(struct nkTree *myTree);
/* Menambahkan node partner*/

nkAddr Search(nkAddr root, infoType src);
/* Mencari apakah ada node dengan nkType src*/
/* Jika ada, mengirimkan address node tsb*/
/* Jika tidak ada, mengirimkan NULL*/

struct Queue *initQueue(int size);

void enQueue(struct Queue *queue, nkAddr node);

nkAddr deQueue(struct Queue *queue);

void levelOrderTraversal(nkAddr root);
