#include<stdio.h>
#include<iostream>
#include<stdbool.h>
#define MAX_ELEMENT 20
#define m 100

int n = 8;
int W[9][9] = { m, m, m, m, m, m, m, m, m,
				m, 0, 5, 8, m, m, m, m, m,
				m, m, 0, 4, m, 4, m, m, m,
				m, m, m, 0, 2, m, m, 5, m,
				m, m, m, m, 0, m, m, m, 7,
				m, 1, m, m, m, 0, m, m, m,
				m, m, 6, m, m, 2, 0, m, m,
				m, m, m, m, 3, m, 8, 0, m,
				m, m, m, m, m, m, 5, 4, 0 };

typedef struct
{
	int level;
	int path[10];
	int bound;
}node;

typedef struct
{
	node heap[MAX_ELEMENT];
	int heap_size;
}HeapType;

void insert(HeapType *h, node item)
{
	int i;
	h->heap_size++;
	i = h->heap_size;

	while ((i != 1) && (item.bound < h->heap[i / 2].bound)){
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = item;
}

node delete1(HeapType *h)
{
    int parent, child, i;
    node item, temp;
 
    item = h->heap[1];
    temp = h->heap[(h->heap_size)];
    h->heap_size--;
 
    parent = 1;
    child = 2;
 
    while (child <= h->heap_size) {
        if ((child < h->heap_size) && (h->heap[child].bound) >(h->heap[child + 1].bound))
            child++;
        if (temp.bound <= h->heap[child].bound) break;
        h->heap[parent] = h->heap[child];
        parent = child;
        child *= 2;
    }
    h->heap[parent] = temp;
 
    return item;
}


bool empty(HeapType *h)
{
	bool switch_;
	switch_ = false;
	if (h->heap_size == 0) switch_ = true;
	return switch_;
}

void init(HeapType *h)
{
	h->heap_size = 0;
}

int bound(node u)
{
    int result_bound = 0;
    int min = m;
    int i, j;
    int check[9] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    
    if (u.level == 0) {
        for (i = 1; i <= n; i++) {
            for (j = 1; j <= n; j++) {
                if (W[i][j] != 0 && min > W[i][j]) min = W[i][j];
            }
            result_bound += min;
            min = m;
        }
    }
    
    else {
        for (i = 2; i <= n; i++) {
            if (u.path[i] != 0) {
                result_bound += W[u.path[i - 1]][u.path[i]];
                check[u.path[i]] = 1;
            }
        }
        for (i = 2; i <= n; i++)
            for (i = 2; i <= n; i++) {
                if (u.path[i + 1] > 0) continue;
                else {
                    for (j = 1; j <= n; j++) {
                        if (W[i][j] != 0 && min > W[i][j]) {
                            if (check[j] == 1) continue;
                            if (check[i] == 1 && j == 1) continue;
                            min = W[i][j];
                        }
                    }
                    result_bound += min;
                    min = m;
                }
            }
    }
    return result_bound;
}
 
int length(node u)
{
    int result_length = 0;
    int i;
    for (i = 2; i <= n + 1; i++)
        result_length += W[u.path[i - 1]][u.path[i]];
 
    return result_length;
}
 
void travel2()
{
    HeapType PQ;
    node u, v;
    int minlength, i, j, k;
    int test[9] = { -1, -1, 2, 3, 4, 5, 6, 7, 8 };
    int opttour[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    int stop, temp;
 
    init(&PQ);
    v.level = 0;
    for (i = 0; i <= n + 1; i++) {
        if (i == 1) v.path[i] = 1;
        else v.path[i] = 0;
    }
    v.bound = bound(v);
    minlength = m;
    insert(&PQ, v);
    while (!empty(&PQ)) {
        v = delete1(&PQ);
        if (v.bound < minlength) {
            u.level = v.level + 1;
 
            for (i = 2; i <= n; i++) {
                for (j = 1; j <= n + 1; j++)
                    u.path[j] = v.path[j];
                stop = 0;
                for (j = 2; j <= n; j++) {
                    if (u.path[j] == i) stop = 1;
                    if (j == n) u.path[u.level + 1] = i;
                }
                if (stop == 1) continue;
                if (u.level == n - 2) {
                    for (j = 2; j <= n; j++)
                        test[u.path[j]] = -1;
                    for (j = 2; j <= n; j++)
                        if (test[j] != -1) temp = j;
                    u.path[n] = temp;
                    u.path[n + 1] = 1;
                    test[2] = 2; test[3] = 3; test[4] = 4; test[5] = 5;
                    test[6] = 6; test[7] = 7; test[8] = 8;
                    if (length(u) < minlength) {
                        minlength = length(u);
                        for (j = 1; j <= n + 1; j++)
                            opttour[j] = u.path[j];
                    }
                }
                else {
                    u.bound = bound(u);
                    if (u.bound < minlength)
                        insert(&PQ, u);
                }
            }
        }
    }
    for (i = 1; i <= n + 1; i++) {
        if (i == 1) printf("최종경로 : %d -> ", opttour[i]);
        else if (i == n + 1) printf("%d 입니다.", opttour[i]);
        else printf(" %d -> ", opttour[i]);
    }
    printf("\n최적의 거리는 %d 입니다.\n", minlength);
}

int main()
{
    travel2();
    system("pause");
}
