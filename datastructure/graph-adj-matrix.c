#include <stdio.h>

#define GRAPH_SIZE 10000

// boolean type 이 1byte 이므로 adj_matrix 는 (graph-size)^2의 크기를 가지게 된다.
// 따라서 메모리 제한이 있는 경우 ( 보통 128 MB ) 그래프 노드의 개수가 1e4 정도까지만 adj matrix 방법을 사용할 수 있다.
char adj_matrix[GRAPH_SIZE][GRAPH_SIZE];

void connect(int node_1, int node_2)
{
    adj_matrix[node_1][node_2] = 1;
    adj_matrix[node_2][node_1] = 1;
}

int check(int node_1, int node_2)
{
    return adj_matrix[node_1][node_2];
}

int main(void)
{

    for (int i = 0; i < GRAPH_SIZE; i++)
        for (int j = 0; j < GRAPH_SIZE; j++)
            adj_matrix[i][j] = 0;

    return 0;
}