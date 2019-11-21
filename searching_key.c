#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void searching_word(char*);
int main()
{
	searching_word(chat_name);
}

void searching_word(char* chat_name)
{
		char str[30];
		char grep_string[50] = "grep -A100000000 ";
		char grep_count[50] = "grep -c";
		printf("검색하실 단어를 입력하세요.\n");
		scanf("%s", str);
		strcat(grep_string, str);
		strcat(grep_string, " -i --color=auto ");  
		strcat(grep_string, chat_name)//chat_name이라는 이름의 채팅방에서 단어 검색
		system(grep_string);
		strcat(grep_count, chat_name);
		printf("검색된 개수 : ");
		system(grep_count);
}

