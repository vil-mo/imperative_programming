#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

typedef enum {
    TOKEN_CONSTANT,
    TOKEN_ADD,
    TOKEN_SUB,
    TOKEN_MUL,
    TOKEN_DIV,
    TOKEN_OPEN_BR,
    TOKEN_CLOSED_BR,
    TOKEN_EOF,
} TokenType;

typedef struct {
    TokenType type;
    double value;
} Token;

Token currentToken;
short endedScanning = 0;
char lastChar = '\0';

char skipWhitespace() {
    if (endedScanning) {
        return '\0';
    }

    while (1) {
        char c;
        if (lastChar == '\0') {
            scanf("%c", &c);
        } else {
            c = lastChar;
            lastChar = '\0';
        }

        switch (c) {
            case ' ': break;
            case '\n':
            case '\0':
                endedScanning = 1;
                return '\0';
            default: return c;
        }
    }
}

void advance() {
    char c = skipWhitespace();

    if (endedScanning) {
        currentToken.type = TOKEN_EOF;
        return;
    }

    switch (c) {
        case '+':
            currentToken.type = TOKEN_ADD;
            break;

        case '-':
            currentToken.type = TOKEN_SUB;
            break;

        case '*':
            currentToken.type = TOKEN_MUL;
            break;

        case '/':
            currentToken.type = TOKEN_DIV;
            break;

        case '(':
            currentToken.type = TOKEN_OPEN_BR;
            break;

        case ')':
            currentToken.type = TOKEN_CLOSED_BR;
            break;

        default:
            currentToken.type = TOKEN_CONSTANT;
            currentToken.value = 0;

            do {
                currentToken.value *= 10;
                currentToken.value += c - '0';
                scanf("%c", &c);
            } while (isdigit(c));

            lastChar = c;
            if (lastChar == '\0' || lastChar == '\n') {
                endedScanning = 1;
            }

            break;
    }
}

double add();

double unary() {
    switch (currentToken.type) {
        case TOKEN_SUB: {
            advance();
            return -unary();
        }

        case TOKEN_CONSTANT: {
            double v = currentToken.value;
            advance();
            return v;
        }

        default: {
            advance();
            double res = add();
            advance();

            return res;
        }
    }
}

double mul() {
    double res = unary();

    while (1) {
        switch (currentToken.type) {
            case TOKEN_MUL: {
                advance();
                res *= unary();
                break;
            }

            case TOKEN_DIV: {
                advance();
                res /= unary();
                break;
            }

            default: return res;
        }
    }
}

double add() {
    double res = mul();

    while (1) {
        switch (currentToken.type) {
            case TOKEN_ADD: {
                advance();
                res += mul();
                break;
            }

            case TOKEN_SUB: {
                advance();
                res -= mul();
                break;
            }

            default: return res;
        }
    }
}

int main(int argc, char *argv[])
{
    advance();
    double res = add();

    printf("%.15lf", res);

    return EXIT_SUCCESS;
} 
