#include "../hdr/generic.h"
#include "../hdr/built_in_library.h"

void trade(USER* login_usr, char(*stock_lst)[50]);
void buy_stock(USER* login_usr, char* stock_usr[], char(*stock_lst)[50]);
void sell_stock(USER* login_usr, char* stock_usr[]);
void update_stock_usr(int u_id, char* stock_num, int stock_cnt, int trade_type);
void update_balance(char* u_id, int money, int type);
void add_trade_data(char* u_id, char* trade_stock_num, char* date, int trade_stock_cnt, int trade_stock_price, int trade_type);
char* str_date_generate(char* date_var);
void user_stock_hold_lst(USER* user, char** stock_hold_lst);


void trade(USER* login_usr, char(*stock_lst)[50])
{
	int flag_type = 1;
	char tmp[50];
	int type;
	int i = 0;

	char* stock_hold_lst[100];
	user_stock_hold_lst(login_usr, stock_hold_lst);

	while (flag_type)
	{
		printf("\n================================================= \n");
		printf("매매 유형을 선택해주세요. ( 1 : 매수 , 2 : 매도, 3 : 현재 주식잔고 출력, -1 : main함수로 복귀) \n => ");
		gets(tmp);
		type = atoi(tmp);
		if (type == -1)
			return;
		else if (type == 1)
		{
			buy_stock(login_usr, stock_hold_lst, stock_lst);
			flag_type = 0;
		}
		else if (type == 2)
		{
			sell_stock(login_usr, stock_hold_lst);
			flag_type = 0;
		}
		else if (type == 3)
		{
			printf("현재 %s 님이 보유하고 계신 주식 잔고는 다음과 같습니다.\n ");
			strtok(stock_hold_lst, " \t");  //u_id 버리기
			printf("%s\t%s\t%s", login_usr->name, strtok(NULL, " \t"), strtok(NULL, " \t"));
			printf("\n=====================================\n");
			while (stock_hold_lst[i])
			{
				printf("%s\n", stock_hold_lst[i]);
				i++;
			}
			printf("\n=====================================\n");
		}
		else
			printf("잘못된 매매 유형입니다. 다시 선택해주세요 \n");
	}
}

// 주식 매수 함수
void buy_stock(USER* login_usr, char* stock_usr[], char(*stock_lst)[50])
{
	int buy_stock_cnt;
	int buy_money_sum;
	int buy_stock_price;
	int market_price;
	int i;
	int buy_flag = 1;
	char buy_stock_num[50];
	char date[12];

	while (buy_flag)
	{
		printf("매수할 종목의 종목번호를 입력하시오. ( -1 : main함수로 복귀)  : ");
		gets(buy_stock_num);

		if (atoi(buy_stock_num) == -1)
			return;
		else 		// 전체 주식 리스트 주식번호와 비교
		{
			for (i = 0; i < STOCK_ALL_CNT; i++)
			{
				if (strcmp(buy_stock_num, stock_lst[i]) == 0)
				{
					printf(" 매수가능한 금액은 %d원입니다. \n", login_usr->balance);

					printf("매수할 수량을 입력해주세요. ( 다른 주식을 거래하고 싶은 경우 수량에 0을 입력해주세요. )  : ");
					scanf("%d", &buy_stock_cnt);
					printf("매수수량에 %d을 입력하셨습니다. \n", buy_stock_cnt);
					{
						if (buy_stock_cnt == 0)
						{
							gets(buy_stock_num);
							break;
						}
					}

					market_price = trade_price_determine(buy_stock_num);
					printf("현재 시장 가격은 %d입니다. \n", market_price);
					printf("매수를 희망하는 금액을 입력해주세요. ( 다른 주식을 거래하고 싶은 경우 수량에 0을 입력해주세요. )  : ");
					scanf("%d%*c", &buy_stock_price);
					printf("매수희망금액에 %d을 입력하셨습니다. \n", buy_stock_price);
					{
						if (buy_stock_price < market_price)
						{
							printf("시장가보다 매수금액이 낮아 거래가 이루어지지 않았습니다. \n");
							i--;
							continue;
						}
					}

					buy_money_sum = buy_stock_cnt * buy_stock_price;

					if (buy_money_sum < login_usr->balance)
					{
						login_usr->balance -= buy_money_sum;
						buy_flag = 0;

						// 잔고 업데이트 함수 작성
						update_stock_usr(login_usr->userNo, buy_stock_num, buy_stock_cnt, 1);

						// 계좌금액 업데이트 함수 
						update_balance(login_usr->userNo, buy_money_sum, 1);

						// 매매내역 추가 함수
						add_trade_data(login_usr->userNo, buy_stock_num, str_date_generate(date), buy_stock_cnt, buy_stock_price, 1);

						buy_flag = 0;
						printf("거래가 완료되었습니다. \n");
						break;
					}
					else
					{
						printf(" 계좌 잔액이 부족합니다. 수량과 금액을 다시 입력해주세요 \n ");
						i--;
					}
				}
				if (i == (STOCK_ALL_CNT))
					printf("잘못된 종목번호입니다. 다시 입력해주세요 \n");
			} // for end
		}// else end
	}//while end
}

