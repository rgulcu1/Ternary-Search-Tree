#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct node{
    int data;
    struct node *right, *left, *middle;
};

typedef struct node node;

void insert(node ** root, int data);
int maxDepth(node  *node);
void createTree(node **root);
node * find(node **root,int data);

int main(){
    node *root;
    node *temp;
    root=NULL;
    createTree(&root);

    temp=find(&root,76);



    if (temp)
    {
        printf("Searched node=%d\n", temp->data);
    }
    else
    {
        printf("Data Not found in tree.\n");
    }

    return 0;
}

void insert(node ** root, int data)
{
    node *temp = NULL;
    if(!(*root))
    {
        temp = (node *)malloc(sizeof(node));
        temp->left =temp->middle= temp->right = NULL;
        temp->data = data;
        *root = temp;
        return;
    }

    if(data < (*root)->data) {
        insert(&((*root)->left), data);
    }
    else if(data <= pow((*root)->data,2)) {
        insert(&((*root)->middle), data);
    }
    else  if(data > pow((*root)->data,2)){
        insert(&((*root)->right),data);
    }

}

void createTree(node **root){
    FILE *file=fopen("input.txt","r");
    int data;
        while(fscanf(file,"%d", &data) != EOF){
            insert(root,data);
        }
}
node * find(node **root,int data){
    if(!(*root)){
        return NULL;
    }

    if(data < (*root)->data){
        return find(&((*root)->left),data);
    }
    else if(data > (*root)->data && data <= pow((*root)->data,2)){
       return find(&((*root)->middle),data);
    }
    else if(data > pow((*root)->data,2)){
       return find(&((*root)->right),data);
    }

    else if(data == (*root)->data){
        return *root;
    }

}

void printTree(node *root){
    int DepthLevel=0;
    int count=0;

    while(root->right!=NULL){
        count++;
        root=root->right;
    }
    count=0;
    DepthLevel=count;

    while(root->middle!=NULL){
        count++;
        root=root->middle;
    }
    count=0;
    DepthLevel=count;

    while(root->right!=NULL){
        count++;
        root=root->right;
    }
    count=0;
    DepthLevel=count;
}

int maxDepth(node* node)
{
    if (node==NULL)
        return 0;
    else
    {
        /* compute the depth of each subtree */
        int lDepth = maxDepth(node->left);
        int mDepth =maxDepth(node->middle);
        int rDepth = maxDepth(node->right);


        if ( lDepth > mDepth && lDepth > rDepth )
            return(lDepth+1);
        else if ( mDepth > rDepth && mDepth > lDepth )
            return(mDepth+1);
        else if ( rDepth > lDepth && rDepth > mDepth )
            return(rDepth+1);
    }
}
