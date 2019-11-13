#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void make_chatting_room();
//void delete_file();

int main() {
	make_chatting_room();
	//delete_file();
}

void make_chatting_room() {

	int check;
	char echo_string[50] = "echo ";
	char name[30] = "name"; 
	char chatting_partner[30];
	printf("대화를 원하는 상대방의 Git 아이디를 입력해주세요 : ");
	scanf("%s",chatting_partner);

	check = strcmp(chatting_partner, name);
	if (check == 1) {
		strcat(echo_string, ">");
		strcat(echo_string, chatting_partner);
		strcat(echo_string, "_");
		strcat(echo_string, name);
	}
	else{
		strcat(echo_string, ">");
		strcat(echo_string, name);
		strcat(echo_string, "_");
		strcat(echo_string, chatting_partner);
	}
	system(echo_string);
}
