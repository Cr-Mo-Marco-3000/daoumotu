#include "../hdr/generic.h"
#include "../hdr/built_in_library.h"



int main(void) 
{	
	USER user = { -1 };
	int choose;

	// 전체 주식 종목번호 배열 생성
	//char stock_lst[STOCK_ALL_CNT][50];
	//stock_usr_array(stock_lst);

	// 전체 루프
	while (1) {
		if (user.userNo == -1) {	// 로그인이 안 된 상태
			printf("서비스에 연결하려면 1, 종료하려면 2를 입력해주세요.\n");
			choose = getchar();
			while (getchar() != '\n');
			if (choose == '1') {
				auth(&user);
			} else if (choose == '2') {
				printf("이용해 주셔서 감사합니다. 안녕히 가십시오.\n");
				Sleep(500);
				exit(1);
			} else {
				printf("입력이 부정확합니다. 다시 입력 부탁드립니다.\n");
				Sleep(1000);
			}
		} else {
			// 이용하실 서비스를 선택해주세요
		
			printf("1. 주식 목록 조회");
			printf("서비스에 등록된 모든 주식을 조회합니다.");

			printf("0. 로그아웃");
			printf("서비스에서 로그아웃합니다.");
			
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