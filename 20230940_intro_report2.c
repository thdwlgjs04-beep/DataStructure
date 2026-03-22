#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 함수 선언
double calculateAverage(int scores[], int size);
int getStudentScore(int scores[], int size, int studentNumber);
void printScore(int scores[], int size, double average, int option);
void deleteStudent(int* scores, int size, int studentNumber);

int main() {

    int* scores;
    int size = 30;
    int capacity = 30;
    int choice, studentNumber;

    scores = (int*)malloc(capacity * sizeof(int));

    if (!scores) {
        printf("allocation error\n");
        return 1;
    }

    srand(time(0));

    // 초기 학생 점수 생성
    for (int i = 0; i < size; i++)
        scores[i] = rand() % 101;

    printf("초기 학생 점수 입력 완료\n");

    while (1) {

        printf("\n--- 학생 성적 관리 프로그램 ---\n");
        printf("1. 학생정보 추가\n");
        printf("2. 학생정보 삭제\n");
        printf("3. 학생정보 검색\n");
        printf("4. 학생정보 출력\n");
        printf("5. 프로그램 종료\n");

        printf("메뉴 선택 : ");
        scanf_s("%d", &choice);

        system("cls");

        switch (choice) {

        case 1: { // 학생 추가

            if (capacity - size < 5) {
                capacity += 10;

                int* newScores = realloc(scores, capacity * sizeof(int));

                if (!newScores) {
                    printf("allocation error\n");
                    return 1;
                }

                scores = newScores;
            }

            int newScore = rand() % 101;

            scores[size] = newScore;
            size++;

            printf("새로운 학생 추가 : 번호 %d / 점수 %d\n", size, newScore);

            break;
        }

        case 2: { // 학생 삭제

            printf("삭제할 학생 번호 입력 (1 ~ %d) : ", size);
            scanf_s("%d", &studentNumber);

            deleteStudent(scores, size, studentNumber);

            break;
        }

        case 3: { // 학생 검색

            printf("검색할 학생 번호 입력 (1 ~ %d) : ", size);
            scanf_s("%d", &studentNumber);

            int score = getStudentScore(scores, size, studentNumber);

            if (score != -1)
                printf("%d번 학생 점수 : %d\n", studentNumber, score);
            else
                printf("존재하지 않는 학생입니다.\n");

            break;
        }

        case 4: { // 학생 출력

            int option;

            printf("0 : 전체 학생\n");
            printf("1 : 평균 이상\n");
            printf("2 : 평균 미만\n");

            printf("옵션 선택 : ");
            scanf_s("%d", &option);

            double average = calculateAverage(scores, size);

            printScore(scores, size, average, option);

            break;
        }

        case 5:

            free(scores);
            printf("프로그램 종료\n");
            return 0;

        default:
            printf("잘못된 입력입니다.\n");
        }
    }

    return 0;
}

// 학생 삭제
void deleteStudent(int* scores, int size, int studentNumber) {

    if (studentNumber < 1 || studentNumber > size) {
        printf("학생번호 오류\n");
        return;
    }

    if (scores[studentNumber - 1] == -1) {
        printf("이미 삭제된 학생입니다\n");
    }
    else {
        scores[studentNumber - 1] = -1;
        printf("%d번 학생 삭제 완료\n", studentNumber);
    }
}

// 평균 계산
double calculateAverage(int scores[], int size) {

    int sum = 0;
    int count = 0;

    for (int i = 0; i < size; i++) {

        if (scores[i] != -1) {
            sum += scores[i];
            count++;
        }
    }

    if (count == 0)
        return 0;

    return (double)sum / count;
}

// 학생 점수 검색
int getStudentScore(int scores[], int size, int studentNumber) {

    if (studentNumber < 1 || studentNumber > size)
        return -1;

    return scores[studentNumber - 1];
}

// 학생 정보 출력
void printScore(int scores[], int size, double average, int option) {

    switch (option) {

    case 0: // 전체 출력

        printf("전체 학생 목록\n");

        for (int i = 0; i < size; i++) {

            if (scores[i] != -1)
                printf("학생번호 : %d / 점수 : %d\n", i + 1, scores[i]);
        }

        break;

    case 1: // 평균 이상

        printf("평균 이상 학생 (평균 %.2f)\n", average);

        for (int i = 0; i < size; i++) {

            if (scores[i] >= average && scores[i] != -1)
                printf("학생번호 : %d / 점수 : %d\n", i + 1, scores[i]);
        }

        break;

    case 2: // 평균 미만

        printf("평균 미만 학생 (평균 %.2f)\n", average);

        for (int i = 0; i < size; i++) {

            if (scores[i] < average && scores[i] != -1)
                printf("학생번호 : %d / 점수 : %d\n", i + 1, scores[i]);
        }

        break;

    default:

        printf("유효하지 않은 옵션입니다.\n");
    }
}