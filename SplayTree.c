#include<stdio.h>
#include<stdlib.h>

typedef struct tree{
    int key;
    struct tree *left;
	struct tree *right;
} tree;

	tree *splay(tree **root, int key);
	tree *newNode(int key);
	tree *rightRotate(tree *x);
	tree *leftRotate(tree *x);
	void bypass(tree *root);
	tree *delete_key(tree **root, int key);
	tree *insert(tree *root, int k);

int main(){
	
	tree *root = NULL;
	int menu, key;
	
	while(1){
		
		printf(
			"\n\n1 - Add node"
			"\n2 - Splay"
			"\n3 - Delete node"
			"\n4 - Print tree"
			"\n0 - EXIT"
			"\nYour chose>"
		);
		
        while(!scanf("%d", &menu) || menu < 0 || menu > 6) {
			printf("Invalid value entered!\n");
			fflush(stdin);	
		}
		
		switch(menu) {
			case 1:{
				printf("Enter the root:");
				while(!scanf("%d", &key)) {
					printf("Invalid value entered!\n");
					fflush(stdin);	
				}
				root = insert(root, key);
				break;
			}
			case 2:{
				printf("Enter the root:");
				while(!scanf("%d", &key)) {
					printf("Invalid value entered!\n");
					fflush(stdin);	
				}
				root = splay(&root, key);
				if (root->key != key) 
			        printf("No such root found!\n");
				break;
			}
			case 3:{
				printf("Enter the root:");
				while(!scanf("%d", &key)) {
					printf("Invalid value entered!\n");
					fflush(stdin);	
				}
				root = delete_key(&root, key);
				break;
			}
			case 4:{
				if(root == NULL){
					printf("The tree is empty!");
				}
				else{
					printf("\nDirect bypass: ");
					bypass(root);
					printf("NULL\n");
				}
				break;
			}
			case 0: exit(0);
		}
	}
}
 
tree *insert(tree *root, int key){
	
    if (root == NULL) return newNode(key);
 
    root = splay(&root, key);
 
    if (root->key == key) return root;
 
    tree *newnode  = newNode(key);
 
    if (root->key > key){
        newnode->right = root;
        newnode->left = root->left;
        root->left = NULL;
    }
 
    else{
        newnode->left = root;
        newnode->right = root->right;
        root->right = NULL;
    }
 
    return newnode;
}
   
tree *rightRotate(tree *x){
    tree *y = x->left;
    x->left = y->right;
    y->right = x;
    return y;
}

tree *leftRotate(tree *x){
    tree *y = x->right;
    x->right = y->left;
    y->left = x;
    return y;
}

tree *delete_key(tree **root, int key){
	
    tree *temp;
    if (!(*root))
        return NULL;
 
    (*root) = splay(&(*root), key);
 
    if (key != (*root)->key){
    	printf("No such root found!\n");
        return (*root);
    }
 
    if (!(*root)->left) {
        temp = (*root);
        (*root) = (*root)->right;
    }
 
    else {
        temp = (*root);
        (*root) = splay(&(*root)->left, key);
        (*root)->right = temp->right;
    }
 
    free(temp);
 
    return (*root);
}
  
tree *splay(tree **root, int key){

    if ((*root) == NULL || (*root)->key == key)
        return (*root);
  	
    if ((*root)->key > key){
    	
        if ((*root)->left == NULL) return (*root);
  
        // Zig-Zig
        if ((*root)->left->key > key){
            (*root)->left->left = splay(&(*root)->left->left, key);
            (*root) = rightRotate((*root));
        }
        // Zig-Zag
        else if ((*root)->left->key < key){
            (*root)->left->right = splay(&(*root)->left->right, key);
            if ((*root)->left->right != NULL)
                (*root)->left = leftRotate((*root)->left);
        }
		// Zig
        return ((*root)->left == NULL)? (*root): rightRotate((*root));
    }
    else{

        if ((*root)->right == NULL) return (*root);
  
        // Zag-Zig
        if ((*root)->right->key > key){
            (*root)->right->left = splay(&(*root)->right->left, key);
            if ((*root)->right->left != NULL)
                (*root)->right = rightRotate((*root)->right);
        }
        // Zag-Zag
        else if ((*root)->right->key < key){
            (*root)->right->right = splay(&(*root)->right->right, key);
            (*root) = leftRotate((*root));
        }
  		// Zag
        return ((*root)->right == NULL)? (*root): leftRotate((*root));
    }
}

tree *newNode(int key){
    tree* node = (tree*)malloc(sizeof(tree));
    node->key   = key;
    node->left  = node->right  = NULL;
    return (node);
}

void bypass(tree *root){
	if(root != NULL){
		if(root->key) printf("%d->", root->key);
		bypass(root->left);
		bypass(root->right);
	}
}

