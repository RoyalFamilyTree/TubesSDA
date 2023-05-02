#include "royalTree.h"

/*sumber referensi : modul MK SDA Praktik topik 9 Adt Non Binary Tree*/
void Create_Tree(struct nkTree *X){ //Create Non Binary Tree
	(*X).root=NULL;
}

boolean isFileEmpty(){
	FILE *file = fopen("KingdomMember.txt", "r");
	boolean isEmpty = true;
	
	if(file){
		//file berhasil dibuka
		fseek(file, 0, SEEK_END);
		if(ftell(file) > 0){
			// file tidak kosong
			isEmpty = false;
		}
		fclose(file);
	}
	return isEmpty;
}

void getKingdomFromFile(struct nkTree *pTree) {
	const char* filename = "KingdomMember.txt";
    FILE *fp;
    char line[100];

    // Membuka file dengan mode read
    fp = fopen(filename, "r");

    // Cek apakah file berhasil dibuka
    if (fp == NULL) {
        printf("Error: Tidak dapat membuka file %s\n", filename);
        exit(1);
    }

    // Membaca data dari file secara baris per baris
    while (fgets(line, sizeof(line), fp) != NULL) {
        // Membuat variabel temporary untuk menyimpan data yang telah diparse dari string
        char name[50], parentName[50], gender[10];
        int age;

        // Memparse baris ke dalam variabel temporary
        sscanf(line, "%[^,],%d,%[^,],%[^\n]", name, &age, parentName, gender);

        // Mengubah gender ke dalam bentuk boolean
        boolean isMale = (strcmp(gender, "male") == 1);

        // Mencari node parent
        nkAddr parentNode = Search((*pTree).root, parentName);

        // Membuat node baru dengan data yang telah diparse
        nkAddr newNode = CreateNode(parentNode, name, age, isMale);

        // Memasukkan node baru ke dalam pohon keluarga
        InsertNode(pTree, newNode);
    }

    // Menutup file setelah selesai membaca
    fclose(fp);
}

boolean isEmpty(struct nkTree X){
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

void DeallocNode(nkAddr *Node)
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
		searchNode=Search(root->fs,src);
		if (searchNode==NULL)
			return Search(root->nb,src);
		else
			return searchNode;
	}
	return NULL;
}

void getDataFromFile(struct nkTree *pTree){
	nkAddr king;
	pairAddr partner;
    infoType name, partnerName;
    int age, partnerAge, temp, partnerTemp;
    boolean gender, partnerGender;
    FILE *file = fopen("KingdomMember.txt", "r");
    
    if (file == NULL) {
//        printf("File tidak dapat dibuka!\n");
        exit(1);
    }
    
    fscanf(file, "NULL, %[^,],%d,%d -> %[^,],%d,%d", name, &age, &temp, partnerName, &partnerAge, &partnerTemp);
    gender = (temp == 1);
    partnerGender = (partnerTemp == 1);
    
    king = CreateNode(NULL, name, age, gender);
    partner = CreateNPartner(partnerName, partnerAge, partnerGender);
    
    InsertNode(pTree, king);
    InsertPartner(king, partner);
    
    fclose(file);
}


