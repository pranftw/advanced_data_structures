#include <stdio.h>
#include <stdlib.h>

struct node{
    int count;
    int data;
    struct node *next;
};

typedef struct node node;

node* new_node(){
    node *x = (node*)malloc(sizeof(node));
    x->count = 0;
    return x;
}

node* insert(int data, node* start){
    node* x = new_node();
    x->data = data;
    x->next = start;
    return x;
}

node* search_move2front(int data, node* start){
    node* ptr = start;
    node *prev = NULL;
    while(ptr!=NULL){
        if(ptr->data==data){
            if(prev!=NULL){
                prev->next = ptr->next;
            }
            if(ptr==start){
                return start;
            }
            ptr->next = start;
            return ptr;
        }
        prev = ptr;
        ptr = ptr->next;
    }
    return start;
}

node* search_count(int data, node* start){
    node *ptr = start;
    node *prev = NULL;
    while(ptr!=NULL){
        if(ptr->data==data){
            ptr->count = ptr->count + 1;
            if(prev!=NULL){
                prev->next = ptr->next;
            }
            node *temp = start;
            node *prev_temp = NULL;
            while(temp!=NULL){
                if(ptr->count >= temp->count){
                    if(prev_temp!=NULL){
                        node *temp_temp = prev_temp->next;
                        prev_temp->next = ptr;
                        temp->next = temp_temp;
                        return start;
                    }
                    else{
                        ptr->next = start;
                        return ptr;
                    }
                }
                prev_temp = temp;
                temp = temp->next;
            }
        }
        prev = ptr;
        ptr = ptr->next;
    }
    return start;
}

node* search_transpose(int data, node* start){
    node* ptr = start;
    node* prev = NULL;
    node* prev_prev = NULL;
    while(ptr!=NULL){
        if(ptr->data==data){
            if(prev!=NULL){
                prev->next = ptr->next;
            }
            else{
                ptr->next = start;
                return ptr;
            }
            if(prev_prev!=NULL){
                prev_prev->next = ptr;
                ptr->next = prev;
            }
            else{
                ptr->next = start;
                return ptr;
            }
        }
        prev_prev = prev;
        prev = ptr;
        ptr = ptr->next;
    }
    return start;
}

void print_ll(node *start){
    node* ptr = start;
    while(ptr!=NULL){
        printf("%d ",ptr->data);
        ptr = ptr->next;
    }
    printf("\n");
    ptr = start;
    while(ptr!=NULL){
        printf("%d ",ptr->count);
        ptr = ptr->next;
    }
    printf("\n");
    printf("\n");
}

int main(){
    node* start = NULL;
    start = insert(2,start);
    start = insert(5,start);
    start = insert(7,start);
    start = insert(8,start);
    print_ll(start);

    // Search Move to front

    // start = search_move2front(7, start);
    // print_ll(start);
    // start = search_move2front(5, start);
    // print_ll(start);

    // Search based on count

    // start = search_count(7, start);
    // print_ll(start);
    // start = search_count(8, start);
    // print_ll(start);
    // start = search_count(7, start);
    // print_ll(start);

    // Search based on transpose

    // start = search_transpose(7, start);
    // print_ll(start);
    // start = search_transpose(5, start);
    // print_ll(start);
    return 0;
}