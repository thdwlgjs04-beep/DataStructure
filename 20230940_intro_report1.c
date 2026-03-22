#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 함수 선언
double calculateAverage(int scores[], int size);
int getStudentScore(int scores[], int size, int studentNumber);
void printfScore(int scores[], int size, double average, int option);

int main() {
    int scores[30]; // 30명의 학생 성적 저장
    int studentNumber;
    double average;

    // 난수 생성 초기화
    srand(time(0));

    // 성적 데이터 초기화
    for (int i = 0; i < 30; i++) {
        scores[i] = rand() % 101; // 0 ~ 100 사이 난수 생성
    }

    // 평균 계산
    average = calculateAverage(scores, 30);
    printf("학급 평균 점수: %.2f\n\n", average);

    // 특정 학생 점수 검색
    printf("학생 번호를 입력하세요 (1 ~ 30): ");
    scanf_s("%d", &studentNumber);

    int score = getStudentScore(scores, 30, studentNumber);

    if (score != -1) {
        printf("%d번 학생의 점수: %d\n\n", studentNumber, score);
    }
    else {
        printf("유효하지 않은 학생 번호입니다.\n\n");
    }

    // 전체 학생 출력
    printfScore(scores, 30, average, 0);

    // 평균 이상 학생
    printfScore(scores, 30, average, 1);

    // 평균 미만 학생
    printfScore(scores, 30, average, 2);

    return 0;
}

// 평균 계산 함수
double calculateAverage(int scores[], int size) {
    int sum = 0;

    for (int i = 0; i < size; i++) {
        sum += scores[i];
    }

    return (double)sum / size;
}

// 특정 학생 점수 검색 함수
int getStudentScore(int scores[], int size, int studentNumber) {

    if (studentNumber < 1 || studentNumber > size) {
        return -1;
    }

    return scores[studentNumber - 1];
}

// 학생 점수 출력 함수
void printfScore(int scores[], int size, double average, int option) {

    switch (option) {

    case 0: // 전체 학생 출력
        printf("전체 학생 점수\n");
        for (int i = 0; i < size; i++) {
            printf("학생번호 : %d, 점수 : %d\n", i + 1, scores[i]);
        }
        printf("\n");
        break;

    case 1: // 평균 이상
        printf("평균 이상 학생\n");
        for (int i = 0; i < size; i++) {
            if (scores[i] >= average) {
                printf("학생번호 : %d, 점수 : %d\n", i + 1, scores[i]);
            }
        }
        printf("\n");
        break;

    case 2: // 평균 미만
        printf("평균 미만 학생\n");
        for (int i = 0; i < size; i++) {
            if (scores[i] < average) {
                printf("학생번호 : %d, 점수 : %d\n", i + 1, scores[i]);
            }
        }
        printf("\n");
        break;

    default:
        printf("유효하지 않은 옵션입니다.\n");
        break;
    }
}