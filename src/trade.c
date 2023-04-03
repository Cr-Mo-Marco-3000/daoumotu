#include "../hdr/generic.h"
#include "../hdr/built_in_library.h"

void trade(USER* login_usr, STOCK_USER* stock_usr, char(*stock_lst)[50]);
void buy_stock(USER* login_usr, STOCK_USER* stock_usr, char(*stock_lst)[50]);
void sell_stock(USER* login_usr, STOCK_USER* stock_usr);
void update_stock_usr(char* u_id, char* stock_num, int stock_cnt, int trade_type);
void update_balance(char* u_id, int money, int type);
void add_trade_date(char* u_id, char* trade_stock_num, char* date, int trade_stock_cnt, int trade_stock_price, int trade_type);


void trade(USER* login_usr, STOCK_USER* stock_usr, char (*stock_lst)[50] )
{
	int flag_type = 1;
	int type;

	while (flag_type)
	{
		printf("\n ================================================= \n");
		printf("매매 유형을 선택해주세요. ( 1 : 매수 , 2 : 매도, -1 : main함수로 복귀) \n =>");
		scanf("%d", &type);
		if (type == -1)
			return;
		else if (type == 1)
		{
			buy_stock(login_usr, stock_usr, stock_lst);
			flag_type = 0;
		}
		else if (type == 2)
		{
			sell_stock(login_usr, stock_usr);
			flag_type = 0;
		}
		else
			printf("잘못된 매매 유형입니다. 다시 선택해주세요");
	}
}

// 주식 매수 함수
void buy_stock(USER* login_usr, STOCK_USER* stock_usr, char(*stock_lst)[50])
{
	int buy_stock_cnt;
	int buy_money_sum;
	int buy_stock_price;
	int i;
	int buy_flag = 1;
	char buy_stock_num[50];

	while (buy_flag)
	{
		printf("매수할 종목의 종목번호를 입력하시오. ( -1 : main함수로 복귀)");
		scanf("%s", buy_stock_num);

		if (atoi(buy_stock_num) == -1)
			return;
		else 		// 전체 주식 리스트 주식번호와 비교
		{
			for (i = 0; i< STOCK_ALL_CNT; i++)
			{
				if (strcmp(buy_stock_num, stock_lst[i]) == 0)
				{

					printf("매수할 수량과 금액을 입력해주세요. ( 다른 주식을 거래하고 싶은 경우 수량에 0을 입력해주세요. )  : ");
					scanf("%d, %d", &buy_stock_cnt, &buy_stock_price);
					{
						if (buy_stock_cnt == 0)
							break;
					}
					buy_money_sum = buy_stock_cnt * buy_stock_price;

					if (buy_stock_price < trade_price_determine(buy_stock_num))
					{
						printf("시장가보다 매수금액이 낮아 거래가 이루어지지 않았습니다.");
						i--;
						continue;
					}

					if (buy_money_sum < login_usr->balance)
					{
						login_usr->balance -= buy_money_sum;
						buy_flag = 0;

						// 잔고 업데이트 함수 작성
						update_stock_usr(login_usr->userNo, buy_stock_num, buy_stock_cnt, 1);

						// 계좌금액 업데이트 함수 
						update_balance(login_usr->userNo, buy_money_sum, 1);

						buy_flag = 0;
						printf("거래가 완료되었습니다.");
						break;
					}
					else
					{
						printf(" 계좌 잔액이 부족합니다. 수량과 금액을 다시 입력해주세요 ");
						i--;
					}
				}

				if (i == (STOCK_ALL_CNT-1))
					printf("잘못된 종목번호입니다. 다시 입력해주세요");
			}
		}
	}
}

// 주식 매도 함수
void sell_stock(USER* login_usr, STOCK_USER* stock_usr)
{
	int usr_stock_hold_cnt, usr_stock_cnt, sell_stock_cnt, sell_stock_price, sell_flag = 1;
	char usr_stock_list[30][50], sell_stock_num[50];

	while (sell_flag)
	{
		printf("매도할 종목의 종목번호를 입력하시오. ( -1 : main함수로 복귀)");
		scanf("%s", sell_stock_num);

		if (atoi(sell_stock_num) == -1)
			return;
		else
		{
			usr_stock_cnt = sizeof(*stock_usr) / sizeof(STOCK_USER);

			for (int i = 0; i < usr_stock_cnt; i++)
			{
				if (strcmp(stock_usr->stock_id, sell_stock_num) == 0)
				{
					usr_stock_cnt = stock_usr->stock_cnt;
					while (1)
					{
						printf(" 판매할 수량과 금액을 입력해주세요 : ");
						scanf("%d %d", &sell_stock_cnt, &sell_stock_price);

						if (sell_stock_cnt > usr_stock_hold_cnt)
							printf("판매할 수량이 부족합니다. 수량을 다시 입력해주세요 :");
						else if (sell_stock_price > trade_price_determine(sell_stock_num))
							printf("시장가보다 매도금액이 높아, 해당 금액으로 매도가 이루어지지 않았습니다.");
						else
							break;
					}

					// 잔고 업데이트 
					update_stock_usr(login_usr->userNo, sell_stock_num, sell_stock_cnt, 2);

					// 계좌금액 업데이트
					update_balance(login_usr->userNo, sell_stock_cnt * sell_stock_price, 2);

					sell_flag = 0;
					break;
				}
				else
					stock_usr++;
			}
		}
	}
}