void InsertKing(struct nkTree *pTree){
	nkAddr king;
	infoType name;
	int age, temp;
	boolean gender;
	FILE *file = fopen("KingdomMember.txt", "w");
	
	if (file == NULL) {
	    printf("File tidak dapat dibuka!\n");
	    return 1;
	}
	
	/*Input nama*/
	printf("\n\tMasukan Identitas Raja / Ratu:\n");
	printf("\n\t%c Nama: ", 175);
	scanf(" %[^\n]", &name);
	/*Insert jenis kelamin*/
	do{
		printf("\n\t%c Pilih jenis kelamin\n", 175);
		printf("\t  0. Wanita\n");
		printf("\t  1. Pria\n");
		printf("\t  Pilihan: ");
		scanf(" %d", &temp);
		if(temp != 0 && temp != 1){
			printf("\t[x] INPUT TIDAK VALID ! [x]\n");
		}else{
			gender = temp;
			break;
		}
	}while(1);
	/*Insert umur raja atau ratu*/
	do{
		printf("\n\t%c Umur (Minimal 50 tahun maksimal 79 tahun): ", 175);
		scanf(" %d", &age);
		if(age < 50 || age >=80){
			printf("\t[x] INPUT TIDAK VALID ! [x]\n");
		}
	}while(age < 50 || age >=80);

	/*Alokasi node*/
	king = CreateNode(NULL, name, age, gender);

	/*Insert ke tree*/
	InsertNode(pTree, king);
	printf("\n\t[o] Raja/ ratu berhasil ditambahkan [o]");
	
	
	fprintf(file, "NULL, %s, %d, %d", name, age, gender);
	fclose(file);
	getch();
}

void InsertVPartner(struct nkTree *pTree){
    nkAddr srcNode;
    pairAddr partner;
    boolean gender;
    infoType name, partnerName;
    int age;
    FILE *file = fopen("KingdomMember.txt", "a");
    
    /*Search node*/
    printf("\n\n\tMasukan 'q' untuk kembali\n");
    printf("\tUmur minimal untuk menikah adalah 18 tahun\n");
    do{
        printf("\n\t%c Nama anggota keluarga yang akan menikah: ", 175);
        scanf(" %[^\n]", &name);
        if(strcmp(name, "q")==0){
            return;
        }
        srcNode=Search((*pTree).root, name);

        if(srcNode == NULL){
            printf("\t[x] Anggota keluarga tidak ditemukan [x]\n");
        }else if(srcNode->partner != NULL){
            printf("\t[x] Anggota keluarga tersebut sudah memiliki pasangan [x]\n");
        }else if(srcNode->info.age < 18){
            printf("\t[x] Anggota keluarga tersebut masih dibawah umur [x]\n");
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
            printf("\t[x] Nama orang tersebut sudah ada pada pohon keluarga [x]\n");
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
            printf("\t[x] Pasangan masih dibawah umur [x]\n");
        }else{
            break;
        }
    }while(true);
    
    /*Alokasi partner*/
    partner = CreateNPartner(partnerName, age, gender);

    /*Insert ke tree*/
    InsertPartner(srcNode, partner);
    system("cls");
    printFromFile("ilustrasi/wedding.txt");
    printf("\n\tPress any key to continue . . . ");
    getch();
    
    /*Write to file*/
    fprintf(file, " -> %s, %d, %d", partnerName, age, gender);
    fclose(file);
}


