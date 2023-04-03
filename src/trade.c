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
		printf("�Ÿ� ������ �������ּ���. ( 1 : �ż� , 2 : �ŵ�, 3 : ���� �ֽ��ܰ� ���, -1 : main�Լ��� ����) \n => ");
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
			printf("���� %s ���� �����ϰ� ��� �ֽ� �ܰ�� ������ �����ϴ�.\n ");
			strtok(stock_hold_lst, " \t");  //u_id ������
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
			printf("�߸��� �Ÿ� �����Դϴ�. �ٽ� �������ּ��� \n");
	}
}

// �ֽ� �ż� �Լ�
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
		printf("�ż��� ������ �����ȣ�� �Է��Ͻÿ�. ( -1 : main�Լ��� ����)  : ");
		gets(buy_stock_num);

		if (atoi(buy_stock_num) == -1)
			return;
		else 		// ��ü �ֽ� ����Ʈ �ֽĹ�ȣ�� ��
		{
			for (i = 0; i < STOCK_ALL_CNT; i++)
			{
				if (strcmp(buy_stock_num, stock_lst[i]) == 0)
				{
					printf(" �ż������� �ݾ��� %d���Դϴ�. \n", login_usr->balance);

					printf("�ż��� ������ �Է����ּ���. ( �ٸ� �ֽ��� �ŷ��ϰ� ���� ��� ������ 0�� �Է����ּ���. )  : ");
					scanf("%d", &buy_stock_cnt);
					printf("�ż������� %d�� �Է��ϼ̽��ϴ�. \n", buy_stock_cnt);
					{
						if (buy_stock_cnt == 0)
						{
							gets(buy_stock_num);
							break;
						}
					}

					market_price = trade_price_determine(buy_stock_num);
					printf("���� ���� ������ %d�Դϴ�. \n", market_price);
					printf("�ż��� ����ϴ� �ݾ��� �Է����ּ���. ( �ٸ� �ֽ��� �ŷ��ϰ� ���� ��� ������ 0�� �Է����ּ���. )  : ");
					scanf("%d%*c", &buy_stock_price);
					printf("�ż�����ݾ׿� %d�� �Է��ϼ̽��ϴ�. \n", buy_stock_price);
					{
						if (buy_stock_price < market_price)
						{
							printf("���尡���� �ż��ݾ��� ���� �ŷ��� �̷������ �ʾҽ��ϴ�. \n");
							i--;
							continue;
						}
					}

					buy_money_sum = buy_stock_cnt * buy_stock_price;

					if (buy_money_sum < login_usr->balance)
					{
						login_usr->balance -= buy_money_sum;
						buy_flag = 0;

						// �ܰ� ������Ʈ �Լ� �ۼ�
						update_stock_usr(login_usr->userNo, buy_stock_num, buy_stock_cnt, 1);

						// ���±ݾ� ������Ʈ �Լ� 
						update_balance(login_usr->userNo, buy_money_sum, 1);

						// �Ÿų��� �߰� �Լ�
						add_trade_data(login_usr->userNo, buy_stock_num, str_date_generate(date), buy_stock_cnt, buy_stock_price, 1);

						buy_flag = 0;
						printf("�ŷ��� �Ϸ�Ǿ����ϴ�. \n");
						break;
					}
					else
					{
						printf(" ���� �ܾ��� �����մϴ�. ������ �ݾ��� �ٽ� �Է����ּ��� \n ");
						i--;
					}
				}
				if (i == (STOCK_ALL_CNT))
					printf("�߸��� �����ȣ�Դϴ�. �ٽ� �Է����ּ��� \n");
			} // for end
		}// else end
	}//while end
}

