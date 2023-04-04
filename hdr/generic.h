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


/*
save_stock_hold_lst.c ���Ͽ� ���� �Լ� �����Դϴ�.
*/

void savestockholdlst(Stock* entire_usr_stock);


/*
trade.c ���Ͽ� ���� �Լ� �����Դϴ�.
*/

void trade(USER* login_usr, Stock* entire_user_stock, StockInfo* entire_stock_info);
void buy_stock(USER* login_usr, Stock* entire_usr_stock, StockInfo* entire_stock_info, char(*stock_lst)[50]);
void sell_stock(USER* login_usr, Stock* entire_usr_stock, Stock* login_usr_stock, StockInfo* entire_stock_info);
void update_balance(USER* login_usr, int money, int trade_type);
void update_stock_usr(int u_id, Stock* entire_usr_stock, char* stock_num, int stock_cnt, int trade_type);
void add_trade_data(int u_id, char* trade_stock_num, char* date, int trade_stock_cnt, int trade_stock_price, int trade_type);
int trade_price_determine(char* stock_num, StockInfo* entire_stock_info);
char* str_date_generate(char* date_var);
void user_stock_hold_lst(USER* user, Stock* entire_user_stock, Stock* login_user_stock);
void entire_stock_lst(StockInfo* entire_stock_info, char(*stock_lst)[50]);


/*
portfolio.c ���Ͽ� ���� �Լ� �����Դϴ�.
*/
void Print_st(USER* user);
void Print_bal(USER* user);
void cashplus(int* sum, USER* user);
void textcolor(int colorNum);
int portfolio(USER* user, Stock* stock, StockInfo* tmp);
void Print_st(Stock* stock, StockInfo* price, USER* user);
void Print_bal(Stock* stock, StockInfo* price, USER* user);
void cashplus(int* sum, USER* user);

/*
tradesearch.c ���Ͽ� ���� �Լ� �����Դϴ�.
*/
void tradesearch(USER* user);
void readTrades(char* filename, struct Trade* trades, int* numTrades, USER* user);
void searchTrades(int searchType, struct Trade* trades, int numTrades);
