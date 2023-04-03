#include "../hdr/generic.h"
#include "../hdr/built_in_library.h"
#define MAX_LEN 20
void Print_st(int id);
void Print_bal(int id);
void cashplus(int *sum, int id);

void textcolor(int colorNum) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorNum);
}
// typedef struct price // ���������� �����ڵ�/����/���� abcde �� ���� �ʴ� ������
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

// typedef struct  // �ܰ��ֽĵ����� ȸ����ȣ/�����ڵ�/�����ֽļ�
// {
// 	int member_num;
// 	char code[MAX_LEN];
// 	int quantity;
// } Stock;

// typedef struct // ȸ������������ ���̵�/��й�ȣ/�̸�/ȸ����ȣ/��������
// {
// 	char id[MAX_LEN];
// 	char password[MAX_LEN];
// 	char name[MAX_LEN];
// 	int member_num;
// 	int account;
// } Member;

int main()   // ���μ��� ȸ����ȣ �޾ƿ´�. ��Ʈ������ �����Լ�
{

	int id = 1; // ���μ��� ���� ��

	printf("PORTFOLIO\n\n");
	printf("�ܰ� ǥ���մϴ�.\n");


	printf("=======================================================\n");




	Print_bal(id);
	Print_st(id);

}


void Print_st(int id) // �����ֽļ� ���
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
	printf("%d�� �ֽ�\n", id);
	fgets(trs, 200, pr);
	while (1)
	{
		int cn;
		cn = fscanf(st, "%d %s %d", &stock.member_num, stock.code, &stock.quantity); // stock ����ü�� �ܰ����� �Է�
		if (cn != 3)
			break;
		if (stock.member_num == id)// �ܰ������� �Է��� ������� id�� ��ġ�ϴ� ��츦 ã��
		{
			while (1)
			{
				int cn;
				cn = fscanf(pr, "%s %s %s %d %d %d %d %d %d", tmp.stock_code, // id�� ��ġ�ϸ� tmp ����ü�� �Ϻ� �ü������͸� �Է�
					tmp.stock_name, tmp.date, &tmp.open, &tmp.compare, &tmp.high, &tmp.low, &tmp.close, &tmp.volume);
				if (cn != 9)
					break;
				if (!strcmp(tmp.stock_code, stock.code)) // �Ϻ��ü������Ϳ� �ܰ������� �ֽ��ڵ尡 ��ġ�Ҷ�
				{
					textcolor(15);
					printf("�ֽ��̸�: %12s | ���� �ֽ� �� % d\n", tmp.stock_name, stock.quantity); // ȭ�鿡 ����Ѵ�.
					break;// �Ϻ��ü������ʹ� �ֽ��� ���ݱ������� ���ĵ������Ƿ� �ϳ��� ã�� break �Ѵ�.
				}

			}
			textcolor(7);

		}
	}
	printf("=======================================================\n");
	fclose(st);
}

void Print_bal(int id) // �ܰ� �� ���ͷ� ǥ��
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
		cn = fscanf(st, "%d %s %d", &stock.member_num, stock.code, &stock.quantity);  // stock ����ü�� �ܰ����͸� ����
		if (cn != 3)
			break;
		if (stock.member_num == id) //  �Է��� id �� ��ġ�ϴ� ��츦 ã����
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
	cashplus(&sum, id);
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


void cashplus(int *sum, int id)  // �ܰ� ���� �߰��ϴ� �Լ� , �����ͺ��� ���
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
		cn = fscanf(mb, "%d %s %s %s %d", &mem.userNo, pid, pw, mem.name, &mem.balance); // mb ����ü�� ȸ�����������͸� �Է�
		if (cn != 5)
			break;
		if (mem.userNo == id) // �Է��� id�� ��ġ�� ���
		{
			printf("\n�������� %d�� �߰�\n", mem.balance);
			*sum += mem.balance; // �ش��ܰ� sum�� ������ �����͸� ����ؼ� ������ ���� �����Ѵ�.
			break;
		}
	}

	fclose(mb);


}