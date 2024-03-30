#include <stdlib.h>
#include <stdio.h>

#define min(a, b) (a) < (b) ? (a) : (b)
#define max(a, b) (a) > (b) ? (a) : (b)


typedef struct {
    int to;
} Edge;

typedef struct {
    int cap;
    int len;
    Edge *buf;
} EdgeList;


void EdgeList_reserve(EdgeList *self, int cap) {
    if (self->cap < cap) {
        self->cap = max(max(cap, self->cap * 1.25), 4);
        self->buf = realloc(self->buf, self->cap * sizeof(Edge));
    }
}

void EdgeList_push(EdgeList *self, Edge item) {
    EdgeList_reserve(self, self->len + 1);

    self->buf[self->len] = item;
    self->len += 1;
}

typedef struct {
    EdgeList neighbors;
} Node;

typedef struct {
    Node *nodes;
    int node_amount;
}Graph;

void Graph_Init(Graph* self, int amount) {
    self->node_amount = amount;
    self->nodes = calloc(amount, sizeof(Node));
}

void Graph_AddEdge(Graph *self, int from, int to) {
    Edge e;
    e.to = to;

    EdgeList_push(&self->nodes[from].neighbors, e);
}

void Graph_Free(Graph *self) {
    for (int i = 0; i < self->node_amount; i++) {
        free(self->nodes[i].neighbors.buf);
    }
    free(self->nodes);
}


typedef struct {
    int node_i;
    int deph;
} DequeEl;


typedef struct Deque {
    int head;
    int len;
    int cap;
    DequeEl *buf;
} Deque;

void Deque_InitWithCapasity(Deque *self, int withCap) {
    self->head = 0;
    self->len = 0;
    self->cap = withCap;
    self->buf = malloc(withCap * sizeof(DequeEl));
}

void Deque_Push(Deque *self, DequeEl value) {
    int ind_to_put = (self->head + self->len) % self->cap;

    self->buf[ind_to_put] = value;
    self->len += 1;
}

DequeEl Deque_Pop(Deque *self) {
    int ind_to_pop = self->head;

    self->len -= 1;
    self->head = (self->head + 1) % self->cap;
    return self->buf[ind_to_pop];
}

void Deque_Free(Deque *self) {
    free(self->buf);
}


void bfs(Graph graph, int *arr) {
    Deque deque;
    Deque_InitWithCapasity(&deque, graph.node_amount);
    
    DequeEl curel;
    curel.node_i = 0;
    curel.deph = 1;
    Deque_Push(&deque, curel);

    while (deque.len > 0) {
        curel = Deque_Pop(&deque);

        if (arr[curel.node_i] == 0) {
            arr[curel.node_i] = curel.deph;
            EdgeList neighbors = graph.nodes[curel.node_i].neighbors;

            curel.deph++;

            for (int i = 0; i < neighbors.len; i++) {
                curel.node_i = neighbors.buf[i].to;
                Deque_Push(&deque, curel);
            }
        }
    }

    Deque_Free(&deque);
}

int main(int argc, char *argv[])
{
    int n, m;
    scanf("%d %d", &n, &m);

    Graph g;
    Graph_Init(&g, n);

    for (int i = 0; i < m; i++) {
        int from, to;
        scanf("%d %d", &from, &to);
        Graph_AddEdge(&g, from - 1, to - 1);
    }

    int *arr = calloc(n, sizeof(int));

    bfs(g, arr);

    for (int i = 0; i < n; i++) {
        printf("%d\n", arr[i] - 1);
    }

    Graph_Free(&g);
    free(arr);

    return EXIT_SUCCESS;
}
