/*
* generic_function.c
* ------------------
* ������Ʈ ���� ���Ͽ��� ����� ���� �Լ��� �����س��� �����Դϴ�.
*/
#include "../hdr/generic.h"
#include "../hdr/built_in_library.h"



/*
* Function: checkStringLength
* ---------------------------
* ���ڿ��� ���̸� Ȯ���ϴ� �Լ��Դϴ�.
* 
* msg: ����� �޽���(�ٹٲ��� �ڵ�)
* string: ���������� ���ڿ��� �Է¹��� ���ڹ迭�� ���� ������
* minSize: ���� �迭�� �ּ� ũ��(���� ���, ���̵�� �� ���ٴ� ���� ��)
* size: ���� �迭�� �ѵ� ������(���ڿ��� �ִ� ������ �ƴ�!)
*/

void checkStringLength(char *msg, char *string, int minSize, int size) {
	char tmp[300];

	int flag = 0;
	do {
		if (flag) {
			puts("�Է� ������ ���� �ʽ��ϴ�\n");
			puts("�ٽ� �Է� ��Ź�帳�ϴ�\n");
		}
		else {
			puts(msg);
			flag = 1;
		}
		gets(tmp);
	} while (strlen(tmp) < minSize || strlen(tmp) >= size);

	strcpy(string, tmp);
}

void num_check(char *msg, int max, int min, int *f_addr)
{
	int tmp;

	do {
		printf("%s ? ", msg);
		scanf("%d%*c", &tmp);
	} while (tmp<min || tmp>max);

	*f_addr = tmp;
}