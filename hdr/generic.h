#pragma once
/*
* generic.h
* ---------
* �� ������Ͽ���, ���� �ҽ����Ͽ��� ���� ����ü, �Լ� ������ ����Ǿ� �ֽ��ϴ�.
*/


/* ��ũ�� ��� */

#define STOCK_ALL_CNT 30
#define MAX_LINE_LENGTH 100
#define MAX_TRADES 1024

/*
����ü �����Դϴ�.
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

typedef struct  // �ܰ��ֽĵ����� ȸ����ȣ/�����ڵ�/�����ֽļ�
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
���� �Լ��� ���� �Լ� �����Դϴ�.
*/
void checkStringLength(char *msg, char *string, int size);
void num_check(char *msg, int max, int min, int *f_addr);



/*
auth.c ���Ͽ� ���� �Լ� �����Դϴ�.
*/

void auth(USER *userP);
void login(USER *userP);
void signup(USER *userP);
void logout(USER *userP);
void loadList(USER **user, USER **head, USER **tail);

void print_function(StockInfo *structptr);

void tradesearch();
void readTrades(char *filename, struct Trade *trades, int *numTrades);
void searchTrades(int searchType, struct Trade *trades, int numTrades);

void savestockholdlst(Stock* entire_usr_stock);