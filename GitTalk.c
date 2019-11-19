#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define CLEAR_BUFFER while(getchar() != '\n')
void main_menu_print(void);
void main_menu(void);
void chatting_menu_print(void);
void chatting_menu(void);
void signIn(void);
int main(){
	system("clear");
	main_menu();
	return 0;
}
void main_menu_print(void){
	printf("1. 회원가입\n");
	printf("2. 로그인\n");
	printf("3. 프로그램 종료\n");
	printf("\n번호를 선택하세요 : ");
}
void main_menu(void){
	int num;
	while(1){
		main_menu_print();
		scanf("%d", &num);
		CLEAR_BUFFER;
		switch(num){
			case 1:
				signIn();
				break;
			case 2:
				break;
			case 3:
				exit(0);
				break;
			default :
				printf("잘못된 번호입니다. 다시 입력하세요.");
				sleep(2);
				system("clear");
		}
	}
}
void chatting_menu_print(void){
	printf("1. 채팅방 등록 \n");
	printf("2. 채팅방 목록\n");
	printf("3. 로그아웃\n");
	printf("\n 번호를 선택하세요 : ");
}
void chatting_menu(void){
	int num;
	while(1){
		chatting_menu_print();
		scanf("%d", &num);
		CLEAR_BUFFER;
		switch(num){
			case 1:
				break;
			case 2:
				break;
			case 3:
				break;
			default:
				printf("잘못된 번호입니다. 다시 입력하세요.");
				sleep(2);
				system("clear");
		}
	}
}
void signIn(void){
	char echo_string_ID[50] = "echo ";
	char echo_string_PW[50] = "echo ";
	char string[30];
	system("clear");
	printf("---------- GitTalk 회원가입 ----------\n");	
	printf("Github 아이디를 입력하세요 : ");
	scanf("%s", string);
	strcat(echo_string_ID, string);
	strcat(echo_string_ID, ">");
	strcat(echo_string_ID, "name.txt");
	system(echo_string_ID);
	
	printf("Github 비밀번호를 입력하세요 : ");
	scanf("%s", string);
	strcat(echo_string_PW, string);
	strcat(echo_string_PW, ">");
	strcat(echo_string_PW, "password.txt");
	system(echo_string_PW);

	// github의 유효한 ID인지 확인절차 필요.
	
	printf("회원가입 성공!\n");
	printf("이전 메뉴로 돌아갑니다.\n");
	sleep(2);
	system("clear");
}

