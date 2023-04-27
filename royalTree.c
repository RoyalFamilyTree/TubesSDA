
#include "royalTree.h"

/*sumber referensi : modul MK SDA Praktik topik 9 Adt Non Binary Tree*/
void Create_Tree(struct nkTree *X){ //Create Non Binary Tree
	(*X).root=NULL;
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

void InputMember(){
	struct nkTree tree;
    tree.root = NULL;

    // Menerima input dari pengguna untuk membuat node baru
    int age, gender;
    infoType name;
    printf("Masukkan data node baru:\n");
    printf("Nama: ");
    scanf("%s", &name);
    printf("Usia: ");
    scanf("%d", &age);
    printf("Jenis Kelamin (1 untuk Laki-laki, 0 untuk Perempuan): ");
    scanf("%d", &gender);

    // Membuat node baru dengan data yang diterima dari pengguna
    nkAddr newNode = (nkAddr)malloc(sizeof(nkAddr));
    strcpy(newNode->info.name, name);
    newNode->info.age = age;
    newNode->info.gender = gender == 1 ? MALE : FEMALE;
    newNode->parent = NULL;
    newNode->fs = NULL;
    newNode->nb = NULL;

    // Memasukkan node baru ke dalam pohon
    InsertNode(&tree, newNode);
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

void InsertVPartner(struct nkTree *pTree){
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

void nextKing(nkAddr root) {
    if (root == NULL) {
        return;
    }

    printf("Penerus Takhta:\n"); 

    // Lakukan pengecekan setiap node di dalam tree
    nkAddr current = root;
    while (current != NULL) {
        // Jika memiliki first son, maka print informasi first son tersebut
        if (current->fs != NULL) {
            printf("- %s\n", current->fs->info.name);
        }

        // Pindah ke node berikutnya (preOrder traversal)
        if (current->fs != NULL) {
            current = current->fs;
        } else if (current->nb != NULL) {
            current = current->nb;
        } else {
            while (current != NULL && current->nb == NULL) {
                current = current->parent;
            }

            if (current != NULL) {
                current = current->nb;
            }
        }
    }
}

void levelOrderTraversal(nkAddr root) {
    if (root == NULL) return;

    // Inisialisasi queue
    struct Queue *queue = initQueue(1000);
	
	nkAddr node = deQueue(queue);
	
    // Tambahkan root ke antrian
    enQueue(queue, root);
    
    // Inisialisasi variabel level dan gotoxy
    int level = 1;
    
    while (queue->front != queue->rear) {
        // Cetak level
        printf("Generasi %d:\n", level);
        int i;
        // Tambahkan semua node pada level ini ke antrian
        int levelSize = queue->rear - queue->front; // levelSize diisi oleh ukuran queue
        for (i = 0; i < levelSize; i++) {
            if (node->partner == NULL) {
				printf("------------------------------------\n");
				printf("|  [%s] -> age : %d , gender : %d  |-----> Belum ada partner :(\n", node->info.name, node->info.age, node->info.gender);
				printf("------------------------------------\n");
        	} else { // Jika sudah memiliki pasangan maka tampilkan beserta pasangannya
				printf("------------------------------------\n");
				printf("|  [%s] -> age : %d , gender : %d  |----->\n", node->info.name, node->info.age, node->info.gender);
				printf("------------------------------------\n");
	            
				printf("------------------------------------\n");
				printf("|  [%s] -> age : %d , gender : %d  |\n", node->partner->info.name, node->partner->info.age, node->partner->info.gender);
				printf("------------------------------------\n");
        		
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

int getGeneration(nkAddr root, infoType x) {
    if (root == NULL) {
        return -1;
    }

    int level = 1;
    nkAddr currentNode = root;
    if (currentNode->info.name == x) {
    	return level;
    	level++;
	}
	level++;
    while (currentNode != NULL) {
        nkAddr childNode = currentNode->fs;
        while (childNode != NULL) {
            if (childNode->info.name == x) {
                return level;
            }
            childNode = childNode->nb;
        }
        currentNode = currentNode->fs;
        level++;
    }
    return -1;
}

int Depth (nkAddr P){
    if (P == NULL) {
        return 0;
    } else {
        int max_depth = -1;
        nkAddr child;
        for (child = P->fs; child != NULL; child = child->nb) {
            int current_depth = Depth(child);
            if (current_depth > max_depth) {
                max_depth = current_depth;
            }
        }
        return max_depth + 1;
    }
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

void gotoxy(int X, int y) {
	COORD coord;
	coord.X = X;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void loading_screen() {
	int i;
	gotoxy(50, 10);
	printf("Loading...");
	gotoxy(50, 12);
	for (i = 0; i <= 17; i++) {
		Sleep(90);
		printf("%c", 177);
	}
	printf("\n\n");
	system("pause");
	system("cls");
}
