#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#define MAXS 20
#define MAX 512
#define AGG "aggiungi-stazione"
#define DEMSTATION "demolisci-stazione"
#define ADDCAR "aggiungi-auto"
#define DESCAR "rottama-auto"
#define PLAN "pianifica-percorso"
#define ERROR "error-input"
#define INT_MAX 2147483647


//bst data structure
typedef struct treenode{
    int prev;
    int station;
    int cars[MAX];
    int maxautonomy;
    int numbers;
    struct treenode *p;
    struct treenode *left;
    struct treenode *right;
}treenode;

typedef struct bst{
    treenode* root;
}bst;
//minheap node data structure
typedef struct Heapnode{
    int station;
    int cost;
    int prev;
    int autonomia;
}Heapnode;
//heap data structure Min heap

typedef struct MinHeap{
    int num;
    int head;
    Heapnode *array;
}Minheap;

void swap(Heapnode *a, Heapnode *b){//swap elements in the heap
    Heapnode temp = *a;
    *a = *b;
    *b = temp;
}
void heapify2(Minheap *minHeap, int idx) { //rearrange max heap

    int largest = idx;
    int left =  idx + 1;
    int right =  idx + 2;

    if (left +minHeap->head< minHeap->num && minHeap->array[minHeap->head+left].cost < minHeap->array[minHeap->head+largest].cost){
        largest = left;

    }
    if (right+minHeap->head < minHeap->num && minHeap->array[minHeap->head+right].cost < minHeap->array[minHeap->head+largest].cost){
        largest = right;
    }
    if (largest != idx) {
        // Swap nodes and update positions
        swap(&minHeap->array[minHeap->head+idx], &minHeap->array[minHeap->head+largest]);
        heapify2(minHeap, largest);
    }
}
Heapnode extractMin2(Minheap *heap) { //extracts the first element from the maxheap and reorders
    if(heap->num -1== heap->head){
        return heap->array[heap->head];

    }
    Heapnode minNode = heap->array[heap->head];
    heap->head = heap->head +1;
    heapify2(heap, 0);
    return minNode;
}


void heapify1(Minheap *minHeap, int idx) { //reorder minheap
    int smallest = idx;
    int left =  2*idx + 1;
    int right = 2* idx + 2;

    if (left+minHeap->head < minHeap->num && minHeap->array[minHeap->head + left].cost <= minHeap->array[minHeap->head + smallest].cost && minHeap->array[minHeap->head +left].station < minHeap->array[minHeap->head + smallest].station)
        smallest = left;

    if (right+minHeap->head < minHeap->num && minHeap->array[minHeap->head+right].cost <= minHeap->array[minHeap->head+smallest].cost && minHeap->array[minHeap->head+right].station < minHeap->array[minHeap->head+smallest].station)
        smallest = right;

    if (smallest != idx) {
        swap(&minHeap->array[minHeap->head +idx], &minHeap->array[minHeap->head+smallest]);
        heapify1(minHeap, smallest);
    }
}
Heapnode extractmin1(Minheap *heap) { //extracts the first element from the minheap
    if(heap->head==heap->num -1){
        return heap->array[heap->head];

    }
    Heapnode minNode = heap->array[heap->head];
    heap->head = heap->head + 1;
    heapify1(heap, 0);
    return minNode;
}

Minheap *createMinHeap(int capacity) { //create a min heap
    Minheap *minHeap = (Minheap*)malloc(sizeof(Minheap));
    if (minHeap == NULL) {
        printf("Memory allocation error\n");
        free(minHeap);
        return NULL;
    }
    minHeap->num = capacity;
    minHeap->head = 0;
    minHeap->array = (Heapnode*)malloc((capacity) * sizeof(Heapnode));
    if (minHeap->array == NULL) {
        printf("Memory allocation error\n");
        free(minHeap->array);
        free(minHeap);
        return NULL;
    }
    return minHeap;
}