// 주식 매도 함수
void sell_stock(USER* login_usr, char** stock_user)
{
	int usr_stock_hold_cnt, usr_stock_class_cnt, sell_stock_cnt, sell_stock_price, sell_flag = 1, flag_stock_match = 0;
	int market_price;
	char usr_stock_list[30][50], sell_stock_num[50], date[20] = "";
	char* token_hold_stock_num;
	char* token_hold_stock_cnt;
	char tmp[50];
	char** hold_stock_user;

	while (sell_flag)
	{
		printf("매도할 종목의 종목번호를 입력하시오. ( -1 : main함수로 복귀)");
		gets(sell_stock_num);

		if (atoi(sell_stock_num) == -1)
			return;
		else
		{
			hold_stock_user = stock_user;
			for (; *hold_stock_user; hold_stock_user++)
			{
				printf("%s\n", *hold_stock_user);
				strcpy(tmp, *hold_stock_user);
				strtok(tmp, " \t");
				token_hold_stock_num = strtok(NULL, " \t");
				token_hold_stock_cnt = atoi(strtok(NULL, " \t"));

				if (strcmp(token_hold_stock_num, sell_stock_num) == 0)
				{
					flag_stock_match = 1;
					while (1)
					{
						market_price = trade_price_determine(sell_stock_num);


						printf("해당 주식의 현재가격은 %d입니다.\n 현재 %s회원님은 해당 주식을 %d주 보유하고 있습니다.\n", market_price,login_usr->name,  token_hold_stock_cnt);
						printf(" 판매할 수량과 금액을 입력해주세요 : \n\t=>  ");
						scanf("%d %d", &sell_stock_cnt, &sell_stock_price);

						if (sell_stock_cnt > token_hold_stock_cnt)
							printf("보유한 주식 수량이 부족합니다. \n");
						else if (sell_stock_price > market_price)
							printf("시장가보다 매도금액이 높아, 해당 금액으로 매도가 이루어지지 않았습니다. \n");
						else
							break;
					}

					// 잔고 업데이트 
					update_stock_usr(login_usr->userNo, sell_stock_num, sell_stock_cnt, 2);

					// 계좌금액 업데이트
					update_balance(login_usr->userNo, sell_stock_cnt * sell_stock_price, 2);

					// 매매데이터 추가
					add_trade_data(login_usr->userNo, sell_stock_num, str_date_generate(date), sell_stock_cnt, sell_stock_price, 2);

					sell_flag = 0;
					break;

				}// 주식번호 비교
			} // for() end
			if (flag_stock_match == 0)
				printf("해당 주식을 보유하고 있지 않습니다.\n");
		} // else() end
	}//while (sell_flag) end
}//sell_stock() end

