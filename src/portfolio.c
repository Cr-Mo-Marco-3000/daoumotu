#include "../hdr/generic.h"
#include "../hdr/built_in_library.h"
#define MAX_LEN 20
void Print_st(USER* user);
void Print_bal(USER* user);
void cashplus(int* sum, USER* user);




void textcolor(int colorNum) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorNum);
}

int portfolio(USER* user, Stock *stock ,StockInfo *tmp)   // ���μ��� ȸ����ȣ �޾ƿ´�. ��Ʈ������ �����Լ�
{

	int id = user->userNo; // ���μ��� ���� ��

	printf("PORTFOLIO\n\n");
	printf("�ܰ� ǥ���մϴ�.\n");


	printf("=======================================================\n");
	printf("%d�� �ֽ�\n", user->userNo);

	

	Print_bal(stock,tmp,user);
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

void Print_bal(Stock *stock,StockInfo *price,USER* user) // �ܰ� �� ���ͷ� ǥ��
{

	int sum = 0, cn, i;

	i = 0;
	while (stock[i].member_num)
	{
		
		
		if (stock[i].member_num == user->userNo) //  �Է��� id �� ��ġ�ϴ� ��츦 ã����
		{
			cn = 0;

			while (1)
			{

				if (!strcmp(stock[i].code, price[cn].stock_code)) // �ü������Ϳ� �ܰ������� �ڵ尡 ��ġ�ϴ� ��츦 ã����
				{
					sum += price[cn].open * stock[i].quantity; // �ܰ� ����ؼ� �־���
					printf("���簡 %7d %15s��(��) %3d�� �� : %d\n", price[cn].open, price[cn].stock_name, stock[i].quantity, price[cn].open *
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

}


void cashplus(int* sum, USER* user)  // �ܰ� ���� �߰��ϴ� �Լ� , �����ͺ��� ���
{
	printf("\n�������� %d�� �߰�\n", user->balance);
	*sum += user->balance;

}