#include <stdbool.h>
#include <stdio.h>

typedef struct Wrapper {
    int parentheses;
    int squareBrackets;
    int curlyBrackets;
    int angleBrackets;
} Wrapper;

void initWrapper(Wrapper *self) {
    self->parentheses = 0;
    self->squareBrackets = 0;
    self->curlyBrackets = 0;
    self->angleBrackets = 0;
}

int getCorresponding(Wrapper *self, char symb) {
    switch (symb) {
    case '(':
    case ')':
        return self->parentheses;
    case '[':
    case ']':
        return self->squareBrackets;
    case '{':
    case '}':
        return self->curlyBrackets;
    case '<':
    case '>':
        return self->angleBrackets;

    default:
        return 0; 
    }
}

void addCorresponding(Wrapper *self, char symb, int val) {
    switch (symb) {
    case '(':
    case ')':
        self->parentheses += val;
        break;
    case '[':
    case ']':
        self->squareBrackets += val;
        break;
    case '{':
    case '}':
        self->curlyBrackets += val;
        break;
    case '<':
    case '>':
        self->angleBrackets += val;
        break;

    default: break;
    }
}

bool isSameType(char s1, char s2) {
    if (
            s1 == '(' && s2 == ')' || 
            s1 == '[' && s2 == ']' || 
            s1 == '{' && s2 == '}' || 
            s1 == '<' && s2 == '>'
        ) {

        return true;
    }

    return false;
}

bool isEmpty(Wrapper *self) {
    return self->parentheses == 0 && 
        self->squareBrackets == 0 &&
        self->curlyBrackets == 0 &&
        self->angleBrackets == 0;
}

bool isClosing(char symb) {
    if (symb == ')' || symb == ']' || symb == '}' || symb == '>') {
        return true;
    }

    return false;
}

bool isOpening(char symb) {
    if (symb == '(' || symb == '[' || symb == '{' || symb == '<') {
        return true;
    }

    return false;
}

int main(int argc, char *argv[]) {
    int n;
    scanf("%d\n", &n);

    Wrapper wrapper;
    initWrapper(&wrapper);

    for (int i = 0; i < n; i++) {
        bool correct = true;
        while (true) {
            char symb;
            scanf("%c", &symb);
            if (symb == '\n') {
                break;
            }
            bool lastClosing = false;

            if (isOpening(symb)) {
                if (lastClosing && !isEmpty(&wrapper)) {
                    correct = false;
                    scanf("\n");
                    break;
                }
                addCorresponding(&wrapper, symb, 1);
                lastClosing = false;
            } else {
                if (getCorresponding(&wrapper, symb) == 0) {
                    correct = false;
                    scanf("\n");
                    break;
                }

                lastClosing = true;

                addCorresponding(&wrapper, symb, -1);
            }
        }
        if (!isEmpty(&wrapper)) {
            correct = false;
        }

        if (correct) {
            printf("T\n");
        } else {
            printf("NIL\n");
        }
    }

    return 0;
}
