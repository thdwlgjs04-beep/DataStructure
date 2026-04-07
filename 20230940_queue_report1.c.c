#include <stdio.h>
#include <stdbool.h>

#define SIZE 30  // 큐 크기 5 -> 30으로 변경

typedef struct {
    int data[SIZE];
    int front;
    int rear;
} LinearQueue;

// 초기화 함수
void initQueue(LinearQueue* q) {
    q->front = 0;
    q->rear = -1;
}

// 큐가 비어 있는지 확인
bool isEmpty(LinearQueue* q) {
    return q->rear < q->front;
}

// 큐가 가득 찼는지 확인
bool isFull(LinearQueue* q) {
    return q->rear == SIZE - 1;
}

// 삽입 함수
bool enqueue(LinearQueue* q, int value) {
    if (isFull(q)) {
        printf("큐가 가득 찼습니다.\n");
        return false;
    }
    q->data[++q->rear] = value;
    return true;
}

// 삭제 함수 (비었을 때 초기화 추가)
int dequeue(LinearQueue* q) {
    if (isEmpty(q)) {
        printf("큐가 비어 있습니다.\n");
        initQueue(q);  // 초기화 추가
        return -1;
    }

    int value = q->data[q->front++];

    // 모든 요소가 빠져나가면 초기화
    if (isEmpty(q)) {
        initQueue(q);
    }

    return value;
}

// 큐 출력 함수 (새로 작성)
void printQueue(LinearQueue* q) {
    if (isEmpty(q)) {
        printf("큐가 비어 있습니다.\n");
        return;
    }

    printf("큐 상태: ");
    for (int i = q->front; i <= q->rear; i++) {
        printf("%d ", q->data[i]);
    }
    printf("\n");
}

// 메뉴 
void menu() {
    printf("\n===== 큐 메뉴 =====\n");
    printf("1. 삽입\n");
    printf("2. 삭제\n");
    printf("3. 큐 데이터 출력\n");
    printf("4. 종료\n");
    printf("선택: ");
}

int main() {
    LinearQueue q;
    initQueue(&q);

    int choice, value;

    while (1) {
        menu();
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("삽입할 값 : ");
            scanf("%d", &value);
            enqueue(&q, value);
            break;

        case 2:
            value = dequeue(&q);
            if (value != -1) {
                printf("삭제 값: %d\n", value);
            }
            break;

        case 3:
            printQueue(&q);
            break;

        case 4:
            printf("프로그램 종료\n");
            return 0;

        default:
            printf("잘못된 입력.\n");
        }
    }
}