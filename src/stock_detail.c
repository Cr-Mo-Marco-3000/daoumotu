#include "../hdr/generic.h"
#include "../hdr/built_in_library.h"


void graph(struct StockInfo **dateArr, int max, int min);
void stockDescription(struct StockInfo **dateArr);

void stock_detail() {
	char stock_code[10];									// ���� �Ѿ�� �� 
	int cnt = 0;

	int max = 0, min = 1000000000;
	char tmp[200];
	FILE *fp;
	char *ptr;
	int flag=1;
	struct StockInfo *dateArr[20];						// ��¥�� ������ ���� ����ü �迭

	printf("���� �ڵ带 �Է����ּ���.\n");
	scanf("%s", stock_code);

	while (getchar() != '\n');


	fp = fopen("data/output.txt", "r");
	if (fp == NULL) {
		perror("Error");
		exit(1);
	}
	while (fgets(tmp, 200, fp)) {
		if (cnt == 20) {								// 20��ġ�� �����͸� ������
			break;
		}
		ptr = strtok(tmp, "\t");
		if (!strcmp(ptr, stock_code)) {						// ���� �����ڵ尡 �����ϸ� ������
			flag = 0;
			dateArr[cnt] = (struct StockInfo *)malloc(sizeof(StockInfo));
			strcpy(dateArr[cnt]->stock_code, ptr);				// �����ڵ� ����
			
			ptr = strtok(NULL, "\t");
			strcpy(dateArr[cnt]->stock_name, ptr);
			ptr = strtok(NULL, "\t");
			strcpy(dateArr[cnt]->date, ptr);
			ptr = strtok(NULL, "\t");
			dateArr[cnt]->close = atoi(ptr);
			ptr = strtok(NULL, "\t");
			dateArr[cnt]->compare = atoi(ptr);
			ptr = strtok(NULL, "\t");
			dateArr[cnt]->open = atoi(ptr);
			ptr = strtok(NULL, "\t");
			dateArr[cnt]->high = atoi(ptr);
			if (atoi(ptr) > max) max = atoi(ptr);
			ptr = strtok(NULL, "\t");
			dateArr[cnt]->low = atoi(ptr);
			if (atoi(ptr) < min) min = atoi(ptr);
			ptr = strtok(NULL, "\t");
			dateArr[cnt]->volume= atoi(ptr);
			cnt++;
			}
		}

	if (flag) {
		printf("ã���ô� �ֽ� ������ �������� �ʽ��ϴ�.");
		Sleep(1000);
		return;
	}

	graph(dateArr, max, min);					// �׷��� �׷��ִ� �Լ�

	printf("\n\n\n");			// �׷��� �Ʒ� ����

	stockDescription(dateArr);		// ���� ��� �Լ�

	for (cnt = 0; cnt < 20; cnt++) {
		free(dateArr[cnt]);
	}
	printf("\n\n");
	return;
	
}

