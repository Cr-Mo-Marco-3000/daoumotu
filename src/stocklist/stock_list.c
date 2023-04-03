#include "../../hdr/generic.h"
#include "../../hdr/built_in_library.h"



void hope_function(StockInfo *structptr) //주식 목록 전체 출력
{

	//주식 목록 출력

	FILE *fp;
	int i;

	fp = fopen("data/output.txt", "r");

	if (fp == NULL)
	{
		printf("파일 출력 실패\n");
		return;
	}

	for (int i = 0; i < 400; i++) {
		fscanf(fp, "%s %s %s %d %d %d %d %d %d\n",
			structptr[i].stock_code,
			structptr[i].stock_name,
			structptr[i].date,
			&structptr[i].close,
			&structptr[i].compare,
			&structptr[i].open,
			&structptr[i].high,
			&structptr[i].low,
			&structptr[i].volume
		);
	}

}

void print_function(StockInfo *structptr) {
	int i;
	for (int i = 0; i < 400; i++)
	{
		printf("%s %s %s %d %d %d %d %d %d\n",
			structptr[i].stock_code,
			structptr[i].stock_name,
			structptr[i].date,
			structptr[i].close,
			structptr[i].compare,
			structptr[i].open,
			structptr[i].high,
			structptr[i].low,
			structptr[i].volume);
	}
}