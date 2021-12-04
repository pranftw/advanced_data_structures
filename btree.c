#include <stdio.h>
#include <stdlib.h>

struct node{
    int* data;
    struct node* children;
    struct node* parent;
};

typedef struct node node;

node* new_node(int order){
    node* x = (node*)malloc(sizeof(node));
    // Create new data and children array and add their addresss to the pointers in node
    const int child_order = order;
    const int key_order = order-1;
    int data[key_order];
    node* children[child_order];
    for(int i=0;i<order;i++){
        children[i] = NULL;
        if(i<order-1){
            data[i] = NULL;
        }
    }
    x->data = &data;
    x->children = &children;
    return x;
}

void sort(int data[], int order){
    int swaps = 0;
    int temp;
    do{
        for(int i=1;i<order-1;i++){ // order-1 because we are sorting keys, whose length is only order-1
            if(data[i]<data[i-1]){
                temp = data[i];
                data[i] = data[i-1];
                data[i-1] = temp;
                swaps++;
            }
        }
    }while(swaps!=0);
}

int main(){
    node* root = NULL;
}