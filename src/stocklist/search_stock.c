//search_stock.c

#include "../../hdr/generic.h"
#include "../../hdr/built_in_library.h"


//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//typedef struct {
//    char stock_code[10];
//    char stock_name[20];
//    char date[30];
//    int close;
//    int compare;
//    int open;
//    int high;
//    int low;
//    int volume;
//} StockInfo;
//
//typedef struct User {
//    int userNo;
//    char name[31];
//    int balance;
//} USER;

void search_stock_info(char* filename, char* stock_code, char* date);

int main() {
    char filename[] = "data/output.txt";
    char stock_code[10];
    char date[30];
    int found = 0;

    do {
        printf("종목번호 6자리를 입력하세요: ");
        scanf("%s", stock_code);
    } while (strlen(stock_code) != 6);

    do {
        printf("형식에 맞춰 날짜를 입력하세요 (yyyy.mm.dd): ");
        scanf("%s", date);
    } while (strlen(date) != 10);

   search_stock_info(filename, stock_code, date);


    return 0;
}

void search_stock_info(char* filename, char* stock_code, char* date) {
    FILE* fp;
    char str_tmp[1024];
    char* token;
    StockInfo stock_info;
    int found = 0;

    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Failed to open file \n");
        return;
    }

    // 입력한 종목코드와 날짜 정보가 일치하는 주식 정보를 찾을 때까지 반복
    while (!found) {
        found = 0; // 초기화

        // 파일에서 한 줄씩 읽으면서 종목번호와 날짜 정보가 일치하는 주식 정보를 출력합니다.
        while (fgets(str_tmp, sizeof(str_tmp), fp) != NULL) {
            token = strtok(str_tmp, " \t");
            strcpy(stock_info.stock_code, token);
            token = strtok(NULL, " \t");
            strcpy(stock_info.stock_name, token);
            token = strtok(NULL, " \t");
            strcpy(stock_info.date, token);

            sscanf(strtok(NULL, " \t"), "%d", &stock_info.close);
            sscanf(strtok(NULL, " \t"), "%d", &stock_info.compare);
            sscanf(strtok(NULL, " \t"), "%d", &stock_info.open);
            sscanf(strtok(NULL, " \t"), "%d", &stock_info.high);
            sscanf(strtok(NULL, " \t"), "%d", &stock_info.low);
            sscanf(strtok(NULL, " \t"), "%d", &stock_info.volume);

            if (strcmp(stock_info.stock_code, stock_code) == 0 && strcmp(stock_info.date, date) == 0) {
                printf("종목코드: %s\n종목명: %s\n날짜: %s\n종가: %d\n전일비: %d\n시가: %d\n고가: %d\n저가: %d\n거래량: %d\n\n",
                    stock_info.stock_code, stock_info.stock_name, stock_info.date, stock_info.close, stock_info.compare, stock_info.open, stock_info.high,
                    stock_info.low, stock_info.volume);

                found = 1;
                break;
            }
        }

        // 찾지 못한 경우, 다시 입력 받기
        if (!found) {
            printf("해당되는 주식 정보가 없습니다.\n\n");
            do {
                printf("종목번호 6자리를 입력하세요: ");
                scanf("%s", stock_code);
            } while (strlen(stock_code) != 6);

            do {
                printf("형식에 맞춰 날짜를 입력하세요 (yyyy.mm.dd): ");
                scanf("%s", date);
            } while (strlen(date) != 10);

            // 파일 포인터를 파일의 시작으로 이동하여 다시 탐색
            fseek(fp, 0, SEEK_SET);
        }
    }

    fclose(fp);
}




/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char stock_code[10];
    char stock_name[20];
    char date[30];
    int compare;
    int open;
    int high;
    int low;
    int close;
    int volume;
} StockInfo;

void search_stock_info(char* filename, char* stock_code, char* date);

int main() {
    char filename[] = "data/output.txt";
    char stock_code[10];
    char date[30];
    int found = 0;


    printf("종목번호를 입력하세요: ");
    scanf("%s", stock_code);

    printf("날짜를 입력하세요 (yyyy.mm.dd): ");
    scanf("%s", date);

    search_stock_info(filename, stock_code, date);


    return 0;
}

void search_stock_info(char* filename, char* stock_code, char* date) {
    FILE* fp;
    char str_tmp[1024];
    char* token;
    StockInfo stock_info;
    int found = 0;

    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Failed to open file \n");
        return;
    }

    // 입력한 종목코드와 날짜 정보가 일치하는 주식 정보를 찾을 때까지 반복
    while (!found) {
        found = 0; // 초기화

        // 파일에서 한 줄씩 읽으면서 종목번호와 날짜 정보가 일치하는 주식 정보를 출력합니다.
        while (fgets(str_tmp, sizeof(str_tmp), fp) != NULL) {
            token = strtok(str_tmp, " \t");
            strcpy(stock_info.stock_code, token);
            token = strtok(NULL, " \t");
            strcpy(stock_info.stock_name, token);
            token = strtok(NULL, " \t");
            strcpy(stock_info.date, token);

            sscanf(strtok(NULL, ","), "%d", &stock_info.close);
            sscanf(strtok(NULL, ","), "%d", &stock_info.compare);
            sscanf(strtok(NULL, ","), "%d", &stock_info.open);
            sscanf(strtok(NULL, ","), "%d", &stock_info.high);
            sscanf(strtok(NULL, ","), "%d", &stock_info.low);
            sscanf(strtok(NULL, ","), "%d", &stock_info.volume);

            if (strcmp(stock_info.stock_code, stock_code) == 0 && strcmp(stock_info.date, date) == 0) {
                printf("종목코드: %s\n종목명: %s\n날짜: %s\n종가: %d\n전일비: %d\n시가: %d\n고가: %d\n저가: %d\n거래량: %d\n\n",
                    stock_info.stock_code, stock_info.stock_name, stock_info.date, stock_info.close, stock_info.compare, stock_info.open, stock_info.high,
                    stock_info.low, stock_info.volume);


                found = 1;
                break;
            }
        }

        // 찾지 못한 경우, 다시 입력 받기
        if (!found) {
            printf("해당되는 주식 정보가 없습니다.\n\n");
            printf("종목번호를 입력하세요: ");
            scanf("%s", stock_code);

            printf("날짜를 입력하세요 (yyyy.mm.dd): ");
            scanf("%s", date);

            // 파일 포인터를 파일의 시작으로 이동하여 다시 탐색
            fseek(fp, 0, SEEK_SET);
        }
    }

    fclose(fp);
}
*/