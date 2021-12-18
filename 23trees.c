#include <stdio.h>
#include <stdlib.h>

struct node{
    int key1, key2, temp_key;
    struct node* child1;
    struct node* child2;
    struct node* child3;
    struct node* temp_child;
    struct node* parent;
};

typedef struct node node;

node* new_node(){
    node* x = (node*)malloc(sizeof(node));
    x->key1 = -1;x->key2 = -1;x->temp_key = -1;
    x->child1 = NULL;x->child2 = NULL;x->child3 = NULL;x->temp_child = NULL;
    return x;
}

node* search(node* root, int data){
    node* ptr = root;
    node* found = NULL;
    while(ptr!=NULL){
        if(data<=ptr->key1){
            if(data==ptr->key1){
                found = ptr;
                break;
            }
            else{
                ptr = ptr->child1;
            }
        }
        else if(data>ptr->key1 && (data<=ptr->key2 || ptr->key2==-1)){
            if(data==ptr->key2){
                found = ptr;
                break;
            }
            else{
                ptr = ptr->child2;
            }
        }
        else if(data>ptr->key2){
            ptr = ptr->child3;
        }
    }
    return found;
}

int get_key_count(node* node_ptr){
    int key_count = 0;
    if(node_ptr->key1!=-1){
        key_count++;
    }
    if(node_ptr->key2!=-1){
        key_count++;
    }
    if(node_ptr->temp_key!=-1){
        key_count++;
    }
    return key_count;
}

node* split(node* node_ptr){
    node* ptr = node_ptr;
    node* parent = node_ptr->parent;
    int temp;
    int middle_key = ptr->key2;
    node* sub_child1 = new_node();
    sub_child1->key1 = ptr->key1;
    node* sub_child2 = new_node();
    sub_child2->key1 = ptr->temp_key;
    sub_child1->child1 = ptr->child1;
    sub_child1->child2 = ptr->child2;
    sub_child2->child1 = ptr->child3;
    sub_child2->child2 = ptr->temp_child;
    if(parent!=NULL){
        sub_child1->parent = parent;
        sub_child2->parent = parent;
        if(middle_key<=parent->key1){
            temp = parent->key1;
            parent->key1 = middle_key;
            parent->key2 = temp;
            parent->child3 = parent->child2;
            parent->child1 = sub_child1;
            parent->child2 = sub_child2;
        }
        else if(middle_key>parent->key1 && (middle_key<=parent->key2 || parent->key2==-1)){
            temp = parent->key2;
            parent->key2 = middle_key;
            parent->temp_key = temp;
            parent->temp_child = parent->child3;
            parent->child2 = sub_child1;
            parent->child3 = sub_child2;
        }
        else if(middle_key>parent->key2){
            parent->temp_key = middle_key;
            parent->child2 = sub_child1;
            parent->child3 = sub_child2;
        }
        return parent;
    }
    else{
        node* new_parent = new_node();
        new_parent->parent = NULL;
        new_parent->key1 = middle_key;
        new_parent->child1 = sub_child1;
        new_parent->child2 = sub_child2;
        sub_child1->parent = new_parent;
        sub_child2->parent = new_parent;
        return new_parent;
    }
}

node* balance(node* root, node* node_ptr){
    node* ptr = node_ptr;
    while(get_key_count(ptr)==3){
        ptr = split(ptr);
    }
    if(ptr->parent==NULL){
        return ptr;
    }
    return root;
}

node* insert(node* root, int data){
    node* ptr = root;
    int temp;
    while(ptr!=NULL){
        if(data<=ptr->key1){
            if(ptr->child1==NULL){
                temp = ptr->key1;
                ptr->key1 = data;
                ptr->key2 = temp;
                break;
            }
            else{
                ptr = ptr->child1;
            }
        }
        else if(data>ptr->key1 && (data<=ptr->key2 || ptr->key2==-1)){
            if(ptr->child2==NULL){
                temp = ptr->key2;
                ptr->key2 = data;
                ptr->temp_key = temp;
                break;
            }
            else{
                ptr = ptr->child2;
            }
        }
        else if(data>ptr->key2){
            if(ptr->child3==NULL){
                ptr->temp_key = data;
                break;
            }
            else{
                ptr = ptr->child3;
            }
        }
    }
    if(ptr==NULL){
        node* x = new_node();
        x->key1 = data;
        x->parent = NULL;
        return x;
    }
    root = balance(root, ptr);
    return root;
}

void print_23(node* root){
    if(root!=NULL){
        print_23(root->child1);
        if(root->key1!=-1){
            printf("%d ",root->key1);
        }
        print_23(root->child2);
        if(root->key2!=-1){
            printf("%d ",root->key2);
        }
        print_23(root->child3);
    }
}

int main(){
    node* root = NULL;
    root = insert(root,20);
    root = insert(root,40);
    root = insert(root,50);
    root = insert(root,30);
    root = insert(root,60);
    root = insert(root,35);
    print_23(root);
    printf("\n");
    node* search_ptr = search(root,100);
    if(search_ptr!=NULL){
        printf("Found!\n");
    }
    else{
        printf("Not found!\n");
    }
    return 0;
}