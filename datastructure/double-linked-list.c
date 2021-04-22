#include <stdio.h>

#define NODE_POOL 10000

typedef struct _NODE
{
    int data;
    struct _NODE *prev;
    struct _NODE *next;
} NODE;

NODE node_pool[NODE_POOL];

////////// util functions ///////////
int myalloc_idx = 0;

NODE *myalloc(void)
{
    return &node_pool[myalloc_idx++];
}
////////////////////////////////////

NODE *head;
NODE *tail;


void insert(int data) {
    NODE * new_node = myalloc();
    new_node->data = data;

    next = head -> next;
    // head 와 new node 연결
    head -> next = new_node;
    new_node -> prev = head;
    // head -> next 였던 node 와 new node 연결
    new_node -> next = next;
    next -> prev = new_node;
}

NODE* find(int data) {
    for(NODE* p = head->next; p != tail; p = p -> next) {
       if(p->data == data) {
           return p;
       } 
    }
    return tail;
}

void delete(int data) {
    NODE* prev = head;
    for(NODE* p = head->next; p != tail; p = p -> next) {
       if(p->data == data) {
           prev -> next = p -> next;
           p -> next -> prev = prev;
       } 
    }
}


int main(void)
{
    // init
    head = myalloc();
    tail = myalloc();
    head->next = tail;
    tail->prev = head;
        



    return 0;
}