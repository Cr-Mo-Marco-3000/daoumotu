#include "../hdr/generic.h"
#include "../hdr/built_in_library.h"



int main(void) 
{	
	USER usertemp = { -1 }; // 임시 더미 회원
	
	USER *user;

	user = &usertemp;

	USER *start = NULL, *end = NULL;		// 회원 연결 리스트의 시작과 끝 주소 

	int choose;

	// 전체 루프
	while (1) {
		if (user->userNo == -1) {	// 로그인이 안 된 상태
			printf("서비스에 연결하려면 1, 종료하려면 2를 입력해주세요.\n");
			choose = getchar();
			while (getchar() != '\n');
			if (choose == '1') {
				auth(user);
			} else if (choose == '2') {
				printf("이용해 주셔서 감사합니다. 안녕히 가십시오.\n");
				Sleep(500);
				exit(1);
			} else {
				printf("입력이 부정확합니다. 다시 입력 부탁드립니다.\n");
				Sleep(1000);
			}
		} else {
			loadList(&user, &start, &end);							// 유저 정보 연결 리스트 만드는 함수
			puts("이용하실 서비스를 선택해 주세요");
			printf("1. 주식 목록 조회\n");
			printf("서비스에 등록된 모든 주식을 조회합니다.\n");
			putchar('\n');
			puts("2. 주식 상세 정보 조회\n");
			printf("종목 코드를 입력하여 주식 상세 정보를 조회합니다.\n");
			putchar('\n');
			puts("3. 주식 매매\n");
			printf("주식을 매매합니다.\n");
			putchar('\n');
			puts("4. 주식 매매내역 검색\n");
			printf("내가 주식을 매매한 내역을 참고합니다.\n");
			putchar('\n');
			puts("5. 포트폴리오 보기\n");
			printf("내가 보유한 주식과 포트폴리오를 참고합니다.\n");
			putchar('\n');
			printf("0. 로그아웃");
			printf("서비스에서 로그아웃합니다.");
			scanf("%d", &choose);
			while (getchar() != '\n');

			if (choose == 1) {
				// 여기 주식 목록 조회
			} else if (choose == 2) {
				// 여기 주식 상세 정보 조회
			} else if (choose == 3) {
				// 여기 주식 매매가 들어가면 됩니다.
			} else if (choose == 4) {
				// 여기 주식 매매내역 검색이 들어가면 됩니다.
			} else if (choose == 5) {
				// 여기 포트폴리오 보기가 들어가면 됩니다.
			} else if (choose == 0) {
				// 여기 저장이 들어가야 함
				saveList(start);
				// 다음으로는 유저 포인터 초기화 및 HEAD 초기화
				user = &usertemp;
				start = end = NULL;			// 다시 로그인 시, 유저 배열을 만들기위해 NULL로 바꿔줌
				puts("로그아웃합니다.");
				Sleep(1000);
			}
		}


	
	}
	/*

	// 포트폴리오 확인 함수

	// 주식 정보 검색 함수

	// 주식 매매내역 검색 함수

	// 매매함수
	STOCK_USER stock_usr[5] = { {4, "009150",7},
						   {4, "105560",15},
						   {4, "051900",5},
						   {4, "035420",10},
						   {4, "068270",1}
	};

	trade(&user,stock_usr, stock_lst);

	printf("%s, %d, %d, 로직끝", user.name, user.userNo, user.balance);

	printf("%d", 10);
	*/
	// 로그아웃 함수
 
	return 0;
}