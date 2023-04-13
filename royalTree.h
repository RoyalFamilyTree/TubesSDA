#define kingdomTree_H

#include "boolean.h"

#define data(P) (P)->data
#define name(P) (P)->name
#define fs(P) (P)->fs
#define nb(P) (P)->nb
#define parent(P) (P)->pr
#define partner(P) (P)->Partner
#define age(P) (P)->age
#define gender(P) (P)->gender
#define married(P) (P)->married

/*Definisi akses component type */
#define info(P) (P)->info
#define next(P) (P)->next
#define Nil NULL

//Maksimal node yang dapat ditampung dalam array
#define jml_maks 50

/***************************/
/*  	  Type data        */
/***************************/

typedef char infoType;
typedef struct kingdomTree *nkAddr;
typedef struct pair *pairAddr;

typedef struct {
	infoType name;
	int age;
	bool gender;
	bool married;
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

/***************************/
/*  S P E S I F I K A S I  */
/***************************/

void Create_Tree(nkTree *X, int Jml_Node);
// Create Non Binary Tree sebanyak Jml_Node
// Tujuan mengentrykan Non Binary Tree ke array Isi_Tree dengan pola Level Order 
// Jml Node adalah banyaknya elemen dalam Tree yang menjadi parameter input

boolean isEmpty (nkTree P);
/* Mengirimkan true jika Isi_Tree KOSONG */

nkAddr CreateNode (nkAddr parent, infoType name, int age, bool gender, bool married);
/*Alokasi node*/

pairAddr CreateNPartner (infoType name, int age, bool gender, bool married);
/*Alokasi node partner*/

nkAddr Search(nkAddr root, intoType src);
/* Mencari apakah ada node dengan nbType src*/
/* Jika ada, mengirimkan address node tsb*/
/* Jika tidak ada, mengirimkan NULL*/

void insertPartner(nkAddr familyMember, pairAddr partner);
/* IS: familyMember sembarang, partner sudah dialokasi*/
/* FS: Menambahakn node partner ber-address partner pada node familyMember*/

void InsertVPartner(nkTree *myTree);
/* Menambahkan node partner*/


