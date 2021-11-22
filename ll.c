#include <stdio.h>
#include <stdlib.h>

struct node{
    int data;
    struct node *next;
};

typedef struct node node;

node *new_node(){
    node *x = (node*)malloc(sizeof(node));
    return x;
}

node *insert_front(node *start, int data){
    node *x = new_node();
    x->data = data;
    if(start==NULL){
        x->next = NULL;
    }
    else{
        x->next = start;
    }
    return x;
}

node *insert_rear(node *start, int data){
    node *x = new_node();
    x->data = data;
    if(start==NULL){
        x->next = NULL;
        return x;    
    }
    node *ptr = start;
    while(ptr->next!=NULL){
        ptr = ptr->next;
    }
    ptr->next = x;
    x->next = NULL;
    return start;
}

void print_ll(node *start){
    node *ptr = start;
    while(ptr!=NULL){
        printf("%d ",ptr->data);
        ptr = ptr->next;
    }
    printf("\n");
}

int main(){
    node *start = NULL;
    start = insert_front(start, 1);
    start = insert_front(start, 2);
    start = insert_front(start, 3);
    start = insert_front(start, 4);
    start = insert_rear(start, 5);
    print_ll(start);
    return 0;
}