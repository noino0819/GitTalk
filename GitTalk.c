#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define CLEAR_BUFFER() while(getchar() != '\n')

void main_menu_print(void);
void main_menu(void);
void chatting_menu_print(void);
void chatting_menu(void);
void sign_up(void);
int log_in(void);
void refresh(void);
void make_chatting_room(void);

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
	int num, exit_code;
	while(1){
		main_menu_print();
		scanf("%d", &num);
		CLEAR_BUFFER();
		switch(num){case 1:
				sign_up();
				break;
			case 2:
				exit_code = log_in();
				if (exit_code){
					chatting_menu();
					system("clear");
				}
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
	FILE *name_fp;
	char name[30];
	char push_string[100];		
	if((name_fp = fopen("./name.txt", "rt")) == NULL){
		printf("ID 파일이 존재하지 않습니다. 회원가입을 다시 진행해주세요.\n");
		return;
	}
	fscanf(name_fp,"%s",name);
	fclose(name_fp);
	int num;
	while(1){
		chatting_menu_print();
		scanf("%d", &num);
		CLEAR_BUFFER();
		switch(num){
			// 채팅방 등록 
			case 1:
				make_chatting_room();
				break;
			// 본인이 포함된 채팅방 검색
			case 2:
				strcat(push_string, "find Chatting/ -name \"*");
				strcat(push_string, name);
				strcat(push_string, "*\"");
				system(push_string);
				break;
			// 로그아웃
			case 3:
				return;
				break;
			default:
				printf("잘못된 번호입니다. 다시 입력하세요.");
				sleep(2);
				system("clear");
		}
	}
}
void sign_up(void){
	char echo_string_ID[50] = "echo ";
	char echo_string_PW[50] = "echo ";
	char string[30];
	system("clear");
	printf("---------- GitTalk 회원가입 ----------\n");	
	printf("Github 아이디를 입력하세요 : ");
	scanf("%s", string);
	CLEAR_BUFFER();
	strcat(echo_string_ID, string);
	strcat(echo_string_ID, ">");
	strcat(echo_string_ID, "name.txt");
	system(echo_string_ID);
	
	printf("Github 비밀번호를 입력하세요 : ");
	scanf("%s", string);
	CLEAR_BUFFER();
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
		
int log_in(void){
	FILE *id_fp, *pw_fp;
	char string[30];
	char string_from_file[30];

	/* 회원가입을 다시 진행해야할 경우 오류 코드 -1을 return하고 함수 종료 */
	if ((id_fp = fopen("./name.txt", "rt")) == NULL){
		printf("ID 파일이 존재하지 않습니다. 회원가입을 다시 진행해주세요.\n");
		return -1;
	}

	if ((pw_fp = fopen("./password.txt", "rt")) == NULL){
		printf("비밀번호 파일이 존재하지 않습니다. 회원가입을 다시 진행해주세요.\n");
		return -1;
	}

	/* 로그인을 다시 진행해야할 경우 오류 코드 0을 return하고 함수 종료 */
	system("clear");
	printf("---------- GitTalk 로그인 ----------\n");
	printf("Github 아이디를 입력하세요 : ");
	scanf("%s", string);
	CLEAR_BUFFER();
	fscanf(id_fp, "%s", string_from_file);
	if (strcmp(string, string_from_file)){
		printf("ID가 일치하지 않습니다. 로그인을 다시 진행해주세요.\n");
		return 0;
	}
	printf("Github 비밀번호를 입력하세요 : ");
	scanf("%s", string);
	CLEAR_BUFFER();
	fscanf(pw_fp, "%s", string_from_file);
	if (strcmp(string, string_from_file)){
		printf("비밀번호가 일치하지 않습니다. 로그인을 다시 진행해주세요.\n");
		return 0;
	}

	printf("로그인이 완료되었습니다.\n");
	printf("GitTalk을 시작합니다.\n");
	sleep(2);
	system("clear");

	/* 성공적으로 로그인하였을 경우 1을 return하고 함수 종료 */
	return 1;
}
void refresh(){
	FILE *name_fp, *pw_fp;
	char name[30];
	char pw[30];
	char push_string[100] = "git push https://";

	name_fp = fopen("./name.txt", "rt");
	pw_fp = fopen("./password.txt", "rt");

	//name.txt 파일이나 password.txt 파일이 없을 때
	if (name_fp == NULL || pw_fp == NULL){
		printf("회원가입이 제대로 진행되지 않았습니다.\n");
		return;
	}
	fscanf(name_fp, "%s", name);
	fscanf(pw_fp, "%s", pw);
	
	fclose(name_fp);
	fclose(pw_fp);

	strcat(push_string, name);
	strcat(push_string, ":");
	strcat(push_string, pw);
	strcat(push_string, "@github.com/noino0819/GitTalk_Test master");

	//https://github.com/noino0810/GitTalk_Test를 리모트 저장소 GitTalk에 추가했다고 가정
	system("git pull GitTalk master");
	system(push_string);
}

void make_chatting_room(void){
	char Git_address[100];
	char echo_string1[100] = "git remote add GitTalk "; //채팅방별로 remote 저장소 이름 다르게 수정 필요함.
	FILE* name_fp;
	char echo_string2[50] = "echo Chatting/";
	char name[30];
	char chatting_partner[30];
	system("clear");
	printf("---------- 채팅방 생성 ----------\n");
	printf("채팅방을 업로드 할 github 주소를 입력하세요 : ");
	scanf("%s", Git_address);
	strcat(echo_string1, Git_address);
	system(echo_string1);

	printf("대화를 원하는 상대방의 Git아이디를 입력하세요 : ");
	scanf("%s", chatting_partner);

	name_fp = fopen("./name.txt", "rt");
	fscanf(name_fp, "%s", name);

	if(strcmp(chatting_partner, name) < 0){//partner_name
		strcat(echo_string2, ">");
		strcat(echo_string2, chatting_partner);
		strcat(echo_string2, "_");
		strcat(echo_string2, name);
	}
	else if(strcmp(chatting_partner, name) > 0){//name_partner
		strcat(echo_string2, ">");
		strcat(echo_string2, name);
		strcat(echo_string2, "_");
		strcat(echo_string2, chatting_partner);
	}
	else{
		printf("자신과의 대화");
	}
	printf("%s", echo_string2);
	system(echo_string2);
}

