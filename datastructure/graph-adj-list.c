#include <stdio.h>

#define GRAPH_SIZE 10000
#define NODE_POOL 100000

typedef struct _NODE
{
    int data;
    struct _NODE *next;
} NODE;

NODE node_pool[NODE_POOL];
int myalloc_idx = 0;

////////// util functions ///////////

NODE *myalloc(void)
{
    return &node_pool[myalloc_idx++];
}
////////////////////////////////////

// adj list 는 ( 그래프 간선 개수 * 2 ) 개의 노드만 필요 하므로 메모리가 부족할 일은 거의 없다.
// 하지만 adj matrix 처럼 node 간의 연결 여부를 바로 알 수 없으므로 adj matrix 에 비해 속도가 느리다.

NODE *adj_list[GRAPH_SIZE];

void connect(int node_1, int node_2)
{
    // add node 2 to node 1's adj list
    NODE *new_node_1 = myalloc();
    new_node_1->data = node_2;
    new_node_1->next = adj_list[node_1];
    adj_list[node_1] = new_node_1;

    // add node 1 to node 2's adj list
    NODE *new_node_2 = myalloc();
    new_node_2->data = node_1;
    new_node_2->next = adj_list[node_2];
    adj_list[node_2] = new_node_2;
}

int check(int node_1, int node_2)
{

    for (NODE *p = adj_list[node_1]; p != NULL; p = p->next)
    {
        if (p->data == node_2)
            return 1; 
    }

    return 0;
}

int main(void)
{
    // init
    for (int i = 0; i < GRAPH_SIZE; i++)
    {
        adj_list[i] = NULL;
    }

    return 0;
}