// 회원 계좌 금액 변경
void update_balance(int* u_id, int money, int trade_type)
{
	FILE* fp_user_before_update;
	FILE* fp_user_after_update;

	int balance;
	int cnt_usr = 0;
	int token_uid;
	int token_balance;
	char* token_id, * token_pw, * token_name, tmp[50], tmp_user[200][50], txt_line[50];
	char* id, * pw, * name;

	// 스트림 열기
	fp_user_before_update = fopen("data/user.txt", "rt");
	if (fp_user_before_update == NULL)
	{
		perror("error :");
		exit(1);
	}

	// 파일 읽고, 해당 회원에 해당되는 부분만 읽어서 수정 후 새로운 txt파일 만들기
	while (fgets(tmp, 200, fp_user_before_update))
	{
		token_uid = atoi(strtok(tmp, " \t"));
		token_id = strtok(NULL, " \t");
		token_pw = strtok(NULL, " \t");
		token_name = strtok(NULL, " \t");
		token_balance = atoi(strtok(NULL, " \t"));
		if (token_uid == u_id)
		{
			if (trade_type == 1)
				token_balance -= money;
			else if (trade_type == 2)
				token_balance += money;
			sprintf(txt_line, "%d\t%s\t%s\t%s\t%d", token_uid, token_id, token_pw, token_name, token_balance);
		}
		else
		{
			sprintf(txt_line, "%d\t%s\t%s\t%s\t%d", token_uid, token_id, token_pw, token_name, token_balance);
		}
		strcpy(tmp_user[cnt_usr++], txt_line);
	}

	fclose(fp_user_before_update);

	//스트림 열기
	fp_user_after_update = fopen("data/user.txt", "wt");

	if (fp_user_after_update == NULL)
	{
		perror("error :");
		exit(1);
	}

	for (int i = 0; i < cnt_usr - 1; i++)
	{
		fputs(tmp_user[i], fp_user_after_update);
		fputs("\n", fp_user_after_update);
	}

	// 스트림 닫기
	fclose(fp_user_after_update);
}

// 회원 잔고 변경
void update_stock_usr(int u_id, char* stock_num, int stock_cnt, int trade_type)
{
	FILE* fp_before_update_usr_stock;
	FILE* fp_after_update_usr_stock;

	char tmp[200], tmp_txt[200][200], * token_stock_num, txt_line[200];
	int token_id;
	int token_stock_cnt;
	int flag_unhold = 1;
	int txt_idx = 0;
	int i = 0;

	// 스트림 열기
	fp_before_update_usr_stock = fopen("data/stock.txt", "rt");
	if (fp_before_update_usr_stock == NULL)
	{
		perror("error :");
		exit(1);
	}

	// 데이터 읽기 및 수정
	while (fgets(tmp, 200, fp_before_update_usr_stock))
	{
		token_id = atoi(strtok(tmp, " \t"));
		token_stock_num = strtok(NULL, " \t");
		token_stock_cnt = atoi(strtok(NULL, " \t"));

		if (u_id == token_id)
		{
			if (strcmp(token_stock_num, stock_num) == 0)
			{
				if (trade_type == 1)
					token_stock_cnt += stock_cnt;
				else if (trade_type == 2)
					token_stock_cnt -= stock_cnt;
				flag_unhold = 0;
				sprintf(txt_line, "%d\t%s\t%d", token_id, token_stock_num, token_stock_cnt);
			}
			else
				sprintf(txt_line, "%d\t%s\t%d", token_id, token_stock_num, token_stock_cnt);
		}
		else
			sprintf(txt_line, "%d\t%s\t%d", token_id, token_stock_num, token_stock_cnt);

		printf("%s\n", txt_line);
		strcpy(tmp_txt[txt_idx], txt_line);
		txt_idx++;
	}

	if (flag_unhold)
	{
		sprintf(txt_line, "%d\t%s\t%d", u_id, stock_num, stock_cnt);
		printf("%s\n", txt_line);
		strcpy(tmp_txt[txt_idx], txt_line);
		txt_idx++;
	}

	//스트림 닫기
	fclose(fp_before_update_usr_stock);

	// 스트림 열기
	fp_after_update_usr_stock = fopen("data/stock.txt", "wt");
	if (fp_after_update_usr_stock == NULL)
	{
		perror("error :");
		exit(1);
	}

	for (i = 0; i < txt_idx; i++)
	{
		fputs(tmp_txt[i], fp_after_update_usr_stock);
		fputs("\n", fp_after_update_usr_stock);
	}

	fclose(fp_after_update_usr_stock);
}

