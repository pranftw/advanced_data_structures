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
    if(node_ptr==NULL){
        return 0;
    }
    int max_val = get_max(calc_height(node_ptr->left),calc_height(node_ptr->right));
    return (1 + max_val);
}

int diff(node* node_ptr){
    if(node_ptr==NULL){
        return 0;
    }
    int left_height = calc_height(node_ptr->left);
    int right_height = calc_height(node_ptr->right);
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
    if(y->parent!=NULL){
        if(y->parent->right==y){ // I'd forgotten about this part where just changing the child's parent was taken care, but the parent's child wasn't set at all!!!
            y->parent->right = x;
        }
        else{
            y->parent->left = x;
        }
    }
    x->parent = y->parent;
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
    // node* a = x->left; node* c = y->right;
    node* b = y->left;
    if(x->parent!=NULL){
        if(x->parent->right==x){ // I'd forgotten about this part where just changing the child's parent was taken care, but the parent's child wasn't set at all!!!
            x->parent->right = y;
        }
        else{
            x->parent->left = y;
        }
    }
    y->parent = x->parent;
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
    node* temp;
    while(ptr!=NULL){
        temp = ptr->parent;
        if(diff(ptr)<0 && diff(ptr->left)<0){ // Both are left heavy
            root = rotate_right(root,ptr);
        }
        else if(diff(ptr)>0 && diff(ptr->right)>0){ // Both are right heavy
            root = rotate_left(root,ptr);
        }
        else if(diff(ptr)<0 && diff(ptr->left)>0){ // One is left heavy and other is right heavy
            root = rotate_left(root,ptr->left);
            root = rotate_right(root,ptr);
        }
        else if(diff(ptr)>0 && diff(ptr->right)<0){ // One is right heavy and other is left heavy
            root = rotate_right(root,ptr->right);
            root = rotate_left(root,ptr);
        }
        ptr = temp;
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

node* delete(node* root, int data){
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
                    ptr->right->parent = prev;
                    if(prev->right==ptr){
                        prev->right = ptr->right;
                    }
                    else{
                        prev->left = ptr->right;
                    }
                }
                else{
                    ptr->right->parent = NULL;
                    return ptr->right;
                }
            }
            else if(ptr->right==NULL){
                if(prev!=NULL){
                    ptr->left->parent = prev;
                    if(prev->right==ptr){
                        prev->right = ptr->left;
                    }
                    else{
                        prev->left = ptr->left;
                    }
                }
                else{
                    ptr->left->parent = NULL;
                    return ptr->left;
                }
            }
            else{
                node* min_val = find_min(ptr->right);
                ptr->data = min_val->data;
                root = delete(root,min_val->data);
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
        prev = temp;
    }
    return root;
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
    root = insert(root,10);
    root = insert(root,8);
    root = insert(root,15);
    root = insert(root,6);
    root = insert(root,5);
    root = insert(root,4);
    root = insert(root,7);
    root = delete(root,4);
    print_avl(root);
    printf("\n%d\n",root->left->data);
    return 0;
}
