#include "../hdr/generic.h"
#include "../hdr/built_in_library.h"

void trade(USER* login_usr, Stock* entire_user_stock, StockInfo* entire_stock_info);
void buy_stock(USER* login_usr, Stock* entire_usr_stock, char(*stock_lst)[50]);
void sell_stock(USER* login_usr, Stock* entire_usr_stock, Stock* login_usr_stock, StockInfo* entire_stock_info);
void update_stock_usr(int u_id, Stock* entire_usr_stock, char* stock_num, int stock_cnt, int trade_type);
void update_balance(USER* login_usr, int money, int trade_type);
void add_trade_data(int u_id, char* trade_stock_num, char* date, int trade_stock_cnt, int trade_stock_price, int trade_type);
char* str_date_generate(char* date_var);
void user_stock_hold_lst(USER* user, Stock* entire_user_stock, Stock* login_user_stock);
void entire_stock_lst(StockInfo* entire_stock_info, char* stock_lst[50]);


void trade(USER* login_usr, Stock* entire_user_stock, StockInfo* entire_stock_info)
{
	Stock login_usr_stock[100];
	char stock_lst[STOCK_ALL_CNT+5][50] ;
	entire_stock_lst(entire_stock_info, stock_lst);

	int flag_type = 1;
	char tmp[50];
	int type;
	int i = 0;

	user_stock_hold_lst(login_usr, entire_user_stock, login_usr_stock);
	system("cls");

	while (flag_type)
	{
		printf("\n\n=================================================\n");
		printf("매매 유형을 선택해주세요. \n( 1 : 매수 , 2 : 매도, 3 : 현재 주식잔고 출력, -1 : main함수로 복귀)\n");
		printf("=================================================\n\n");
		printf("매매 유형 선택 :     ");
		scanf("%d%*c", &type);
		if (type == -1)
			return;
		else if (type == 1)
		{
			buy_stock(login_usr, entire_user_stock, entire_stock_info, stock_lst);
			flag_type = 0;
		}
		else if (type == 2)
		{
			sell_stock(login_usr, entire_user_stock, login_usr_stock, entire_stock_info);
			flag_type = 0;
		}
		else if (type == 3)
		{
			system("cls");
			printf("현재 %s 님이 보유하고 계신 주식 잔고는 다음과 같습니다.\n\n", login_usr->name);
			printf("종목번호\t보유수량");
			printf("\n=====================================\n");
			while (login_usr_stock[i].member_num)
			{
				printf("%s\t\t\t%d", login_usr_stock[i].code, login_usr_stock[i].quantity);
				i++;
				printf("\n");
			}
			printf("\n=====================================\n");
		}
		else
			printf("잘못된 매매 유형입니다. 다시 선택해주세요 \n");
	}
}