void graph(struct StockInfo **dateArr, int max, int min) {		// �����͸� ����Ű�� �����͸� �Ѱ�����
	int row = 0;
	int col = 0;
	double interval = (double)(max - min) / 35;					// �׷����� ���� ������ ���͹�
	double graphNow = (double)max + 5 * interval;				// �׷��� ���� ���� �� 
	int stockNow = 0;											// ���� ���� �ְ�
	int flag = 1;												// �ֽ� �̼� ������ �÷���
	char *ptr;

	HANDLE h_console = GetStdHandle(STD_OUTPUT_HANDLE); // ���� ������ ������ �ڵ�
	// SetConsoleTextAttribute(h_console, 4); // => ���� ������
	// SetConsoleTextAttribute(h_console, 1); // => ���� �Ķ��� |�� ���
	// SetConsoleTextAttribute(h_console, BACKGROUND_RED + 4); // => ���� + ��� ������
	// SetConsoleTextAttribute(h_console, BACKGROUND_BLUE + 1); // => ���� + ��� �Ķ���
	// SetConsoleTextAttribute(h_console, 15); // => ���� ���, ��� ������ �⺻��
	// SetConsoleTextAttribute(h_console, 0); // => ���ڱ��� ������

	// �� �� ����
	printf("\n\n\n\n\n");
	printf("\t\t\t\t\t\t\t\t   ");
	printf("%20s 20�� �ְ� ���� �׷���\n", dateArr[0]->stock_name);
	putchar('\n'); putchar('\n');
	printf("\t      ");
	printf("���͹�: %.lf\n", interval);
	putchar('\n');
	// �� 20��ġ�� ������ ���
	// y���� ����ϴ� �ݺ�
	for (row = 0; row < 45; row++) {
		SetConsoleTextAttribute(h_console, 15);
		if (row == 0 || row % 5) {			// �� ���ٰ�, 5�������� �࿡�� ���� ǥ��
			printf("              | ");
		}
		else if (!(row % 5)) {
			printf("%13.lf + ", graphNow);  // ���Ŀ� ���缭, 5�ܰ� ���� ���� ��� (20�� �ְ��� ������ ���� �� 35�ܰ�)
		}

		// ���� ���� ����ϴ� ������ �־�� �Ѵ�. => �� 180�÷�
		for (col = 0; col < 141; col++) {
				if (!((col - 2) % 7)) {																			  // ���� ��¥�� �ִ� ���̸� ���� �������� ��
					stockNow = 19 - (col - 2) / 7;
					if (dateArr[stockNow]->close - dateArr[stockNow]->open > 0) {								  // ����
						if (dateArr[stockNow]->close < graphNow && graphNow <= dateArr[stockNow]->high) {		  // ���ذ��� �ְ��� ���� ����
							SetConsoleTextAttribute(h_console, 4);
							if (graphNow - interval < dateArr[stockNow]->open) {								  // �ٵ� �������̰� interval��ŭ �ȳ���
								flag = 2;
							}
						} else if (dateArr[stockNow]->open <= graphNow && graphNow <= dateArr[stockNow]->close) {	// ���� �ð��� ���� �����ε�
							if (dateArr[stockNow]->close - dateArr[stockNow]->open < interval) {					// ���� ������ interval ���϶��
								SetConsoleTextAttribute(h_console, 4);												// ��, �������� ������
								flag = 0;
							} else {
								SetConsoleTextAttribute(h_console, BACKGROUND_RED + 4);								// �������� ũ�� �Ӱ� ĥ��
							}
						} else if (dateArr[stockNow]->low <= graphNow && graphNow < dateArr[stockNow]->open) {
							SetConsoleTextAttribute(h_console, 4);
							//if (graphNow + interval > dateArr[stockNow]->close) {					
							//	flag = 0;
							//}
						}
						flag == 1 ? putchar('|') : flag == 2 ? putchar('+') : putchar('=');
						SetConsoleTextAttribute(h_console, 0);														// ���� + ��� ���������� �ٲٱ�
						flag = 1;
					} else if (dateArr[stockNow]->close - dateArr[stockNow]->open < 0) {								// �༼
						if (dateArr[stockNow]->open < graphNow && graphNow <= dateArr[stockNow]->high) {
							SetConsoleTextAttribute(h_console, 1);
							//if (graphNow - interval < dateArr[stockNow]->close) {
							//	flag = 0;
							//}
						} else if (dateArr[stockNow]->close <= graphNow && graphNow <= dateArr[stockNow]->open) {
							if (dateArr[stockNow]->open - dateArr[stockNow]->close < interval)
							{
								SetConsoleTextAttribute(h_console, 1);
								flag = 0;
							} else {
								SetConsoleTextAttribute(h_console, BACKGROUND_BLUE + 1);
							}
						} else if (dateArr[stockNow]->low <= graphNow && graphNow < dateArr[stockNow]->close) {
							SetConsoleTextAttribute(h_console, 1);
							if (graphNow + interval > dateArr[stockNow]->open) {
								flag = 2;
							}
						}
						flag == 1 ? putchar('|') : flag == 2 ? putchar('+') : putchar('=');
						flag = 1;
					} else {																						// ����: ������ �༼�� �ƴ� ��
						if (dateArr[stockNow]->low <= graphNow && graphNow <= dateArr[stockNow]->high) {			// �ش��ϸ� �Ͼ��
							SetConsoleTextAttribute(h_console, 15);
							if (dateArr[stockNow]->open <= graphNow + interval / 2 && dateArr[stockNow]->open > graphNow - interval / 2) {
								putchar('=');
							}
							else {
								putchar('|');
							}
						} else {
							SetConsoleTextAttribute(h_console, 0);
							putchar('|');
						}
					}
				} else {
					SetConsoleTextAttribute(h_console, 0);
					putchar('|');
				}
			}
		SetConsoleTextAttribute(h_console, 0);	// �׷��� �ٱ��ʿ���, 0�� �־� ���������� ����� �־�� ���� ������ ����
		putchar('|');
		puts("");
		graphNow -= interval;
	}
	SetConsoleTextAttribute(h_console, 15);

	// �� �Ʒ� ���� �� ��¥ ���
	printf("               ");
	for (col = 0; col < 20; col++) {
		printf("===|===");
	}
	puts("");
	printf("               ");
	for (col = 0; col < 20; col++) {
		ptr = dateArr[19 - col]->date;
		printf(" %s ", ptr + 5);
	}

	// ��Ʈ�� ���� ����
	puts("\n\n\n");
	printf("\t      ");
	printf("- �׷��� Y���� �� ĭ�� ������ ĭ�� ���͹���ŭ�� ���̰� ���� ���� ������ �ǹ��մϴ�.\n");
	putchar('\n');

	printf("\t      ");
	printf("- �ش� ���� ������ �ð��� ���� ���̿� ���� ���� ������, ���� ���� ���̿� ���� ���� ������ ǥ���մϴ�.\n");
	
	putchar('\n');
	printf("\t      ");
	printf("- �༼ �Ǵ� ������ ��\n");
	printf("\t      ");
	printf("	1) =�� �ش� ���� ������ �ð��� ���� ���̿� ������, �ð��� ������ ���̰� ���͹����� ���� ���� ��Ÿ���ϴ�. \n");
	printf("\t      ");
	printf("	2) -�� �ش� ���� ������ ������Ÿ ũ��, (���� ���� - ���͹�)���� �ð��� Ŭ ��, �� �ð��� ������ ���̰� ���͹����� ���� ���� ��Ÿ���ϴ�. \n");
	printf("\t      ");
	printf("	3) +�� �ش� ���� ������ ������Ÿ �۰�, (���� ���� + ���͹�)���� �ð��� ���� ��, �� �ð��� ������ ���̰� ���͹����� ���� ���� ��Ÿ���ϴ�. \n");
	
	putchar('\n');
	printf("\t      ");
	printf("- ����(�ð� = ����)�� ��\n");
	printf("\t      ");
	printf("	1) =�� �ش� ���� �������κ��� - ���͹� / 2 �� ���ݰ�, + ���͹� / 2�� ���� ���̿�, �ð�(����)�� ��ġ�Ѵٴ� ���� �ǹ��մϴ�.\n");
	printf("\n\n");
}

