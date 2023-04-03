#include "../hdr/generic.h"
#include "../hdr/built_in_library.h"


void auth(USER *userP);
void login(USER *userP);
void signup(USER *userP);
void logout(USER *userP);

void auth(USER *userP) {
	char tmp[250]; // ����
	int tempUserno; // ȸ����ȣ ������ ����

	while (1) {

		int oneOrTwo;

		printf("���� ���� ���α׷� Ũ����Ƽ\n");
		printf("ȯ���մϴ�! �α���(1) Ȥ�� ȸ������(2)�� ������ �ּ���! \n");

		scanf("%s", tmp);
		
		while (getchar() != '\n');

		if (atoi(tmp) == 1 && strlen(tmp) == 1) {
			login(userP);
			break;
		}
		else if (atoi(tmp) == 2 && strlen(tmp) == 1) {
			signup(userP);
			break;
		}
		else {
			printf("�Է� ������ ���� �ʽ��ϴ�.\n");
		}

	}
}


void login(USER *userP) {
	char id[31];
	char password[31];
	char tmp[100];
	FILE *fp;
	char *ptr;
	int flag = 0;
	int cnt = 1;

	while (!flag) {
		printf("���̵� �Է��� �ּ���\n");
		scanf("%s", id);
		printf("�н����带 �Է��� �ּ���\n");
		scanf("%s", password);

		fp = fopen("data/user.txt", "r");

		if (fp == NULL) {
			perror("Error");
			exit(1);
		}

		while (fgets(tmp, 100, fp)) {
			ptr = strtok(tmp, "\t");
			if (!strcmp(strtok(NULL, "\t"), id) && !strcmp(strtok(NULL, "\t"), password)) {
				userP->userNo = cnt;
				strcpy(userP->name, strtok(NULL, "\t"));
				userP->balance = atoi(strtok(NULL, "\t"));
				flag = 1;
				break;
			}
			cnt++;
		}
		if (flag) {
			printf("�α��� �Ϸ�!\n");
			printf("%d, %s, %d\n", userP->userNo, userP->name, userP->balance);
			puts("");

		}
		else {
			printf("ȸ�������� �ٽ� Ȯ�����ּ���\n");
			puts("");
		}
		cnt = 1;
		fclose(fp);
	}
}

void signup(USER *userP) {
	char id[31];
	char password[31];
	char passwordConfirm[31];
	char name[21];

	char tmp[200];
	FILE *fp;
	char *ptr;

	int flag = 1;
	int cnt = 1;

	char yOrN;

	while (1) { // ��ü�Լ�

		flag = 1;

		// ���̵� �ߺ� Ȯ�� �Լ�
		while (flag) {
			checkStringLength("���̵� �Է��� �ּ���(�ּ� 5����)", id, 5, 31); // ���̵� ���� Ȯ��
			flag = 0;
			fp = fopen("data/user.txt", "r");

			if (fp == NULL) {
				perror("Error");
				exit(1);
			}

			while (fgets(tmp, 100, fp)) {
				ptr = strtok(tmp, "\t");
				if (!strcmp(strtok(NULL, "\t"), id)) {
					printf("�̹� �����ϴ� ���̵��Դϴ�\n");
					flag = 1;
					break;
				}
			}
			fclose(fp);
		}

		// ��й�ȣ Ȯ�� �Լ�
		while (1) {
			checkStringLength("��й�ȣ�� �Է��� �ּ���(�ּ� 5����)", password, 5, 31);
			checkStringLength("��й�ȣ Ȯ���� �Է��� �ּ���", passwordConfirm, 5, 31);
			if (strcmp(password, passwordConfirm)) {
				printf("��й�ȣ�� ��й�ȣ Ȯ���� ���� �ʽ��ϴ�\n");
				continue;
			}
			break;
		}

		// �̸� Ȯ�� �Լ�
		checkStringLength("�̸��� �Է��� �ּ���(�ѱ� 3����, ���� 5����)", name, 5, 21);

		flag = 0;
		do {
			if (flag) {
				puts("�ٽ� �Է� ��Ź�帳�ϴ�");
			}
			else {
				puts("�����Ͻô� ȸ������ ������ ������ �½��ϱ�?(y/n) \n");
				printf("���̵�: %s \n", id);
				printf("�̸�: %s \n", name);
				flag = 1;
			}
			yOrN = getchar();
			yOrN = tolower(yOrN);
			while (getchar() != '\n');
		} while (!(yOrN == 'n' || yOrN == 'y'));

		if (yOrN == 'n') {
			printf("���̵� �Է����� �ǵ��ư��ϴ�\n");
			continue;
		}
		else if (yOrN == 'y') {
			cnt = 1;
			fp = fopen("data/user.txt", "a+");

			while (fgets(tmp, 100, fp)) {
				cnt++;
			}
			fprintf(fp, "\n%d\t%s\t%s\t%s\t%d", cnt, id, password, name, 10000000);
			fclose(fp);

			printf("ȸ�������� �Ϸ��߽��ϴ�\n");
			Sleep(1000);
			strcpy(userP->name, name);
			userP->userNo = cnt;
			userP->balance = 10000000;

			return;
		}
	}
}

void logout(USER *userP) {
	userP->userNo = -1;
	strcpy(userP->name,"");
	userP->balance = -1;
	return;
}