// 주식 매수 함수
void buy_stock(USER* login_usr, Stock* entire_usr_stock, StockInfo* entire_stock_info, char(*stock_lst)[50])
{
	int buy_stock_cnt;
	int buy_money_sum;
	int buy_stock_price;
	int market_price;
	int i;
	int buy_flag = 1;
	int stock_entire_cnt;
	char buy_stock_num[50];
	char date[12];

	while (buy_flag)
	{
		system("cls");
		printf("전체 주식 종목 리스트\n");
		printf("\n=========================================\n");
		printf("종목이름(종목번호)");
		printf("\n-----------------------------------------\n");
		i = 0;
		stock_entire_cnt = 0;
		while (stock_entire_cnt < STOCK_ALL_CNT)
		{
			if (strcmp(stock_lst[stock_entire_cnt], entire_stock_info[i].stock_code) == 0)
			{
				printf("%s(%s)\n", stock_lst[stock_entire_cnt], entire_stock_info[i].stock_name);
				stock_entire_cnt++;
			}
			i++;
		}
		printf("\n-----------------------------------------\n\n");
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
					system("cls");
					printf("\n\n=====================================\n");
					printf("%s 님의 현재 매수가능한 금액은 %d원입니다. \n\n", login_usr->name, login_usr->balance);

					printf("매수할 수량을 입력해주세요. ( 다른 주식을 거래하고 싶은 경우 수량에 0을 입력해주세요. )  : ");
					scanf("%d%*c", &buy_stock_cnt);
					{
						if (buy_stock_cnt == 0)
						{
							break;
						}
					}

					market_price = trade_price_determine(buy_stock_num);
					printf("현재 시장 가격은 %d입니다. \n", market_price);
					printf("매수를 희망하는 금액을 입력해주세요.  : ");
					scanf("%d%*c", &buy_stock_price);
					{
						if (buy_stock_price < market_price)
						{
							system("cls");
							printf("\n\n\n\n\=====================================\n");
							printf("시장가보다 매수금액이 낮아 거래가 이루어지지 않았습니다. \n");
							printf("===================================== \n");
							Sleep(1500);							
							i--;
							continue;
						}
					}

					buy_money_sum = buy_stock_cnt * buy_stock_price;

					if (buy_money_sum < login_usr->balance)
					{
						buy_flag = 0;

						// 잔고 업데이트 함수 작성
						update_stock_usr(login_usr->userNo, entire_usr_stock, buy_stock_num, buy_stock_cnt, 1);

						// 계좌금액 업데이트 함수 
						update_balance(login_usr, buy_money_sum, 1);

						// 매매내역 추가 함수
						add_trade_data(login_usr->userNo, buy_stock_num, str_date_generate(date), buy_stock_cnt, buy_stock_price, 1);

						buy_flag = 0;
						system("cls");
						printf("\n\n\n\n=====================================\n");
						printf("%s 님의 매수가 완료되었습니다. \n", login_usr->name);
						printf("=====================================\n\n");
						Sleep(1500);
						system("cls");
						break;
					}
					else
					{
						system("cls");
						printf("\n\n\n\n\=====================================\n");
						printf(" 계좌 잔액이 부족하여 매수가 이루어지지 않았습니다. 수량과 금액을 다시 입력해주세요 \n ");
						printf("===================================== \n");
						Sleep(1500);						
						i--;
					}
				}
				if (i == (STOCK_ALL_CNT - 1))
				{
					system("cls");
					printf("\n\n\n\n\=====================================\n");
					printf("잘못된 종목번호입니다. 다시 입력해주세요 \n");
					printf("===================================== \n");
					Sleep(1500);
				}
			} // for end
		}// else end
	}//while end
}

// 주식 매도 함수
void sell_stock(USER* login_usr, Stock* entire_usr_stock, Stock* login_usr_stock, StockInfo* entire_stock_info)
{
	int usr_stock_hold_cnt, usr_stock_class_cnt, sell_stock_cnt, sell_stock_price, sell_flag = 1, flag_stock_match = 0;
	int market_price;
	int token_hold_stock_cnt;
	char usr_stock_list[30][50], sell_stock_num[50], date[20] = "";
	char* token_hold_stock_num;
	char tmp[50];
	char** hold_stock_user;
	int i;
	int j;
	int cnt;
	int stock_entire_cnt;
	int sell_money_sum;

	while (sell_flag)
	{
		system("cls");
		printf("현재 %s 님이 보유하고 계신 주식 잔고는 다음과 같습니다.\n\n", login_usr->name);
		printf("종목번호\t보유수량");
		printf("\n=====================================\n");
		i = 0;
		cnt = 0;
		//while (login_usr_stock[i].member_num)
		//{
		//	printf("%s\t\t\t%d", login_usr_stock[i].code, login_usr_stock[i].quantity);
		//	i++;
		//	cnt++;
		//	printf("\n");
		//}
		//printf("\n=====================================\n\n\n\n");

		while (login_usr_stock[i].member_num)
		{
			j = 0;
			while (entire_stock_info[j].open)
			{
				if (strcmp(login_usr_stock[i].code, entire_stock_info[j].stock_code) == 0)
				{
					printf("%s(%s)\t\t\t%d\n", entire_stock_info[j].stock_name, login_usr_stock[i].code, login_usr_stock[i].quantity);
					break;
				}
				j++;
			}
			i++;
		}



		printf("매도할 종목의 종목번호를 입력하시오. ( -1 : main함수로 복귀) : ");
		gets(sell_stock_num);

		if (atoi(sell_stock_num) == -1)
			return;
		else
		{
			for (i = 0; i < cnt; i++)
			{
				if (strcmp(login_usr_stock[i].code, sell_stock_num) == 0)
				{
					flag_stock_match = 1;
					market_price = trade_price_determine(sell_stock_num);
					while (1)
					{
						system("cls");
						printf("해당 주식의 현재가격은 %d입니다.\n 현재 %s 님은 해당 주식을 %d주 보유하고 있습니다.\n", market_price, login_usr->name, login_usr_stock[i].quantity);
						printf("판매할 수량을 입력해주세요 : \t");
						scanf("%d%*c", &sell_stock_cnt);
						printf("판매할 금액을 입력해주세요 : \t");
						scanf("%d%*c", &sell_stock_price);
						if (sell_stock_cnt > login_usr_stock[i].quantity)
						{
							system("cls");
							printf("\n\n\n\n\=====================================\n");
							printf("보유한 주식 수량이 부족하여 매도가 이루어지지 않았습니다. \n");
							printf("===================================== \n");
							Sleep(1500);
						}
						else if (sell_stock_price > market_price)
						{
							system("cls");
							printf("\n\n\n\n\=====================================\n");
							printf("시장가보다 매도금액이 높아, 해당 금액으로 매도가 이루어지지 않았습니다. \n");
							printf("===================================== \n");
							Sleep(1500);
						}
						else
							break;
					}
					sell_money_sum = sell_stock_cnt * sell_stock_price;

					// 잔고 업데이트 
					update_stock_usr(login_usr->userNo, entire_usr_stock, sell_stock_num, sell_stock_cnt, 2);

					// 계좌금액 업데이트
					update_balance(login_usr, sell_money_sum, 2);

					// 매매데이터 추가
					add_trade_data(login_usr->userNo, sell_stock_num, str_date_generate(date), sell_stock_cnt, sell_stock_price, 2);

					sell_flag = 0;

					system("cls");
					printf("\n\n\n\n=====================================\n");
					printf("%s 님의 매도가 완료되었습니다. \n", login_usr->name);
					printf("=====================================\n\n");
					Sleep(1500);

					break;

				}// 주식번호 비교
			} // for() end
			if (flag_stock_match == 0)
			{
				system("cls");
				printf("\n\n\n\n\=====================================\n");
				printf("해당 주식을 보유하고 있지 않습니다.\n");
				printf("===================================== \n");
				Sleep(1500);
			}
		} // else() end
	}//while (sell_flag) end
}//sell_stock() end

