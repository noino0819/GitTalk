#include <stdio.h>
#include <stdlib.h>
#define CLEAR_BUFFER while(getchar() != '\n')
void main_menu_print(void){
	printf("1. 회원 가입\n");
	printf("2. 로그인\n");
	printf("3. 프로그램 종료\n");
	printf("\n번호를 선택하세요 : ");
}
void main_menu(void){ //입력인자 void는 나중에 파일 입출력 포인터로 변경.
	int num;
	while(1){
		main_menu_print();
		scanf("%d", &num);
		CLEAR_BUFFER;
		switch(num){
			case 1: //회원가입
				break;
			case 2: //로그인
				break;
			case 3: //프로그램 종료
				exit(0);
				break;
			default :
				printf("잘못된 번호입니다. 다시 입력하세요");
				sleep(2);
				system("clear");
		}
	}
}
void chatting_menu_print(void){
	printf("1. 채팅방 등록\n");
	printf("2. 채팅방 목록\n");
	printf("3. 로그아웃\n");
	printf("\n번호를 선택하세요 : ");
}
void chatting_menu(void){
	int num;
	while(1){
		chatting_menu_print();
		scanf("%d", &num);
		CLEAR_BUFFER;
		switch(num){
			case 1: //채팅방 등록
				break;
			case 2: //채팅방 목록
				break;
			case 3: //이전으로
				break;
			default:
				printf("잘못된 번호입니다. 다시 입력하세요");
				sleep(2);
				system("clear");
		}
	}
}
int main(){
	system("clear");
	main_menu();
	
	return 0;
}
