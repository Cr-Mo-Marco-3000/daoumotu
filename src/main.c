#include "../hdr/generic.h"
#include "../hdr/built_in_library.h"



int main(void) 
{	
	USER user = { -1 };
	int choose;

	// ��ü �ֽ� �����ȣ �迭 ����
	//char stock_lst[STOCK_ALL_CNT][50];
	//stock_usr_array(stock_lst);

	// ��ü ����
	while (1) {
		if (user.userNo == -1) {	// �α����� �� �� ����
			printf("���񽺿� �����Ϸ��� 1, �����Ϸ��� 2�� �Է����ּ���.\n");
			choose = getchar();
			while (getchar() != '\n');
			if (choose == '1') {
				auth(&user);
			} else if (choose == '2') {
				printf("�̿��� �ּż� �����մϴ�. �ȳ��� ���ʽÿ�.\n");
				Sleep(500);
				exit(1);
			} else {
				printf("�Է��� ����Ȯ�մϴ�. �ٽ� �Է� ��Ź�帳�ϴ�.\n");
				Sleep(1000);
			}
		} else {
			// �̿��Ͻ� ���񽺸� �������ּ���
		
			printf("1. �ֽ� ��� ��ȸ");
			printf("���񽺿� ��ϵ� ��� �ֽ��� ��ȸ�մϴ�.");

			printf("0. �α׾ƿ�");
			printf("���񽺿��� �α׾ƿ��մϴ�.");
			
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