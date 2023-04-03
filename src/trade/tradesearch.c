#include "../../hdr/generic.h"
#include "../../hdr/built_in_library.h"

#define MAX_LINE_LENGTH 100
#define MAX_TRADES 1024


// �Լ� ����


void tradesearch() {
    char filename[] = "data/tradelist.txt";
    Trade trades[MAX_TRADES]; // �ִ� 1024���� �Ÿų����� �����ϴ� ����ü �迭
    int numTrades = 40; // ���� ����� �Ÿų����� ����

    // �Ÿų��� ����(tradelist.txt)�� �о trades ����ü �迭�� ����
    readTrades(filename, trades, &numTrades);

    // �˻��� Ÿ�� �Է¹ޱ�
    int searchType;
    do {
        printf("�˻��� Ÿ���� �Է��ϼ��� (1: ��¥, 2: �Ÿ�Ÿ��, 3: �����ȣ): ");
        scanf("%d", &searchType);
    } while (searchType != 1 && searchType != 2 && searchType != 3);

    // �Ÿų��� �˻�
    searchTrades(searchType, trades, numTrades);

}

// tradelist.txt ���Ͽ��� �Ÿų����� �о trades ����ü �迭�� �����ϴ� �Լ�
void readTrades(char* filename, struct Trade* trades, int* numTrades) {
    FILE* fp;
    char line[MAX_LINE_LENGTH];
    char* token;
    

    fp = fopen("data/tradelist.txt", "r");
    if (fp == NULL) {
        printf("������ �� �� �����ϴ�.\n");
        exit(1);
    }

    // ù ��° ���� ����
    fgets(line, MAX_LINE_LENGTH, fp);

    while (fgets(line, MAX_LINE_LENGTH, fp) != NULL) {
            token = strtok(line, " \t"); //ȸ����ȣ ������

        if (atoi(token) == 1) //1�� ������ ȸ����ȣ�� �� �Ŷ� �̰� ȸ����ȣ �Ѱ� �� �� userNo ������ �ٲ� ��� ��
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
        printf("�˻��� ��¥�� �Է��ϼ���. (YYYY.MM.DD): \n");
        scanf("%s", inputDate);
        } while (strlen(inputDate) != 10);

        for (i = 0; i < numTrades; i++) {
            if (strcmp(trades[i].date, inputDate) == 0) {
                //printf("%s", trades[i].date);
                printf("�����ȣ: %s, ��¥: %s, �ŷ�����: %d, �ŷ�����: %d, �Ÿ�Ÿ��: %d \n", trades[i].code, trades[i].date, trades[i].amount, trades[i].price, trades[i].type);
                found = 1;
            }
        }

        if (!found) {
            printf("��ġ�ϴ� �Ÿų����� �����ϴ�.\n");
        }
    }


    if (searchType == 2) {
        do {
            printf("�˻��� �Ÿ�Ÿ���� �Է��ϼ���. (1: �ż� 2: �ŵ�) \n");
            scanf("%d", &tradetype);
        } while (tradetype != 1 && tradetype != 2);

        for (i = 0; i < numTrades; i++) {
            if (trades[i].type == tradetype) {
                printf("�����ȣ: %s, ��¥: %s, �ŷ�����: %d, �ŷ�����: %d, �Ÿ�Ÿ��: %d \n", trades[i].code, trades[i].date, trades[i].amount, trades[i].price, trades[i].type);
                found = 1;
            }
        }

        if (!found) {
            printf("��ġ�ϴ� �Ÿų����� �����ϴ�.\n");
        }
    }


    if (searchType == 3) {
        do {
        printf("�˻��� �����ڵ� 6�ڸ��� �Է��ϼ���. \n");
            scanf("%s", tradecode);
        } while (strlen(tradecode) != 6);

        for (i = 0; i < numTrades; i++) {
            if (strcmp(trades[i].code, tradecode) == 0) {
                printf("�����ȣ: %s, ��¥: %s, �ŷ�����: %d, �ŷ�����: %d, �Ÿ�Ÿ��: %d \n", trades[i].code, trades[i].date, trades[i].amount, trades[i].price, trades[i].type);
                found = 1;
            }
        }

        if (!found) {
            printf("��ġ�ϴ� �Ÿų����� �����ϴ�.\n");
        }
    }


}