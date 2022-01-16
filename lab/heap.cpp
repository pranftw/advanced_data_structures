#include <bits/stdc++.h> 
using namespace std; 
  
struct Node 
{ 
    int val, degree; 
    Node *parent, *child, *sibling; 
}; 
   
Node *root = NULL; 
  
void binomialLink(Node *h1, Node *h2) 
{ 
    h1->parent = h2; 
    h1->sibling = h2->child; 
    h2->child = h1; 
    h2->degree = h2->degree + 1; 
} 
  
Node *createNode(int n) 
{ 
    Node *new_node = new Node; 
    new_node->val = n; 
    new_node->parent = NULL; 
    new_node->sibling = NULL; 
    new_node->child = NULL; 
    new_node->degree = 0; 
    return new_node; 
} 
  
Node *mergeBHeaps(Node *h1, Node *h2) 
{ 
    if (h1 == NULL) 
        return h2; 
    if (h2 == NULL) 
        return h1; 

    Node *res = NULL; 
   
    if (h1->degree <= h2->degree) 
        res = h1; 
  
    else if (h1->degree > h2->degree) 
        res = h2; 
  
    while (h1 != NULL && h2 != NULL) 
    { 
        if (h1->degree < h2->degree) 
            h1 = h1->sibling; 
  
        else if (h1->degree == h2->degree) 
        { 
            Node *sib = h1->sibling; 
            h1->sibling = h2; 
            h1 = sib; 
        } 
  
        else
        { 
            Node *sib = h2->sibling; 
            h2->sibling = h1; 
            h2 = sib; 
        } 
    } 
    return res; 
} 
  
Node *unionBHeaps(Node *h1, Node *h2) 
{ 
    if (h1 == NULL && h2 == NULL) 
       return NULL; 
  
    Node *res = mergeBHeaps(h1, h2); 
  
    Node *prev = NULL, *curr = res, 
         *next = curr->sibling; 
    while (next != NULL) 
    { 
        if ((curr->degree != next->degree) || ((next->sibling != NULL) && (next->sibling)->degree == curr->degree)) 
        { 
            prev = curr; 
            curr = next; 
        } 
        else
        { 
            if (curr->val <= next->val) 
            { 
                curr->sibling = next->sibling; 
                binomialLink(next, curr); 
            } 
            else
            { 
                if (prev == NULL) 
                    res = next; 
                else
                    prev->sibling = next; 
                binomialLink(curr, next); 
                curr = next; 
            } 
        } 
        next = curr->sibling; 
    } 
    return res; 
} 
  
void binomialHeapInsert(int x) 
{ 
    root = unionBHeaps(root, createNode(x)); 
} 
   
void display(Node *h) 
{ 
    while (h) 
    { 
        cout << h->val << " "; 
        display(h->child); 
        h = h->sibling; 
    } 
} 

void revertList(Node *h) 
{ 
    if (h->sibling != NULL) 
    { 
        revertList(h->sibling); 
        (h->sibling)->sibling = h; 
    } 
    else
        root = h; 
} 
  
Node *extractMin(Node *h) 
{ 
    if (h == NULL) 
       return NULL; 
  
    Node *min_node_prev = NULL; 
    Node *min_node = h; 
  
    int min = h->val; 
    Node *curr = h;
    Node *prev = NULL; 
    while (curr!= NULL) 
    { 
        if (curr->val < min) 
        { 
            min = curr->val; 
            min_node_prev = prev; 
            min_node = curr; 
        }
        prev = curr; 
        curr = curr->sibling; 
    }
    if (min_node_prev == NULL && 
        min_node->sibling == NULL) 
        h = NULL; 
  
    else if (min_node_prev == NULL) 
        h = min_node->sibling; 
  
    else
        min_node_prev->sibling = min_node->sibling; 

    if (min_node->child != NULL) 
    { 
        revertList(min_node->child); 
        (min_node->child)->sibling = NULL; 
    } 
    return unionBHeaps(h, root); 
} 
  
Node *findNode(Node *h, int val) 
{ 
    if (h == NULL) 
      return NULL; 
  
    if (h->val == val) 
        return h; 
  
    Node *res = findNode(h->child, val); 
    if (res != NULL) 
       return res; 
  
    return findNode(h->sibling, val); 
} 

void decreaseKey(Node *H, int old_val, int new_val) 
{ 
    Node *node = findNode(H, old_val); 
   
    if (node == NULL) 
        return; 
  
    node->val = new_val; 
    Node *parent = node->parent; 
  
    while (parent != NULL && node->val < parent->val) 
    { 
        swap(node->val, parent->val); 
        node = parent; 
        parent = parent->parent; 
    } 
} 
   
Node *Delete(Node *h, int val) 
{ 
    if (h == NULL) 
        return NULL; 
  
    decreaseKey(h, val, -1); 
  
    return extractMin(h); 
} 
  
int main() 
{  
    int element,option;

    while(1){
        cout<<"\n\n1)Insert\n2)Delete\n3)Decrease\n4)Exit\n";
        cin>>option;
        switch(option){
            case 1: cout<<"\nEnter element: ";
                    cin>>element;
                    binomialHeapInsert(element); 
                    cout<<"\nHeap: ";
                    display(root);
                    break;
            case 2: cout<<"\nEnter element: ";
                    cin>>element;
                    Delete(root, element);
                    cout<<"\nHeap: ";
                    display(root);
                    break;
            case 3: cout << "\nEnter old element value: ";
                    int old_element, new_element;
                    cin>>old_element;
                    cout << "\nEnter new element value: ";
                    cin>>new_element;
                    decreaseKey(root,old_element,new_element);
                    cout<<"\nHeap: ";
                    display(root);
                    break;
            case 4: exit(0);
        }
    }
    return 0; 
} 

/*

OUTPUT

pranavsastry@Pranavs-MacBook-Pro:~/Documents/c/ads/lab$ runcpp heap.cpp 


1)Insert
2)Delete
3)Decrease
4)Exit
1

Enter element: 2

Heap: 2 

1)Insert
2)Delete
3)Decrease
4)Exit
1

Enter element: 4

Heap: 2 4 

1)Insert
2)Delete
3)Decrease
4)Exit
15


1)Insert
2)Delete
3)Decrease
4)Exit
1

Enter element: 5

Heap: 5 2 4 

1)Insert
2)Delete
3)Decrease
4)Exit
1

Enter element: 7

Heap: 2 5 7 4 

1)Insert
2)Delete
3)Decrease
4)Exit
1

Enter element: 6

Heap: 6 2 5 7 4 

1)Insert
2)Delete
3)Decrease
4)Exit
2

Enter element: 2

Heap: 4 5 7 6 

1)Insert
2)Delete
3)Decrease
4)Exit
3

Enter old element value: 7

Enter new element value: 1

Heap: 1 4 5 6 

1)Insert
2)Delete
3)Decrease
4)Exit
^C
*/