// �ֽ� �ŵ� �Լ�
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
		printf("�ŵ��� ������ �����ȣ�� �Է��Ͻÿ�. ( -1 : main�Լ��� ����)");
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


						printf("�ش� �ֽ��� ���簡���� %d�Դϴ�.\n ���� %sȸ������ �ش� �ֽ��� %d�� �����ϰ� �ֽ��ϴ�.\n", market_price,login_usr->name,  token_hold_stock_cnt);
						printf(" �Ǹ��� ������ �ݾ��� �Է����ּ��� : \n\t=>  ");
						scanf("%d %d", &sell_stock_cnt, &sell_stock_price);

						if (sell_stock_cnt > token_hold_stock_cnt)
							printf("������ �ֽ� ������ �����մϴ�. \n");
						else if (sell_stock_price > market_price)
							printf("���尡���� �ŵ��ݾ��� ����, �ش� �ݾ����� �ŵ��� �̷������ �ʾҽ��ϴ�. \n");
						else
							break;
					}

					// �ܰ� ������Ʈ 
					update_stock_usr(login_usr->userNo, sell_stock_num, sell_stock_cnt, 2);

					// ���±ݾ� ������Ʈ
					update_balance(login_usr->userNo, sell_stock_cnt * sell_stock_price, 2);

					// �Ÿŵ����� �߰�
					add_trade_data(login_usr->userNo, sell_stock_num, str_date_generate(date), sell_stock_cnt, sell_stock_price, 2);

					sell_flag = 0;
					break;

				}// �ֽĹ�ȣ ��
			} // for() end
			if (flag_stock_match == 0)
				printf("�ش� �ֽ��� �����ϰ� ���� �ʽ��ϴ�.\n");
		} // else() end
	}//while (sell_flag) end
}//sell_stock() end

// ȸ�� ���� �ݾ� ����
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

	// ��Ʈ�� ����
	fp_user_before_update = fopen("data/user.txt", "rt");
	if (fp_user_before_update == NULL)
	{
		perror("error :");
		exit(1);
	}

	// ���� �а�, �ش� ȸ���� �ش�Ǵ� �κи� �о ���� �� ���ο� txt���� �����
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

	//��Ʈ�� ����
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

	// ��Ʈ�� �ݱ�
	fclose(fp_user_after_update);
}

// ȸ�� �ܰ� ����
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

	// ��Ʈ�� ����
	fp_before_update_usr_stock = fopen("data/stock.txt", "rt");
	if (fp_before_update_usr_stock == NULL)
	{
		perror("error :");
		exit(1);
	}

	// ������ �б� �� ����
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

	//��Ʈ�� �ݱ�
	fclose(fp_before_update_usr_stock);

	// ��Ʈ�� ����
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

//�Ÿŵ����� ���Ͽ� �����̱�
void add_trade_data(int u_id, char* trade_stock_num, char* date, int trade_stock_cnt, int trade_stock_price, int trade_type)
{
	FILE* fp_trade;

	char trade_line[200];

	sprintf(trade_line, "\n%d\t%s\t%s\t%d\t%d\t%d", u_id, trade_stock_num, date, trade_stock_cnt, trade_stock_price, trade_type);

	//��Ʈ�� ����
	fp_trade = fopen("data/tradelist.txt", "at");
	if (fp_trade == NULL)
	{
		perror("error :");
		exit(1);
	}
	// ���� �����̱�
	fputs(trade_line, fp_trade);

	// ��Ʈ�� �ݱ�
	fclose(fp_trade);
}

// �ŸŰ��� ����
int trade_price_determine(char* stock_num)
{
	FILE* fp_stock;
	char tmp[200], * token;
	int market_price;

	// ��Ʈ�� ����
	fp_stock = fopen("data/output.txt", "rt");
	if (fp_stock == NULL)
	{
		perror("error :");
		exit(1);
	}

	// ������ �б�
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

// ��¥ ���ڿ� ���� �Լ�
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

// ���� ���� �ֽ� ����Ʈ ���
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

	// ������ �б� �� ����
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

	//��Ʈ�� �ݱ�
	fclose(fp_stock_hold);
}