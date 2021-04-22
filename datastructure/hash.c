#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define PRIME_HASH_SIZE 100000037 // hash 테이블의 크기는 무조건 소수로 설정
#define MALLOC_SIZE 200000000

typedef struct _NODE
{ // key : char[7]  value : int
    char key[7];
    int data;
    struct _NODE *next;
} NODE;

NODE *prime_hash_table[PRIME_HASH_SIZE];
NODE myalloc_array[MALLOC_SIZE];
unsigned long myalloc_idx = 0;

////////// for test ///////////

#define TEST_CASES 1000000

char test_set[TEST_CASES][7];

char (*generate_random_string(void))[7]
{

    srand(time(NULL));

    for (int i = 0; i < TEST_CASES; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            test_set[i][j] = rand() % 26 + 'a';
        }
        test_set[i][6] = '\0';
    }

    return test_set;
}

///////////////////////////////////

////////// util functions ///////////

NODE *myalloc(void)
{
    return &myalloc_array[myalloc_idx++];
}

int mystrcmp(char *a, char *b)
{
    while (*a != '\0' && *b != '\0')
    {
        if (*a++ != *b++)
        {
            return *a - *b;
        }
    }
    return 0;
}

void mystrcpy(char *src, char *dst)
{
    while ((*dst++ = *src++) != '\0')
    {
    }
}

////////////////////////////////////

unsigned long hash_func(const char *str)
{
    unsigned long hash = 5381;
    char c;
    while (c = *str++)
    {
        // hash 에 33 을 곱한 후 현재 현재 char 의 값을 더함
        // 곱셈 연산 비트연산을 사용함으로써 속도 up
        hash = (((hash << 5) + hash) + c) % PRIME_HASH_SIZE; 
    }
    return hash;
}

void insert(const char *str, int data)
{
    unsigned long hash_key = hash_func(str);
    NODE *entity_head = prime_hash_table[hash_key];

    // 해당 엔티티의 링크드 리스트에 head 에 추가 ( 끝에 추가하게 되면, 링크드 리스트를 순회해야 하여 느려짐 )

    NODE *new_node = myalloc();

    mystrcpy(str, new_node->key);
    new_node->data = data;
    new_node->next = entity_head -> next;

    entity_head -> next = new_node;
}

int find(const char *str)
{
    unsigned long hash_key = hash_func(str); // hash 키 생성
    NODE *node = prime_hash_table[hash_key]->next;
    int idx = 0;
    while (node)
    { // hash table entity 의 linked list 에서 해당 스트링 검색
        if (!mystrcmp(node->key, str))
        {
            return node->data;
        }

        idx++;
        node = node->next;
    }

    return -1; // 없을 시 -1 반환
}

int main(void)
{

    // test set 준비
    char(*test_set)[7] = generate_random_string();

    // hash table 초기화
    for (int i = 0; i < PRIME_HASH_SIZE; i++)
    {
        prime_hash_table[i] = myalloc(); // dummy head
    }

    clock_t insert_st = clock();

    printf("start hash table test : insert - %d times, find - %d times\n", TEST_CASES, TEST_CASES);
    // 테스트 케이스를 hash table 에 입력
    for (int i = 0; i < TEST_CASES; i++)
    {
        insert(test_set[i], rand());
    }
    clock_t insert_ed = clock();

    clock_t find_st = clock();
    // 테스트 케이스 검색
    for (int i = 0; i < TEST_CASES; i++)
    {
        find(test_set[i]);
    }

    clock_t find_ed = clock();

    printf("elapsed time : insert -  %.5f sec, find - %.5f sec \n", (float)(insert_ed - insert_st) / CLOCKS_PER_SEC, (float)(find_ed - find_st) / CLOCKS_PER_SEC);
}
