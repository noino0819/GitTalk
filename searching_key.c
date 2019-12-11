#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void searching_word(char*);
int main()
{
	searching_word(chat_name);
}

void searching_word(char* chat_name)  //chat_name이라는 채팅방 파일
{
		char str[30];
		char grep_string[50] = "grep -A100000000 ";
		char grep_count[50] = "grep -c";
		printf("검색하실 단어를 입력하세요.\n");
		scanf("%s", str);	//검색할 단어를 str에 넣음
		strcat(grep_string, str);	
		strcat(grep_string, " -i --color=auto ");  
		strcat(grep_string, chat_name)	
		system(grep_string);	//chat_name이라는 이름의 채팅방에서 str 이라는 단어를 검색 후 그 단어가 포함된 단어는 highlight 후 채팅방 내용 출력함.
		strcat(grep_count, chat_name);
		printf("검색된 개수 : ");
		system(grep_count);	//검색된 총 단어의 수 출력
}