void InputMember(struct nkTree *pTree){
    nkAddr parentNode, newNode;

    // Menerima input dari pengguna untuk membuat node baru
    int temp;
	int age; 
	boolean gender;
    infoType name, parentName;
    FILE *file = fopen("KingdomMember.txt", "a");
    
    /*cari parent*/
    printf("\n\tMasukan 'q' untuk kembali\n");
	do{
		printf("\n\t%c Nama orang tua: ", 175);
		scanf(" %[^\n]", &parentName);
		if(strcmp(parentName, "q")==0){
			return;
		}
		parentNode = Search((*pTree).root, parentName);
		if(parentNode == NULL){
			printf("\t[x] Nama orang tua tidak ditemukan [x]\n");
		}else if(parentNode->partner == NULL){
			printf("\t[x] Orang tersebut tidak memiliki pasangan [x]\n");
		}else{
			break;
		}
	}while(1);
    	
    /*Input nama*/
	do{
		printf("\n\t%c Masukan nama: ", 175);
		scanf(" %[^\n]", &name);
		if(Search((*pTree).root, name)!=NULL){ /*Check jika ada node yg memiliki nama yg sama di tree*/
			printf("\t[x] Nama orang tersebut sudah ada pada pohon keluarga [x]\n");
		}else{
			break;
		}
	}while(1);
	
	/*Input usia*/
	do{
		printf("\n\tUmur anak minimal 19 tahun lebih muda dari kedua orang tua\n");
		printf("\n\t%c Masukan umur: ", 175);
		scanf(" %d", &age);
		if(age >= 1 && age <= parentNode->info.age - 19 && age <= parentNode->partner->info.age - 19){ //Umur minimal 19 tahun lebih muda dari parent
			break;
		}else{
			printf("\t[x] INPUT TIDAK VALID ! [x]\n");
		}
	}while(1);
   	
	/*Input jenis kelamin*/
	do{
		printf("\n\t%c Pilih jenis kelamin\n", 175);
		printf("\t  0. Wanita\n");
		printf("\t  1. Pria\n");
		printf("\t  Pilihan: ");
		scanf(" %d", &temp);
		if(temp != 0 && temp != 1){
		printf("\t[x] INPUT TIDAK VALID ! [x]\n");
		}else{
			gender = temp;
			break;
		}
	}while(1);
	
     /* Membuat node baru dengan data yang diterima dari pengguna */
	newNode = CreateNode(parentNode, name, age, gender);
	 /* Write newNode ke file txt*/
	fprintf(file, "\n%s, %s, %d, %d", parentName, name, age, gender);

    // Memasukkan node baru ke dalam pohon
    InsertNode(pTree, newNode);
    printf("\n\t[o] Anggota keluarga berhasil ditambahkan [o]");
 	fclose(file);
	getch();
}

void InsertNode(struct nkTree *treeRoot, nkAddr newNode){
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
	/*Cari posisi terakhir pada list anak*/
	temp=temp->fs;
	while(temp->nb != NULL) {
		temp = temp->nb;
	}
	
	temp->nb = newNode;
}

void InsertPartner(nkAddr familyMember, pairAddr partner){
	familyMember->partner = partner;
}

//nkAddr FindParent(nkAddr root, nkAddr node) {
//    if (root == NULL || root == node) {
//        return NULL;
//    }
//    if (root->fs == node || root->nb == node) {
//        return root;
//    }
//    nkAddr parent = FindParent(root->fs, node);
//    if (parent != NULL) {
//        return parent;
//    }
//    return FindParent(root->nb, node);
//}
//
//nkAddr FindSuccessor(nkAddr root, nkAddr node) {
//    nkAddr current = node->fs;
//    while (current != NULL && current->nb != NULL) {
//        current = current->nb;
//    }
//    return current;
//}
//
//void DeleteNode(nkAddr root) {
//	infoType target;
//	
//	printf("Ketik nama anggota yang akan dihapus: ");
//	scanf("%s", &target);
//	
//    nkAddr parent = NULL;
//    nkAddr node = Search(root, target);
//    
//    // If target node not found, return
//    if (node == NULL) {
//        return;
//    }
//    
//    // Find parent node of the target node
//    if (node != root) {
//        parent = FindParent(root, node);
//    }
//    
//    // If target node has no child nodes
//    if (node->fs == NULL && node->nb == NULL) {
//        // If the target node is the root node
//        if (node == root) {
//            DeallocNode(&node);
//            root = NULL;
//            return;
//        }
//        // If the target node is a child node
//        if (node == parent->fs) {
//            parent->fs = NULL;
//        } else {
//            parent->nb = NULL;
//        }
//        DeallocNode(&node);
//        return;
//    }
//    
//    // If target node has only one child node
//    if (node->fs != NULL && node->nb == NULL) {
//        // If the target node is the root node
//        if (node == root) {
//            nkAddr temp = node->fs;
//            DeallocNode(&node);
//            root = temp;
//            return;
//        }
//        // If the target node is a child node
//        if (node == parent->fs) {
//            parent->fs = node->fs;
//        } else {
//            parent->nb = node->fs;
//        }
//        DeallocNode(&node);
//        return;
//    }
//    if (node->fs == NULL && node->nb != NULL) {
//        // If the target node is the root node
//        if (node == root) {
//            nkAddr temp = node->nb;
//            DeallocNode(&node);
//            root = temp;
//            return;
//        }
//        // If the target node is a child node
//        if (node == parent->fs) {
//            parent->fs = node->nb;
//        } else {
//            parent->nb = node->nb;
//        }
//        DeallocNode(&node);
//        return;
//    }
//    
//    // If target node has two child nodes
//    nkAddr successor = FindSuccessor(root, node);
//    nkAddr successorParent = FindParent(root, successor);
//    // Copy successor's info to target node
//    node->info = successor->info;
//    // Remove successor node from the tree
//    if (successor == successorParent->fs) {
//        successorParent->fs = successor->nb;
//    } else {
//        nkAddr temp = successor->nb;
//        successorParent->nb = temp;
//    }
//    DeallocNode(&successor);
//}

