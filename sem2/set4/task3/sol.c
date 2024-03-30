#include "sol.h"
#include <stdlib.h>

typedef struct {
    int to;
    int weight;
} EdgeInList;

typedef struct {
    int cap;
    int len;
    EdgeInList *buf;
} EdgeList;

#define max(a, b) (a) > (b) ? (a) : (b)

void EdgeList_reserve(EdgeList *self, int cap) {
    if (self->cap < cap) {
        self->cap = max(cap, self->cap * 1.25);
        self->buf = realloc(self->buf, self->cap * sizeof(EdgeInList));
    }
}

void EdgeList_push(EdgeList *self, EdgeInList item) {
    EdgeList_reserve(self, self->len + 1);

    self->buf[self->len] = item;
    self->len += 1;
}


EdgeList *incidentList;


// implement these functions in your solution:
// this function is called first to initialize graph
// you are expected to read graph here and fill internal data structures
void init() {
    incidentList = calloc(getVerticesCount(), sizeof(EdgeList));
    
    Edge edge;
    while (readEdge(&edge)) {
        EdgeInList eil;
        eil.weight = edge.weight;

        eil.to = edge.to;
        EdgeList_push(&incidentList[edge.from], eil);

        eil.to = edge.from;
        EdgeList_push(&incidentList[edge.to], eil);
    }
}

//this function is called whet the graph is no more needed
//you are expected to cleanup the used resources
void destroy() {
    for (int i = 0; i < getVerticesCount(); i++) {
        free(incidentList[i].buf);
    }
    free(incidentList);
}


// returns number of edges indicent to vertex iVertex
int getEdgesCount(int iVertex) {
    return incidentList[iVertex].len;
}

// returns iIndex-th edge incident to the vertex iVertex
// it must have .from == Vertex and .to denoting the other end
Edge getIncidentEdge(int iVertex, int iIndex) {
    EdgeInList eil = incidentList[iVertex].buf[iIndex];

    Edge e;
    e.from = iVertex;
    e.to = eil.to;
    e.weight = eil.weight;

    return e;
}
