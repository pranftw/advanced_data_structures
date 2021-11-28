#include <stdio.h>
#include <stdlib.h>

struct node{
    int data;
    struct node* right;
    struct node* left;
};

typedef struct node node;

node* new_node(){
    node* x = (node*)malloc(sizeof(node));
    x->right = NULL;
    x->left = NULL;
    return x;
}

node* find_min(node* root){
    if(root->left==NULL){
        return root;
    }
    return find_min(root->left);
}

node* find_max(node* root){
    if(root->right==NULL){
        return root;
    }
    return find_max(root->right);
}

node* insert(node* root, int data){
    node* x = new_node();
    x->data = data;
    node* ptr = root;
    while(ptr!=NULL){
        if(data>ptr->data){
            if(ptr->right==NULL){
                ptr->right = x;
                break;
            }
            else{
                ptr = ptr->right;
            }
        }
        else{
            if(ptr->left==NULL){
                ptr->left = x;
                break;
            }
            else{
                ptr = ptr->left;
            }
        }
    }
    if(ptr==NULL){
        return x;
    }
    else{
        return root;
    }
}

node* delete(node* root, int data){
    node* ptr = root;
    node* prev = NULL;
    node* temp;
    while(ptr!=NULL){
        // printf("%d ",ptr->data);
        temp = ptr;
        if(ptr->data==data){
            //First check if data is greater than or <= the ptr data
            if(ptr->right==NULL && ptr->left==NULL){
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
                root = delete(root,min_val->data);
                ptr->data = min_val->data;
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

void print_bst(node* root){ //prints inorder of the tree, to visualize construct one in https://yongdanielliang.github.io/animation/web/BST.html
    if(root->left!=NULL){
        print_bst(root->left);
    }
    printf("%d ",root->data);
    if(root->right!=NULL){
        print_bst(root->right);
    }
}

int main(){
    node* root = NULL;
    root = insert(root,10);
    root = insert(root,4);
    root = insert(root,6);
    root = insert(root,5);
    root = insert(root,2);
    root = insert(root,3);
    root = insert(root,1);
    root = delete(root,4);
    print_bst(root);
    return 0;
}