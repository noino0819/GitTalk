#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <termio.h>
#define CLEAR_BUFFER() {int ch; while((ch = getchar()) != EOF && ch != '\n'){}}

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
int getch(void);
void password_look_star(char[]);
int overlap_title_check(char[]);
void scanf_int(int*, int, int);
void scanf_str(char*);
void scanf_char(char*, char, char);
int getTotalLine(char *name);	// ������ ���� �� �����ϴ� �Լ�

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
	printf("┌─────────────────────────────────────────────────────────────────────────────┐\n");
	printf("│                                                                             │\n");
	printf("│                                   GitTalk                                   │\n");
	printf("│                                                                             │\n");
	printf("├─────────────────────────────────────────────────────────────────────────────┤\n");
	printf("│                                                                             │\n");
	printf("│                                1. 회원가입                                  │\n");
	printf("│                                2. 로그인                                    │\n");
	printf("│                                3. 프로그램 종료                             │\n");
	printf("│                                                                             │\n");
	printf("└─────────────────────────────────────────────────────────────────────────────┘\n");
	printf(" 번호를 선택하세요 : ");
}
void main_menu(void){
	int num, exit_code;
	while(1){
		main_menu_print();
		scanf_int(&num, 1, 3);
		switch(num){
			case 1:
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
			// default :
			// 	printf("잘못된 번호입니다. 다시 입력하세요.");
			// 	sleep(2);
			// 	system("clear");
		}
	}
}
void chatting_menu_print(void){
	printf("┌─────────────────────────────────────────────────────────────────────────────┐\n");
	printf("│                                                                             │\n");
	printf("│                                   GitTalk                                   │\n");
	printf("│                                                                             │\n");
	printf("├─────────────────────────────────────────────────────────────────────────────┤\n");
	printf("│                                                                             │\n");
	printf("│                                1. 채팅방 등록                               │\n");
	printf("│                                2. 채팅방 목록                               │\n");
	printf("│                                3. 로그아웃                                  │\n");
	printf("│                                                                             │\n");
	printf("└─────────────────────────────────────────────────────────────────────────────┘\n");
	printf(" 번호를 선택하세요 : ");
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
		scanf_int(&num, 1, 3);
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
	printf("┌─────────────────────────────────────────────────────────────────────────────┐\n");
	printf("│                                                                             │\n");
	printf("│                               GitTalk 회원가입                              │\n");
	printf("│                                                                             │\n");
	printf("└─────────────────────────────────────────────────────────────────────────────┘\n");	
	printf(" Github 아이디를 입력하세요 : ");
	scanf_str(ID);

	printf(" Github 비밀번호를 입력하세요 : ");
	scanf_str(PW);

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
	printf("┌─────────────────────────────────────────────────────────────────────────────┐\n");
	printf("│                                                                             │\n");
	printf("│                               GitTalk 로그인                                │\n");
	printf("│                                                                             │\n");
	printf("└─────────────────────────────────────────────────────────────────────────────┘\n");
	printf(" Github 아이디를 입력하세요 : ");
	scanf_str(string);
	fscanf(id_fp, "%s", string_from_file);
	if (strcmp(string, string_from_file)){
		printf("\nID가 일치하지 않습니다. 로그인을 다시 진행해주세요.\n");
		sleep(1);
		system("clear");
		return 0;
	}
	printf(" Github 비밀번호를 입력하세요 : ");
	password_look_star(string);
	fscanf(pw_fp, "%s", string_from_file);
	if (strcmp(string, string_from_file)){
		printf("\n비밀번호가 일치하지 않습니다. 로그인을 다시 진행해주세요.\n");
		sleep(1);
		system("clear");
		return 0;
	}

	printf("\n\n로그인이 완료되었습니다.\n");
	printf("GitTalk을 시작합니다.\n");
	sleep(1);
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
	strcat(push_string, "@github.com/noino0819/GitTalk master >> bin.txt 2>> bin.txt");

	//https://github.com/noino0810/GitTalk_Test를 리모트 저장소 GitTalk에 추가했다고 가정
	system("git pull origin master >> bin.txt 2>> bin.txt");
	// system(push_string);
}