void treeinsert(bst *head, treenode *element){ //insert element into binary search tree
    if(head->root == NULL){
        head->root = element;
        printf("aggiunta\n");
        return;
    }

    treenode *x = head->root;
    treenode *y = NULL;

    while(x != NULL){
        y = x;
        if(element->station < x->station){
            x = x->left;
        }else if(element->station == x->station){
            printf("non aggiunta\n");
            return;

        }else{
            x = x->right;
        }
    }

    element->p = y;

    if(element->station < y->station){
        if(y->left != NULL){
        element->left = y->left->left;

        }
        y->left = element;


    }else if(element->station == y->station){
        printf("non aggiunta\n");
        return;
    }else{
        if(y->right!= NULL){
        element->right = y->right->right;
        }
        y->right = element;

    }
    printf("aggiunta\n");
}

treenode * treeminimum(treenode *element){ // find the minimum
    while(element->left != NULL){
        element = element->left;
    }
    return element;

}
treenode *treesuccessor(treenode *element){ // finds the smallest node with the next key to element
    if(element == NULL){
        return NULL;
    }
    if(element->right != NULL){
        return treeminimum(element->right);
    }
    treenode *y = element->p;
    while(y != NULL && element == y->right){
        element = y;
        y = y->p;
    }
    return y;
}

treenode *treemaxx(treenode *element){ //find the maximum
    while(element->right != NULL){
        element = element->right;
    }
    return element;

}

treenode *treeprecedessor(treenode *element){ //finds the precedent of a bst node
    if(element->left != NULL){
        return treemaxx(element->left);
    }
    treenode* y = element->p;
    while(y!= NULL && element == y->left){
        element = y;
        y = y->p;
    }
    return y;
}
treenode *treesearch(treenode *head, int stazione){ //searches for an element in the bst
    if(head == NULL || head->station == stazione){
        return head;
    }
    if(stazione < head->station){
        return treesearch(head->left, stazione);
    }else{
        return treesearch(head->right, stazione);
    }

}
void TreeDelete(bst* T, treenode* z) { //delete bst node
    int i;
    if (z == NULL){
        printf("non demolita\n");
        return;
    }
    treenode* y;
    if (z->left == NULL || z->right == NULL)
        y = z;
    else
        y = treesuccessor(z);

    treenode* x;
    if (y->left != NULL)
        x = y->left;
    else
        x = y->right;

    if (x != NULL)
        x->p = y->p;

    if (y->p == NULL)
        T->root = x;
    else if (y == y->p->left)
        y->p->left = x;
    else
        y->p->right = x;

    if (y != z) {
        z->prev = y->prev;
        z->station = y->station;
        z->maxautonomy = y->maxautonomy;
        z->numbers = y->numbers;
        for(i=0; i<y->numbers; i++){
            z->cars[i]= y->cars[i];
        }
    }

    free(y);
    printf("demolita\n");
}

void CancellaNodo(bst *head, int stazione){ //support function
    treenode* z = treesearch(head->root, stazione);
    if (z != NULL){
        TreeDelete(head, z);
    }else{
        printf("non demolita\n");
    }
}
treenode *untilstart(treenode *head, int start){ //inorder until you get to the beginning'
    if(head == NULL || start == head->station){
        return head;
    }
    if(start < head->station){
        return untilstart(head->left, start);

    }else{
        return untilstart(head->right, start);
    }

}


int contanodes(treenode *head, int start, int finish){ //inorder counts nodes
    if(head == NULL){
        return 0;
    }

    int count = 0;
    if(head->station >= start && head->station <=finish){
        count++;
    }
    count = count + contanodes(head->left, start, finish);
    count = count+ contanodes(head->right, start, finish);
    return count;
}


