#include "../hdr/generic.h"
#include "../hdr/built_in_library.h"



int main(void) 
{	
	USER usertemp = { -1 }; // �ӽ� ���� ȸ��
	
	USER *user;

	user = &usertemp;

	USER *start = NULL, *end = NULL;		// ȸ�� ���� ����Ʈ�� ���۰� �� �ּ� 

	int choose;

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
			printf("1. �ֽ� ��� ��ȸ\n");
			printf("���񽺿� ��ϵ� ��� �ֽ��� ��ȸ�մϴ�.\n");
			putchar('\n');
			puts("2. �ֽ� �� ���� ��ȸ\n");
			printf("���� �ڵ带 �Է��Ͽ� �ֽ� �� ������ ��ȸ�մϴ�.\n");
			putchar('\n');
			puts("3. �ֽ� �Ÿ�\n");
			printf("�ֽ��� �Ÿ��մϴ�.\n");
			putchar('\n');
			puts("4. �ֽ� �Ÿų��� �˻�\n");
			printf("���� �ֽ��� �Ÿ��� ������ �����մϴ�.\n");
			putchar('\n');
			puts("5. ��Ʈ������ ����\n");
			printf("���� ������ �ֽİ� ��Ʈ�������� �����մϴ�.\n");
			putchar('\n');
			printf("0. �α׾ƿ�");
			printf("���񽺿��� �α׾ƿ��մϴ�.");
			scanf("%d", &choose);
			while (getchar() != '\n');

			if (choose == 1) {
				// ���� �ֽ� ��� ��ȸ
			} else if (choose == 2) {
				// ���� �ֽ� �� ���� ��ȸ
			} else if (choose == 3) {
				// ���� �ֽ� �ŸŰ� ���� �˴ϴ�.
			} else if (choose == 4) {
				// ���� �ֽ� �Ÿų��� �˻��� ���� �˴ϴ�.
			} else if (choose == 5) {
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
	/*

	// ��Ʈ������ Ȯ�� �Լ�

	// �ֽ� ���� �˻� �Լ�

	// �ֽ� �Ÿų��� �˻� �Լ�

	// �Ÿ��Լ�
	STOCK_USER stock_usr[5] = { {4, "009150",7},
						   {4, "105560",15},
						   {4, "051900",5},
						   {4, "035420",10},
						   {4, "068270",1}
	};

	trade(&user,stock_usr, stock_lst);

	printf("%s, %d, %d, ������", user.name, user.userNo, user.balance);

	printf("%d", 10);
	*/
	// �α׾ƿ� �Լ�
 
	return 0;
}