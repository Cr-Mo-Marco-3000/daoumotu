#include "../hdr/generic.h"
#include "../hdr/built_in_library.h"



int main(void) 
{	
	USER usertemp = { -1 }; // �ӽ� ���� ȸ��
	
	USER *user;

	user = &usertemp;

	USER *start = NULL, *end = NULL;		// ȸ�� ���� ����Ʈ�� ���۰� �� �ּ� 

	int choose;

	// �ֽ� �迭 ����Ʈ
	StockInfo stockInfoList[500];


	// �ֽ� �迭 ��� �Լ�
	

	//  ������ ����ü �迭�� ���
	StockInfo tmp[600] = { 0 };
	Stock stock[100] = { 0 };
	FILE* st, * pr;
	char trs[200];
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

	// ��ü ����
	while (1) {
		if (user->userNo == -1) {	// �α����� �� �� ����
			printf("���񽺿� �����Ϸ��� 1, �����Ϸ��� 2�� �Է����ּ���.\n");
			choose = getchar();
			while (getchar() != '\n');
			if (choose == '1') {
				auth(user);
			} else if (choose == '2') {
				printf("�̿��� �ּż� �����մϴ�. �ȳ��� ���ʽÿ�.\n");
				Sleep(500);
				exit(1);
			} else {
				printf("�Է��� ����Ȯ�մϴ�. �ٽ� �Է� ��Ź�帳�ϴ�.\n");
				Sleep(1000);
			}
		} else {
			loadList(&user, &start, &end);							// ���� ���� ���� ����Ʈ ����� �Լ�
			puts("�̿��Ͻ� ���񽺸� ������ �ּ���");
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
			printf("==================================\n���� ��ȣ �Է� : ");
			scanf("%d", &choose);
			while (getchar() != '\n');

			if (choose == 1) {
				print_function(tmp);
			} else if (choose == 2) {
				stock_detail();
			} else if (choose == 3) {
				// ���� �ֽ� �ŸŰ� ���� �˴ϴ�.
				//trade(&user);
			} else if (choose == 4) {
				tradesearch();
			} else if (choose == 5) {
				portfolio(user, stock, tmp);
				// ���� ��Ʈ������ ���Ⱑ ���� �˴ϴ�.
			} else if (choose == 0) {
				// ���� ������ ���� ��
				saveList(start);
				// �������δ� ���� ������ �ʱ�ȭ �� HEAD �ʱ�ȭ
				user = &usertemp;
				start = end = NULL;			// �ٽ� �α��� ��, ���� �迭�� ��������� NULL�� �ٲ���
				puts("�α׾ƿ��մϴ�.");
				Sleep(1000);
			}
		}
	}
	
	return 0;
}