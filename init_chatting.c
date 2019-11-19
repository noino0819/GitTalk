#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void init_chatting();

int main(){
	
	return 0;
}

void init_chatting(){
	char remote_add_string[80] = "git remote add ";
	char id[30];
	FILE *id_fp;

	if ((id_fp = fopen("./name.txt", "rt")) == NULL){
		printf("ID 파일이 존재하지 않습니다. 회원가입을 다시 해주세요.\n");
	}

	fscanf(id_fp, "%s", id);
	strcat(remote_add_string, id);
	strcat(remote_add_string, " https://github.com/noino0819/GitTalk_Test");
	//추후에 채팅 시작이 아닌 채팅방 만들 때 리모트 저장소를 출력하도록
	system(remote_add_string);
	system("echo > chatting");

	fclose(id_fp);
}