// 회원 계좌 금액 변경
void update_balance(USER* login_usr, int money, int trade_type)
{
	printf("매매 전 금액 : %d\n", login_usr->balance);
	if (trade_type == 1)
		(login_usr->balance) -= money;
	else if (trade_type == 2)
		(login_usr->balance) += money;
	printf("매매 후 금액 : %d\n", login_usr->balance);
}

// 회원 잔고 변경
void update_stock_usr(int u_id, Stock* entire_usr_stock, char* stock_num, int stock_cnt, int trade_type)
{
	char tmp[200], tmp_txt[200][200], * token_stock_num, txt_line[200];
	int token_id;
	int token_stock_cnt;
	int flag_unhold = 1;
	int txt_idx = 0;
	int i = 0;

	for (i = 0; entire_usr_stock[i].member_num; i++)
	{
		if (entire_usr_stock[i].member_num == u_id && strcmp(entire_usr_stock[i].code, stock_num) == 0)
		{
			if (trade_type == 1)
				entire_usr_stock[i].quantity += stock_cnt;
			else if (trade_type == 2)
				entire_usr_stock[i].quantity -= stock_cnt;
			flag_unhold = 0;
		}
	}

	if (flag_unhold)
	{
		entire_usr_stock[i].member_num = u_id;
		strcpy(entire_usr_stock[i].code, stock_num);
		entire_usr_stock[i].quantity = stock_cnt;
	}

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

	market_price += (random_percent / 100) * market_price * (random_status);

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
void user_stock_hold_lst(USER* user, Stock* entire_user_stock, Stock* login_user_stock)
{
	int i = 0;
	int u_id;
	int login_user_stock_cnt = 0;
	u_id = user->userNo;

	while (entire_user_stock[i].member_num)
	{
		if (entire_user_stock[i].member_num == u_id)
		{
			login_user_stock[login_user_stock_cnt].member_num = u_id;
			strcpy(login_user_stock[login_user_stock_cnt].code, entire_user_stock[i].code);
			login_user_stock[login_user_stock_cnt].quantity = entire_user_stock[i].quantity;
			login_user_stock_cnt++;
		}
		i++;
	}
	login_user_stock[login_user_stock_cnt].member_num = 0;
}

// 주식 전체 목록 리스트 출력
void entire_stock_lst(StockInfo* entire_stock_info, char(*stock_lst)[50])
{
	int i = 0;
	int cnt = 0;

	while (cnt < STOCK_ALL_CNT)
	{
		if (strcmp(entire_stock_info[i].date, entire_stock_info[0].date) == 0)
		{
			memmove(stock_lst[cnt], entire_stock_info[i].stock_code, sizeof(entire_stock_info[i].stock_code));
			cnt += 1;
		}
		i++;
	}
	*stock_lst[cnt] = '\0';

	return;
}