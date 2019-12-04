#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void overlap_title_check(char);
int main()
{
		overlap_title_check(void);

}

void overlap_title_check(void)
{
		FILE *pFile;
		char echo_string[60] = "echo ";
		char check_string[20];
		char Findfunc[60] = "find . -type f -name ";
		char chatting_title[60];
		while(1)
		{		printf("채팅방 이름을 쳐봐\n");	
				scanf("%s", chatting_title);
				strcat(Findfunc, chatting_title);
				strcat(Findfunc, "|wc -l> title_check.txt");
				system(Findfunc);
				pFile = fopen("title_check.txt", "r");
				fgets(check_string,100,pFile);
				printf("%s", check_string);
				if(strcmp(check_string, 1) == 0)
				printf("이미 존재하는 채팅방 이름입니다.\n");
				else
				{
					strcat(echo_string, chatting_title);	//echo_string은 make_multi_room.c의 함수에 선언 되어 있음.
					printf("%s\n", echo_string);
					system(echo_string);
				}
		}
}
