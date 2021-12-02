#include <stdio.h>
#include <stdlib.h>

// If red black properties aren't satisfied by recoloring, only then you check balance.

struct node{
    int data;
    struct node* left;
    struct node* right;
    struct node* parent;
    int color; // Red 1 Black 0
};

typedef struct node node;

node* new_node(){
    node* x = (node*)malloc(sizeof(node));
    x->right = NULL;
    x->left = NULL;
    x->color = 1;
    return x;
}

node* find_min(node* root){
    if(root->left==NULL){
        return root;
    }
    return find_min(root->left);
}

int get_max(int x,int y){
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

int get_color(node* node_ptr){
    if(node_ptr!=NULL){
        return node_ptr->color;
    }
    return 0;
}

node* rotate_right(node* root, node* node_ptr){
    node* y = node_ptr;
    node* x = y->left;
    node* b = x->right;
    x->parent = y->parent;
    if(y->parent!=NULL){
        if(y->parent->right==y){
            y->parent->right = x;
        }
        else{
            y->parent->left = x;
        }
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
    if(x->parent!=NULL){
        if(x->parent->right==x){
            x->parent->right = y;
        }
        else{
            x->parent->left = y;
        }
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
    node* temp;
    // Balance required if ptr's grandparent has one red and one black child, but recoloring required
    // Balance not required when ptr's grandparent has two red children, but recoloring required
    while(get_color(ptr)==1 && get_color(ptr->parent)==1){ // Only balance if both ptr and its parent are red
        node* ptrs_gp = ptr->parent->parent;
        if(ptrs_gp!=NULL){
            if(get_color(ptrs_gp->left) + get_color(ptrs_gp->right)==2){ // Both are red
                ptrs_gp->right->color = 0;
                ptrs_gp->left->color = 0;
                if(ptrs_gp->parent!=NULL){
                    ptrs_gp->color = 1;
                    ptr = ptrs_gp; // Here next ptr will be ptrs grandparent as it got recolored to red
                }
            }
            else{ // One child is red and another is black
                // Only balance is required in this case
                ptrs_gp->color = 1 // True in every case, there is no need to check if its parent is null, because after rotation it will be a child
                if(diff(ptrs_gp)<0 && diff(ptrs_gp->left)<0){ // Both are left heavy
                    ptr->parent->color = 0;
                    root = rotate_right(root,ptrs_gp);
                    ptr = ptr->parent; // Here in these two cases, ptr's parent will be next ptr as after rotation, they become the root of the subtree
                }
                else if(diff(ptrs_gp)>0 && diff(ptrs_gp->right)>0){ // Both are right heavy
                    ptr->parent->color = 0;
                    root = rotate_left(root,ptrs_gp);
                    ptr = ptr->parent; // Here in these two cases, ptr's parent will be next ptr as after rotation, they become the root of the subtree
                }
                else if(diff(ptrs_gp)<0 && diff(ptrs_gp->left)>0){ // One is left heavy and other is right heavy
                    // Here in these two cases, the ptr itself becomes the new root after both the rotations
                    ptr->color = 0;
                    root = rotate_left(root,ptrs_gp->left);
                    root = rotate_right(root,ptrs_gp);
                }
                else if(diff(ptrs_gp)>0 && diff(ptrs_gp->right)<0){ // One is right heavy and other is left heavy
                    // Here in these two cases, the ptr itself becomes the new root after both the rotations
                    ptr->color = 0;
                    root = rotate_right(root,ptrs_gp->right);
                    root = rotate_left(root,ptrs_gp);
                }
            }
        }
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
        x->color = 0; // Root should always be black
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
    root = balance(root,x);
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
                root = delete(root,min_val->data);
                ptr->data = min_val->data;
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
    return root;
}

void print_redblack(node* root){
    if(root!=NULL){
        print_redblack(root->left);
        printf("%d ",root->data);
        print_redblack(root->right);
    }
}

int main(){
    node* root = NULL;
    root = insert(root,10);
    root = insert(root,8);
    root = insert(root,6);
    root = insert(root,3);
    root = insert(root,2);
    root = insert(root,4);
    root = insert(root,5);
    root = insert(root,7);
    print_redblack(root);
    printf("\n");
    printf("%d\n",root->data);
    return 0;
}