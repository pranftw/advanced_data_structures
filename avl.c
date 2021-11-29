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
    x->right = NULL;
    x->left = NULL;
    return x;
}

int get_max(int a, int b){
    if(a>b){
        return a;
    }
    return b;
}

int calc_height(node* node_ptr){
    if(ptr==NULL){
        return 0;
    }
    int max_val = get_max(calc_height(ptr->left),calc_height(ptr->right));
    return (1 + max_val);
}

int diff(node* node_ptr){
    int left_height = calc_height(ptr->left);
    int right_height = calc_height(ptr->right);
    return (right_height-left_height);
}

node* find_min(node* root){
    if(root->left==NULL){
        return root;
    }
    return find_min(root->left);
}

node* rotate_right(node* root, node* node_ptr){
    node* y = node_ptr;
    node* x = node_ptr->left;
    // node* a = x->left; node* c = y->right;
    node* b = x->right;
    x->parent = y->parent;
    x->right = y;
    y->parent = x;
    y->left = b;
    b->parent = y;
    if(x->parent==NULL){
        return x;
    }
    return root;
}

node* rotate_left(node* root, node* node_ptr){
    node* x = node_ptr;
    node* y = x->right;
    // node* a = x->left; node* c = y->right;
    node* b = y->left;
    y->parent = x->parent;
    y->left = x;
    x->parent = y;
    x->right = b;
    b->parent = x;
    if(y->parent==NULL){
        return y;
    }
    return root;
}

node* balance(node* root, node* node_ptr){
    node* ptr = node_ptr;
    while(ptr!=NULL){ // Keeps balancing until the parent is null(root)
        if(diff(ptr)<0 && diff(ptr->left)<0){ // Both are left heavy
            root = rotate_right(ptr);
        }
        else if(diff(ptr)>0 && diff(ptr->right)>0){ // Both are right heavy
            root = rotate_left(ptr);
        }
        else if(diff(ptr)<0 && diff(ptr->left)>0){ // One is left heavy and other is right heavy
            root = rotate_left(ptr->left);
            root = rotate_right(ptr);
        }
        else if(diff(ptr)>0 && diff(ptr->right)<0){ // One is right heavy and other is left heavy
            root = rotate_right(ptr->right);
            root = rotate_left(ptr);
        }
        ptr = ptr->parent;
    }
    return root;
}

node* insert_bst(node* root, node* x){
    node* ptr = root;
    while(ptr!=NULL){
        if(ptr->data>x->data){
            if(ptr->right==NULL){
                ptr->right = x;
                x->parent = ptr;
                break; // Dont forget to use break here!!
            }
            else{
                ptr = ptr->right;
            }
        }
        else{
            if(ptr->left==NULL){
                ptr->left = x;
                x->parent = ptr;
                break; // Dont forget to use break here!!
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
    else{
        return root;
    }
}

node* insert(node* root, int data){
    // Create a new node here to pass it to insert bst and then later to pass the same to balance
    // Call to insert_bst
    // Call to balance
    node* x = new_node();
    x->data = data;
    root = insert_bst(root, x);
    root = balance(root, x);
    return root;
}

node* delete_bst(node* root, int data){
    node* ptr = root;
    node* prev = NULL;
    node* temp;
    while(ptr!=NULL){
        temp = ptr;
        if(ptr->data==data){
            if(ptr->left==NULL && ptr->right==NULL){
                if(prev!=NULL){
                    if(prev->right==ptr){
                        prev->right = NULL;
                    }
                    else{
                        prev->left = NULL;
                    }
                }
                else{
                    return NULL;
                }
            }
            else if(ptr->left==NULL){
                if(prev!=NULL){
                    if(prev->right==ptr){
                        prev->right = ptr->right;
                    }
                    else{
                        prev->left = ptr->right;
                    }
                }
                else{
                    return ptr->right;
                }
            }
            else if(ptr->right==NULL){
                if(prev!=NULL){
                    if(prev->right==ptr){
                        prev->right = ptr->left;
                    }
                    else{
                        prev->left = ptr->left;
                    }
                }
                else{
                    return ptr->left;
                }
            }
            else{
                node* min_val = find_min(ptr->right);
                ptr->data = min_val->data;
                root = delete_bst(root,min_val->data);
            }
            return root;
        }
        else if(data>ptr->data){
            ptr = ptr->right;
        }
        else{
            ptr = ptr->left;
        }
        prev = temp;
    }
    return root;
}

node* delete(node* root, int data){
    // Call to delete_bst
    // Call to balance

}

void print_avl(node* root){
    if(root!=NULL){
        print_avl(root->left);
        printf("%d ",root->data);
        print_avl(root->right);
    }
}

int main(){
    node* root = NULL;
    return 0;
}