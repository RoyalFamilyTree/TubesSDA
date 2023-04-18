#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "royalTree.h"

/*sumber referensi : modul MK SDA Praktik topik 9 Adt Non Binary Tree*/
void Create_Tree(nkTree *X){ //Create Non Binary Tree
	(*X).root=NULL;
}

boolean isEmpty(nkTree X){
	return (X.root==NULL);
}

nkAddr CreateNode (nkAddr parent, infoType name, int age, boolean gender){
	nkAddr newNode;
	newNode = (nkAddr) malloc(sizeof(nkTreeNode));

	if (newNode != Nil){
		fs(newNode) = Nil;
		nb(newNode) = Nil;
		parent(newNode) = Nil;
        strcpy(name(&info(newNode)), name);
		age(&info(newNode)) = age;
        gender(&info(newNode)) = gender;
		partner(newNode) = Nil;
	}
	return newNode;
}

pairAddr CreateNPartner (infoType name, int age, boolean gender){
	pairAddr newNode;
	newNode = (pairAddr) malloc(sizeof(nkPairNode));

	if (newNode != Nil){
		strcpy(name(&info(newNode)), name);
		age(&info(newNode)) = age;
		gender(&info(newNode)) = gender;
	}
	return newNode;
}

void DeleteNode(nkAddr *Node)
{
	fs(*Node)=Nil;
	fs(*Node)-=Nil;
	parent(*Node)=Nil;
	free(*Node);
}

nkAddr Search(nkAddr root, infoType src){
	nkAddr nSrc;
	if (root!=Nil){
        if (strcmp(name(&info(root)), src) == 0) {
			return root;
		}
		if(partner(root)!=Nil){
            if (strcmp(name(&info(partner(root))), src) == 0) {
				return root;
			}
		}
		nSrc=nkSearch(fs(root), src);
		if (nSrc==Nil)
			return nkSearch(nb(root),src);
		else
			return nSrc;
	}
	return Nil;
}

void insertMember(nkTree *tree, nkAddr parent, identity newIdentity){
    nkAddr newMember = (nkAddr) malloc(sizeof(nkTreeNode));
    newMember->fs = NULL;
    newMember->nb = NULL;
    newMember->parent = parent;
    newMember->info = newIdentity;
    newMember->partner = NULL;
    
    if (parent == NULL) { // jika parent kosong, maka newMember adalah root
        tree->root = newMember;
    } else { // jika parent tidak kosong, maka hubungkan newMember dengan parent
        if (parent->fs == NULL) {
            parent->fs = newMember;
        } else {
            nkAddr sibling = parent->fs;
            while (sibling->nb != NULL) {
                sibling = sibling->nb;
            }
            sibling->nb = newMember;
        }
    }
}

void InsertNode(nkTree *treeRoot, nkAddr newNode){
	nkAddr temp;
	/*Jika belum ada root*/
	if(parent(newNode)==Nil){
		treeRoot->root=newNode;
		return;
	}
	
	temp=parent(newNode);
	/*Jika tidak memiliki first son*/
	if(fs(temp)==Nil){
		fs(temp)=newNode;
		return;
	}
	
	/*Bandingkan prioritas fs dengan newNode*/
	temp=fs(temp);
	if(gender((&info)newNode)==MALE && gender((&info)temp)==FEMALE){
		nb(newNode) = fs(temp);
		fs(temp) = newNode;
		return;
	}
	
	if(gender((&info)newNode) ==  gender((&info)temp)){
		if(age((&info)newNode) > age((&info)temp) ){
			nb(newNode) = fs(temp)
			fs(temp) = newNode;
			return;
		}
	}
	
	/*Jika prioritas newNode lebih rendah daripada fs*/
	/*Jika newNode male*/
	if(gender((&info)newNode)==MALE){
		/*Travers hingga ketemu next brother yang umurnya lebih muda atau yang gendernya female*/
		while(nb(temp)!=Nil && gender(((&info)nb)temp) == MALE && age((&info)newNode) <= age(((&info)nb)temp)){
			temp = nb(temp);
		}
	}
	
	/*Jika newNode female*/
	if(gender((&info)newNode)==FEMALE){
		/*Travers selama next brother male, kemudian travers hingga menemukan next brother yang umurnya lebih muda*/
		while(nb(temp)!=Nil && gender(((&info)nb)temp) == MALE){
			temp=temp->nb;
		}
		while(nb(temp)!=Nil && age((&info)newNode) <= age(((&info)nb)temp)){
			temp=nb(temp);
		}
	}
	
	if(nb(temp)!=Nil){ /*Jika prioritas newNode berada di tengah*/
		nb(newNode) = nb(temp);
	    nb(temp) = newNode;
	    return;
	} 
	
	/*Jika prioritas newNode paling rendah*/
	nb(temp)=newNode;
}