void make_chatting_room(void){
	char Git_address[100];
	char echo_remote[100] = "git remote add "; //remote 저장소 이름은 채팅방 이름과 동일.
	FILE* name_fp;
	char echo_string2[50] = "echo  ";
	char name[30];
	char chatting_partner[30];
	char chatting_room_name[50] = "";
	char echo_chattinglist[100] = "echo ";
	int option;
	
	//chatting_list 구조체 선언 및 list_num 체크
	struct chatting_list{
		int num;
		char chatting_room[100];	// 채팅방 이름
		int unread;			// 안읽은 메시지
		int individual_or_group;	// 개인톡/단톡
		char key[20];			// 암호화 키
	}list[100];				// 채팅방 리스트 100개 까지 
	FILE *list_fp;
	
	if((list_fp = fopen("./chatting_list.txt","rt")) == NULL){
		system("touch chatting_list.txt");
		list_fp = fopen("./chatting_list.txt","rt");
	}
	int list_num = 1;
	char slash;
	while(fscanf(list_fp, "%c",&slash) != EOF)
		if(slash == '\\') list_num++;
	fclose(list_fp);
	//chatting_list

	system("clear");
	printf("┌─────────────────────────────────────────────────────────────────────────────┐\n");
	printf("│                                                                             │\n");
	printf("│                                 채팅방 생성                                 │\n");
	printf("│                                                                             │\n");
	printf("└─────────────────────────────────────────────────────────────────────────────┘\n");
	printf(" 채팅방 옵션을 선택하세요. (1. 개인채팅방 2. 단체채팅방) : ");
	scanf_int(&option, 1, 2);
	
	printf("\n채팅방을 업로드 할 github 주소를 입력하세요 : ");
	scanf_str(Git_address);
	
	if(option == 1){
		printf("대화를 원하는 상대방의 Git아이디를 입력하세요 : ");
		scanf_str(chatting_partner);

		name_fp = fopen("./name.txt", "rt");
		fscanf(name_fp, "%s", name);
		
		if(strcmp(chatting_partner, name) < 0){//partner_name
			strcat(echo_string2, ">"); //echo  >
			strcat(echo_string2, "./Chatting/"); //echo  >./Chatting/
			strcat(echo_string2, chatting_partner); //echo  >./Chatting/chatting_partner
			strcat(echo_string2, "_"); //echo >./Chatting/chatting_partner_
			strcat(echo_string2, name); //echo >./Chatting/chatting_partner_name
			
			strcat(chatting_room_name, chatting_partner);
			strcat(chatting_room_name, "_");
			strcat(chatting_room_name, name); //chatting_room_name = chatting_partner_name
		}
		else if(strcmp(chatting_partner, name) > 0){//name_partner
			strcat(echo_string2, ">"); //echo  >
			strcat(echo_string2, "./Chatting/"); //echo  >./Chatting/
			strcat(echo_string2, name); //echo  >./Chatting/name
			strcat(echo_string2, "_"); //echo  >./Chatting/name_
			strcat(echo_string2, chatting_partner); //echo  >./Chatting/name_chatting_partner

			strcat(chatting_room_name, name);
			strcat(chatting_room_name, "_");
			strcat(chatting_room_name, chatting_partner);//chatting_room_name = name_chatting_partner
		}
		else{
			printf("자신과의 대화");
		}
	}
	else if(option == 2){
		printf("생성할 채팅방의 이름을 입력하세요 : ");
		scanf_str(chatting_room_name);
		strcat(echo_string2, ">"); //echo  >
		strcat(echo_string2, "./Chatting/"); //echo  >./Chatting/
		strcat(echo_string2, chatting_room_name); //echo  >./Chatting/chatting_room_name
	}
	
	// chatting_list 파일에 지정된 형식대로 입력
	list_fp = fopen("./chatting_list.txt","at");
	
	list[list_num].num = list_num;
	strcpy(list[list_num].chatting_room, chatting_room_name);
	list[list_num].unread = 0;
	list[list_num].individual_or_group = option;
	strcpy(list[list_num].key,"random");			
	// 암호화키 생성 추가 예정 (랜덤 난수 혹은 스트링)
		
	fprintf(list_fp, "%d %s %d %d %s;\n",
			list[list_num].num,
			list[list_num].chatting_room,
			list[list_num].unread,
			list[list_num].individual_or_group,
			list[list_num].key);
	fclose(list_fp);
	// chatting_list
	
	if(overlap_title_check(chatting_room_name) == 0){
		printf("이전 메뉴로 돌아갑니다.\n");
		sleep(2);
		system("clear");
	}
	else{
		system(echo_string2);
		strcat(echo_remote, chatting_room_name); //git remote add 채팅방이름
		strcat(echo_remote, " "); 
		strcat(echo_remote, Git_address); //git remote add 채팅방이름 주소
		system(echo_remote);
		printf("%s  채팅방이 생성되었습니다.\n", chatting_room_name);
		printf("채팅을 원하시면 채팅방 목록에서 채팅방을 선택해주세요.\n");
		sleep(2);
		system("clear");
	}
}
char* show_list(void){
	char ls_string[100] = "ls -1 --format=single-column ./Chatting"; //한줄에 한개씩 세로로 출력
	char* select;
	char* select2;
	char select_arr[100] = "";
	char rm_string[50] = "rm ";
	char remote_rm_string[50] = "git remote rm ";
	int option;
	char yn;

	select = (char*)malloc(sizeof(char)*100);
	select2 = (char*)malloc(sizeof(char)*100);
	system("clear");
	printf("┌─────────────────────────────────────────────────────────────────────────────┐\n");
	printf("│                                                                             │\n");
	printf("│                                 채팅방 목록                                 │\n");
	printf("│                                                                             │\n");
	printf("└─────────────────────────────────────────────────────────────────────────────┘\n");
	putchar('\n');
	system(ls_string);
	printf("\n옵션을 선택해주세요. (1. 채팅 시작 2. 채팅방 삭제 3. 이전으로 돌아가기) : ");
	scanf_int(&option, 1, 3);
	if(option == 1){ //채팅시작
		printf("\n원하는 채팅방의 이름을 입력하세요 : ");
		scanf_str(select);
		//채팅방 이름이 없을 경우를 검사해서 예외처리 해야됨.
		printf("%s 채팅방이 선택되었습니다.\n", select);
		sleep(2);
		system("clear");
		return select;
	}

	if(option == 2){ //채팅방 삭제
		printf("\n삭제할 채팅방의 이름을 입력하세요 : ");
		scanf_str(select2);
		strcpy(select_arr, select2);
		strcat(rm_string, "./Chatting/");
		strcat(rm_string, select_arr);
		strcat(remote_rm_string, select_arr);
		printf("%s 채팅방을 삭제하시겠습니까?(y/n) : ", select2);
		scanf_char(&yn, 'y', 'n');
		if(yn == 'y'){
			("%s 채팅방을 삭제합니다. \n", select_arr);
			system(rm_string);
			system(remote_rm_string);
			printf("이전메뉴로 돌아갑니다.\n");
			sleep(2);
			system("clear");
			return NULL;
		}
		else if(yn == 'n'){
			printf("채팅방 삭제가 취소되었습니다. 이전메뉴로 돌아갑니다.\n");
			sleep(2);
			system("clear");
			return NULL;
		}
	}
	if(option == 3){ //이전으로 돌아가기
		printf("이전 메뉴로 돌아갑니다.\n");
		sleep(2);
		system("clear");
		return NULL;
	}	
}
void chatting(char *chatting_file){
	FILE *ifp, *ofp;
	pthread_t refresh_thread;
	struct tm* tm_ptr;
	time_t timer;

	char ch;
	char* AM_PM[2] = {"오전", "오후"};
	char name[30], pw[30];
	char push_string[100] = "git push https://";
	char chatting_file_string[100] = "./Chatting/";
	char msg[200];
	char total_msg[300];
	char add_string[100] = "git add ";

	if (chatting_file == NULL){
		return;
	}
	
	strcat(chatting_file_string, chatting_file);
	strcat(add_string, chatting_file_string);
	strcat(add_string, ">> bin.txt 2>> bin.txt");

	if ((ifp = fopen(chatting_file_string, "rt")) == NULL){
			printf("채팅방이 존재하지 않습니다.");
			system("clear");
			return;
	}
	
	ifp = fopen("./name.txt", "rt");
	fscanf(ifp, "%s", name);
	fclose(ifp);
	ifp = fopen("./password.txt", "rt");
	fscanf(ifp, "%s", pw);
	fclose(ifp);

	strcat(push_string, name);
	strcat(push_string, ":");
	strcat(push_string, pw);
	strcat(push_string, "@github.com/noino0819/GitTalk master >> bin.txt 2>> bin.txt");

	pthread_create(&refresh_thread, NULL, refresh_routine, chatting_file_string);
	sleep(1);
	while(1){
		ch = getch();
		if (ch == 10){ //'\n' == 10
			pthread_cancel(refresh_thread);
			printf("보낼 메시지를 입력하세요. (200바이트 이내)\n");
			scanf("%[^\n]", msg);
			CLEAR_BUFFER();
			timer = time(NULL);
			tm_ptr = localtime(&timer);
			if (tm_ptr -> tm_hour > 12){ //오후
				if (tm_ptr -> tm_min < 10){
					sprintf(total_msg, "[%s] [%d/%d %s %d:0%d] ", name, tm_ptr -> tm_mon, tm_ptr -> tm_mday, AM_PM[1], tm_ptr -> tm_hour - 12, tm_ptr -> tm_min);
				} else {	
					sprintf(total_msg, "[%s] [%d/%d %s %d:%d] ", name, tm_ptr -> tm_mon, tm_ptr -> tm_mday, AM_PM[1], tm_ptr -> tm_hour - 12, tm_ptr -> tm_min);
				}
			} else if (tm_ptr -> tm_hour == 12){ //오후 12시
				if (tm_ptr -> tm_min < 10){
					sprintf(total_msg, "[%s] [%d/%d %s %d:0%d] ", name, tm_ptr -> tm_mon, tm_ptr -> tm_mday, AM_PM[1], tm_ptr -> tm_hour, tm_ptr -> tm_min);
				} else {
					sprintf(total_msg, "[%s] [%d/%d %s %d:%d] ", name, tm_ptr -> tm_mon, tm_ptr -> tm_mday, AM_PM[1], tm_ptr -> tm_hour, tm_ptr -> tm_min);
				}
			} else { //오전
				if (tm_ptr -> tm_min < 10){
					sprintf(total_msg, "[%s] [%d/%d %s %d:0%d] ", name, tm_ptr -> tm_mon, tm_ptr -> tm_mday, AM_PM[0], tm_ptr -> tm_hour, tm_ptr -> tm_min);
				} else {
					sprintf(total_msg, "[%s] [%d/%d %s %d:%d] ", name, tm_ptr -> tm_mon, tm_ptr -> tm_mday, AM_PM[0], tm_ptr -> tm_hour, tm_ptr -> tm_min);
				}
			}
			strcat(total_msg, msg);			
			ofp = fopen(chatting_file_string, "at");
			fprintf(ofp, "\n%s", total_msg);
			fclose(ofp);
			system(add_string);
			system("git commit -m 'chatting_test_commit' >> bin.txt 2>> bin.txt"); //나중에 커밋 메시지 수정 예정
			printf("git commit 실행 중...\n");
			system("git pull origin master >> bin.txt 2>> bin.txt");
			printf("git pull 실행 중...\n");
			system(push_string);
			printf("git push 실행 중...\n");
			printf("메시지 전송이 완료되었습니다. 채팅을 재개합니다.\n");
			sleep(1);
			pthread_create(&refresh_thread, NULL, refresh_routine, chatting_file_string);
		} else if (ch == 27){ //ESC == 27
			pthread_cancel(refresh_thread);
			printf("이전 메뉴로 돌아갑니다.\n");
			sleep(1);
			system("clear");
			return;
		}
	}
}
void *refresh_routine(void *chatting_file_string){
	FILE *ifp;
	char ch;
	while(1){
		refresh();
		system("clear");
		ifp = fopen(chatting_file_string, "rt");
		while ((ch = getc(ifp)) != EOF){
			putchar(ch);
		}
		fclose(ifp);
		printf("\n────────────────────────────────────채팅 내용────────────────────────────────────\n");
		printf("** 내용을 입력하려면 [Enter] 키를, 이전으로 돌아가려면 [Esc] 키를 눌러주세요.\n");
		sleep(5);
	}
}

