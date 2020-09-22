/*COP 3502C Final term Assignment 2
This program is written by: Esteban Brugal*/

/*Takes an input.txt file that starts with 3 numbers. These are the number of words,
number of words searched from the tree, and number of words deleted. The words are then
written in that order. So first all of the words, then the words searched for, and finally
the words that will be deleted. Results are printed in an output.txt file.
This was done to show my understanding of binary search trees.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tree{
    char* data;
    struct tree* left;
    struct tree* right;
}tree;

tree* insertNode(tree* root, tree* node);   //inserts tree node following BST rules
tree* createNode(char*);                    //creates tree node
void preorder(tree*, FILE*);
void inorder(tree*, FILE*);
void postorder(tree*, FILE*);
int isBalanced(tree*, FILE*);
int height(tree*);
tree* find(tree*, char*);
int countBefore(tree*, char*);
int leafNode(tree*);              //Determines if it's a leaf node, returns 1 if leaf, 0 if isn't
int onlyLeftChild(tree*);         //Returns 1 if has only left child, else return 0
int onlyRightChild(tree*);        //Returns 1 if has only right child, else returns 0
tree* parent(tree*, char*);       //finds parent of a node
int twoChildren(tree*);           //Returns 1 if node has two children
tree* delete(tree*, char*, FILE*, int);
tree* findMax(tree*);
int totalCharacters(tree*);


int main()
{
    tree* root = NULL;
    FILE* input = fopen("input.txt", "r");
    FILE* output = fopen("output.txt", "w");
    if(input == NULL){
        printf("No File Found.");
    }else{
        int amount, search, erase;
        fscanf(input, "%d %d %d", &amount, &search, &erase);
        for(int i=0; i<amount; i++){
            char* word = malloc(10*sizeof(char));
            fscanf(input, "%s", word);
            tree* node = createNode(word);
            if(node!=NULL)
                root = insertNode(root, node);
        }
        printf("Pre Order: ");
        fprintf(output,"Pre Order: ");
        preorder(root, output);
        printf("\n");
        printf("In Order: ");
        fprintf(output,"\nIn Order: ");
        inorder(root, output);
        printf("\n");
        printf("Post Order: ");
        fprintf(output,"\nPost Order: ");
        postorder(root, output);
        printf("\n");
        printf("Total Characters: %d\n", totalCharacters(root));
        fprintf(output, "\nTotal Character: %d\n", totalCharacters(root));
        isBalanced(root, output);
        printf("Search Phase:\n");
        fprintf(output, "Search Phase:\n");
        printf("%d\n", countBefore(root, "judy"));
        for(int i=0; i<search; i++){
            char* word = malloc(10*sizeof(char));
            fscanf(input, "%s", word);
            tree* node = find(root, word);

            if(node!=NULL){
                printf("%s: Found, Items before: %d\n", node->data, countBefore(root, word));
                fprintf(output,"%s: Found, Items before: %d\n", node->data, countBefore(root, word));
            }else{
                printf("%s: Not found, Items before: 0\n", word);
                fprintf(output, "%s: Not found, Items before: 0\n", word);
            }
        }
        printf("Delete Phase:\n");
        fprintf(output, "Delete Phase:\n");
        for(int i=0; i<erase; i++){
            char* word = malloc(10*sizeof(char));
            fscanf(input, "%s", word);
            root = delete(root, word, output, 0);
        }
        printf("In Order: ");
        fprintf(output, "In Order: ");
        inorder(root, output);
        printf("\nTotal Characters: %d\n", totalCharacters(root));
        fprintf(output, "\nTotal Characters: %d\n", totalCharacters(root));
        fclose(input);
    }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

tree* createNode(char* word){
    tree* node = malloc(sizeof(tree));
    node->data = word;
    node->left = NULL;
    node->right = NULL;
    return node;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

tree* insertNode(tree* root, tree* node){
    if(root == NULL)
        return node;
    else{
        if(strcmp(root->data, node->data)>0){
            if(root->left != NULL)
                root->left = insertNode(root->left, node);
            else
                root->left = node;
        }else{
            if(root->right!=NULL)
                root->right = insertNode(root->right, node);
            else
                root->right = node;
        }
        return root;
    }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void preorder(tree* root, FILE* output){
    if(root != NULL){
        printf("%s ", root->data);
        fprintf(output, root->data);
        fprintf(output, " ");
        preorder(root->left, output);
        preorder(root->right, output);
    }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void inorder(tree* root, FILE* output){
    if(root != NULL){
        inorder(root->left, output);
        fprintf(output, root->data);
        fprintf(output, " ");
        printf("%s ", root->data);
        inorder(root->right, output);
    }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void postorder(tree* root, FILE* output){
    if(root != NULL){
        postorder(root->left, output);
        postorder(root->right, output);
        printf("%s ", root->data);
        fprintf(output, root->data);
        fprintf(output, " ");
    }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int isBalanced(tree* root, FILE* output){
    int lh = height(root->left)-1;
    int rh = height(root->right)-1;
    if(lh-rh>1 || lh-rh<-1){
        printf("Height left = %d, height right = %d. The tree is imbalanced.\n", lh, rh);
        fprintf(output, "Height left = %d, height right = %d. The tree is imbalanced.\n", lh, rh);
        return 0;
    }
    printf("Height left = %d, height right = %d. The tree is balanced.\n", lh, rh);
    fprintf(output, "Height left = %d, height right = %d. The tree is balanced.\n", lh, rh);
    return 1;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int height(tree* root){
    int left, right;

    if(root == NULL)
        return 0;

    left = height(root->left);
    right = height(root->right);

    if(left > right)
        return left+1;

    return right+1;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

tree* find(tree* root, char* word){
    if(root != NULL){
        if(strcmp(root->data, word) == 0){
            return root;
        }else{
            if(strcmp(word, root->data) < 0)
                return find(root->left, word);
            else
                return find(root->right, word);
        }
    }
    return NULL;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int countBefore(tree* root, char* word){

    if(root!=NULL){
        if(strcmp(root->data, word)<0)
            return 1 + countBefore(root->left, word) + countBefore(root->right, word);
        else
            return countBefore(root->left, word) + countBefore(root->right, word);
    }
    else
        return 0;

}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int leafNode(tree* node){
    if(node->left == NULL && node->right == NULL)
        return 1;
    return 0;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int onlyLeftChild(tree* node){
    if(node->left != NULL && node->right == NULL)
        return 1;
    return 0;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int onlyRightChild(tree* node){
    if(node->left == NULL && node->right != NULL)
        return 1;
    return 0;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int twoChildren(tree* node){
    if(node->left != NULL && node->right != NULL)
        return 1;
    return 0;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

tree* parent(tree* root, char* word){
    if(root!=NULL){
        if(twoChildren(root)){
          if(strcmp(root->left->data, word) == 0 || strcmp(root->right->data, word) == 0){
            //printf("%s", root->data);
            return root;
            }
        }
        else if(onlyLeftChild(root)){
            if(strcmp(root->left->data, word) == 0){
                //printf("%s", root->data);
                return root;
            }
        }
        else if(onlyRightChild(root)){
            if(strcmp(root->right->data, word) == 0){
                //printf("%s", root->data);
                return root;
            }
        }
            if(strcmp(word, root->data) < 0)
                return parent(root->left, word);
            else
                return parent(root->right, word);
    }
    return NULL;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

tree* delete(tree* root, char* word, FILE* output, int x){
    tree* par = parent(root, word);
    tree* del = find(root, word);
    tree* temp; tree* new_del;
    char* save;
    if(del!=NULL){
        if(x==0){
            printf("%s: Deleted\n", word);
            fprintf(output, "%s: Deleted\n", word);
        }
        if(leafNode(del)){
        if(par == NULL){
            free(del);
            return NULL;
        }
        if(strcmp(del->data, par->data)<0){
            free(del);
            par->left = NULL;
        }
        else{
            free(del);
            par->right = NULL;
        }
        return root;
    }
    if(onlyLeftChild(del)){
        if(par == NULL){
            temp = del->left;
            free(del);
            return temp;
        }
        if(strcmp(del->data, par->data)<0){
            temp = par->left;
            par->left = par->left->left;
            free(temp);
        }
        else{
            temp = par->right;
            par->right = par->right->left;
            free(temp);
        }
        return root;
    }
    if(onlyRightChild(del)){
        if(par == NULL){
            temp = del->right;
            free(del);
            return temp;
        }
        if(strcmp(del->data, par->data)<0){
            temp = par->left;
            par->left = par->left->right;
            free(temp);
        }
        else{
            temp = par->right;
            par->right = par->right->right;
            free(temp);
        }
        return root;
    }
    if(twoChildren(del)){
        new_del = findMax(del->left);
        save = new_del->data;
        delete(root, save, output, x+1);
        del->data = save;
        return root;
    }
    }
    else{
        printf("%s: Doesn't exist\n", word);
        fprintf(output, "%s: Doesn't exist\n", word);
        return root;
    }


}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

tree* findMax(tree* root){
    if(root->right != NULL){
        findMax(root->right);
    }else
        return root;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

totalCharacters(tree* root){
    int count = 0;
    if(root!=NULL){
        count += strlen(root->data) + totalCharacters(root->left) + totalCharacters(root->right);
    }
    return count;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

