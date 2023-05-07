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

//Sumber : Tugas Program Struktur Non Binary Tree SDA-P
void Create_Tree(struct nkTree *X);
// Membuat tree kosong

/**** Manajemen Memory ****/
/*Penambahan tipe data*/

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
void InputMember(struct nkTree *pTree);
/* IS: pTREE tidak kosong*/
/* FS: Meminta input identitas node dari user, mengalokasi node dan menambahkan node tsb kedalam tree*/
/* Menambahkan node anggota keluarga*/

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

//Dibuat oleh : Adinda
void Upgrade(nkAddr *root);
/* IS: Pointer "root" menunjuk ke alamat suatu objek nkAddr yang mungkin berisi data*/
/* FS: fungsi "Upgrade" telah melakukan pembaruan pada struktur data yang ditunjuk oleh "root" dengan mengatur 
       nilai pointer "fs" dan "parent" pada elemen-elemen yang terlibat dalam iterasi*/ 

//Dibuat oleh : Fikri
//Modifikasi oleh : Adinda
void deleteNode(nkAddr *pDel, struct nkTree *pTree);
/* IS: node member dengan info sembarang tersedia/tidak tersedia */
/* FS: apabila node member dengan info sembarang tersedia, maka akan terhapus. apabila tidak tersedia, muncul output "nama anggota tidak tersedia"*/

/**** PROSES SEMUA NODE TREE  ****/
//Dibuat oleh : Welsya
struct Queue *initQueue(int size);
/* IS : queue belum dialokasikan dan masih bernilai sembarang */
/* FS : terbentuk queue yang sudah diinisialisasi kosong */

//Dibuat oleh : Welsya
void enQueue(struct Queue *queue, nkAddr node);
/* IS : queue masih kosong, node-node terdefinisi */
/* FS : node per level masuk ke dalam queue */

//Dibuat oleh : Welsya
nkAddr deQueue(struct Queue *queue);
/* IS : node masih berada di dalam antrian */
/* FS : node dikeluarkan dari queue kemudian mengembalikan node baru */

//Dibuat oleh : Welsya
void levelOrderTraversal(nkAddr root);
/* IS : node-node terdefinisi */
/* FS : menampilkan node atau silsilah kerajaan secara level order, disertai perhitungan generasi */

//Dibuat oleh : Welsya
void nextKing(nkAddr root);
/* IS: Silsilah sudah terisi ataupun kosong */
/* FS: Ditampilkan nama-nama anggota kerajaan yang merupakan penerus takhta */

//Dibuat oleh : Adinda
int GetNodeDegree(nkAddr node);
/*Mengirimkan nilai degree dari suatu node*/

//Dibuat oleh : Adinda
void printNodeInfo(nkAddr node, infoType name);
/* IS: node sembarang, name sama dengan node->info.name atau node->partner->info.name*/
/* FS: Menampilkan nama, umur, jenis kelamin, orang tua, saudara, dan anak dari node jika atribut tersebut ada*/

//Dibuat oleh : Adinda
void TimeSkip(nkAddr node, int year);
/* Rekursif untuk menambahkan node->info.age dengan year pada setiap node */

//Dibuat oleh : Adinda
void ProceedTimeSkip(nkAddr *root, int year);
/* Process eksekusi dan passing address kepada node untuk menambahkan node->info.age dengan year*/

//sumber : github
void gotoxy(int, int);
//Memindahkan kursor ke posisi tertentu di layar 

//Sumber : github
void loading_screen();
/*Menampilkan tulisan loading*/

//Dibuat oleh : Adinda
void printFromFile(const char* location);
/* Menampilkan teks pada file yang terdapat pada location*/



#endif


