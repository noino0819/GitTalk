#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void refresh();

int main(){
	refresh();
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
	strcat(push_string, "@github.com/noino0819/GitTalk master");

	//https://github.com/noino0810/GitTalk을 git clone해서 만든 디렉토리라고 가정
	system("git pull origin master");
	system(push_string);

	return;
}

