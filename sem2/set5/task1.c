#pragma comment(linker, "/STACK:50000000")

#include <stdlib.h>
#include <stdio.h>

void dfs(char *self, int n, int x, int y) {
    self[x * n + y] = '-';
    if (x > 0 && self[(x - 1) * n + y] == ' ') {
        dfs(self, n, x - 1, y);
    }
    
    if (x < n - 1 && self[(x + 1) * n + y] == ' ') {
        dfs(self, n, x + 1, y);
    }

    if (y > 0 && self[x * n + y - 1] == ' ') {
        dfs(self, n, x, y - 1);
    }

    if (y < n - 1 && self[x * n + y + 1] == ' ') {
        dfs(self, n, x, y + 1);
    }
}

int main(int argc, char *argv[])
{
    int n;
    scanf("%d", &n);
    
    char *graph = malloc(n * n * sizeof(char));

    for (int x = 0; x < n; x++) {
        for (int y = 0; y < n; y++) {
            scanf("%c", &graph[x * n + y]);
            while (graph[x * n + y] != ' ' && graph[x * n + y] != '*') {
                scanf("%c", &graph[x * n + y]);
            }
        }
    }

    int r = -1;

    for (int x = 0; x < n; x++) {
        for (int y = 0; y < n; y++) {
            if (graph[x * n + y] == ' ') {
                dfs(graph, n, x, y);
                r += 1;
            }
        }
    }
    
    printf("%d", r);

    free(graph);

    return EXIT_SUCCESS;
}
