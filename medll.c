#include <stdio.h>
#include <stdlib.h>

struct node{
    int data;
    struct node *link;
};

typedef struct node node;

node* new_node(){
    node *x = (node*)malloc(sizeof(node));
    return x;
}

node *XOR(node *x, node *y){
    node *xord = (node*)((uintptr_t)(x)^(uintptr_t)(y));
    return xord;
}

node *get_next(node *ptr, node *prev){
    node *next = XOR(ptr->link, prev);
    return next;
}

node *get_prev(node *ptr, node *next){
    node *prev = XOR(ptr->link, next);
    return prev;
}

node* insert_front(node *start, int data){
    node *x = new_node();
    x->data = data;
    x->link = start;
    if(start!=NULL){
        node *start_next = get_next(start, NULL);
        start->link = XOR(x, start_next);
    }
    return x;
}

node* insert_rear(node *start, int data){
    node *x = new_node();
    x->data = data;
    if(start==NULL){
        x->link = NULL;
        return x;
    }
    
    node *prev = NULL;
    node *next;
    node *ptr = start;
    while(ptr!=NULL){
        next = get_next(ptr, prev);
        prev = ptr;
        ptr = next;
    }
    ptr = prev;
    x->link = ptr;
    node *ptr_prev = get_prev(ptr, NULL);
    ptr->link = XOR(ptr_prev, x);
    return start;
}

node* delete(node* start, int idx){
    node* ptr = start;
    node *prev = NULL;
    node* next;
    int i=0;
    while(ptr!=NULL){
        next = get_next(ptr, prev);
        if(i==idx){
            if(prev!=NULL){
                node* prev_prev = get_prev(prev,ptr);
                prev->link = XOR(prev_prev,next);
            }
            if(next!=NULL){
                node* next_next = get_next(next,ptr);
                next->link = XOR(prev,next_next);
            }
            free(ptr);
            if(prev==NULL){
                return next;
            }
            else{
                return start;
            }
        }
        i++;
        prev = ptr;
        ptr = next;
    }
    return start;
}

void print_ll(node *start){
    node *ptr = start;
    node *prev = NULL;
    node *next;
    while(ptr!=NULL){
        printf("%d ",ptr->data);
        next = get_next(ptr, prev);
        prev = ptr;
        ptr = next;
    }
    printf("\n");
}

void print_ll_backwards(node *start){
    node *ptr = start;
    node *prev = NULL;
    node *next;
    while(ptr!=NULL){
        next = get_next(ptr, prev);
        prev = ptr;
        ptr = next;
    }
    ptr = prev;
    next = NULL;
    while(ptr!=NULL){
        printf("%d ", ptr->data);
        prev = get_prev(ptr, next);
        next = ptr;
        ptr = prev;
    }
    printf("\n");
}

int main(){
    node* start = NULL;
    start = insert_front(start, 1);
    start = insert_front(start, 2);
    start = insert_front(start, 3);
    start = insert_front(start, 4);
    start = insert_rear(start, 5);
    print_ll(start);
    start = delete(start,4);
    print_ll(start);
    // print_ll_backwards(start);
}