//매매데이터 파일에 덧붙이기
void add_trade_data(int u_id, char* trade_stock_num, char* date, int trade_stock_cnt, int trade_stock_price, int trade_type)
{
	FILE* fp_trade;

	char trade_line[200];

	sprintf(trade_line, "\n%d\t%s\t%s\t%d\t%d\t%d", u_id, trade_stock_num, date, trade_stock_cnt, trade_stock_price, trade_type);

	//스트림 열기
	fp_trade = fopen("data/tradelist.txt", "at");
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
	char tmp[200], * token;
	int market_price;

	// 스트림 열기
	fp_stock = fopen("data/output.txt", "rt");
	if (fp_stock == NULL)
	{
		perror("error :");
		exit(1);
	}

	// 데이터 읽기
	while (fgets(tmp, 200, fp_stock))
	{
		fgets(tmp, 100, fp_stock);
		token = strtok(tmp, " \t");
		if (strcmp(token, stock_num) == 0)
		{
			strtok(NULL, " \t");
			strtok(NULL, " \t");
			market_price = atoi(strtok(NULL, " \t"));
			break;
		}
	}

	srand(time(NULL));

	int random_percent = rand() % 31;
	int random_status = rand() % 2 ? 1 : -1;

	market_price += round(random_percent / 100) * market_price * (random_status);

	return market_price;
}

// 날짜 문자열 생성 함수
char* str_date_generate(char* date_var)
{
	time_t curr_t;
	struct tm* ptr;

	char month_s[3], day_s[3];
	int month, day;

	curr_t = time(NULL);
	ptr = localtime(&curr_t);

	month = ptr->tm_mon + 1;
	day = ptr->tm_mday;

	if (month < 10)
		sprintf(month_s, "%d%d", 0, month);
	else
		sprintf(month_s, "%d", month);

	if (day < 10)
		sprintf(day_s, "%d%d", 0, day);
	else
		sprintf(day_s, "%d", day);

	sprintf(date_var, "%d.%s.%s", ptr->tm_year + 1900, month_s, day_s);

	//if (strlen(date_var) >= sizeof(date_var)) 		// handle Debug error here
	//{
	//	return NULL;
	//} 

	return date_var;
}

// 유저 보유 주식 리스트 출력
void user_stock_hold_lst(USER* user, char** stock_hold_lst)
{
	FILE* fp_stock_hold;

	char tmp[100];
	char tmp_txt[100][100];
	char txt_line[100];
	char* token_id, * token_stock_num, * token_stock_cnt;
	int u_id;
	int hold_cnt = 0;
	fp_stock_hold = fopen("data/stock.txt", "rt");

	if (fp_stock_hold == NULL)
	{
		perror("error :");
		exit(1);
	}

	// 데이터 읽기 및 수정
	while (fgets(tmp, 200, fp_stock_hold))
	{
		token_id = atoi(strtok(tmp, " \t"));
		if (user->userNo == token_id)
		{
			token_stock_num = strtok(NULL, " \t");
			token_stock_cnt = atoi(strtok(NULL, " \t"));
			sprintf(txt_line, "%d\t%s\t%d", token_id, token_stock_num, token_stock_cnt);

			stock_hold_lst[hold_cnt] = (char*)malloc((strlen(txt_line) + 1) * sizeof(char));
			strcpy(stock_hold_lst[hold_cnt], txt_line);
			printf("%s\n", stock_hold_lst[hold_cnt]);
			hold_cnt++;
		}
	}

	stock_hold_lst[hold_cnt] = NULL;

	//스트림 닫기
	fclose(fp_stock_hold);
}