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
		printf("큠 모의투자 서비스 실시간 주식 목록 \n\n");
		//주식 목록 출력

		
		FILE *fp;

		fp = fopen("data/output.txt", "r");
		if (fp == NULL)
		{	
			printf("파일 출력 실패\n");
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
		printf("1: 매수/매도 페이지로 이동\n");
		printf("2: 주식별 상세 페이지로 이동\n");
		printf("============================\n");

		scanf("%d", &MENU);

		if (MENU == 1)
			printf("여기 매수매도 함수 나와야 댐\n");
		else if (MENU == 2)
			printf("여기 상세페이지 가야 댐\n");
	} while (MENU != 1 && MENU != 2);


}