//orderly path
void dijkstra1(treenode *Start, int conta, int start, int finish){
    Minheap *minheap = createMinHeap(conta);
    int max, i, j, indice, riordina;
    treenode *scorri = Start;
    for(int i=0; i<conta; i++){
        minheap->array[i].cost = INT_MAX;
        minheap->array[i].autonomia = scorri->maxautonomy;
        minheap->array[i].station = scorri->station;
        minheap->array[i].prev = -1;
        if(scorri->station == finish) {
            break;
        }
        scorri = treesuccessor(scorri);
    }
    minheap->array[0].cost = 0;

    Heapnode *stampa = (Heapnode*)malloc(sizeof(Heapnode) * conta);
    minheap->num = conta;
    indice = conta;
    while(indice>0){
        stampa[(indice)-1] = extractmin1(minheap);
        max = stampa[(indice)-1].station + stampa[(indice)-1].autonomia;
        riordina=minheap->head;
        for(i=minheap->head; i<conta; i++){
            if(stampa[indice-1].cost != INT_MAX && max>=minheap->array[i].station){
                if(1 + stampa[indice -1].cost < minheap->array[i].cost){
                    minheap->array[i].prev = stampa[indice - 1].station;
                    minheap->array[i].cost = 1 + stampa[(indice)-1].cost;
                    riordina = i-minheap->head;
                    while(riordina > 0 && minheap->array[((riordina-1)/2)+minheap->head].cost > minheap->array[riordina+minheap->head].cost){

                        swap(&minheap->array[riordina+minheap->head], &minheap->array[((riordina-1)/2)+minheap->head]);

                        riordina = (riordina-1)/2;

                    }
                }
            }

        }
        indice = indice -1;
    }
    if(conta>0){
            if(stampa != NULL && stampa[0].cost == INT_MAX){
                printf("nessun percorso\n");
                free(minheap->array);
                free(minheap);
                free(stampa);
                scorri = NULL;
                return;

            }else{
                int nodo = finish;
                int *percorso = (int*)malloc(sizeof(int)*(stampa[0].cost+1));
                if(percorso == NULL){
                    printf("error memory");
                }
                j=0;
                for(i=0; i<conta; i++){
                    if(nodo == stampa[i].station){
                        nodo = stampa[i].prev;
                        percorso[j] = stampa[i].station;
                        j++;
                    }
                }
                for(i=stampa[0].cost; i>0; i--){
                            printf("%d ", percorso[i]);
                    }

                printf("%d\n", percorso[0]);
                free(percorso);
                free(minheap->array);
                free(minheap);
                free(stampa);
                scorri = NULL;
            }
    }
}
//reverse path
void dijkstra2(treenode *Finish, int conta, int start, int finish){
    Minheap *minheap = createMinHeap(conta);
    int max, i, indice, riordina;
    treenode *scorri = Finish;
    for(int i=0; i<conta; i++){
        minheap->array[i].cost = INT_MAX;
        minheap->array[i].autonomia = scorri->maxautonomy;
        minheap->array[i].station = scorri->station;
        minheap->array[i].prev = -1;
        if(scorri->station == finish) {
            break;
        }
        scorri = treeprecedessor(scorri);
    }
    minheap->array[0].cost = 0;
    Heapnode *stampa = (Heapnode*)malloc(sizeof(Heapnode) * conta);
    minheap->num = conta;
    indice = conta;
    while(indice>0){
        stampa[(indice)-1] = extractMin2(minheap);
        max = stampa[(indice)-1].station - stampa[(indice)-1].autonomia;
        riordina=minheap->head;
        for(i=minheap->head; i<conta; i++){
            if(stampa[indice-1].cost != INT_MAX && max<=minheap->array[i].station){
                if(1 + stampa[(indice)-1].cost <= minheap->array[i].cost){
                    if(minheap->array[i].prev == -1){
                        minheap->array[i].prev = stampa[(indice)- 1].station;
                        minheap->array[i].cost = 1 + stampa[(indice)-1].cost;
                        riordina = i-minheap->head;
                        while(riordina > 0 && minheap->array[((riordina-1)/2)+minheap->head].cost > minheap->array[riordina+minheap->head].cost){

                            swap(&minheap->array[riordina+minheap->head], &minheap->array[((riordina-1)/2)+minheap->head]);

                            riordina = (riordina-1)/2;
                        }

                    }else if(minheap->array[i].prev != -1 && minheap->array[i].prev > stampa[indice-1].station){
                         minheap->array[i].prev = stampa[indice - 1].station;
                        minheap->array[i].cost = 1 + stampa[(indice)-1].cost;
                        riordina = i-minheap->head;
                        while(riordina > 0 && minheap->array[((riordina-1)/2)+minheap->head].cost > minheap->array[riordina+minheap->head].cost){

                            swap(&minheap->array[riordina+minheap->head], &minheap->array[((riordina-1)/2)+minheap->head]);

                            riordina = (riordina-1)/2;

                        }
                    }
                }

            }
        }

        indice = indice-1;
    }

    if(conta>0){
            if(stampa != NULL && stampa[0].cost == INT_MAX){
                printf("nessun percorso\n");
                free(minheap->array);
                free(minheap);
                free(stampa);
                scorri = NULL;
                return;

            }else{
                int nodo = finish;
                int *percorso = (int*)malloc(sizeof(int)*(stampa[0].cost));
                int j =0;
                for(i=0; i<conta -1; i++){
                    if (nodo == stampa[i].station){
                        percorso[j] = nodo;
                        nodo = stampa[i].prev;
                        j++;
                    }

                }
                printf("%d ", start);
                for(j = j-1; j>0; j--){
                    printf("%d ",percorso[j]);

                }
                printf("%d\n", finish);
                free(percorso);
                free(minheap->array);
                free(minheap);
                free(stampa);
                scorri = NULL;
            }
    }
}

