//include required libraries
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct node { //create node for TST
    int data;
    struct node *right, *left, *middle;
};

typedef struct node node;//typedef node

//declare functions
void insert(node **root, int data);

void createTree(node **root);

void find(node *root, int key);

node *search(node *root, int data);

void rebuildMidChild(node *root, node **tree, int referenceValue);

void rebuildRightChild(node *root, node **tree, int referenceValue);

void rebuildTree(node *root, node **tree, int referenceValue);

node *findMax(node *root);

node *findMin(node *root);

void removeNode(node **tree, int key);

void removee(node **root, int key);

void printLMNR(node *root);


int main() {
    node *root;//create root node
    root = NULL;
    int key;
    createTree(&root); //creat the Tree with read inputs from file
    printf("Travel tree LMNR: "); //print the the tree depend on LMNR
    printLMNR(root);
    puts("");


    int choice;
    while(1){ //Method choice Menu
        puts("");
        puts("Method Choice Menu");
        puts("0-Exit");
        puts("1-Search node");
        puts("2-Dele Node");
        puts("3-Print Tree");

        if(!scanf("%d",&choice)) {
            puts("Invalid input.The program will terminate");
            break;
        }

        if(choice==0) break; //if input 0 terminate the program.



        switch(choice){
            case 1:
                printf("\nPlease enter data for search in tree:"); //Prompt input from user for search node
                scanf("%d", &key);
                find(root, key); //find the given node
                break;
            case 2:
                printf("Please enter data to remove from tree:"); //Prompt input from user for delete a node
                scanf("%d", &key);
                removee(&root, key); //remove the given node
                break;
            case 3:
                printf("Travel tree LMNR: "); //print the the tree depend on LMNR
                printLMNR(root);
                puts("");
                break;
            default:
                puts("Inlavid choice.Please try again");
                continue;
        }

    }

    return 0;
}

//insert function for insert a node on tree.The functions find the right place for data recursively
void insert(node **root, int data) {
    node *temp = NULL;
    if (!(*root)) { //if root is null add the node this place
        temp = (node *) malloc(sizeof(node)); //malloc for new node
        temp->left = temp->middle = temp->right = NULL; //new node's child define NULL
        temp->data = data;//equalize the data
        *root = temp; //add the node main tree
        return;
    }

    //move the tree until find the right place depend on tree's formula
    if (data < (*root)->data) {
        insert(&((*root)->left), data);
    } else if (data <= pow((*root)->data, 2)) {
        insert(&((*root)->middle), data);
    } else if (data > pow((*root)->data, 2)) {
        insert(&((*root)->right), data);
    }

}

//createTee function for read inputs from file and and dd the inputs on tree with call insert function
void createTree(node **root) {
    FILE *file = fopen("input.txt", "r"); //open the file
    int data;
    while (fscanf(file, "%d", &data) != EOF) { //read input and call insert function for every node
        insert(root, data);
    }
    fclose(file); //close the file
    puts("Tree is created."); //informatin massage
}

//search function for search the given value on tree and return the founded node
node *search(node *root, int data) {
    if (!(root)) {
        return NULL;
    }
    // search the value depend on tree's function
    if (data < (root)->data) {
        return search(((root)->left), data);
    } else if (data > (root)->data && data <= pow((root)->data, 2)) {
        return search(((root)->middle), data);
    } else if (data > pow((root)->data, 2)) {
        return search(((root)->right), data);
    } else if (data == (root)->data) {
        return root;
    }

}

//find fucntion is call the search function with given value and chechk the return value is null or exist on tree
void find(node *root, int key) {
    node *temp = search(root, key);

    if (temp) {
        printf("Searched node = %d\n", temp->data);
    } else {
        printf("Data Not found in tree.\n");
    }
}

