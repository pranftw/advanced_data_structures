#include <stdio.h>
#include <stdlib.h>

struct node{
    int data;
    struct node* parent;
    struct ll_node* children;
};

typedef struct node node;

struct ll_node{
    node* data;
    struct ll_node* next;
};

typedef struct ll_node ll_node;

node* new_node(){
    node* x = (node*)malloc(sizeof(node));
    x->parent = NULL;
    x->children = NULL;
    return x;
}

ll_node* new_ll_node(){
    ll_node* x = (ll_node*)malloc(sizeof(ll_node));
    return x;
}

ll_node* insert_ll(ll_node* start, node* data){
    ll_node* x = new_ll_node();
    x->next = start;
    x->data = data;
    start = x;
    return start;
}

int get_order(node* root){
    if(root->children==NULL){
        return 0;
    }
    ll_node* ptr = root->children;
    int max_val = 0;
    while(ptr!=NULL){
        int child_order = 1 + get_order(ptr->data);
        if(child_order>max_val){
            max_val = child_order;
        }
        ptr = ptr->next;
    }
    return max_val;
}

ll_node* sort_by_order(ll_node* start){
    ll_node* ptr = start;
    int swaps = 0;
    do{
        swaps = 0;
        ll_node* inner_ptr = start;
        ll_node* inner_prev = NULL;
        while(inner_ptr->next!=NULL){
            if(get_order(inner_ptr->data)>get_order(inner_ptr->next->data)){
                ll_node* temp = inner_ptr->next;
                inner_ptr->next = temp->next;
                temp->next = inner_ptr;
                if(inner_prev!=NULL){
                    inner_prev->next = temp;
                }                
                if(inner_ptr==start){
                    start = temp;
                }
                swaps++;
            }
            inner_prev = inner_ptr;
            inner_ptr = inner_ptr->next;
        }
    }while(swaps!=0);
    return start;
}

ll_node* merge(ll_node* sorted_start){
    int merges = 0;
    do{
        merges = 0;
        ll_node* ptr = sorted_start;
        ll_node* prev = NULL;
        while(ptr!=NULL && ptr->next!=NULL){
            if(get_order(ptr->data)==get_order(ptr->next->data)){
                if(ptr->data->data<=ptr->next->data->data){
                    ptr->data->parent = ptr->next->data;
                    if(ptr->data->parent!=NULL){
                        ptr->data->parent->children = insert_ll(ptr->data->parent->children,ptr->data);
                    }
                    if(prev!=NULL){
                        prev->next = ptr->next;
                    }
                    if(ptr==sorted_start){
                        sorted_start = ptr->next;
                    }
                }
                else{
                    ptr->next->data->parent = ptr->data;
                    if(ptr->next->data->parent!=NULL){
                        ptr->next->data->parent->children = insert_ll(ptr->next->data->parent->children, ptr->next->data);
                    }
                    ptr->next = ptr->next->next;
                }
                merges++;
            }
            prev = ptr;
            ptr = ptr->next;
        }
    }while(merges!=0);
    return sorted_start;
}

ll_node* insert(ll_node* start, int data){
    node* x = new_node();
    x->data = data;
    start = insert_ll(start, x);
    start = sort_by_order(start);
    start = merge(start);
    return start;
}

node* search_ll(ll_node* start, int value){

}

node* search(node* root, int value){
    if(root->data==value){
        return root;
    }
    ll_node* its_children = root->children;
    ll_node* ptr = its_children;
    while(ptr!=NULL){
        
        ptr = ptr->next;
    }
}

int main(){
    ll_node* heap = NULL;
    heap = insert(heap, 2);
    heap = insert(heap, 3);
    heap = insert(heap,4);
    printf("%d",heap->next->data->data);
    return 0;
}