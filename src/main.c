#include "../hdr/generic.h"
#include "../hdr/built_in_library.h"



int main(void)
{
	FILE *st, *pr, *fp;
	StockInfo tmp[600] = { 0 };
	Stock stock[100] = { 0 };
	char trs[200];
	USER *user;
	USER usertemp = { -1 }; // �ӽ� ���� ȸ��
	USER *start = NULL, *end = NULL;		// ȸ�� ���� ����Ʈ�� ���۰� �� �ּ� 
	int choose;
	StockInfo stockInfoList[500];
	char print_tmp[256];
	HANDLE h_console = GetStdHandle(STD_OUTPUT_HANDLE); // ���� ������ ������ �ڵ�
	fp = fopen("data/pictogram.txt", "r");

	puts("");
	SetConsoleTextAttribute(h_console, 4); // => ���� ������
	if (fp == NULL)
	{
		printf("���� �ҷ����� ���� \n");
		return 1;
	}
	while (fgets(print_tmp, 255, fp) != NULL) {
		printf(print_tmp);
		if (print_tmp[9] == ' ') {
			SetConsoleTextAttribute(h_console, 1); // => ���� �Ķ��� |�� ���
		}
	}
	SetConsoleTextAttribute(h_console, 15);
	fclose(fp);

	user = &usertemp;

	// �ֽ� �迭 ����Ʈ


	// �ֽ� �迭 ��� �Լ�


	//  ������ ����ü �迭�� ���

	st = fopen("data/stock.txt", "rt");
	if (st == NULL) {
		perror("ERROR");
	}


	pr = fopen("data/output.txt", "rt");
	if (pr == NULL) {
		perror("ERROR");
	}

	fgets(trs, 200, pr);
	int i = 0;
	while (1)
	{
		int cn;
		cn = fscanf(pr, "%s %s %s %d %d %d %d %d %d", tmp[i].stock_code, // id�� ��ġ�ϸ� tmp ����ü�� �Ϻ� �ü������͸� �Է�
			tmp[i].stock_name, tmp[i].date, &tmp[i].open, &tmp[i].compare, &tmp[i].high, &tmp[i].low, &tmp[i].close, &tmp[i].volume);
		if (cn != 9)
			break;
		i++;
	}
	i = 0;


	while (1)
	{
		int cn;
		cn = fscanf(st, "%d %s %d", &stock[i].member_num, stock[i].code, &stock[i].quantity);
		if (cn != 3)
			break;
		i++;
	}
	//����ü �迭 ��ƿ��� ��

	fclose(st);
	fclose(pr);
	// ��ü ����
	while (1) {
		if (start == NULL) {	// �α����� �� �� ����
			Sleep(1000);
			printf("\n���񽺿� �����Ϸ��� 1, �����Ϸ��� 2�� �Է����ּ���.\n");
			choose = getchar();
			while (getchar() != '\n');
			if (choose == '1') {
				auth(user);
				loadList(&user, &start, &end);							// ���� ���� ���� ����Ʈ ����� �Լ�
			}
			else if (choose == '2') {
				printf("�̿��� �ּż� �����մϴ�. �ȳ��� ���ʽÿ�.\n");
				Sleep(500);
				exit(1);
			}
			else {
				printf("�Է��� ����Ȯ�մϴ�. �ٽ� �Է� ��Ź�帳�ϴ�.\n");
				Sleep(1000);
			}
		}
		else {
			puts("\n�̿��Ͻ� ���񽺸� ������ �ּ���\n");
			printf("==================================\n");
			printf("1. ��� �ֽ� ���� ��ȸ\n");
			printf("���񽺿� ��ϵ� ��� �ֽ��� 20��ġ ������ ��ȸ�մϴ�.\n");
			putchar('\n');
			printf("2. �ֽ� �� ���� ��ȸ\n");
			printf("���� �ڵ带 �Է��Ͽ� �ֽ� �� ������ ��ȸ�մϴ�.\n");
			putchar('\n');
			printf("3. �ֽ� �Ÿ�\n");
			printf("�ֽ��� �Ÿ��մϴ�.\n");
			putchar('\n');
			printf("4. �ֽ� �Ÿų��� �˻�\n");
			printf("���� �ֽ��� �Ÿ��� ������ �����մϴ�.\n");
			putchar('\n');
			printf("5. ��Ʈ������ ����\n");
			printf("���� ������ �ֽİ� ��Ʈ�������� �����մϴ�.\n");
			putchar('\n');
			printf("0. �α׾ƿ�\n");
			printf("���񽺿��� �α׾ƿ��մϴ�.\n");
			Sleep(500);
			printf("\n==================================\n���� ��ȣ �Է� : ");
			scanf("%d", &choose);
			while (getchar() != '\n');

			if (choose == 1) {
				print_function(tmp);
			}
			else if (choose == 2) {
				stock_detail();
			}
			else if (choose == 3) {
				// ���� �ֽ� �ŸŰ� ���� �˴ϴ�.
				trade(user, stock, tmp);
			}
			else if (choose == 4) {
				tradesearch(user);
			}
			else if (choose == 5) {
				portfolio(user, stock, tmp);
				// ���� ��Ʈ������ ���Ⱑ ���� �˴ϴ�.
			}
			else if (choose == 0) {


				// ���� ������ ���� ��
				saveList(start);
				savestockholdlst(stock);
				// �������δ� ���� ������ �ʱ�ȭ �� HEAD �ʱ�ȭ
				user = &usertemp;
				start = end = NULL;			// �ٽ� �α��� ��, ���� �迭�� ��������� NULL�� �ٲ���
				puts("\n�α׾ƿ��մϴ�.\n");
				Sleep(1000);
			}
		}
	}

	return 0;
}