#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void searching_word();
int main()
{
	searching_word();
}

void searching_word()
{
		char str[30];
		char grep_string[80] = "grep -A100000000 ";
		
		printf("검색하실 단어를 입력하세요.\n");
		scanf("%s", str);
		strcat(grep_string, str);
		strcat(grep_string, " -i --color=auto test");  //user1_user2라는 채팅방에서 단어 검색
		system(grep_string);
}

