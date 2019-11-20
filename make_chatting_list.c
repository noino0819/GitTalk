#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void check_where_make_room(); //채팅방을 만드는 위치 결정
void make_chatting_room(); //채팅방 만들기
void push_chatting_room(); //채팅방을 GIT에 업로드

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void check_where_make_room(); //채팅방을 만드는 위치 결정
void make_chatting_room(); //채팅방 만들기

int main() {
	check_where_make_room();
	make_chatting_room();
}

void check_where_make_room() {
	printf("채팅방을 업로드할 깃허브 주소를 알려주세요");
	char Git_address[70];
	scanf("%s", Git_address);
	char echo_string[100] = "git remote add GitTalk ";
	strcat(echo_string, Git_address);
	system(echo_string);
}

void make_chatting_room() {
	FILE* name_fp;
	char echo_string[50] = "echo Chatting/";
	char name[30];
	char chatting_partner[30];

	printf("대화를 원하는 상대방의 Git 아이디를 입력해주세요 : ");
	scanf("%s", chatting_partner);
	name_fp = fopen("./name.txt", "rt");
	fscanf(name_fp, "%s", name);

	if (strcmp(chatting_partner, name) < 0) { //partner_name
		strcat(echo_string, ">");
		strcat(echo_string, chatting_partner);
		strcat(echo_string, "_");
		strcat(echo_string, name);
	}
	else if (strcmp(chatting_partner, name) > 0) { //name_partner
		strcat(echo_string, ">");
		strcat(echo_string, name);
		strcat(echo_string, "_");
		strcat(echo_string, chatting_partner);
	}
	else {
		printf("자신과의 대화");
	}
	printf("%s", echo_string);
	system(echo_string);
	//git push를 위한 작업시작
	char add_room[30] = "git add ";
	char* ptr = strtok(echo_string, " ");
	ptr = strtok(NULL, " ");
	strcat(add_room, ptr);
	system(add_room);
	char push_room[30] = "git push GitTalk master"; //지금은 마스터로 사용하지만, 이후에 Git브랜치 이름을 정할 경우 수정
	system(push_room);

}
