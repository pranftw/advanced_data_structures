#include <stdio.h>
#include <stdlib.h>

struct node{
	int data;
	struct node* parent;
	struct node* left;
	struct node* right;
};

typedef struct node node;

node* new_node(){
	node* x = (node*)malloc(sizeof(node));
	x->left = NULL;
	x->right = NULL;
	return x;
}

node* find_min(node* root){
	if(root->left==NULL){
		return root;
	}
	return find_min(root->left);
}

int get_max(int x, int y){
	if(x>y){
		return x;
	}
	return y;
}

int calc_height(node* root){
	if(root==NULL){
		return 0;
	}
	return get_max(1+calc_height(root->left),1+calc_height(root->right));
}

int diff(node* root){
	int left_height = calc_height(root->left);
	int right_height = calc_height(root->right);
	return (right_height-left_height);
}

node* rotate_right(node* root, node* node_ptr){
	node* y = node_ptr;
	node* x = y->left;
	node* b = x->right;
	x->parent = y->parent;
	if(y->parent->right==y){
		y->parent->right = x;
	}
	else{
		y->parent->left = x;
	}
	x->right = y;
	y->parent = x;
	y->left = b;
	if(b!=NULL){
		b->parent = y;
	}
	if(x->parent==NULL){
		return x;
	}
	return root;
}

node* rotate_left(node* root, node* node_ptr){
	node* x = node_ptr;
	node* y = x->right;
	node* b = y->left;
	y->parent = x->parent;
	if(x->parent->right==x){
		x->parent->right = y;
	}
	else{
		x->parent->left = y;
	}
	y->left = x;
	x->parent = y;
	x->right = b;
	if(b!=NULL){
		b->parent = x;
	}
	if(y->parent==NULL){
		return y;
	}
	return root;
}

node* balance(node* root, node* node_ptr){
	node* ptr = node_ptr;
	if(diff(ptr)<0 && diff(ptr->left)<0){ // Both are left heavy
		root = rotate_right(root,ptr);
	}
	else if(diff(ptr)>0 && diff(ptr->right)>0){ // Both are right heavy
		root = rotate_left(root,ptr);
	}
	else if(diff(ptr)>0 && diff(ptr->right)<0){ // One is right heavy and other is left heavy
		root = rotate_right(root,ptr->right);
		root = rotate_left(root,ptr);
	}
	else if(diff(ptr)<0 && diff(ptr->left)>0){ // One is left heavy and other is right heavy
		root = rotate_left(root,ptr->left);
		root = rotate_right(root,ptr);
	}
	return root;
}

node* splay(node* root, node* node_ptr){
	node* ptr = node_ptr;
	while(ptr->parent!=NULL){
		if(ptr->parent->left==ptr){
			root = rotate_right(root,ptr->parent);
		}
		else{
			root = rotate_left(root,ptr->parent);
		}
	}
	return root;
}

node* search(node* root, int data){
	node* ptr = root;
	while(ptr!=NULL){
		if(ptr->data==data){
			root = splay(root,ptr);
		}
		else if(data>ptr->data){
			ptr = ptr->right;
		}
		else{
			ptr = ptr->left;
		}
	}
	if(ptr!=NULL){
		printf("It is present.\n")
	}
	else{
		printf("It is not present.\n")
	}
	return root;
}

node* insert_bst(node* root, node* x){
	node* ptr = root;
	while(ptr!=NULL){
		if(x->data>ptr->data){
			if(ptr->right==NULL){
				ptr->right = x;
				x->parent = ptr;
			}
			else{
				ptr = ptr->right;
			}
		}
		else{
			if(ptr->left==NULL){
				ptr->left = x;
				x->parent = ptr;
			}
			else{
				ptr = ptr->left;
			}
		}
	}
	if(ptr==NULL){
		x->parent = NULL;
		return x;
	}
	return root;
}

node* insert(node* root, int data){
	node* x = new_node();
	x->data = data;
	root = insert_bst(root,x);
	root = balance(root,x);
	return root;
}

node* delete(node* root, int data){
	node* ptr = root;
	while(ptr!=NULL){
		if(ptr->data==data){
			if(ptr->left==NULL && ptr->right==NULL){
				if(ptr->parent!=NULL){
					if(ptr->parent->left==ptr){
						ptr->parent->left = NULL;
					}
					else{
						ptr->parent->right = NULL;
					}
				}
				else{
					return NULL;
				}
			}
			else if(ptr->left==NULL){
				ptr->right->parent = ptr->parent;
				if(ptr->parent!=NULL){
					if(ptr->parent->right==ptr){
						ptr->parent->right = ptr->right;
					}
					else{
						ptr->parent->left = ptr->right;
					}
				}
				else{
					return ptr->right;
				}
			}
			else if(ptr->right==NULL){
				ptr->left->parent = ptr->parent;
				if(ptr->parent!=NULL){
					if(ptr->parent->right==ptr){
						ptr->parent->right = ptr->left;
					}
					else{
						ptr->parent->left = ptr->left;
					}
				}
				else{
					return ptr->left;
				}
			}	
			else{
				node* min_val = find_min(ptr->right);
				ptr->data = min_val->data;
				root = delete(root,min_val);
			}
			root = balance(root,ptr);
			return root;
		}
		else if(data>ptr->data){
			ptr = ptr->right;
		}
		else{
			ptr = ptr->left;
		}
	}
}

void print_splay(node* root){
	if(root!=NULL){
		print_splay(root->left);
		printf("%d ",root->data);
		print_splay(root->right);
	}
}

int main(){
	return 0;
}
