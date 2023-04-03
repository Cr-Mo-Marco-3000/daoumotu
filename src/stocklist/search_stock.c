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
        printf("�����ȣ 6�ڸ��� �Է��ϼ���: ");
        scanf("%s", stock_code);
    } while (strlen(stock_code) != 6);

    do {
        printf("���Ŀ� ���� ��¥�� �Է��ϼ��� (yyyy.mm.dd): ");
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

    // �Է��� �����ڵ�� ��¥ ������ ��ġ�ϴ� �ֽ� ������ ã�� ������ �ݺ�
    while (!found) {
        found = 0; // �ʱ�ȭ

        // ���Ͽ��� �� �پ� �����鼭 �����ȣ�� ��¥ ������ ��ġ�ϴ� �ֽ� ������ ����մϴ�.
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
                printf("�����ڵ�: %s\n�����: %s\n��¥: %s\n����: %d\n���Ϻ�: %d\n�ð�: %d\n��: %d\n����: %d\n�ŷ���: %d\n\n",
                    stock_info.stock_code, stock_info.stock_name, stock_info.date, stock_info.close, stock_info.compare, stock_info.open, stock_info.high,
                    stock_info.low, stock_info.volume);

                found = 1;
                break;
            }
        }

        // ã�� ���� ���, �ٽ� �Է� �ޱ�
        if (!found) {
            printf("�ش�Ǵ� �ֽ� ������ �����ϴ�.\n\n");
            do {
                printf("�����ȣ 6�ڸ��� �Է��ϼ���: ");
                scanf("%s", stock_code);
            } while (strlen(stock_code) != 6);

            do {
                printf("���Ŀ� ���� ��¥�� �Է��ϼ��� (yyyy.mm.dd): ");
                scanf("%s", date);
            } while (strlen(date) != 10);

            // ���� �����͸� ������ �������� �̵��Ͽ� �ٽ� Ž��
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


    printf("�����ȣ�� �Է��ϼ���: ");
    scanf("%s", stock_code);

    printf("��¥�� �Է��ϼ��� (yyyy.mm.dd): ");
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

    // �Է��� �����ڵ�� ��¥ ������ ��ġ�ϴ� �ֽ� ������ ã�� ������ �ݺ�
    while (!found) {
        found = 0; // �ʱ�ȭ

        // ���Ͽ��� �� �پ� �����鼭 �����ȣ�� ��¥ ������ ��ġ�ϴ� �ֽ� ������ ����մϴ�.
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
                printf("�����ڵ�: %s\n�����: %s\n��¥: %s\n����: %d\n���Ϻ�: %d\n�ð�: %d\n��: %d\n����: %d\n�ŷ���: %d\n\n",
                    stock_info.stock_code, stock_info.stock_name, stock_info.date, stock_info.close, stock_info.compare, stock_info.open, stock_info.high,
                    stock_info.low, stock_info.volume);


                found = 1;
                break;
            }
        }

        // ã�� ���� ���, �ٽ� �Է� �ޱ�
        if (!found) {
            printf("�ش�Ǵ� �ֽ� ������ �����ϴ�.\n\n");
            printf("�����ȣ�� �Է��ϼ���: ");
            scanf("%s", stock_code);

            printf("��¥�� �Է��ϼ��� (yyyy.mm.dd): ");
            scanf("%s", date);

            // ���� �����͸� ������ �������� �̵��Ͽ� �ٽ� Ž��
            fseek(fp, 0, SEEK_SET);
        }
    }

    fclose(fp);
}
*/