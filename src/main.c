#include "../hdr/generic.h"
#include "../hdr/built_in_library.h"



int main(void)
{
	FILE *st, *pr, *fp;
	StockInfo tmp[600] = { 0 };
	Stock stock[100] = { 0 };
	char trs[200];
	USER *user;
	USER usertemp = { -1 }; // 임시 더미 회원
	USER *start = NULL, *end = NULL;		// 회원 연결 리스트의 시작과 끝 주소 
	int choose;
	StockInfo stockInfoList[500];
	char print_tmp[256];
	HANDLE h_console = GetStdHandle(STD_OUTPUT_HANDLE); // 색상 조작을 도와줄 핸들
	fp = fopen("data/pictogram.txt", "r");

	puts("");
	SetConsoleTextAttribute(h_console, 4); // => 글자 빨간색
	if (fp == NULL)
	{
		printf("파일 불러오기 실패 \n");
		return 1;
	}
	while (fgets(print_tmp, 255, fp) != NULL) {
		printf(print_tmp);
		if (print_tmp[9] == ' ') {
			SetConsoleTextAttribute(h_console, 1); // => 글자 파란색 |에 사용
		}
	}
	SetConsoleTextAttribute(h_console, 15);
	fclose(fp);

	user = &usertemp;

	// 주식 배열 리스트


	// 주식 배열 담는 함수


	//  파일을 구조체 배열에 담기

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
	//구조체 배열 담아오기 끝

	fclose(st);
	fclose(pr);
	// 전체 루프
	while (1) {
		if (start == NULL) {	// 로그인이 안 된 상태
			Sleep(1000);
			printf("\n서비스에 연결하려면 1, 종료하려면 2를 입력해주세요.\n");
			choose = getchar();
			while (getchar() != '\n');
			if (choose == '1') {
				auth(user);
				loadList(&user, &start, &end);							// 유저 정보 연결 리스트 만드는 함수
			}
			else if (choose == '2') {
				printf("이용해 주셔서 감사합니다. 안녕히 가십시오.\n");
				Sleep(500);
				exit(1);
			}
			else {
				printf("입력이 부정확합니다. 다시 입력 부탁드립니다.\n");
				Sleep(1000);
			}
		}
		else {
			puts("\n이용하실 서비스를 선택해 주세요\n");
			printf("==================================\n");
			printf("1. 모든 주식 정보 조회\n");
			printf("서비스에 등록된 모든 주식의 20일치 정보를 조회합니다.\n");
			putchar('\n');
			printf("2. 주식 상세 정보 조회\n");
			printf("종목 코드를 입력하여 주식 상세 정보를 조회합니다.\n");
			putchar('\n');
			printf("3. 주식 매매\n");
			printf("주식을 매매합니다.\n");
			putchar('\n');
			printf("4. 주식 매매내역 검색\n");
			printf("내가 주식을 매매한 내역을 참고합니다.\n");
			putchar('\n');
			printf("5. 포트폴리오 보기\n");
			printf("내가 보유한 주식과 포트폴리오를 참고합니다.\n");
			putchar('\n');
			printf("0. 로그아웃\n");
			printf("서비스에서 로그아웃합니다.\n");
			Sleep(500);
			printf("\n==================================\n서비스 번호 입력 : ");
			scanf("%d", &choose);
			while (getchar() != '\n');

			if (choose == 1) {
				print_function(tmp);
			}
			else if (choose == 2) {
				stock_detail();
			}
			else if (choose == 3) {
				// 여기 주식 매매가 들어가면 됩니다.
				trade(user, stock, tmp);
			}
			else if (choose == 4) {
				tradesearch(user);
			}
			else if (choose == 5) {
				portfolio(user, stock, tmp);
				// 여기 포트폴리오 보기가 들어가면 됩니다.
			}
			else if (choose == 0) {


				// 여기 저장이 들어가야 함
				saveList(start);
				savestockholdlst(stock);
				// 다음으로는 유저 포인터 초기화 및 HEAD 초기화
				user = &usertemp;
				start = end = NULL;			// 다시 로그인 시, 유저 배열을 만들기위해 NULL로 바꿔줌
				puts("\n로그아웃합니다.\n");
				Sleep(1000);
			}
		}
	}

	return 0;
}