void password_look_star(char password[30]){
	int i = 0;
	
	while(1){
		password[i] = getch();
		if(password[i] == '\n'){
			password[i] = '\0';
			break;
		} else if(password[i] == 127 || password[i] == 8){
			password[i] = '\0';
			if (i != 0){
				i--;
				printf("\b \b");
			}
			continue;
		}
		if(i == 29){
			printf("비밀번호 제한을 초과하셨습니다.");
			break;
		}
		i++;
		printf("*");
	}
}


int overlap_title_check(char chatting_room_name[50]){
	FILE *pFile;
	char ls_string[100] = "ls -1 --format=single-column ./Chatting >title_check.txt";
	char title[30] = "";
	char chatting_room[50] = "";
	strcpy(chatting_room, chatting_room_name);
	system(ls_string);
	pFile = fopen("title_check.txt", "r");
	while(!feof(pFile)){
		fgets(title, 30, pFile);
		strcat(chatting_room, "\n");
		if(strcmp(title, chatting_room) == 0){
			printf("이미 존재하는 이름의 채팅방입니다.\n");
			return 0;
		}
		
	}
	return 1;
}
/* start_range <= int값 <= end_range일 때까지 입력하게 해주는 입력 함수 */
void scanf_int(int* ap, int start_range, int end_range){
	scanf("%d", ap);
	CLEAR_BUFFER();
	while (*ap < start_range || *ap > end_range){
		printf("\n잘못된 값을 입력했습니다. %d부터 %d까지의 값을 입력해주세요.\n", start_range, end_range);
		printf("번호를 선택하세요 : ");
		scanf("%d", ap);
		CLEAR_BUFFER();
	}
}
void scanf_str(char* ap){
	scanf("%s", ap);
	CLEAR_BUFFER();
}
void scanf_char(char* ap, char choice1, char choice2){
	scanf("%c", ap);
	CLEAR_BUFFER();
	while (*ap != choice1 || *ap != choice2){
		printf("\n잘못된 값을 입력했습니다. %c혹은 %c를 입력해주세요.\n", choice1, choice2);
		printf("번호를 선택하세요 : ");
		scanf("%c", ap);
		CLEAR_BUFFER();
	}
}
int getTotalLine(char *name){
  FILE *fp;
  int line=0;
  char c;
  fp=fopen(name,"r");
  while((c=fgetc(fp))!=EOF)
    if(c=='\n') line++;
  fclose(fp);
  return(line);
}