void InsertPartner(nkAddr familyMember, pairAddr partner){
	partner(familyMember) = partner;
}

void InsertVPartner(nkTree *pTree){
	nkAddr srcNode;
	pairAddr partner;
	boolean gender;
	infoType name, partnerName;
	int age;

    /*Search node*/
    printf("\tUmur minimal untuk menikah adalah 18 tahun\n");
	do{
		printf("\n\t%c Nama anggota keluarga yang akan menikah: ", 175);
		scanf(" %[^\n]", &name);
        srcNode=Search((*pTree).root, name);
        if(srcNode == Nil){
			printf("\t[Anggota keluarga tidak ditemukan]\n");
		}else if(partner(srcNode)) != Nil){
			printf("\t[Menolak Keras poligami]\n");
		}else if(age((&info)srcNode) < 18){
			printf("\t[Anggota keluarga tersebut masih dibawah umur]\n");
		}else{
			break;
		}
	}while(1);

    /*Get gender*/
	if(gender(&info(srcNode)) == 0){
		gender = true;
	}else{
		gender = false;
	}

	/*Insert identitas partner*/
	do{
		printf("\n\t%c Masukan nama pasangan: ", 175);
		scanf(" %[^\n]", &partnerName);
		if(Search((*pTree).root, partnerName)!=NULL){ /*Check jika ada node yg memiliki nama yg sama di tree*/
			printf("\t[Nama orang tersebut sudah ada pada pohon keluarga]\n");
		}else{
			break;
		}
	}while(1);
	do{
		fflush(stdin);
		printf("\n\tUmur pasangan minimal 18 tahun\n");
		printf("\t%c Masukan umur pasangan: ", 175);
		scanf(" %d", &age);

		if(age < 18){
			printf("\t[Menolak Keras Pedofilia]\n");
		}else{
			break;
		}
	}while(true);

	/*Alokasi partner*/
	partner = CreateNPartner(partnerName, age, gender);

	/*Insert ke tree*/
	InsertPartner(srcNode, partner);
	printf("\n\t[Pasangan berhasil ditambahkan]");
	printf("\n\t semoga sakinnah mawaddah warrahmah");
	getch();
}

struct Queue *initQueue(int size) {
    struct Queue *queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->front = 0;
    queue->rear = 0;
    queue->size = size;
    queue->arr = (nkAddr*)malloc(size * sizeof(nkAddr));
    return queue;
}

void enQueue(struct Queue *queue, nkAddr node) {
    if (queue->rear == queue->size - 1) {
        printf("Queue is full");
        return;
    }
    queue->arr[queue->rear] = node;
    queue->rear++;
}

nkAddr deQueue(struct Queue *queue) {
    if (queue->front == queue->rear) {
        printf("Queue is empty");
        return NULL;
    }
    nkAddr node = queue->arr[queue->front];
    queue->front++;
    return node;
}

void levelOrderTraversal(nkAddr root) {
    if (root == NULL) return;

    // Inisialisasi queue
    struct Queue *queue = initQueue(1000);

    // Tambahkan root ke antrian
    enQueue(queue, root);

    while (queue->front != queue->rear) {
        // Hapus node dari queue kemudian print
        nkAddr node = deQueue(queue);
        printf("%s -> age : %d | gender : %d | married : %d\n", node->info.name, node->info.age, node->info.gender, node->info.married);

        // Tambahkan semua anak dari node ke antrian
        nkAddr child = node->fs;
        while (child != NULL) {
            enQueue(queue, child);
        	child = child->nb;
        }
    }
}
