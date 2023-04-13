#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "royalTree.h"

/*sumber referensi : modul MK SDA Praktik topik 9 Adt Non Binary Tree*/
void Create_Tree(nkTree *X){ //Create Non Binary Tree
	(*X).root=NULL;
}

boolean isEmpty(nkTree P){
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

void DeleteNode(nbAddr *Node)
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

void InsertPartner(nkAddr familyMember, pairAddr partner){
	partner(familyMember) = partner;
}

void InsertVPartner(nkTree *pTree){
	nkAddr srcNode;
	pairAddr partner;
	boolean gender;
	infoType name, partnerName;
	int age;

    printf("\tUmur minimal untuk menikah adalah 18 tahun\n");
	do{
		printf("\n\t%c Nama anggota keluarga yang akan menikah: ", 175);
		scanf(" %[^\n]", &name);
        srcNode=Search((*pTree).root, name);
