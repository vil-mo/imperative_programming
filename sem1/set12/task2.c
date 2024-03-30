#include <stdio.h>
#include <stdlib.h>

typedef struct BTree {
    int height;

    int val;
    struct BTree *left;
    struct BTree *right;
} BTree;

// Преобразуем дерево в массив
void flatten(BTree *currTree, int *arr, int *i) {
    if (currTree->left != NULL) {
        flatten(currTree->left, arr, i);
    }

    arr[*i] = currTree->val;
    (*i)++;

    if (currTree->right != NULL) {
        flatten(currTree->right, arr, i);
    }
}

int max(int left, int right) {
    return left > right ? left : right;
}

int btreeGetHeight(BTree *self) {
    if (self == NULL) {
        return 0;
    }
    return self->height;
}

void btreeUpdateHeight(BTree *self) {
     self->height = max(btreeGetHeight(self->left), btreeGetHeight(self->right)) + 1;
}

BTree *btreeRotateRight(BTree *self) {
    BTree *left = self->left;
    self->left = left->right;
    left->right = self;

    btreeUpdateHeight(self);
    btreeUpdateHeight(left);

    return left;
}

BTree *btreeRotateLeft(BTree *self) {
    BTree *right = self->right;
    self->right = right->left;
    right->left = self;

    btreeUpdateHeight(self);
    btreeUpdateHeight(right);

    return right;
}

BTree *btreeAdd(BTree *self, BTree *toAdd) {
    // Добавляем, обновляем ссылку на корень вращаемого дерева
    if (self->val > toAdd->val) {
        if (self->left == NULL) {
            self->left = toAdd;
        } else {
            self->left = btreeAdd(self->left, toAdd);
        }
    } else {
        if (self->right == NULL) {
            self->right = toAdd;
        } else {
            self->right = btreeAdd(self->right, toAdd);
        }
    }
    
    int leftHeight = btreeGetHeight(self->left);
    int rightHeight = btreeGetHeight(self->right);

    if (leftHeight - rightHeight >= 2) {
        if (self->left->right != NULL) {
            self->left = btreeRotateLeft(self->left);
        }
        return btreeRotateRight(self);
    } else if (rightHeight - leftHeight >= 2) {
        if (self->right->left != NULL) {
            self->right = btreeRotateRight(self->right);
        }
        return btreeRotateLeft(self);
    }

    btreeUpdateHeight(self);
    return self;
}

void treeSort(int *arr, int len) {
    if (len == 0) {
        return;
    }

    BTree *treeArr = malloc(len * sizeof(BTree));

    treeArr[0].left = NULL;
    treeArr[0].right = NULL;
    treeArr[0].val = arr[0];
    treeArr[0].height = 1;

    BTree *currTree = &treeArr[0];

    for (int i = 1; i < len; i++) {
        treeArr[i].left = NULL;
        treeArr[i].right = NULL;
        treeArr[i].val = arr[i];
        treeArr[i].height = 1;

        currTree = btreeAdd(currTree, &treeArr[i]);
    }

    int i = 0;
    flatten(currTree, arr, &i);

    free(treeArr);
}

int main(int argc, char *argv[]) { 

    FILE *in = fopen("input.bin", "rb");
    FILE *out = fopen("output.bin", "wb");

    int n;
    fread(&n, 4, 1, in);
    // scanf("%d", &n);

    int *arr = malloc(n * sizeof(int));
    fread(arr, 4, n, in);

    // for (int i = 0; i < n; i++) {
    //     scanf("%d", &arr[i]);
    // }

    treeSort(arr, n);

    fwrite(arr, 4, n, out);
    // for (int i = 0; i < n; i++) {
    //     printf("%d, ", arr[i]);
    // }



    free(arr);

    fclose(in);
    fclose(out);

    return EXIT_SUCCESS; 
}
