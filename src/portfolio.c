#include "../hdr/generic.h"
#include "../hdr/built_in_library.h"
#define MAX_LEN 20
void Print_st(USER* user);
void Print_bal(USER* user);
void cashplus(int* sum, USER* user);




void textcolor(int colorNum) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorNum);
}

int portfolio(USER* user)   // 가인수로 회원번호 받아온다. 포트폴리오 시작함수
{

	int id = user->userNo; // 가인수로 넣을 값

	printf("PORTFOLIO\n\n");
	printf("잔고를 표시합니다.\n");


	printf("=======================================================\n");
	printf("%d의 주식\n", user->userNo);

	StockInfo tmp[600] = { 0 };
	Stock stock[100] = { 0 };
	FILE* st, * pr;
	char trs[200];
	st = fopen("data/stock.txt", "rt");
	if (st == NULL) {
		perror("ERROR");
	}


	pr = fopen("data/output.txt", "rt");
	if (pr == NULL) {
		perror("ERROR");
	}
	
	fgets(trs, 200, pr);
	int i = 0;
	while (1)
	{
		int cn;
		cn = fscanf(pr, "%s %s %s %d %d %d %d %d %d", tmp[i].stock_code, // id와 일치하면 tmp 구조체에 일별 시세데이터를 입력
			tmp[i].stock_name, tmp[i].date, &tmp[i].open, &tmp[i].compare, &tmp[i].high, &tmp[i].low, &tmp[i].close, &tmp[i].volume);
		if (cn != 9)
			break;
		i++;
		}
	i = 0;
	while (1)
	{
		int cn;
		cn = fscanf(st, "%d %s %d", &stock[i].member_num, stock[i].code, &stock[i].quantity);
		if (cn != 3)
			break;

		i++;
	}


	
	Print_bal(user);
	Print_st(stock,tmp,user);

}


void Print_st(Stock* stock, StockInfo* price, USER* user) // 보유주식수 출력
{
	int i = 0;
	while (stock[i].member_num)
	{
		if (stock[i].member_num == user->userNo)// 잔고데이터중 입력한 사용자의 id와 일치하는 경우를 찾음
		{
			int cn = 0;
			while (1)
			{
				
				if (!strcmp(price[cn].stock_code, stock[i].code)) // 일별시세데이터와 잔고데이터의 주식코드가 일치할때
				{
					textcolor(15);
					printf("주식이름: %12s | 보유 주식 수 % d\n", price[cn].stock_name, stock[i].quantity); // 화면에 출력한다.
					break;// 일별시세데이터는 최신의 가격기준으로 정렬되있으므로 하나만 찾고 break 한다.
				}
				cn++;
			}
			
			textcolor(7);

		}
		i++;
	}
	printf("=======================================================\n");

}

void Print_bal(USER* user) // 잔고 및 수익률 표시
{
	printf("\n보유현금 %d원 추가\n", user->balance);
	StockInfo tmp;
	Stock stock;
	int sum = 0;
	FILE* st, * pr;
	char trs[200];

	st = fopen("data/stock.txt", "rt");
	if (st == NULL) {
		perror("ERROR");
	}
	pr = fopen("data/output.txt", "rt");
	if (pr == NULL) {
		perror("ERROR");
	}
	fgets(trs, 200, pr);

	while (1)
	{
		int cn;
		cn = fscanf(st, "%d %s %d", &stock.member_num, stock.code, &stock.quantity);  // stock 구조체에 잔고데이터를 담음
		if (cn != 3)
			break;
		if (stock.member_num == user->userNo) //  입력한 id 와 일치하는 경우를 찾으면
		{

			while (1)
			{
				cn = fscanf(pr, "%s %s %s %d %d %d %d %d %d", tmp.stock_code,
					tmp.stock_name, tmp.date, &tmp.open, &tmp.compare, &tmp.high, &tmp.low, &tmp.close, &tmp.volume); // tmp에 일별 시세데이터를 담고
				if (cn != 9)
					break;

				if (!strcmp(stock.code, tmp.stock_code)) // 시세데이터와 잔고데이터의 코드가 일치하는 경우를 찾으면
				{
					sum += tmp.open * stock.quantity; // 잔고에 계산해서 넣어줌
					printf("현재가 %7d %15s가(이) %3d주 합 : %d\n", tmp.open, tmp.stock_name, stock.quantity, tmp.open *
						stock.quantity);
					break;
				}


			}
		}

	}
	cashplus(&sum, user);
	int bal = sum - 10000000;
	if (bal >= 0)
	{
		printf("잔고는 %d원입니다.(+%d)\n", sum, bal);
	}
	else {
		printf("잔고는 %d원입니다.(%d)\n", sum, bal);
	}

	float ror = (sum / 10000000.0) * 100 - 100;
	//수익률이 양수면 빨 음수면 파
	if (ror >= 0)
	{
		textcolor(4);
	}
	else {
		textcolor(1);
	}
	printf("수익률은 %.2f %%입니다.\n", ror);
	textcolor(7);
	printf("=======================================================\n");

	fclose(st);
	fclose(pr);
}


void cashplus(int* sum, USER* user)  // 잔고에 현금 추가하는 함수 , 포인터변수 사용
{
	printf("\n보유현금 %d원 추가\n", user->balance);
	*sum += user->balance;

}