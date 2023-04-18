#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "royalTree.h"

/*sumber referensi : modul MK SDA Praktik topik 9 Adt Non Binary Tree*/
void Create_Tree(struct nkTree *X){ //Create Non Binary Tree
	(*X).root=NULL;
}

boolean isEmpty(nkTree X){
	return (X.root==NULL);
}

nkAddr CreateNode (nkAddr parent, infoType name, int age, boolean gender){
	nkAddr newNode;
	newNode = (nkAddr) malloc(sizeof(nkTreeNode));

	if (newNode != NULL){
		newNode->fs=NULL;
		newNode->nb=NULL;
		newNode->parent=parent;
		strcpy(newNode->info.name, name);
		newNode->info.age=age;
		newNode->info.gender=gender;
		newNode->partner=NULL;
	}
	return newNode;
}

pairAddr CreateNPartner (infoType name, int age, boolean gender){
	pairAddr newNode;
	newNode = (pairAddr) malloc(sizeof(nkPairNode));

	if (newNode != NULL){
		strcpy(newNode->info.name, name);
		newNode->info.age = age;
		newNode->info.gender = gender;
	}
	return newNode;
}

void DeleteNode(nkAddr *Node)
{
	(*Node)->fs=NULL;
	(*Node)->fs=NULL;
	(*Node)->parent=NULL;
	free(*Node);
}

nkAddr Search(nkAddr root, infoType src){
	nkAddr searchNode;
	if (root!=NULL){
		if (strcmp(root->info.name, src)==0){
			return root;
		}
		if(root->partner!=NULL){
			if(strcmp(root->partner->info.name, src)==0){
				return root;
			}
		}
		nSrc=Search(root->fs,src);
		if (searchNode==NULL)
			return Search(root->nb,src);
		else
			return searchNode;
	}
	return NULL;
}

void insertMember(struct nkTree *tree, nkAddr parent, identity newIdentity){
    nkAddr newMember = (nkAddr) malloc(sizeof(nkTreeNode));
    newMember->fs = NULL;
    newMember->nb = NULL;
    newMember->parent = parent;
    newMember->info = newIdentity;
    newMember->partner = NULL;
    
    if (parent == NULL) { // jika parent kosong, maka newMember adalah root
        tree->root = newMember;
    } else { // jika parent tidak kosong, maka hubungkan newMember dengan parent
        if (parent->partner == NULL) {
			printf("\nyakali jomblo pengen punya anak\n");
        } if (parent->fs == NULL && parent->info.age == 19 && parent->partner != NULL)
		{
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
	if(newNode->parent==NULL){
		treeRoot->root=newNode;
		return;
	}
	
	temp=newNode->parent;
	/*Jika tidak memiliki first son*/
	if(temp->fs==NULL){
		temp->fs=newNode;
		return;
	}
	
	/*Bandingkan prioritas fs dengan newNode*/
	temp=temp->fs;
	if(newNode->info.gender==MALE && temp->info.gender==FEMALE){
		newNode->nb = temp->fs;
		temp->fs = newNode;
		return;
	}
	
	if(newNode->info.gender == temp->info.gender){
		if(newNode->info.age > temp->info.age){
			newNode->nb = temp->fs;
			temp->fs = newNode;
			return;
		}
	}
	
	/*Jika prioritas newNode lebih rendah daripada fs*/
	/*Jika newNode male*/
	if(newNode->info.gender==MALE){
		/*Travers hingga ketemu next brother yang umurnya lebih muda atau yang gendernya female*/
		while(temp->nb!=NULL && temp->nb->info.gender == MALE && newNode->info.age <= temp->nb->info.age){
			temp = temp->nb;
		}
	}
	
	/*Jika newNode female*/
	if(newNode->info.gender==FEMALE){
		/*Travers selama next brother male, kemudian travers hingga menemukan next brother yang umurnya lebih muda*/
		while(temp->nb!=NULL && temp->nb->info.gender == MALE){
			temp=temp->nb;
		}
		while(temp->nb!=NULL && newNode->info.age <= temp->nb->info.age){
			temp=temp->nb;
		}
	}
	
	if(temp->nb!=NULL){ /*Jika prioritas newNode berada di tengah*/
		newNode->nb = temp->nb;
	    temp->nb = newNode;
	    return;
	} 
	
	/*Jika prioritas newNode paling rendah*/
	temp->nb=newNode;
}

void InsertPartner(nkAddr familyMember, pairAddr partner){
	familyMember->partner = partner;
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

		if(srcNode == NULL){
			printf("\t[x] Anggota keluarga tidak ditemukan\n");
		}else if(srcNode->partner != NULL){
			printf("\t[x] Anggota keluarga tersebut sudah memiliki pasangan\n");
		}else if(srcNode->info.age < 18){
			printf("\t[x] Anggota keluarga tersebut masih dibawah umur\n");
		}else{
			break;
		}
	}while(1);

	/*Get gender*/
	if(srcNode->info.gender == 0){
		gender = true;
	}else{
		gender = false;
	}

	/*Insert identitas partner*/
	do{
		printf("\n\t%c Masukan nama pasangan: ", 175);
		scanf(" %[^\n]", &partnerName);
		if(Search((*pTree).root, partnerName)!=NULL){ /*Check jika ada node yg memiliki nama yg sama di tree*/
			printf("\t[x] Nama orang tersebut sudah ada pada pohon keluarga\n");
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
			printf("\t[x] Pasangan masih dibawah umur\n");
		}else{
			break;
		}
	}while(true);

	/*Alokasi partner*/
	partner = CreateNPartner(partnerName, age, gender);

	/*Insert ke tree*/
	InsertPartner(srcNode, partner);
	printf("\n\t[o] Pasangan berhasil ditambahkan");
	getch();
}
	


