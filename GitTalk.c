#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <termio.h>
#define CLEAR_BUFFER() while(getchar() != '\n')

int getch(void);
void main_menu_print(void);
void main_menu(void);
void chatting_menu_print(void);
void chatting_menu(void);
void sign_up(void);
int log_in(void);
void refresh(void);
void make_chatting_room(void);
void chatting(char *);
void *refresh_routine(void *);
char* show_list(void);

int main(){
	system("clear");
	main_menu();
	return 0;
}

int getch(void){
    int ch;
    struct termios buf, save;
    tcgetattr(0,&save);
    buf = save;
    buf.c_lflag &= ~(ICANON|ECHO);
    buf.c_cc[VMIN] = 1;
    buf.c_cc[VTIME] = 0;
    tcsetattr(0, TCSAFLUSH, &buf);
    ch = getchar();
    tcsetattr(0, TCSAFLUSH, &save);
    return ch;
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
	char push_string[100] = "";		
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
				chatting(show_list());
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
	char ID[30];
	char PW[30];
	char string_push[100] = "git push https://";
	char check_string[100] = "";
	char check_compare[100] = "remote: Invalid username or password.\n";
	FILE *pFile;
	system("clear");
	printf("---------- GitTalk 회원가입 ----------\n");	
	printf("Github 아이디를 입력하세요 : ");
	scanf("%s", ID);
	CLEAR_BUFFER();

	printf("Github 비밀번호를 입력하세요 : ");
	scanf("%s", PW);
	CLEAR_BUFFER();

	strcat(string_push, ID); //git push https://ID
	strcat(string_push, ":"); //git push https://ID:
	strcat(string_push, PW); //git push https://name:PW
	strcat(string_push, "@github.com/noino0819/GitTalk_Test master 2> check.txt");
	system(string_push);

	pFile = fopen("check.txt", "r");
	fgets(check_string, 100, pFile);
	if(strcmp(check_string, check_compare) == 0){ //유효한 ID가 아닐 경우	
		printf("유효한 ID와 비밀번호가 아닙니다.\n");
		printf("이전메뉴로 돌아갑니다.\n");
		sleep(2);
		system("clear");
	}
	else{
	strcat(echo_string_ID, ID); //echo ID 
	strcat(echo_string_ID, ">"); //echo ID>
	strcat(echo_string_ID, "name.txt"); //echo ID>name.txt
	system(echo_string_ID);
	strcat(echo_string_PW, PW); //echo PW
	strcat(echo_string_PW, ">"); //echo PW>
	strcat(echo_string_PW, "password.txt"); //echo PW>password.txt
	system(echo_string_PW);

	printf("회원가입 성공!\n");
	printf("이전 메뉴로 돌아갑니다.\n");
	sleep(2);
	system("clear");
	}
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
void refresh(void){
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
	strcat(push_string, "@github.com/noino0819/GitTalk master 2> bin.txt");

	//https://github.com/noino0810/GitTalk_Test를 리모트 저장소 GitTalk에 추가했다고 가정
	system("git pull origin master 2> bin.txt");
	// system(push_string);
}

void make_chatting_room(void){
	char Git_address[100];
	char echo_remote[100] = "git remote add "; //remote 저장소 이름은 채팅방 이름과 동일.
	FILE* name_fp;
	char echo_string2[50] = "echo Chatting/";
	char name[30];
	char chatting_partner[30];
	char chatting_room_name[50] = "";
	char echo_chattinglist[100] = "echo ";
	system("clear");
	printf("---------- 채팅방 생성 ----------\n");
	printf("채팅방을 업로드 할 github 주소를 입력하세요 : ");
	scanf("%s", Git_address);

	printf("대화를 원하는 상대방의 Git아이디를 입력하세요 : ");
	scanf("%s", chatting_partner);

	name_fp = fopen("./name.txt", "rt");
	fscanf(name_fp, "%s", name);

	if(strcmp(chatting_partner, name) < 0){//partner_name
		strcat(echo_string2, ">");
		strcat(echo_string2, chatting_partner);
		strcat(echo_string2, "_");
		strcat(echo_string2, name);

		strcat(chatting_room_name, chatting_partner);
		strcat(chatting_room_name, "_");
		strcat(chatting_room_name, name);
	}
	else if(strcmp(chatting_partner, name) > 0){//name_partner
		strcat(echo_string2, ">");
		strcat(echo_string2, name);
		strcat(echo_string2, "_");
		strcat(echo_string2, chatting_partner);

		strcat(chatting_room_name, name);
		strcat(chatting_room_name, "_");
		strcat(chatting_room_name, chatting_partner);
	}
	else{
		printf("자신과의 대화");
	}
	//미리 검사해서 동일한 이름의 채팅방을 만들지 못하게 막아야됨.
	system(echo_string2);
	strcat(echo_remote, chatting_room_name);
	strcat(echo_remote, " ");
	strcat(echo_remote, Git_address);
	system(echo_remote);

	strcat(echo_chattinglist, chatting_room_name);
	strcat(echo_chattinglist, ">>");
	strcat(echo_chattinglist, "chattinglist");
	system(echo_chattinglist);
	printf("%s  채팅방이 생성되었습니다.\n", chatting_room_name);
	printf("채팅을 원하시면 채팅방 목록에서 채팅방을 선택해주세요.\n");
	sleep(30);
	system("clear");
}
char* show_list(void){
	char cat[100] = "cat chattinglist";
	char* select;
	select = (char*)malloc(sizeof(char)*100);
	system("clear");
	printf("---------- 채팅방 목록 ----------\n");
	sleep(1);
	system(cat);
	printf("\n원하는 채팅방의 이름을 입력하세요 : ");
	scanf("%s", select);

	//채팅방 이름이 없을 경우를 검사해서 예외처리 해야됨.
	
	printf("%s 채팅방이 선택되었습니다.\n", select);
	sleep(2);
	system("clear");
	return select;
}
void chatting(char *chatting_file){
	FILE *ifp, *ofp;
	pthread_t refresh_thread;
	char ch;
	char *chatting_content;
	char name[30], pw[30];
	char push_string[100] = "git push https://";
	char chatting_file_string[100] = "./Chatting/";
	char msg[200];

	strcat(chatting_file_string, chatting_file);

	ifp = fopen("./name.txt", "rt");
	fscanf(ifp, "%s", name);
	fclose(ifp);
	ifp = fopen("./password.txt", "rt");
	fscanf(ifp, "%s", pw);
	fclose(ifp);

	strcat(push_string, name);
	strcat(push_string, ":");
	strcat(push_string, pw);
	strcat(push_string, "@github.com/noino0819/GitTalk master 2> bin.txt");

	pthread_create(&refresh_thread, NULL, refresh_routine, chatting_file_string);
	sleep(1);
	while(1){
		CLEAR_BUFFER();
		ch = getch();
		if (ch == 10){ //'\n' == 10, '\r' == 13
			//Enter를 통해 채팅 입력
			printf("보낼 메시지를 입력하세요. (200바이트 이내)\n");
			//메시지 받고 pull
			//메시지를 파일에 저장
			//push 진행 (refresh)
		} else if (ch == 27){ //ESC == 27
			//채팅 끝
			pthread_cancel(refresh_thread);
			return;
		}
	}
}
void *refresh_routine(void *chatting_file_string){
	FILE *ifp;
	char ch;
	while(1){
		system("clear");
		refresh();
		if ((ifp = fopen((char *)chatting_file_string, "rt")) == NULL){
			printf("채팅방이 존재하지 않습니다.");
			return NULL;
		}
		while ((ch = getc(ifp)) != EOF){
			putchar(ch);
		}
		fclose(ifp);
		sleep(5);
	}
}
