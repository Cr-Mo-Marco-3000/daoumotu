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

// 로그인 시 유저 리스트를 연결 리스트로 만드는 함수
void loadList(USER** user, USER **head, USER **tail) {	// user에는, 포인터를 가리키는 포인터가 담김, 현재 그 포인터는 userTemp를 가리키고 있음, userTemp를 검사해서, 
	char tmp[200];
	USER *ptr;
	FILE *fp;
	fp = fopen("data/user.txt", "r");
	if (fp == NULL) {
		perror("Error");
		exit(1);
	}
	while (1) {
		ptr = (USER *)malloc(sizeof(USER));			// 구조체 동적할당
		if (ptr == NULL) {
			perror("메모리 부족");
			exit(1);
		}
		if (fgets(tmp, 100, fp) == NULL) {			// 파일의 끝 => break
			break;
		} else {									// 아니면 위에서 생성한 구조체에 정보를 저장
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

		if (*head == NULL) {						// 만약 head에 없으면
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
	char tmp[250]; // 버퍼
	int tempUserno; // 회원번호 저장할 변수

	while (1) {

		int oneOrTwo;
		puts("\n\n\n");
		printf("모의 투자 프로그램 다우모투\n");
		printf("환영합니다! 로그인(1) 혹은 회원가입(2)을 선택해 주세요! \n");

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
			printf("입력 형식이 맞지 않습니다.\n");
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
		printf("아이디를 입력해 주세요\n");
		scanf("%s", id);
		printf("패스워드를 입력해 주세요\n");
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
			printf("로그인 완료!\n");
			puts("");

		}
		else {
			printf("회원정보를 다시 확인해주세요\n");
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

	while (1) { // 전체함수

		flag = 1;

		// 아이디 중복 확인 함수
		while (flag) {
			checkStringLength("아이디를 입력해 주세요(최소 5글자)", id, 5, 31); // 아이디 길이 확인
			flag = 0;
			fp = fopen("data/user.txt", "r");

			if (fp == NULL) {
				perror("Error");
				exit(1);
			}

			while (fgets(tmp, 100, fp)) {
				ptr = strtok(tmp, "\t");
				if (!strcmp(strtok(NULL, "\t"), id)) {
					printf("이미 존재하는 아이디입니다\n");
					flag = 1;
					break;
				}
			}
			fclose(fp);
		}

		// 비밀번호 확인 함수
		while (1) {
			checkStringLength("비밀번호를 입력해 주세요(최소 5글자)", password, 5, 31);
			checkStringLength("비밀번호 확인을 입력해 주세요", passwordConfirm, 5, 31);
			if (strcmp(password, passwordConfirm)) {
				printf("비밀번호와 비밀번호 확인이 같지 않습니다\n");
				continue;
			}
			break;
		}

		// 이름 확인 함수
		checkStringLength("이름을 입력해 주세요(한글 3글자, 영문 5글자)", name, 5, 21);

		flag = 0;
		do {
			if (flag) {
				puts("다시 입력 부탁드립니다");
			}
			else {
				puts("가입하시는 회원님의 정보가 다음이 맞습니까?(y/n) \n");
				printf("아이디: %s \n", id);
				printf("이름: %s \n", name);
				flag = 1;
			}
			yOrN = getchar();
			yOrN = tolower(yOrN);
			while (getchar() != '\n');
		} while (!(yOrN == 'n' || yOrN == 'y'));

		if (yOrN == 'n') {
			printf("아이디 입력으로 되돌아갑니다\n");
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

			printf("회원가입을 완료했습니다\n");
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