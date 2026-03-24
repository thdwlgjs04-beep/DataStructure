int main() {
    Stack s;
    char str[MAX];

    // 스택 초기화
    initStack(&s);

    // 문자열 입력
    printf("문자열 입력 : ");
    fgets(str, MAX, stdin);

    // 개행 문자 제거
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '\n') {
            str[i] = '\0';
            break;
        }
    }

    // 스택에 push
    for (int i = 0; str[i] != '\0'; i++) {
        push(&s, str[i]);
    }

    // 스택에서 pop하며 역순 출력
    printf("거꾸로 된 문자열 : ");
    while (!isEmpty(&s)) {
        printf("%c", pop(&s));
    }
    printf("\n");

    return 0;
}