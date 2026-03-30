#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

// Stack 
typedef struct {
    int data[MAX];
    int top;
} Stack;

void initStack(Stack* s) { s->top = -1; }
int isEmpty(Stack* s) { return s->top == -1; }
void push(Stack* s, int value) { s->data[++(s->top)] = value; }
int pop(Stack* s) { return s->data[(s->top)--]; }
int peek(Stack* s) { return s->data[s->top]; }

// 우선순위 
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return -1;
}

// 변환
void infixToPostfix(char* infix, char* postfix) {
    Stack s;
    initStack(&s);
    int i, j = 0;

    for (i = 0; infix[i] != '\0'; i++) {
        char ch = infix[i];

        // 피연산자
        if (isdigit(ch)) {
            postfix[j++] = ch;
        }
        // '('
        else if (ch == '(') {
            push(&s, ch);
        }
        // ')'
        else if (ch == ')') {
            while (!isEmpty(&s) && peek(&s) != '(') {
                postfix[j++] = pop(&s);
            }
            pop(&s); 
        }
        // 연산자
        else {
            while (!isEmpty(&s) &&
                precedence(peek(&s)) >= precedence(ch)) {
                postfix[j++] = pop(&s);
            }
            push(&s, ch);
        }
    }

    // 남은 연산자
    while (!isEmpty(&s)) {
        postfix[j++] = pop(&s);
    }

    postfix[j] = '\0';
}

// 후위표기
int evaluatePostfix(char* postfix) {
    Stack s;
    initStack(&s);

    for (int i = 0; postfix[i] != '\0'; i++) {
        char ch = postfix[i];

        // 숫자
        if (isdigit(ch)) {
            push(&s, ch - '0');
        }
        // 연산자
        else {
            int b = pop(&s);
            int a = pop(&s);
            int result;

            switch (ch) {
            case '+': result = a + b; break;
            case '-': result = a - b; break;
            case '*': result = a * b; break;
            case '/': result = a / b; break;
            }

            push(&s, result);
        }
    }

    return pop(&s);
}

// =메인
int main(void) {
    char infix[MAX];
    char postfix[MAX];
    int result;

    printf(":중위표기식 입력 : ");
    scanf("%s", infix);

    infixToPostfix(infix, postfix);      // 변환
    result = evaluatePostfix(postfix);   // 계산

    printf("후위표기식 : %s\n", postfix);
    printf("후위표기식 계산 결과 : %d\n", result);

    return 0;
}