void Upgrade(nkAddr *root){
	nkAddr temp;
	temp= (*root)->nb;
	if ((*root)->fs==NULL)
		(*root)->fs=temp;
	while(temp!=NULL){
		temp->parent= *root;
		temp=temp->nb;
	}
}

void deleteNode(nkAddr *pDel, struct nkTree *pTree){
	nkAddr pCur;
	pCur=*pDel;

	if((*pTree).root == NULL) //kondisi ketika root kosong
	{
		printf("Tree Kosong");
		return;
	}
	//kondisi node merupakan leaf dan jika merupakan first son maka next brothernya menjadi first son
	if(pCur->fs == NULL)
	{
		if(pCur->parent->fs == pCur) //kondisi ketika node merupakan anak pertama dari parent
		{
			if(pCur->nb != NULL) //ketika first son memiliki sibling
				pCur->parent->fs = pCur->nb;
			else
				pCur->parent->fs = NULL;
			DeallocNode(&(*pDel));
		}else //kondisi ketika node bukan merupakan anak pertama
		{
			pCur = pCur->parent->fs; //pCur ditunjuk ke anak pertama
			while(pCur->nb != *pDel) //pencarian node sebelum pDel
				pCur = pCur->nb;
			if((*pDel)->nb == NULL) //kondisi ketika pDel merupakan last son
			{
				pCur->nb = NULL;
				DeallocNode(&(*pDel));
			}
			else //kondisi ketika pDel bukan merupakan last son
			{
                pCur->nb = (*pDel)->nb;
				DeallocNode(&(*pDel));
			}
		}
		return;
	}
	else //kondisi node memiliki child
	{
		while( pCur->fs!=NULL )
			pCur = pCur->fs; // pcur diisi dengan First son sampai null
		while (pCur != *pDel){
			Upgrade(&pCur);
			if (pCur->parent!=NULL)
				pCur->nb=pCur->parent->nb;
			else
				pCur->nb=NULL;
			pCur= pCur->parent;
		}

		pCur = *pDel;
		if(pCur->parent != NULL ) // ketika node memiliki parent
		{
			if(pCur->parent->fs == *pDel) //kondisi node merupakan first son dari parentnya
			{
				pCur->parent->fs=pCur->fs;
				pCur->fs->parent = pCur->parent;
				DeallocNode(&(*pDel));
			}else //kondisi node bukan merupakan first son
			{
				pCur = (*pDel)->parent->fs;
				while(pCur->nb != *pDel) //pencarian node sebelum pDel
					pCur = pCur->nb;
				pCur->nb = (*pDel)->fs;
				if((*pDel)->nb == NULL)
					(*pDel)->fs->nb = NULL;
				else
					(*pDel)->fs->nb = (*pDel)->nb;
				DeallocNode(&(*pDel));
			}
			return;
		}
		else //kondisi ketika yang dihapus merupakan root
		{
			(*pTree).root = pCur->fs	;
			(*pTree).root->parent = NULL;
			DeallocNode(&(*pDel));
//			system("PAUSE");
		}
		printf("berhasil dihapus");
		system("PAUSE");
	}
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
        printf("[x] Queue is full [x]");
        return;
    }
    queue->arr[queue->rear] = node;
    queue->rear++;
}

