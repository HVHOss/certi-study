#include <stdio.h>

#define MAX_NODE 1000000
#define NODE_POOL (2 * MAX_NODE)

typedef struct _NODE
{
    int data;     // 현재 node 의 unique id
    struct _NODE *next; // 링크드 리스트의 다음 node
} NODE;

NODE node_pool[NODE_POOL];

int parent_info[NODE_POOL];
NODE *child_info[NODE_POOL];

////////// util functions ///////////
int myalloc_idx = 0;

NODE *myalloc(void)
{
    return &node_pool[myalloc_idx++];
}
////////////////////////////////////

void connect(int parent_id, int child_id)
{   
    printf("connect node - parent : %d, child : %d \n", parent_id, child_id);
    // child 의 부모 노드 정보에 parent id 를 저장
    parent_info[child_id] = parent_id;

    NODE *new_node = myalloc();

    // 새 노드를 생성하여 child 의 정보 입력
    new_node->data = child_id;
    new_node->next = child_info[parent_id];
    child_info[parent_id] = new_node;
}


void travel(int node_id) {
    printf("travel node - current : %d \n", node_id);

    // 재귀로 현재 노드의 하위 노드를 탐색 ( dfs )
    for(NODE *p = child_info[node_id]; p != NULL; p = p->next) {
        travel(p->data);
    }
}

int main(void)
{
    // init
    myalloc_idx = 0;
    for(int i = 0; i < NODE_POOL; i++) {
        child_info[i] = NULL;
        parent_info[i] = -1;
    }

    int N;
    scanf("%d", &N);

    // 부모 - 자식 관계 입력
    int parent, child;
    for(int i = 0; i < N; i++) {
        scanf("%d  %d\n", &parent, &child);
        connect(parent, child);
    }

    // root 노드르 찾기 위해서는 아무 노드에서 부모 노드를 찾아 올라가거나,
    // parent_info 가 혼자 -1 인 node 를 찾으면 됨

    int root_id = child;

    while(parent_info[root_id] != -1) {
        root_id = parent_info[root_id];
    }

    // root 로 부터 트리 dfs 로 순회

    travel(root_id);


    return 0;
}
