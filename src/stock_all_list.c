#include "../hdr/generic.h"
#include "../hdr/built_in_library.h"

void stock_usr_array(char stock_lst[STOCK_ALL_CNT][50])
{
	int cnt = 0;

	FILE* fp_stock;
	// ��Ʈ�� ����
	fp_stock = fopen("data/output_tab.txt", "r");

	if (fp_stock == NULL)
	{
		perror("error :");
		exit(1);
	}

	char tmp[200];
	char* token_stock, *token_date;

	// ������ �б�

	while (cnt < STOCK_ALL_CNT)
	{
		fgets(tmp, sizeof(tmp) - 1, fp_stock);
		token_stock = strtok(tmp, " \t");
		strtok(NULL, " \t");
		token_date = strtok(NULL, " \t");
		if (strcmp(token_date, "2023.03.30") == 0)
		{
			strcpy(stock_lst[cnt], token_stock);
			cnt++;
		}
		else
			continue;
	}
	// ��Ʈ�� �ݱ�
	fclose(fp_stock);

	return;
}