#include <stdio.h>
#include <stdlib.h>

struct node{
    int data;
    struct node* left;
    struct node* right;
    struct node* parent;
    int color; // Red 1 Black 0
}

typedef struct node node;

node* new_node(){
    node* x = (node*)malloc(sizeof(struct));
    x->right = NULL;
    x->left = NULL;
    x->color = 1;
    return x;
}

int find_min(node* root){
    if(root->left==NULL){
        return root;
    }
    return find_min(root->left);
}

node* rotate_right(node* root, node* node_ptr){

}

node* rotate_left(node* root, node* node_ptr){

}

node* balance(node* root, node* node_ptr){

}

node* insert_bst(node* root, node* x){
    node* ptr = root;
    while(ptr!=NULL){
        if(x->data>ptr->data){
            if(ptr->right==NULL){
                ptr->right = x;
                x->parent = ptr;
                break;
            }
            else{
                ptr = ptr->right;
            }
        }
        else{
            if(ptr->left==NULL){
                ptr->left = x;
                x->parent = ptr;
                break;
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
    node* x = new_node();
    x->data = data;
    root = insert_bst(root,x);
    // TODO: Call to balance
    return root;
}

node* delete(node* root, int data){
    node* ptr = root;
    while(ptr!=NULL){
        if(ptr->data==data){
            if(ptr->left==NULL && ptr->right==NULL){
                if(ptr->parent!=NULL){
                    if(ptr->parent->right==ptr){
                        ptr->parent->right = NULL;
                    }
                    else{
                        ptr->parent->left = NULL;
                    }
                }
                else{
                    return NULL;
                }
            }
            else if(ptr->left==NULL){
                if(ptr->parent!=NULL){
                    ptr->right->parent = ptr->parent;
                    if(ptr->parent->right==ptr){
                        ptr->parent->right = ptr->right;
                    }
                    else{
                        ptr->parent->left = ptr->right;
                    }
                }
                else{
                    ptr->right->parent = NULL;
                    return ptr->right;
                }
            }
            else if(ptr->right==NULL){
                if(ptr->parent!=NULL){
                    ptr->left->parent = ptr->parent;
                    if(ptr->parent->right==ptr){
                        ptr->parent->right = ptr->left;
                    }
                    else{
                        ptr->parent->left = ptr->left;
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
                root = delete(min_val);
            }
            // TODO: Call to balance
            return root;
        }
        else if(data>ptr->data){
            ptr = ptr->right;
        }
        else{
            ptr = ptr->left;
        }
    }
    return root;
}

int main(){
    node* root = NULL;
    return 0;
}