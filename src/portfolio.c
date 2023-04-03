#include "../hdr/generic.h"
#include "../hdr/built_in_library.h"
#define MAX_LEN 20
void Print_st(int id);
void Print_bal(int id);
void cashplus(int *sum, int id);

void textcolor(int colorNum) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorNum);
}
// typedef struct price // 종가데이터 종목코드/일자/종가 abcde 는 쓰지 않는 데이터
// {
// 	char code[MAX_LEN];
// 	char st_name[MAX_LEN];
// 	char date[MAX_LEN];
// 	int fin_price;
// 	int a;
// 	int b;
// 	int c;
// 	int d;
// 	int e;

// }PRICE; 

// typedef struct  // 잔고주식데이터 회원번호/종목코드/보유주식수
// {
// 	int member_num;
// 	char code[MAX_LEN];
// 	int quantity;
// } Stock;

// typedef struct // 회원정보데이터 아이디/비밀번호/이름/회원번호/보유현금
// {
// 	char id[MAX_LEN];
// 	char password[MAX_LEN];
// 	char name[MAX_LEN];
// 	int member_num;
// 	int account;
// } Member;

int main()   // 가인수로 회원번호 받아온다. 포트폴리오 시작함수
{

	int id = 1; // 가인수로 넣을 값

	printf("PORTFOLIO\n\n");
	printf("잔고를 표시합니다.\n");


	printf("=======================================================\n");




	Print_bal(id);
	Print_st(id);

}


void Print_st(int id) // 보유주식수 출력
{
	StockInfo tmp;
	Stock stock;
	FILE *st, *pr;
	char trs[200];
	st = fopen("data/stock.txt", "rt");
	if (st == NULL) {
		perror("ERROR");
	}
	pr = fopen("data/output.txt", "rt");
	if (pr == NULL) {
		perror("ERROR");
	}
	printf("%d의 주식\n", id);
	fgets(trs, 200, pr);
	while (1)
	{
		int cn;
		cn = fscanf(st, "%d %s %d", &stock.member_num, stock.code, &stock.quantity); // stock 구조체에 잔고데이터 입력
		if (cn != 3)
			break;
		if (stock.member_num == id)// 잔고데이터중 입력한 사용자의 id와 일치하는 경우를 찾음
		{
			while (1)
			{
				int cn;
				cn = fscanf(pr, "%s %s %s %d %d %d %d %d %d", tmp.stock_code, // id와 일치하면 tmp 구조체에 일별 시세데이터를 입력
					tmp.stock_name, tmp.date, &tmp.open, &tmp.compare, &tmp.high, &tmp.low, &tmp.close, &tmp.volume);
				if (cn != 9)
					break;
				if (!strcmp(tmp.stock_code, stock.code)) // 일별시세데이터와 잔고데이터의 주식코드가 일치할때
				{
					textcolor(15);
					printf("주식이름: %12s | 보유 주식 수 % d\n", tmp.stock_name, stock.quantity); // 화면에 출력한다.
					break;// 일별시세데이터는 최신의 가격기준으로 정렬되있으므로 하나만 찾고 break 한다.
				}

			}
			textcolor(7);

		}
	}
	printf("=======================================================\n");
	fclose(st);
}

void Print_bal(int id) // 잔고 및 수익률 표시
{

	StockInfo tmp;
	Stock stock;
	int sum = 0;
	FILE *st, *pr;
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
		if (stock.member_num == id) //  입력한 id 와 일치하는 경우를 찾으면
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
	cashplus(&sum, id);
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


void cashplus(int *sum, int id)  // 잔고에 현금 추가하는 함수 , 포인터변수 사용
{
	char pid[20], pw[20];
	FILE *mb;
	USER mem;
	mb = fopen("data/user.txt", "rt");
	if (mb == NULL) {
		perror("ERROR");
	}

	while (1)
	{
		int cn;
		cn = fscanf(mb, "%d %s %s %s %d", &mem.userNo, pid, pw, mem.name, &mem.balance); // mb 구조체에 회원정보데이터를 입력
		if (cn != 5)
			break;
		if (mem.userNo == id) // 입력한 id와 일치할 경우
		{
			printf("\n보유현금 %d원 추가\n", mem.balance);
			*sum += mem.balance; // 해당잔고를 sum에 더해줌 포인터를 사용해서 변수의 값을 변경한다.
			break;
		}
	}

	fclose(mb);


}