void stockDescription(struct StockInfo **dateArr) {
	int cnt;
	char *ptr = "------------------- ";
	printf("\t\t\t\t\t\t\t\t\t");
	printf("���ں� �� ����\n");
	putchar('\n'); putchar('\n');
	// ���ں� ������ ���(20��)
	printf("                %-20s%-20s%-20s%-20s%-20s%-20s%-20s\n\n", "��¥(date)", "����", "���Ϻ�", "�ð�", "��", "����", "�ŷ���");
	printf("                %-20s%-20s%-20s%-20s%-20s%-20s%-20s\n\n", ptr, ptr, ptr, ptr, ptr, ptr, ptr);
	//printf("�����ڵ�, �����, ��¥, ����, ���Ϻ�, �ð�, ��, ����, �ŷ���\n");
	for (cnt = 0; cnt < 20; cnt++) {
		printf("                ");
		//printf("%-20d", dateArr[cnt]->stock_code);		// �����ڵ�
		//printf("%-20s", dateArr[cnt]->stock_name);		// �����
		printf("%-20s", dateArr[cnt]->date);		// ��¥
		printf("%-20d", dateArr[cnt]->close);		// ����
		printf("%-20d", dateArr[cnt]->compare);		// ���Ϻ�
		printf("%-20d", dateArr[cnt]->open);		// �ð�
		printf("%-20d", dateArr[cnt]->high);	// ��
		printf("%-20d", dateArr[cnt]->low);	// ����
		printf("%-20d\n", dateArr[cnt]->volume);		// �ŷ���
		putchar('\n');
	}
}
