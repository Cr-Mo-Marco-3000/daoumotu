#include "../hdr/generic.h"
#include "../hdr/built_in_library.h"

void savestockholdlst(Stock* entire_usr_stock)
{

	FILE* fp_save_stock;
	int i = 0;
	fp_save_stock = fopen("data/stock.txt", "wt");

	while (entire_usr_stock[i].member_num)
	{
		fprintf(fp_save_stock, "%d\t%s\t%d\n", entire_usr_stock[i].member_num, entire_usr_stock[i].code, entire_usr_stock[i].quantity);
		printf("%s\n", entire_usr_stock[i].code);
	}

	fclose(fp_save_stock);
	printf("보유 주식 잔고 파일이 저장되었습니다");
}