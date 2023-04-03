#include "../hdr/generic.h"
#include "../hdr/built_in_library.h"
#define MAX_LEN 20
void Print_st(USER* user);
void Print_bal(USER* user);
void cashplus(int* sum, USER* user);




void textcolor(int colorNum) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorNum);
}

int portfolio(USER* user, Stock *stock ,StockInfo *tmp)   // 가인수로 회원번호 받아온다. 포트폴리오 시작함수
{

	int id = user->userNo; // 가인수로 넣을 값

	printf("PORTFOLIO\n\n");
	printf("잔고를 표시합니다.\n");


	printf("=======================================================\n");
	printf("%d의 주식\n", user->userNo);

	

	Print_bal(stock,tmp,user);
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

void Print_bal(Stock *stock,StockInfo *price,USER* user) // 잔고 및 수익률 표시
{

	int sum = 0, cn, i;

	i = 0;
	while (stock[i].member_num)
	{
		
		
		if (stock[i].member_num == user->userNo) //  입력한 id 와 일치하는 경우를 찾으면
		{
			cn = 0;

			while (1)
			{

				if (!strcmp(stock[i].code, price[cn].stock_code)) // 시세데이터와 잔고데이터의 코드가 일치하는 경우를 찾으면
				{
					sum += price[cn].open * stock[i].quantity; // 잔고에 계산해서 넣어줌
					printf("현재가 %7d %15s가(이) %3d주 합 : %d\n", price[cn].open, price[cn].stock_name, stock[i].quantity, price[cn].open *
						stock[i].quantity);
					break;
				}

				cn++;
			}
		}
		i++;

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

}


void cashplus(int* sum, USER* user)  // 잔고에 현금 추가하는 함수 , 포인터변수 사용
{
	printf("\n보유현금 %d원 추가\n", user->balance);
	*sum += user->balance;

}