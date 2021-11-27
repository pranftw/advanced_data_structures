#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max_str_len 50

struct node{
    char key[max_str_len];
    int data;
    struct node* next; 
};

typedef struct node node;

int get_random(int upper, int lower){
    int val = (rand()%(upper-lower+1))+lower;
    return val;
}

int hash_idx(int table_len, char key[]){
    int sum = 0;
    for(int i=0;i<max_str_len;i++){
        if(key[i]=='\0'){
            break;
        }
        sum = sum + key[i];
    }
    int val = sum%table_len;
    return val;
}

node* new_node(){
    node* x = (node*)malloc(sizeof(node));
    return x;
}

node* search(char key[], int table_len, node* table[]){
    int idx = hash_idx(table_len, key);
    node* ptr = table[idx];
    while(ptr!=NULL){
        if(strcmp(ptr->key,key)==0){
            break;
        }
        ptr = ptr->next;
    }
    return ptr; //Returns the pointer with the key else returns null
}

node* insert(int data, char key[], node* table[], int table_len){
    node* search_ptr = search(key,table_len,table);
    if(search_ptr!=NULL){
        search_ptr->data = data;
    }
    else{
        int idx = hash_idx(table_len, key);
        node* x = new_node();
        strcpy(x->key,key);
        x->data = data;
        x->next = table[idx];
        table[idx] = x;
    }
    return *table;
}

node* delete(char key[], int table_len, node* table[]){
    int idx = hash_idx(table_len, key);
    node* ptr = table[idx];
    node* prev = NULL;
    while(ptr!=NULL){
        if(strcmp(ptr->key,key)==0){
            if(prev!=NULL){
                prev->next = ptr->next;
            }
            else{
                table[idx] = ptr->next;
            }
            free(ptr);
            return *table;        
        }
        prev = ptr;
        ptr = ptr->next;
    }
    return *table;
}

void print_ll(node* table[], int table_len){
    node* ptr;
    for(int i=0;i<table_len;i++){
        ptr = table[i];
        printf("%d -> ",i);
        while(ptr!=NULL){
            printf("%s:%d ",ptr->key,ptr->data);
            ptr = ptr->next;
        }
        printf("\n");
    }
}

int main(){
    const int table_len = 7;
    node* table[table_len];
    for(int i=0;i<table_len;i++){
        table[i] = NULL;
    }
    *table = insert(2,"Hello",table,table_len);
    *table = insert(3,"World",table,table_len);
    *table = insert(5,"Boo",table,table_len); // These two
    *table = insert(6,"Cno",table,table_len); // are to check collisions
    print_ll(table, table_len);
    *table = delete("Foo",table_len,table);
    print_ll(table, table_len);
    return 0;
}