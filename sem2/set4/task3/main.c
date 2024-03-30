#include "sol.h"
#include <stdio.h>



int currentEdge = 0;


int getVerticesCount() {
    return 6;
}

int readEdge(Edge *oEdge) {
    if (currentEdge >= 10) {
        return 0;
    }
    oEdge->from = currentEdge % getVerticesCount();
    oEdge->to = (currentEdge * 2) % getVerticesCount();
    oEdge->weight = currentEdge;

    currentEdge++;

    return 1;
}

int main(int argc, char *argv[])
{
    init();

    for (int i = 0; i < getVerticesCount(); i++) {
        printf("%d: \n", i);

        for (int j = 0; j < getEdgesCount(i); j++) {
            Edge e = getIncidentEdge(i, j);
            printf("\t%d: %d -> %d | %d \n", j, e.from, e.to, e.weight);
        }
    }

    destroy();

    return 0;
}