// 회원 계좌 금액 변경
void update_balance(char* u_id, int money, int trade_type)
{
	FILE* fp_user_before_update;
	FILE* fp_user_after_update;



	int balance;
	char tmp[200], * token, * balance_str, * txt_line;
	char* id, * pw, * name;

	// 스트림 열기
	fp_user_before_update = fopen("data/user.txt", "rt");
	if (fp_user_before_update == NULL)
	{
		perror("error :");
		exit(1);
	}
	fp_user_after_update = fopen("data/user.txt", "wt");
	if (fp_user_after_update == NULL)
	{
		perror("error :");
		exit(1);
	}

	// 파일 읽고, 해당 회원에 해당되는 부분만 읽어서 수정 후 새로운 txt파일 만들기
	while (fp_user_before_update)
	{
		fgets(tmp, 200, fp_user_before_update);
		token = strtok(tmp, " \t");
		if (strcmp(token, u_id) == 0)
		{
			id = strtok(NULL, " \t");
			pw = strtok(NULL, " \t");
			name = strtok(NULL, " \t");
			balance = atoi(strtok(NULL, " \t"));
			if (trade_type == 1)
				balance -= money;
			else if (trade_type == 2)
				balance += money;
			sprintf(txt_line, "%s\t%s\t%s\t%s\t%d", token, id, pw, name, balance);
		}
		fputs(tmp, fp_user_after_update);
	}
	// 스트림 닫기
	fclose(fp_user_before_update);
	fclose(fp_user_after_update);
}


// 회원 잔고 변경
void update_stock_usr(char* u_id, char* stock_num, int stock_cnt, int trade_type)
{
	FILE* fp_before_update_usr_stock;
	FILE* fp_after_update_usr_stock;

	char tmp[200], * token_id, * token_stock_num, * token_stock_cnt, * txt_line;
	int stock_hold_cnt;

	// 스트림 열기
	fp_before_update_usr_stock = fopen("data/stock_2.txt", "rt");
	if (fp_before_update_usr_stock == NULL)
	{
		perror("error :");
		exit(1);
	}
	if (fp_after_update_usr_stock == NULL)
	{
		perror("error :");
		exit(1);
	}
	fp_after_update_usr_stock = fopen("data.stock_2.txt", "wt");


	// 데이터 읽기 및 수정
	while (fp_before_update_usr_stock)
	{
		fgets(tmp, 200, fp_before_update_usr_stock);
		token_id = strtok(tmp, " \t");
		if (strcmp(u_id, token_id) == 0)
		{
			token_stock_num = strtok(NULL, " \t");
			if (strcmp(token_stock_num, stock_num) == 0)
			{
				token_stock_cnt = strtok(NULL, " \t");
				stock_hold_cnt = atoi(token_stock_cnt);
				{
					if (trade_type == 1)
						stock_hold_cnt += stock_cnt;
					else if (trade_type == 2)
						stock_hold_cnt -= stock_cnt;
				}
				sprintf(txt_line, "%s\t%d\t%d", u_id, stock_num, stock_hold_cnt);
			}
			else
				sprintf(txt_line, "%s\t%d\t%d", u_id, stock_num, stock_cnt);
			fputs(txt_line, fp_after_update_usr_stock);
		}
		else
		{
			sprintf(txt_line, "%s\t%d\t%d", u_id, stock_num, stock_cnt);
		}
		fputs(tmp, fp_after_update_usr_stock);
	}

	//스트림 닫기
	fclose(fp_before_update_usr_stock);
	fclose(fp_after_update_usr_stock);

}

//매매데이터 파일에 덧붙이기
void add_trade_date(char* u_id, char* trade_stock_num, char* date, int trade_stock_cnt, int trade_stock_price, int trade_type)
{
	FILE* fp_trade;

	char* trade_line;

	sprintf(trade_line, "%s\t%s\t%s\t%d\t%d\t%d", u_id, trade_stock_num, date, trade_stock_cnt, trade_stock_price, trade_type);

	//스트림 열기
	fp_trade = fopen("data/매매데이터_최종.txt", "at");
	if (fp_trade == NULL)
	{
		perror("error :");
		exit(1);
	}

	// 파일 덧붙이기
	fputs(trade_line, fp_trade);

	// 스트림 닫기
	fclose(fp_trade);
}

// 매매가격 결정
int trade_price_determine(char* stock_num)
{
	FILE* fp_stock;
	char tmp[100], *token;
	int price;

	// 스트림 열기
	fp_stock = fopen("data/output_tab.txt", "rt");
	if (fp_stock == NULL)
	{
		perror("error :");
		exit(1);
	}

	// 데이터 읽기
	while (fgets(tmp, 100, fp_stock))
	{
		fgets(tmp, 100, fp_stock);
		token = strtok(tmp, " \t");
		if (strcmp(token, stock_num) == 0)
		{
			strtok(NULL, " \t");
			strtok(NULL, " \t");
			price = strtok(NULL, " \t");
		}
	}

	srand(time(NULL));

	int random_percent = rand() % 31;
	int random_status = rand() % 2 ? 1 : -1;

	price += (100 - (random_percent) * (random_status)) * price;

	return price;
}