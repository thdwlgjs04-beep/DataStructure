#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 스택 구조체
typedef struct {
    char* data;
    int top;
    int capacity;
} Stack;

// 초기화
void initStack(Stack* s, int size) {
    s->data = (char*)malloc(size * sizeof(char));
    s->top = -1;
    s->capacity = size;
}

// 비었는지 확인
int isEmpty(Stack* s) {
    return s->top == -1;
}

// 가득 찼는지 확인
int isFull(Stack* s) {
    return s->top == s->capacity - 1;
}

// 크기 확장
void expandStack(Stack* s) {
    s->capacity += 10;
    s->data = (char*)realloc(s->data, s->capacity);
}

// push
void push(Stack* s, char c) {
    if (isFull(s)) {
        expandStack(s);
    }
    s->data[++(s->top)] = c;
}

// pop
char pop(Stack* s) {
    if (isEmpty(s)) return '\0';
    return s->data[(s->top)--];
}

// 괄호 짝 확인 함수
int isMatchingPair(char open, char close) {
    return (open == '(' && close == ')') ||
        (open == '{' && close == '}') ||
        (open == '[' && close == ']');
}

// 괄호 검사 함수
int checkValid(char* str) {
    Stack s;
    initStack(&s, 10);

    for (int i = 0; i < strlen(str); i++) {
        char ch = str[i];

        // 여는 괄호
        if (ch == '(' || ch == '{' || ch == '[') {
            push(&s, ch);
        }
        // 닫는 괄호
        else if (ch == ')' || ch == '}' || ch == ']') {
            if (isEmpty(&s)) return 0;

            char top = pop(&s);
            if (!isMatchingPair(top, ch)) {
                return 0;
            }
        }
    }

    return isEmpty(&s);
}

// 메인 함수
int main() {
    char str[100];

    printf("문자열을 입력하세요: ");
    fgets(str, sizeof(str), stdin);

    if (checkValid(str)) {
        printf("유효한 괄호\n");
    }
    else {
        printf("유효하지 않은 괄호\n");
    }

    return 0;
}