#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NODE_POOL 100000

int arr_idx = 0;

typedef struct _NODE
{
    int v;
} NODE;

// NODE_POOL  만큼의 메모리를 실행 전 미리 할당
NODE node_pool[NODE_POOL];

NODE *myalloc(void)
{
    return &node_pool[arr_idx++];
}

int main(void)
{
    // malloc 을 100000 번 테스트
    printf("start malloc test : 100000 loop\n");

    clock_t st = clock();
    for (int i = 0; i < 10000; i++)
    {
        NODE *node = (NODE *)malloc(sizeof(NODE));
        free(node);
    }
    clock_t ed = clock();

    printf("elapsed time : %.5f sec \n", (float)(ed - st) / CLOCKS_PER_SEC);

    // my alloc 을 100000 번 테스트

    printf("start myalloc test : 100000 loop\n");
    st = clock();
    for (int i = 0; i < 100000; i++)
    {
        NODE *node = myalloc();
    }
    ed = clock();

    printf("elapsed time : %.5f sec \n", (float)(ed - st) / CLOCKS_PER_SEC);
}