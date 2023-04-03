#include "../hdr/generic.h"
#include "../hdr/built_in_library.h"


void graph(struct StockInfo **dateArr, int max, int min);
void stockDescription(struct StockInfo **dateArr);

void stock_detail() {
	char stock_code[10];									// 차후 넘어올 것 
	int cnt = 0;

	int max = 0, min = 1000000000;
	char tmp[200];
	FILE *fp;
	char *ptr;
	int flag=1;
	struct StockInfo *dateArr[20];						// 날짜별 정보를 담을 구조체 배열

	printf("종목 코드를 입력해주세요.\n");
	scanf("%s", stock_code);

	while (getchar() != '\n');


	fp = fopen("data/output.txt", "r");
	if (fp == NULL) {
		perror("Error");
		exit(1);
	}
	while (fgets(tmp, 200, fp)) {
		if (cnt == 20) {								// 20일치의 데이터만 보여줌
			break;
		}
		ptr = strtok(tmp, "\t");
		if (!strcmp(ptr, stock_code)) {						// 만약 종목코드가 동일하면 가져옴
			flag = 0;
			dateArr[cnt] = (struct StockInfo *)malloc(sizeof(StockInfo));
			strcpy(dateArr[cnt]->stock_code, ptr);				// 종목코드 저장
			
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
		printf("찾으시는 주식 종목이 존재하지 않습니다.");
		Sleep(1000);
		return;
	}

	graph(dateArr, max, min);					// 그래프 그려주는 함수

	printf("\n\n\n");			// 그래프 아래 공백

	stockDescription(dateArr);		// 정보 출력 함수

	for (cnt = 0; cnt < 20; cnt++) {
		free(dateArr[cnt]);
	}
	printf("\n\n");
	return;
	
}

void graph(struct StockInfo **dateArr, int max, int min) {		// 포인터를 가리키는 포인터를 넘겨주자
	int row = 0;
	int col = 0;
	double interval = (double)(max - min) / 35;					// 그래프의 작은 단위별 인터벌
	double graphNow = (double)max + 5 * interval;				// 그래프 가장 높은 곳 
	int stockNow = 0;											// 현재 비교할 주가
	int flag = 1;												// 주식 미세 변동용 플래그
	char *ptr;

	HANDLE h_console = GetStdHandle(STD_OUTPUT_HANDLE); // 색상 조작을 도와줄 핸들
	// SetConsoleTextAttribute(h_console, 4); // => 글자 빨간색
	// SetConsoleTextAttribute(h_console, 1); // => 글자 파란색 |에 사용
	// SetConsoleTextAttribute(h_console, BACKGROUND_RED + 4); // => 글자 + 배경 빨간색
	// SetConsoleTextAttribute(h_console, BACKGROUND_BLUE + 1); // => 글자 + 배경 파란색
	// SetConsoleTextAttribute(h_console, 15); // => 글자 흰색, 배경 검은색 기본값
	// SetConsoleTextAttribute(h_console, 0); // => 글자까지 검은색

	// 맨 위 공백
	printf("\n\n\n\n\n");
	printf("\t\t\t\t\t\t\t\t   ");
	printf("%20s 20일 주가 변동 그래프\n", dateArr[0]->stock_name);
	putchar('\n'); putchar('\n');
	printf("\t      ");
	printf("인터벌: %.lf\n", interval);
	putchar('\n');
	// 총 20일치의 데이터 출력
	// y축을 출력하는 반복
	for (row = 0; row < 45; row++) {
		SetConsoleTextAttribute(h_console, 15);
		if (row == 0 || row % 5) {			// 맨 윗줄과, 5단위마다 행에는 숫자 표시
			printf("              | ");
		}
		else if (!(row % 5)) {
			printf("%13.lf + ", graphNow);  // 형식에 맞춰서, 5단계 기준 가격 출력 (20일 최고가와 최저가 사이 총 35단계)
		}

		// 안쪽 값을 출력하는 조건을 주어야 한다. => 총 180컬럼
		for (col = 0; col < 141; col++) {
				if (!((col - 2) % 7)) {																			  // 만약 날짜가 있는 열이면 내부 조건으로 들어감
					stockNow = 19 - (col - 2) / 7;
					if (dateArr[stockNow]->close - dateArr[stockNow]->open > 0) {								  // 강세
						if (dateArr[stockNow]->close < graphNow && graphNow <= dateArr[stockNow]->high) {		  // 기준가가 최고가와 종가 사이
							SetConsoleTextAttribute(h_console, 4);
							if (graphNow - interval < dateArr[stockNow]->open) {								  // 근데 가격차이가 interval만큼 안나면
								flag = 2;
							}
						} else if (dateArr[stockNow]->open <= graphNow && graphNow <= dateArr[stockNow]->close) {	// 만약 시가와 종가 사이인데
							if (dateArr[stockNow]->close - dateArr[stockNow]->open < interval) {					// 당일 변동이 interval 이하라면
								SetConsoleTextAttribute(h_console, 4);												// 즉, 변동폭이 작으면
								flag = 0;
							} else {
								SetConsoleTextAttribute(h_console, BACKGROUND_RED + 4);								// 변동폭이 크면 붉게 칠함
							}
						} else if (dateArr[stockNow]->low <= graphNow && graphNow < dateArr[stockNow]->open) {
							SetConsoleTextAttribute(h_console, 4);
							//if (graphNow + interval > dateArr[stockNow]->close) {					
							//	flag = 0;
							//}
						}
						flag == 1 ? putchar('|') : flag == 2 ? putchar('+') : putchar('=');
						SetConsoleTextAttribute(h_console, 0);														// 글자 + 배경 검은색으로 바꾸기
						flag = 1;
					} else if (dateArr[stockNow]->close - dateArr[stockNow]->open < 0) {								// 약세
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
					} else {																						// 도지: 강세도 약세도 아닐 때
						if (dateArr[stockNow]->low <= graphNow && graphNow <= dateArr[stockNow]->high) {			// 해당하면 하얀색
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
		SetConsoleTextAttribute(h_console, 0);	// 그래프 바깥쪽에도, 0을 넣어 검은색으로 출력해 주어야 색이 번지지 않음
		putchar('|');
		puts("");
		graphNow -= interval;
	}
	SetConsoleTextAttribute(h_console, 15);

	// 맨 아래 밑줄 및 날짜 출력
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

	// 차트에 대한 설명
	puts("\n\n\n");
	printf("\t      ");
	printf("- 그래프 Y축의 각 칸은 인접한 칸과 인터벌만큼의 차이가 나는 기준 가격을 의미합니다.\n");
	putchar('\n');

	printf("\t      ");
	printf("- 해당 기준 가격이 시가와 종가 사이에 있을 때는 면으로, 고가와 저가 사이에 있을 때는 선으로 표시합니다.\n");
	
	putchar('\n');
	printf("\t      ");
	printf("- 약세 또는 강세일 때\n");
	printf("\t      ");
	printf("	1) =는 해당 기준 가격이 시가와 종가 사이에 있지만, 시가와 종가의 차이가 인터벌보다 적을 때를 나타냅니다. \n");
	printf("\t      ");
	printf("	2) -는 해당 기준 가격이 종가보타 크고, (기준 가격 - 인터벌)보다 시가가 클 때, 즉 시가와 종가의 차이가 인터벌보다 적을 때를 나타냅니다. \n");
	printf("\t      ");
	printf("	3) +는 해당 기준 가격이 종가보타 작고, (기준 가격 + 인터벌)보다 시가가 작을 때, 즉 시가와 종가의 차이가 인터벌보다 적을 때를 나타냅니다. \n");
	
	putchar('\n');
	printf("\t      ");
	printf("- 도지(시가 = 종가)일 때\n");
	printf("\t      ");
	printf("	1) =는 해당 기준 가격으로부터 - 인터벌 / 2 한 가격과, + 인터벌 / 2한 가격 사이에, 시가(종가)가 위치한다는 것을 의미합니다.\n");
	printf("\n\n");
}

void stockDescription(struct StockInfo **dateArr) {
	int cnt;
	char *ptr = "------------------- ";
	printf("\t\t\t\t\t\t\t\t\t");
	printf("일자별 상세 정보\n");
	putchar('\n'); putchar('\n');
	// 일자별 상세정보 출력(20일)
	printf("                %-20s%-20s%-20s%-20s%-20s%-20s%-20s\n\n", "날짜(date)", "종가", "전일비", "시가", "고가", "저가", "거래량");
	printf("                %-20s%-20s%-20s%-20s%-20s%-20s%-20s\n\n", ptr, ptr, ptr, ptr, ptr, ptr, ptr);
	//printf("종목코드, 종목명, 날짜, 종가, 전일비, 시가, 고가, 저가, 거래량\n");
	for (cnt = 0; cnt < 20; cnt++) {
		printf("                ");
		//printf("%-20d", dateArr[cnt]->stock_code);		// 종목코드
		//printf("%-20s", dateArr[cnt]->stock_name);		// 종목명
		printf("%-20s", dateArr[cnt]->date);		// 날짜
		printf("%-20d", dateArr[cnt]->close);		// 종가
		printf("%-20d", dateArr[cnt]->compare);		// 전일비
		printf("%-20d", dateArr[cnt]->open);		// 시가
		printf("%-20d", dateArr[cnt]->high);	// 고가
		printf("%-20d", dateArr[cnt]->low);	// 저가
		printf("%-20d\n", dateArr[cnt]->volume);		// 거래량
		putchar('\n');
	}
}
