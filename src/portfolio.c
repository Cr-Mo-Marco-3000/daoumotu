#include "../hdr/generic.h"
#include "../hdr/built_in_library.h"
#define MAX_LEN 20
void Print_st(USER* user);
void Print_bal(USER* user);
void cashplus(int* sum, USER* user);




void textcolor(int colorNum) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorNum);
}

int portfolio(USER* user)   // ���μ��� ȸ����ȣ �޾ƿ´�. ��Ʈ������ �����Լ�
{

	int id = user->userNo; // ���μ��� ���� ��

	printf("PORTFOLIO\n\n");
	printf("�ܰ� ǥ���մϴ�.\n");


	printf("=======================================================\n");
	printf("%d�� �ֽ�\n", user->userNo);

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
		cn = fscanf(pr, "%s %s %s %d %d %d %d %d %d", tmp[i].stock_code, // id�� ��ġ�ϸ� tmp ����ü�� �Ϻ� �ü������͸� �Է�
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


void Print_st(Stock* stock, StockInfo* price, USER* user) // �����ֽļ� ���
{
	int i = 0;
	while (stock[i].member_num)
	{
		if (stock[i].member_num == user->userNo)// �ܰ������� �Է��� ������� id�� ��ġ�ϴ� ��츦 ã��
		{
			int cn = 0;
			while (1)
			{
				
				if (!strcmp(price[cn].stock_code, stock[i].code)) // �Ϻ��ü������Ϳ� �ܰ������� �ֽ��ڵ尡 ��ġ�Ҷ�
				{
					textcolor(15);
					printf("�ֽ��̸�: %12s | ���� �ֽ� �� % d\n", price[cn].stock_name, stock[i].quantity); // ȭ�鿡 ����Ѵ�.
					break;// �Ϻ��ü������ʹ� �ֽ��� ���ݱ������� ���ĵ������Ƿ� �ϳ��� ã�� break �Ѵ�.
				}
				cn++;
			}
			
			textcolor(7);

		}
		i++;
	}
	printf("=======================================================\n");

}

void Print_bal(USER* user) // �ܰ� �� ���ͷ� ǥ��
{
	printf("\n�������� %d�� �߰�\n", user->balance);
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
		cn = fscanf(st, "%d %s %d", &stock.member_num, stock.code, &stock.quantity);  // stock ����ü�� �ܰ����͸� ����
		if (cn != 3)
			break;
		if (stock.member_num == user->userNo) //  �Է��� id �� ��ġ�ϴ� ��츦 ã����
		{

			while (1)
			{
				cn = fscanf(pr, "%s %s %s %d %d %d %d %d %d", tmp.stock_code,
					tmp.stock_name, tmp.date, &tmp.open, &tmp.compare, &tmp.high, &tmp.low, &tmp.close, &tmp.volume); // tmp�� �Ϻ� �ü������͸� ���
				if (cn != 9)
					break;

				if (!strcmp(stock.code, tmp.stock_code)) // �ü������Ϳ� �ܰ������� �ڵ尡 ��ġ�ϴ� ��츦 ã����
				{
					sum += tmp.open * stock.quantity; // �ܰ� ����ؼ� �־���
					printf("���簡 %7d %15s��(��) %3d�� �� : %d\n", tmp.open, tmp.stock_name, stock.quantity, tmp.open *
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
		printf("�ܰ�� %d���Դϴ�.(+%d)\n", sum, bal);
	}
	else {
		printf("�ܰ�� %d���Դϴ�.(%d)\n", sum, bal);
	}

	float ror = (sum / 10000000.0) * 100 - 100;
	//���ͷ��� ����� �� ������ ��
	if (ror >= 0)
	{
		textcolor(4);
	}
	else {
		textcolor(1);
	}
	printf("���ͷ��� %.2f %%�Դϴ�.\n", ror);
	textcolor(7);
	printf("=======================================================\n");

	fclose(st);
	fclose(pr);
}


void cashplus(int* sum, USER* user)  // �ܰ� ���� �߰��ϴ� �Լ� , �����ͺ��� ���
{
	printf("\n�������� %d�� �߰�\n", user->balance);
	*sum += user->balance;

}