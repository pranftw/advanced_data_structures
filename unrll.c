#include <stdio.h>
#include <stdlib.h>
#define max_num 2

struct node{
    int data[max_num];
    int num_elem;
    struct node *next;
};

typedef struct node node;

node* new_node(){
    node *x = (node*)malloc(sizeof(node));
    x->num_elem = 0;
    for(int i=0;i<max_num;i++){
        x->data[i] = NULL;
    }
    return x;
}

node* insert(int data, node* start){
    node* ptr = start;
    while(ptr!=NULL){
        if(ptr->num_elem!=max_num){
            for(int i=0;i<max_num;i++){
                if(ptr->data[i]==NULL){
                    ptr->data[i] = data;
                    ptr->num_elem++;
                    return start;
                }
            }
        }
        ptr = ptr->next;
    }
    node *x = new_node();
    x->data[x->num_elem] = data;
    x->num_elem++;
    x->next = start;
    return x;
}

node* delete(int idx, node* start){
    int ptr_idx = idx/max_num;
    int inside_arr_idx = idx%max_num;
    node* ptr = start;
    node* prev = NULL;
    int i=0;
    while(ptr!=NULL){
        if(i==ptr_idx){
            if(ptr->num_elem==1){
                if(prev!=NULL){
                    prev->next = ptr->next;
                }
                free(ptr);
                return NULL;
            }
            else{
                ptr->data[inside_arr_idx] = NULL;
                ptr->num_elem--;
            }
            return start;
        }
        i++;
        prev = ptr;
        ptr = ptr->next;
    }
    return start;
}

void print_ll(node *start){
    node *ptr = start;
    while(ptr!=NULL){
        for(int i=0;i<max_num;i++){
            if(ptr->data[i]!=NULL){
                printf("%d ",ptr->data[i]);
            }
            else{
                printf("NULL ");
            }
        }
        printf("\t");
        ptr = ptr->next;
    }
    printf("\n");
}

int main(){
    node *start = NULL;
    // start = insert(1,start);
    // start = insert(5,start);
    // start = insert(8,start);
    // start = insert(9,start);
    // start = insert(3,start);
    // start = insert(2,start);
    start = insert(1,start);
    print_ll(start);
    start = delete(0,start);
    print_ll(start);
    start = insert(1,start);
    print_ll(start);
    return 0;
}