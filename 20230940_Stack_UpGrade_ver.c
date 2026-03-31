#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

// STACK
typedef struct {
    int data[MAX];
    int top;
} Stack;

void initStack(Stack* s) { s->top = -1; }
int isEmpty(Stack* s) { return s->top == -1; }

void push(Stack* s, int value) {
    if (s->top == MAX - 1) {
        printf("Stack Overflow\n");
        exit(1);
    }
    s->data[++(s->top)] = value;
}

int pop(Stack* s) {
    if (isEmpty(s)) {
        printf("Stack Underflow\n");
        exit(1);
    }
    return s->data[(s->top)--];
}

int peek(Stack* s) {
    return s->data[s->top];
}

// 연산자 우선순위
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// 변수 값 반환
int getValue(char* var) {
    if (strcmp(var, "num") == 0) return 5;
    if (strcmp(var, "size") == 0) return 3;
    return 0;
}

// 중위표기식을 후위표기식으로 변환
void infixToPostfix(char* infix, char* postfix) {
    Stack s;
    initStack(&s);

    int i = 0, j = 0;

    while (infix[i] != '\0') {

        // 공백 무시
        if (isspace(infix[i])) {
            i++;
            continue;
        }

        // 여러 자리 숫자 처리
        if (isdigit(infix[i])) {
            while (isdigit(infix[i])) {
                postfix[j++] = infix[i++];
            }
            postfix[j++] = ' ';
        }

        // 변수 처리
        else if (isalpha(infix[i])) {
            while (isalpha(infix[i])) {
                postfix[j++] = infix[i++];
            }
            postfix[j++] = ' ';
        }

        // 여는 괄호
        else if (infix[i] == '(') {
            push(&s, infix[i++]);
        }

        // 닫는 괄호
        else if (infix[i] == ')') {
            while (!isEmpty(&s) && peek(&s) != '(') {
                postfix[j++] = pop(&s);
                postfix[j++] = ' ';
            }
            pop(&s);
            i++;
        }

        // 연산자 처리
        else {
            while (!isEmpty(&s) &&
                precedence(peek(&s)) >= precedence(infix[i])) {
                postfix[j++] = pop(&s);
                postfix[j++] = ' ';
            }
            push(&s, infix[i++]);
        }
    }

    // 남은 연산자 처리
    while (!isEmpty(&s)) {
        postfix[j++] = pop(&s);
        postfix[j++] = ' ';
    }

    postfix[j] = '\0';
}

// 후위표기식 계산
int evaluatePostfix(char* postfix) {
    Stack s;
    initStack(&s);

    char token[MAX];
    int i = 0;

    while (postfix[i] != '\0') {

        if (isspace(postfix[i])) {
            i++;
            continue;
        }

        int k = 0;

        // 토큰 추출
        while (!isspace(postfix[i]) && postfix[i] != '\0') {
            token[k++] = postfix[i++];
        }
        token[k] = '\0';

        // 숫자 처리
        if (isdigit(token[0])) {
            push(&s, atoi(token));
        }

        // 변수 처리
        else if (isalpha(token[0])) {
            push(&s, getValue(token));
        }

        // 연산자 처리
        else {
            int b = pop(&s);
            int a = pop(&s);

            switch (token[0]) {
            case '+': push(&s, a + b); break;
            case '-': push(&s, a - b); break;
            case '*': push(&s, a * b); break;
            case '/': push(&s, a / b); break;
            }
        }
    }

    return pop(&s);
}

// 메인 함수
int main() {
    char infix[MAX];
    char postfix[MAX];

    printf("중위식 입력: ");
    fgets(infix, MAX, stdin);

    infixToPostfix(infix, postfix);

    printf("후위식: %s\n", postfix);
    printf("결과: %d\n", evaluatePostfix(postfix));

    return 0;
}