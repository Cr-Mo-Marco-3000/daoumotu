#pragma once
/*
* generic.h
* ---------
* 이 헤더파일에는, 여러 소스파일에서 사용될 구조체, 함수 원형이 선언되어 있습니다.
*/

/*
구조체 선언문입니다.
*/
typedef struct User {
	int userNo;
	char id[31];
	char password[31];
	char name[31];
	int balance;
	struct User *next;
} USER;

typedef struct Trade {
	char date[11];
	int type;
	char code[11];
	int amount;
	int price;
}Trade;

typedef struct  // 잔고주식데이터 회원번호/종목코드/보유주식수
{
	int member_num;
	char code[30];
	int quantity;
} Stock;

typedef struct StockInfo {
	char stock_code[10];
	char stock_name[20];
	char date[30];
	int close;
	int compare;
	int open;
	int high;
	int low;
	int volume;
} StockInfo;

typedef struct Stock_user_Array
{
	int size;
	int max_size;
	Stock *stackArrayP;
} STOCK_USER_ARRAY, *LPSTOCK_USER_ARRAY;


/*
공용 함수에 대한 함수 원형입니다.
*/
void checkStringLength(char *msg, char *string, int size);
void num_check(char *msg, int max, int min, int *f_addr);

#define STOCK_ALL_CNT 30



/*
auth.c 파일에 대한 함수 원형입니다.
*/

void auth(USER *userP);
void login(USER *userP);
void signup(USER *userP);
void logout(USER *userP);
void loadList(USER **user, USER **head, USER **tail);

