/*
* generic_function.c
* ------------------
* 프로젝트 여러 파일에서 사용할 공용 함수를 구현해놓은 파일입니다.
*/
#include "../hdr/generic.h"
#include "../hdr/built_in_library.h"



/*
* Function: checkStringLength
* ---------------------------
* 문자열의 길이를 확인하는 함수입니다.
* 
* msg: 출력할 메시지(줄바꿈은 자동)
* string: 최종적으로 문자열을 입력받을 문자배열의 시작 포인터
* minSize: 문자 배열의 최소 크기(예를 들어, 아이디는 얘 보다는 길어야 함)
* size: 문자 배열의 한도 사이즈(문자열의 최대 사이즈 아님!)
*/

void checkStringLength(char *msg, char *string, int minSize, int size) {
	char tmp[300];

	int flag = 0;
	do {
		if (flag) {
			puts("입력 형식이 맞지 않습니다\n");
			puts("다시 입력 부탁드립니다\n");
		}
		else {
			puts(msg);
			flag = 1;
		}
		gets(tmp);
	} while (strlen(tmp) < minSize || strlen(tmp) >= size);

	strcpy(string, tmp);
}

void num_check(char *msg, int max, int min, int *f_addr)
{
	int tmp;

	do {
		printf("%s ? ", msg);
		scanf("%d%*c", &tmp);
	} while (tmp<min || tmp>max);

	*f_addr = tmp;
}