nkAddr deQueue(struct Queue *queue) {
    if (queue->front == queue->rear) {
        printf("[x] Queue is empty [x]");
        return NULL;
    }
    nkAddr node = queue->arr[queue->front];
    queue->front++;
    return node;
}

void nextKing(nkAddr root) {
	int i, x, y;
	
    if (root == NULL) {
    	printf("\n[x] Belum ada silsilah [x]\n\n");
    	system("Pause");
        return;
    }
	gotoxy(38, 4); printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"); 
    gotoxy(38, 5); printf("        Penerus Takhta        \n"); 
    gotoxy(38, 6); printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"); 

    // Lakukan pengecekan setiap node di dalam tree
    nkAddr current = root;
    if(current->fs == NULL) {
    	gotoxy(32, 10); printf("[x] Raja/Ratu belum memiliki keturunan [x]\n\n");
    	system("Pause");
    	return;
	}
	x = 40; y = 8; i = 1;
    while (current != NULL) {
        if (current->fs != NULL) {
            gotoxy(x, y); printf("%d. %s (First Son of %s)\n", i, current->fs->info.name, current->fs->parent->info.name);
        }
        
        // Jika first son tidak mempunyai anak lagi, tampilkan next brothernya
        if (current->fs->fs == NULL) {
        	current = current->fs;
        	while (current->nb != NULL) {
	        	y++;
	        	i++;
	            gotoxy(x, y); printf("%d. %s (Next Brother of %s)\n", i, current->nb->info.name, current->info.name);
	            current = current->nb;
        	}
		}
        
        // Pindah ke node berikutnya 
        if (current->fs != NULL) {
            current = current->fs;
        } else if (current->nb != NULL) {
            current = current->nb;
        } else {
            while (current != NULL && current->nb == NULL) {
                current = current->parent;
                getchar();
            }

            if (current != NULL) {
                current = current->nb;
            }
        }
        i++;
        y++;
        
//        system("Pause");
		getchar();
    }
     
    
    if (current == NULL) {
    	printf("\n");
    	system("Pause");
	}
}
    

void levelOrderTraversal(nkAddr root) {
    if (root == NULL) return;

    // Inisialisasi queue
    struct Queue *queue = initQueue(1000);
	
    // Tambahkan root ke antrian
    enQueue(queue, root);
    
    // Inisialisasi variabel level dan gotoxy
    int level = 1;
    
    while (queue->front != queue->rear) {
        // Cetak level
        printf("\t\tGenerasi %d :\n", level);
        int i;
        // Tambahkan semua node pada level ini ke antrian
        int levelSize = queue->rear - queue->front; // levelSize diisi oleh ukuran queue
        for (i = 0; i < levelSize; i++) {
        	nkAddr node = deQueue(queue);
            if (node->partner == NULL) {
				printf("[%s] -> (%d) (%s) x [Belum ada partner]\n", node->info.name, node->info.age, node->info.gender ? "P" : "W");
        	} else { // Jika sudah memiliki pasangan maka tampilkan beserta pasangannya
				printf("[%s] -> (%d) (%s) x [%s] -> (%d) (%s)\n", node->info.name, node->info.age, node->info.gender ? "P" : "W", node->partner->info.name, node->partner->info.age, node->partner->info.gender ? "P" : "W");
			}
			
            // Tambahkan semua anak dari node ke antrian
            nkAddr child = node->fs;
            while (child != NULL) {
                enQueue(queue, child);
                child = child->nb;
            }
        }
        printf("\n");	
        // Naikkan level
        level++;
    }
}


//int Depth (nkAddr P){
//    if (P == NULL) {
//        return 0;
//    } else {
//        int max_depth = -1;
//        nkAddr child;
//        for (child = P->fs; child != NULL; child = child->nb) {
//            int current_depth = Depth(child);
//            if (current_depth > max_depth) {
//                max_depth = current_depth;
//            }
//        }
//        return max_depth + 1;
//    }
//}