//rebuild Midlle Child for removed root
void rebuildMidChild(node *root, node **tree, int referenceValue) {
    node *childRoot = (*tree)->middle;
    if (childRoot == NULL) {
        return;
    }
    if (childRoot->data >= pow(referenceValue,
                               2)) { //if the data is not suitible for new parent root instert this node again tree and remove this place node
        insert(&root, childRoot->data);
        removeNode(&(*tree)->middle, childRoot->data);
        rebuildMidChild(root, &(*tree), referenceValue); //check child datas recursively
    } else {
        rebuildMidChild(root, &childRoot, referenceValue);
    }
}

//rebuilfrightChild is work wih same logic rebuildMidChild
void rebuildRightChild(node *root, node **tree, int referenceValue) {
    node *childRoot = (*tree)->right;
    if (childRoot == NULL) {
        return;
    }
    if (childRoot->data < pow(referenceValue, 2)) {
        insert(&root, childRoot->data);
        removeNode(&(*tree)->right, childRoot->data);
        rebuildRightChild(root, &(*tree), referenceValue);
    } else {
        rebuildRightChild(root, &childRoot, referenceValue);
    }
}

//revuildTree function is called rebuildMidChild and rebuildRightChild inside
void rebuildTree(node *root, node **tree, int referenceValue) {
    rebuildMidChild(root, tree, referenceValue);
    rebuildRightChild(root, tree, referenceValue);
}

//remove the given key node and left max node or middle min node replaces deleted value
void removeNode(node **tree, int key) {
    node *temp;

    //call removeNode function recursively until find the right node
    if (key < (*tree)->data) {
        removeNode(&(*tree)->left, key);
    } else if (key > (*tree)->data && key <= pow((*tree)->data, 2)) {
        removeNode(&(*tree)->middle, key);
    } else if (key > pow((*tree)->data, 2)) {
        removeNode(&(*tree)->right, key);
    } else {//when find the right node
        //check the node is has least two child
        if (((*tree)->right && (*tree)->left) || ((*tree)->right && (*tree)->middle) ||
            ((*tree)->middle && (*tree)->left)) {

            if ((*tree)->left) { //if node has left child replace the minumum value of left side
                temp = findMax((*tree)->left);
                (*tree)->data = temp->data;
                removeNode(&(*tree)->left, temp->data);
            } else {//if node has not left child replace the maximum  value of middle side
                temp = findMin((*tree)->middle);
                (*tree)->data = temp->data;
                removeNode(&(*tree)->middle, temp->data);
            }

        } else {//if node has not least two node replace the node which is single child
            temp = (*tree);
            if (((*tree)->right == NULL && (*tree)->left == NULL)) {
                (*tree) = (*tree)->middle;
            } else if (((*tree)->left == NULL && (*tree)->middle == NULL)) {
                (*tree) = (*tree)->right;
            } else if (((*tree)->right == NULL && (*tree)->middle == NULL)) {
                (*tree) = (*tree)->left;
            }

            free(temp); //free memory for removed node
        }

    }
}

//removee function is remove node with call removeNode function and rebuild the tree
void removee(node **root, int key) {
    node *temp = search(*root, key);
    if (temp == NULL) { //if tree has not given data
        puts("Data Not found in tree.");
        return;
    }
    removeNode(root, key); //remove the node
    rebuildTree(*root, &temp, temp->data); //rebuild the data depend on removed node

    printf("%d is removed from tree. \n", key); //information massage
}

//find the maximum data on given root and return this node
node *findMax(node *root) {
    if (root == NULL) {
        return NULL;
    } else if (!root->right == NULL) {
        return findMax(root->right);
    } else if (root->middle == NULL) {
        return root;
    } else {
        return findMax(root->middle);
    }
}

//find the maximum data on given root and return this node
node *findMin(node *root) {
    if (root == NULL) {
        return NULL;
    } else if (!root->left == NULL) {
        return findMax(root->left);
    } else {
        return root;
    }

}

//print the tree with traversal LMNR
void printLMNR(node *root) {

    if (root) {
        printLMNR(root->left);
        printLMNR(root->middle);
        printf("%d ", root->data);
        printLMNR(root->right);
    }

}



