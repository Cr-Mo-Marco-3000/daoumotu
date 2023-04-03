#include "../../hdr/generic.h"
#include "../../hdr/built_in_library.h"

#define MAX_LINE_LENGTH 100
#define MAX_TRADES 1024


// 함수 선언


void tradesearch() {
    char filename[] = "data/tradelist.txt";
    Trade trades[MAX_TRADES]; // 최대 1024개의 매매내역을 저장하는 구조체 배열
    int numTrades = 40; // 실제 저장된 매매내역의 개수

    // 매매내역 파일(tradelist.txt)을 읽어서 trades 구조체 배열에 저장
    readTrades(filename, trades, &numTrades);

    // 검색할 타입 입력받기
    int searchType;
    do {
        printf("검색할 타입을 입력하세요 (1: 날짜, 2: 매매타입, 3: 종목번호): ");
        scanf("%d", &searchType);
    } while (searchType != 1 && searchType != 2 && searchType != 3);

    // 매매내역 검색
    searchTrades(searchType, trades, numTrades);

}

// tradelist.txt 파일에서 매매내역을 읽어서 trades 구조체 배열에 저장하는 함수
void readTrades(char* filename, struct Trade* trades, int* numTrades) {
    FILE* fp;
    char line[MAX_LINE_LENGTH];
    char* token;
    

    fp = fopen("data/tradelist.txt", "r");
    if (fp == NULL) {
        printf("파일을 열 수 없습니다.\n");
        exit(1);
    }

    // 첫 번째 줄을 버림
    fgets(line, MAX_LINE_LENGTH, fp);

    while (fgets(line, MAX_LINE_LENGTH, fp) != NULL) {
            token = strtok(line, " \t"); //회원번호 버리기

        if (atoi(token) == 1) //1을 임의의 회원번호로 준 거라서 이걸 회원번호 넘겨 줄 때 userNo 변수로 바꿔 줘야 함
        {
            token = strtok(NULL, " \t");
            strcpy(trades[*numTrades].code, token);

            token = strtok(NULL, " \t");
            strcpy(trades[*numTrades].date, token);

            token = strtok(NULL, " \t");
            trades[*numTrades].amount = atoi(token);

            token = strtok(NULL, " \t");
            trades[*numTrades].price = atoi(token);

            token = strtok(NULL, " \t");
            trades[*numTrades].type = atoi(token);

            (*numTrades)++;
        }

        if (*numTrades == MAX_TRADES) {
            printf("Maximum number of trades reached.\n");
            break;
        }
    }

    fclose(fp);

}

void searchTrades(int searchType, struct Trade* trades, int numTrades) {
    char inputDate[50];
    int tradetype;
    char tradecode[11];
    int i;
    int found = 0;

    if (searchType == 1) {
        do{
        printf("검색할 날짜를 입력하세요. (YYYY.MM.DD): \n");
        scanf("%s", inputDate);
        } while (strlen(inputDate) != 10);

        for (i = 0; i < numTrades; i++) {
            if (strcmp(trades[i].date, inputDate) == 0) {
                //printf("%s", trades[i].date);
                printf("종목번호: %s, 날짜: %s, 거래수량: %d, 거래가격: %d, 매매타입: %d \n", trades[i].code, trades[i].date, trades[i].amount, trades[i].price, trades[i].type);
                found = 1;
            }
        }

        if (!found) {
            printf("일치하는 매매내역이 없습니다.\n");
        }
    }


    if (searchType == 2) {
        do {
            printf("검색할 매매타입을 입력하세요. (1: 매수 2: 매도) \n");
            scanf("%d", &tradetype);
        } while (tradetype != 1 && tradetype != 2);

        for (i = 0; i < numTrades; i++) {
            if (trades[i].type == tradetype) {
                printf("종목번호: %s, 날짜: %s, 거래수량: %d, 거래가격: %d, 매매타입: %d \n", trades[i].code, trades[i].date, trades[i].amount, trades[i].price, trades[i].type);
                found = 1;
            }
        }

        if (!found) {
            printf("일치하는 매매내역이 없습니다.\n");
        }
    }


    if (searchType == 3) {
        do {
        printf("검색할 종목코드 6자리를 입력하세요. \n");
            scanf("%s", tradecode);
        } while (strlen(tradecode) != 6);

        for (i = 0; i < numTrades; i++) {
            if (strcmp(trades[i].code, tradecode) == 0) {
                printf("종목번호: %s, 날짜: %s, 거래수량: %d, 거래가격: %d, 매매타입: %d \n", trades[i].code, trades[i].date, trades[i].amount, trades[i].price, trades[i].type);
                found = 1;
            }
        }

        if (!found) {
            printf("일치하는 매매내역이 없습니다.\n");
        }
    }


}