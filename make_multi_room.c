#include<stdio.h>
#include<string.h>
#include<stdlib.h>
void check_total_number();
void make_multi_room(int);

int main()
{
		check_total_number();
}

void check_total_number()
{
		int Tnum;
		while(1)
		{
				printf("만드실 채팅방의 나를 포함한 인원수를 입력하시오.\n>>");
				scanf("%d", Tnum);

				if(Tnum == 2)
				{
						make_chatting_room();	//make_chatting_list.c의 함수
						break;
				}
				else if(Tnum >= 3)
				{
						make_multi_room(T_num);
						break;
				}
				else
						printf("다시 입력하세요.\n");
}
void make_multi_room(int num)
{
		check_where_make_room();	//make_chatting_list.c의 함수
		char ** chatting_partner[num-1][70];
		char echo_string[80] = "echo Chatting/";
		char add_room[80] = "git add ";
		char chatting_title[40];
		printf("초대할 친구들의 깃주소를 쓰시오.\n");
		for(int i = 0 ; i < num-1 ; i++)
		{
				printf("%d번째 참여자 >>", num);
				scanf("%s", chatting_partner[i]);	//직접 쓰지는 않았지만 우선 톡방 chatting_partner들의 깃허브 주소들을 받아두었습니다.
		}
		overlap_title_check();	 //overlap.c의 함수, 톡방이름이 겹치는지 확인 후 톡방 생성 

		char* ptr = strtok(echo_string, " ");
		ptr = strtok(NULL, " ");
		strcat(add_room, ptr);
		printf("%s\n", add_room);
		system(add_room);
		char push_room[30] = "git push GitTalk master";
		system(push_room);	//make_chatting_list.c의 make_chatting_room함수와 동일한 방식으로 구현함.
}
