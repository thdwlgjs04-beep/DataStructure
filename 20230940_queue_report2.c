#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 10

typedef struct {
    char documentName[50];
    int numPages;
} PrintJob;

typedef struct {
    PrintJob queue[SIZE];
    int front;
    int rear;
} PrintQueue;

void initQueue(PrintQueue* q) {
    q->front = 0;
    q->rear = 0;
}

bool isEmpty(PrintQueue* q) {
    return q->front == q->rear;
}

bool isFull(PrintQueue* q) {
    return (q->rear + 1) % SIZE == q->front;
}

// 페이지 제한 포함
bool enqueue(PrintQueue* q, char* documentName, int numPages) {

    if (numPages > 50) {
        printf("50장을 초과하는 문서는 추가할 수 없습니다.\n");
        return false;
    }

    if (isFull(q)) {
        printf("대기열이 가득 찼습니다.\n");
        return false;
    }

    strcpy(q->queue[q->rear].documentName, documentName);
    q->queue[q->rear].numPages = numPages;
    q->rear = (q->rear + 1) % SIZE;

    printf("'%s' (%d 페이지) 추가됨\n", documentName, numPages);
    return true;
}

PrintJob dequeue(PrintQueue* q) {
    if (isEmpty(q)) {
        printf("대기열이 비어 있습니다.\n");
        PrintJob empty = { "", 0 };
        return empty;
    }

    PrintJob job = q->queue[q->front];
    q->front = (q->front + 1) % SIZE;
    return job;
}

// 작업 취소
void cancelJob(PrintQueue* q, char* documentName) {
    if (isEmpty(q)) {
        printf("대기열이 비어 있습니다.\n");
        return;
    }

    int count = (q->rear - q->front + SIZE) % SIZE;
    int found = -1;

    for (int i = 0; i < count; i++) {
        int idx = (q->front + i) % SIZE;
        if (strcmp(q->queue[idx].documentName, documentName) == 0) {
            found = idx;
            break;
        }
    }

    if (found == -1) {
        printf("해당 문서가 없습니다.\n");
        return;
    }

    while (found != q->rear) {
        int next = (found + 1) % SIZE;
        q->queue[found] = q->queue[next];
        found = next;
    }

    q->rear = (q->rear - 1 + SIZE) % SIZE;

    printf("'%s' 작업 취소됨\n", documentName);
}

// 전체 초기화
void clearQueue(PrintQueue* q) {
    q->front = 0;
    q->rear = 0;
    printf("대기열 초기화 완료\n");
}

void printQueue(PrintQueue* q) {
    if (isEmpty(q)) {
        printf("대기열이 비어 있습니다.\n");
        return;
    }

    int i = q->front;
    printf("대기 작업 목록:\n");

    while (i != q->rear) {
        printf("- %s (%d 페이지)\n",
            q->queue[i].documentName,
            q->queue[i].numPages);
        i = (i + 1) % SIZE;
    }
}

int main() {
    PrintQueue q;
    initQueue(&q);

    int choice;
    char documentName[50];
    int numPages;

    while (1) {
        printf("\n1. 작업 추가\n2. 작업 처리\n3. 출력\n4. 작업 취소\n5. 초기화\n6. 종료\n선택: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("문서 이름: ");
            scanf("%s", documentName);
            printf("페이지 수: ");
            scanf("%d", &numPages);
            enqueue(&q, documentName, numPages);
            break;

        case 2: {
            PrintJob job = dequeue(&q);
            if (strlen(job.documentName) > 0) {
                printf("'%s' 출력 중...\n", job.documentName);
            }
            break;
        }

        case 3:
            printQueue(&q);
            break;

        case 4:
            printf("취소할 문서 이름: ");
            scanf("%s", documentName);
            cancelJob(&q, documentName);
            break;

        case 5:
            clearQueue(&q);
            break;

        case 6:
            return 0;

        default:
            printf("잘못된 입력\n");
        }
    }
}