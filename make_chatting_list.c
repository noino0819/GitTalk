#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void make_chatting_room();

int main() {
	make_chatting_room();
}

void make_chatting_room() {
	FILE *name_fp;
	char echo_string[50] = "echo Chatting/"
	char name[30];
	char chatting_partner[30];

	printf("대화를 원하는 상대방의 Git 아이디를 입력해주세요 : ");
	scanf("%s",chatting_partner);
	
	name_fp = fopen("./name.txt","rt");
	fscanf(name_fp, "%s", name);

	if (strcmp(chatting_partner, name) < 0) { //partner_name
		strcat(echo_string, ">");
		strcat(echo_string, chatting_partner);
		strcat(echo_string, "_");
		strcat(echo_string, name);
	}
	else if(strcmp(chatting_partner, name) > 0) { //name_partner
		strcat(echo_string, ">");
		strcat(echo_string, name);
		strcat(echo_string, "_");
		strcat(echo_string, chatting_partner);
	}else{
		printf("자신과의 대화");
	}
	printf("%s", echo_string);
	system(echo_string);
}
