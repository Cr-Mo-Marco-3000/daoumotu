//stock_list.c

#include "../../hdr/generic.h"
#include "../../hdr/built_in_library.h"

//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//typedef struct {
//	char stock_code[10];
//	char stock_name[20];
//	char date[30];
//	int compare;
//	int open;
//	int high;
//	int low;
//	int close;
//	int volume;
//} StockInfo;
//
//typedef struct User {
//	int userNo;
//	char name[31];
//	int balance;
//} USER;

void hope_function();


int main()
{
	hope_function();


	return 0;
}

void hope_function()
{
	int MENU;
	char str_tmp[1024];
		printf("Ũ �������� ���� �ǽð� �ֽ� ��� \n\n");
		//�ֽ� ��� ���

		
		FILE *fp;

		fp = fopen("data/output.txt", "r");
		if (fp == NULL)
		{	
			printf("���� ��� ����\n");
				return 1;
		}
		while (fgets(str_tmp, sizeof(str_tmp), fp) != NULL) {
			printf("%s", str_tmp);
		}
		fclose(fp);


	do
	{

		printf("\n");
		printf("============================\n");
		printf("1: �ż�/�ŵ� �������� �̵�\n");
		printf("2: �ֽĺ� �� �������� �̵�\n");
		printf("============================\n");

		scanf("%d", &MENU);

		if (MENU == 1)
			printf("���� �ż��ŵ� �Լ� ���;� ��\n");
		else if (MENU == 2)
			printf("���� �������� ���� ��\n");
	} while (MENU != 1 && MENU != 2);


}