void printTree(nkAddr node, char tab[]) {
    char newTab[255];
    strcpy(newTab, tab);
    strcat(newTab, "-");
    
    if (node != NULL) {
        if (node->partner != NULL) {
            printf("\t\t\t\t\t%s%s [%d] [%s] x %s [%d] [%s]\n", tab, &(node->info.name), node->info.age, node->info.gender ? "P" : "W", &(node->partner->info.name), node->partner->info.age, node->partner->info.gender ? "P" : "W");
        } else {
            printf("\t\t\t\t\t%s%s [%d] [%s]\n", tab, &(node->info.name), node->info.age, node->info.gender ? "P" : "W");
        }
        printTree(node->fs, newTab);
        printTree(node->nb, tab);
    }
}

int GetNodeDegree(nkAddr node){
	if(node != NULL){
		nkAddr temp;
		int count;
		if(node->fs == NULL)
			return 0;
		temp = node->fs;
		while(temp != NULL){
			count++;
			temp = temp->nb;
		}
		return count;
	}
	return 0;
}

void printNodeInfo(nkAddr node, infoType name){
	nkAddr temp;
	int count=1;

	if(node->partner != NULL){
		if(strcmp(node->partner->info.name, name)==0){ //Jika search nama partner
			printf("\t%c Umur: %d\n", 175, node->partner->info.age);
			printf("\t%c Jenis kelamin: %s\n", 175, node->partner->info.gender ? "Pria" : "Wanita");
			printf("\t%c %s: %s\n", 175, node->partner->info.gender ? "Istri" : "Suami", &(node->info.name));
		}
	}

	if(strcmp(node->info.name, name)==0){
		printf("\t%c Umur: %d\n", 175, node->info.age);
		printf("\t%c Jenis kelamin: %s\n", 175, node->info.gender ? "Pria" : "Wanita");
		if(node->partner!=NULL)
			printf("\t%c %s: %s\n", 175, node->info.gender ? "Istri" : "Suami", &(node->partner->info.name));
		if(node->parent!=NULL)
			printf("\t%c Predecessor: %s dan %s\n", 175, &(node->parent->info.name), &(node->parent->partner->info.name));
		else
			printf("\t%c %s adalah %s\n", 175, &(node->info.name), node->info.gender ? "raja" : "ratu");
		if(GetNodeDegree(node->parent)>1){
			printf("\t%c Saudara/ saudari:\n", 175);
			temp = node->parent->fs;
			while(temp!=NULL){
				if(strcmp(node->info.name, temp->info.name) != 0){
					printf("\t  %d. %s\n", count, &(temp->info.name));
					count++;
				}
				temp = temp ->nb;
			}
			count=1;
		}
	}

	if(node->fs!=NULL){
		printf("\t%c Successor:\n", 175);
		temp = node->fs;
		while(temp!=NULL){
			printf("\t  %d. %s\n", count, &(temp->info.name));
			temp = temp->nb;
			count++;
		}
	}

}

void gotoxy(int X, int y) {
	COORD coord;
	coord.X = X;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void loading_screen() {
	int i;
	gotoxy(50, 10); printf("Loading...");
	gotoxy(50, 12);
	for (i = 0; i <= 17; i++) {
		Sleep(90);
		printf("%c", 177);
	}
	printf("\n\n");
	system("pause");
	system("cls");
}

void printFromFile(const char* location){
	FILE *read;
	char c;

	read=fopen(location, "rt");
	while((c=fgetc(read))!=EOF){
		printf("%c", c);
	}

	fclose(read);
}

void TimeSkip(nkAddr node, int year){
	if (node!=NULL){
		if(node->partner != NULL){
            node->info.age += year;
			node->partner->info.age += year;
		}else{
			node->info.age += year;
		}
		TimeSkip(node->fs,year);
		TimeSkip(node->nb,year);
	}
}

void ProceedTimeSkip(nkAddr *root, int year)
{
    TimeSkip(*root,year);
}