int main(){
    FILE *file = stdin;
    treenode* aggcar = NULL;
    treenode* delcar= NULL;
    treenode* Start;
    treenode* Finish;
    bst head;
    char comando[MAXS];
    int autonomie[MAX];
    int start, finish;
    int i, autonomia, esci, stazione, maxfuel, number_cars, conta;
    int position, j;
    head.root = NULL;
    while(fscanf(file,"%s", comando) != EOF){
        if(strcmp(comando, AGG)==0){
            if(fscanf(file, "%d %d ", &stazione, &number_cars)!= EOF){
                treenode *element = (treenode*)malloc(sizeof(treenode));
                element->left = NULL;
                            element->right = NULL;
                            element->p = NULL;
                            element->station = stazione;
                            element->numbers = number_cars;
                            element->maxautonomy = 0;

                if(element == NULL){
                            printf("memory error\n");
                            return 0;
                }
                for(int i=1; i<=number_cars; i++){
                    if(fscanf(file, "%d", &autonomie[i-1])!=EOF);

                    }
                    if(number_cars >0){
                            element->maxautonomy = autonomie[0];
                            for(i=0; i<number_cars; i++){
                                element->cars[i] = autonomie[i];
                                if(autonomie[i] > element->maxautonomy){
                                    element->maxautonomy = autonomie[i];

                                }
                            }
                    }

                treeinsert(&head, element);
            }
        }else if(strcmp(comando, DEMSTATION)==0){
             i=1;
            while(i){
                if(fscanf(file, "%d", &stazione) != EOF){
                    aggcar = NULL;
                    delcar = NULL;
                    CancellaNodo(&head, stazione);
                    i--;
                }
            }
        }else if(strcmp(comando, ADDCAR)==0){
            j=1;
            esci =0;
            while(j){
                if(fscanf(file, "%d %d", &stazione, &autonomia)!= EOF){
                    if(head.root == NULL){
                        printf("non aggiunta\n");
                        i =0;
                        break;
                    }else if(aggcar != NULL && aggcar->station == stazione){
                        if(aggcar->numbers < MAX){
                            position = aggcar->numbers;
                            aggcar->cars[position] = autonomia;
                            aggcar->numbers = aggcar->numbers +1;
                            printf("aggiunta\n");
                            if(autonomia>aggcar->maxautonomy){
                                aggcar->maxautonomy = autonomia;
                            }
                        }else{
                            for(i=0; i<MAX && !esci; i++){
                                if(aggcar->cars[i]== -1){
                                    aggcar->cars[i]= autonomia;
                                    esci = 1;
                                    if(aggcar->maxautonomy < autonomia){
                                        aggcar->maxautonomy = autonomia;

                                    }
                                }
                            }printf("aggiunta\n");
                        }

                    }else{
                        aggcar = treesearch(head.root, stazione);
                        if(aggcar != NULL){
                                if(aggcar->numbers < MAX){
                                    position = aggcar->numbers;
                                    aggcar->cars[position] = autonomia;
                                    aggcar->numbers = aggcar->numbers +1;
                                    if(autonomia>aggcar->maxautonomy){
                                        aggcar->maxautonomy = autonomia;
                                    }
                                    printf("aggiunta\n");
                                }else{
                                    for(i=0; i<MAX && !esci; i++){
                                        if(aggcar->cars[i]== -1){
                                            aggcar->cars[i]= autonomia;
                                            esci = 1;
                                            if(aggcar->maxautonomy < autonomia){
                                                aggcar->maxautonomy = autonomia;
                                            }
                                        }
                                    }
                                    printf("aggiunta\n");
                                }

                            }else{
                                printf("non aggiunta\n");
                            }
                        }
                        j--;
                }
            }
        }
                else if(strcmp(comando, DESCAR)==0){
                    j=1;
                    esci=0;
                    while(j){
                    if(fscanf(file, "%d %d", &stazione, &autonomia)!= EOF){//stesso metodo del puntatore (aggiungi macchina)implementare
                            if(head.root == NULL){
                                printf("non rottamata\n");
                            }else if(delcar != NULL && delcar->station == stazione){
                                for(i=0; i<delcar->numbers && !esci; i++){ //per rimuovere un auto scriviamo -1 nella sua autonomia
                                    if(delcar->cars[i] == autonomia){
                                        delcar->cars[i]= -1;
                                        esci = 1;
                                        printf("rottamata\n");
                                        if(autonomia == delcar->maxautonomy){ //caso in cui la stazione tolta è quella con autonomia massima
                                            maxfuel = delcar->cars[0];
                                            for(i=0; i <delcar->numbers ; i++){
                                                if(maxfuel < delcar->cars[i]){
                                                    maxfuel = delcar->cars[i];
                                                }
                                            }
                                            delcar->maxautonomy = maxfuel;
                                        }
                                    }

                                }
                                if(esci==0){
                                    printf("non rottamata\n");
                                }
                            }else{
                                delcar = treesearch(head.root, stazione);
                                if(delcar != NULL){
                                    for(i=0; i<delcar->numbers && !esci; i++){
                                        //per rimuovere un auto scriviamo -1 nella sua autonomia
                                        if(delcar->cars[i] == autonomia){
                                            delcar->cars[i]= -1;
                                            esci = 1;
                                            printf("rottamata\n");
                                            if(autonomia == delcar->maxautonomy){ //caso in cui la stazione tolta è quella con autonomia massima
                                                maxfuel = delcar->cars[0];
                                                for(i=0; i <delcar->numbers ; i++){
                                                    if(maxfuel < delcar->cars[i]){
                                                        maxfuel = delcar->cars[i];
                                                    }
                                                }
                                                delcar->maxautonomy = maxfuel;
                                            }
                                        }
                                    }if(esci==0){
                                        printf("non rottamata\n");
                                    }

                                }else{
                                    printf("non rottamata\n");
                                }
                            }
                        }
                        j--;
                    }
        }else if(strcmp(comando, PLAN)==0){
            i=1;
            while(i){
                if(fscanf(file, "%d %d", &start, &finish)!= EOF){
                    if(start < finish){

                        Start = untilstart(head.root, start);
                        conta = contanodes(head.root, start, finish);
                        dijkstra1(Start, conta, start, finish);
                        Start = NULL;
                    }else if(start == finish){
                        printf("%d\n", start);

                    }else if(start > finish){
                        Finish = untilstart(head.root, start);
                        conta = contanodes(head.root, finish, start);
                        dijkstra2(Finish, conta, start, finish);
                        Finish = NULL;


                    }
                    i--;
                }
            }

        }
    }
    return 0;
}
