#include "../hdr/generic.h"
#include "../hdr/built_in_library.h"


void auth(USER *userP);
void login(USER *userP);
void signup(USER *userP);
void logout(USER *userP);


/*
typedef struct User {
	int userNo;
	char name[31];
	int balance;
} USER;
*/

// �α��� �� ���� ����Ʈ�� ���� ����Ʈ�� ����� �Լ�
void loadList(USER** user, USER **head, USER **tail) {	// user����, �����͸� ����Ű�� �����Ͱ� ���, ���� �� �����ʹ� userTemp�� ����Ű�� ����, userTemp�� �˻��ؼ�, 
	char tmp[200];
	USER *ptr;
	FILE *fp;
	fp = fopen("data/user.txt", "r");
	if (fp == NULL) {
		perror("Error");
		exit(1);
	}
	while (1) {
		ptr = (USER *)malloc(sizeof(USER));			// ����ü �����Ҵ�
		if (ptr == NULL) {
			perror("�޸� ����");
			exit(1);
		}
		if (fgets(tmp, 100, fp) == NULL) {			// ������ �� => break
			break;
		} else {									// �ƴϸ� ������ ������ ����ü�� ������ ����
			ptr->userNo = atoi(strtok(tmp, "\t"));
			strcpy(ptr->id, strtok(NULL, "\t"));
			strcpy(ptr->password, strtok(NULL, "\t"));
			strcpy(ptr->name, strtok(NULL, "\t"));
			ptr->balance = atoi(strtok(NULL, "\t"));
			if (ptr->userNo == (*user)->userNo) {
				*user = ptr;
			}
		}

		ptr->next = NULL;

		if (*head == NULL) {						// ���� head�� ������
			*head = *tail = ptr;
		} else {
			(*tail)->next = ptr;
			(*tail) = ptr;
		}
	}

	fclose(fp);
	free(ptr);

}

void saveList(USER *node) {
	FILE *fp;
	USER *prev;
	fp = fopen("data/user.txt", "w");

	if (fp == NULL) {
		perror("Error");
		exit(1);
	}
	while (1) {
		if (node->next == NULL) {
			fprintf(fp, "%d\t%s\t%s\t%s\t%d", node->userNo, node->id, node->password, node->name, node->balance);
			free(node);
			break;
		} else {
			fprintf(fp, "%d\t%s\t%s\t%s\t%d\n", node->userNo, node->id, node->password, node->name, node->balance);
		}
		prev = node;
		node = node->next;
		free(prev);
	}

	fclose(fp);
}


void auth(USER *userP) {
	char tmp[250]; // ����
	int tempUserno; // ȸ����ȣ ������ ����

	while (1) {

		int oneOrTwo;
		puts("\n\n\n");
		printf("���� ���� ���α׷� �ٿ����\n");
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
	char tmp[200];
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
		
		while (fgets(tmp, 200, fp) != NULL) {
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