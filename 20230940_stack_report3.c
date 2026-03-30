#include <stdio.h>
#include <ctype.h>
#define MAX 100

// Stack
typedef struct {
    int data[MAX];
    int top;
} Stack;

void init(Stack* s) { s->top = -1; }
void push(Stack* s, int x) { s->data[++(s->top)] = x; }
int pop(Stack* s) { return s->data[(s->top)--]; }
int peek(Stack* s) { return s->data[s->top]; }
int isEmpty(Stack* s) { return s->top == -1; }

//  우선 
int priority(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

//  계산 
int calc(int a, int b, char op) {
    switch (op) {
    case '+': return a + b;
    case '-': return a - b;
    case '*': return a * b;
    case '/': return a / b;
    }
    return 0;
}

//  핵심 
int infixToPostfix(char* infix, char* postfix) {
    Stack opStack, valStack;
    init(&opStack);
    init(&valStack);

    int i = 0, j = 0;

    while (infix[i] != '\0') {
        char ch = infix[i];

        // 숫자 처리
        if (isdigit(ch)) {
            postfix[j++] = ch;
            push(&valStack, ch - '0');
        }

        else if (ch == '(') {
            push(&opStack, ch);
        }

        else if (ch == ')') {
            while (!isEmpty(&opStack) && peek(&opStack) != '(') {
                char op = pop(&opStack);
                postfix[j++] = op;

                int b = pop(&valStack);
                int a = pop(&valStack);
                push(&valStack, calc(a, b, op));
            }
            pop(&opStack); 
        }

        // 연산자
        else {
            while (!isEmpty(&opStack) &&
                priority(peek(&opStack)) >= priority(ch)) {

                char op = pop(&opStack);
                postfix[j++] = op;

                int b = pop(&valStack);
                int a = pop(&valStack);
                push(&valStack, calc(a, b, op));
            }
            push(&opStack, ch);
        }

        i++;
    }

    // 남은 연산자 처리
    while (!isEmpty(&opStack)) {
        char op = pop(&opStack);
        postfix[j++] = op;

        int b = pop(&valStack);
        int a = pop(&valStack);
        push(&valStack, calc(a, b, op));
    }

    postfix[j] = '\0';

    return pop(&valStack); // 반환
}