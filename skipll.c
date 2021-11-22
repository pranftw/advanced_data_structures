#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct node{
    int data;
    struct node *next;
    struct node *down;
};

typedef struct node node;

node* new_node(){
    node *x = (node*)malloc(sizeof(node));
    return x;
}

node* insert(node *x, node *start, int data){
    x->data = data;
    if(start==NULL){
        x->next = NULL;
        return x;
    }
    node *ptr = start;
    node *prev = start;
    while(ptr!=NULL){
        if(data<ptr->data){
            break;
        }
        prev = ptr;
        ptr = ptr->next;
    }
    if(ptr==start&&prev==start){
        x->next = ptr;
        return x;
    }
    prev->next = x;
    x->next = ptr;
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

float gen_ran(){
    int val = rand();
    float ret_val = (val%10)*0.1;
    return ret_val;
}

node* search(int data, node *start){
    node *ptr = start;
    node *prev = start;
    while(ptr!=NULL){
        if(data==ptr->data){
            return ptr;
        }
        else if(data<ptr->data){
            return prev->down;
        }
        prev = ptr;
        ptr = ptr->next;
    }
    return ptr;
}

node* search_levels(int data, int max_level, node* arr[]){
    int i = max_level-1;
    node *ptr = arr[max_level-1];
    while(i>=0){
        ptr = search(data, ptr);
        if(ptr==NULL && i!=0){
            ptr = arr[i-1];
        }
        else if((ptr==NULL && i==0) || ptr->data==data){
            break;
        }
        i--;
    }
    return ptr;
}

//For deletion, make a search, get the pointer, delete the ptr element and for next
//element, go to "down" of ptr and keep going until ptr==NULL

node* insert_levels(int max_levels, node *arr[], int data){
    node *start;
    node *x;
    node *prev = NULL;
    float rand_val;
    for(int i=0;i<max_levels;i++){
        rand_val = gen_ran();
        if(rand_val>=0.5 || i==0){
            x = new_node();
            x->down = prev;
            start = arr[i];
            start = insert(x, start, data);
            arr[i] = start;
            prev = x;
        }
        else{
            break;
        }
    }
    return *arr;
}

void print_all_levels(int max_levels, node* arr[]){
    printf("\n");
    for(int i=0;i<max_levels;i++){
        printf("Level %d: ",i);
        print_ll(arr[i]);
    }
    printf("\n");
}

int main(){
    srand(time(NULL));
    const int max_levels = 5;
    node* arr[max_levels];
    for(int i=0;i<max_levels;i++){
        arr[i] = NULL;
    }

    *arr = insert_levels(max_levels, arr, 1);
    *arr = insert_levels(max_levels, arr, 4);
    *arr = insert_levels(max_levels, arr, 2);

    node *is_present = search_levels(4,max_levels, arr);
    if(is_present==NULL){
        printf("False");
    }
    else{
        printf("True");
    }
    print_all_levels(max_levels,arr);
    return 0;
}